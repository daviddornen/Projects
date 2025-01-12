#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "pugixml.hpp"
#include <map>
#include <string>
#include <ctime>

#define PORT 5555
#define MAX_CLIENTS 2
#define MAX_USERS_PER_CLIENT 1

pthread_t client_threads[MAX_CLIENTS]; 
pthread_mutex_t threads_mutex = PTHREAD_MUTEX_INITIALIZER; 
std::map<std::string, int> active_users; 
std::map<int, int> client_user_count;
pthread_mutex_t users_mutex = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t id_mutex = PTHREAD_MUTEX_INITIALIZER;
int id=1;

int receiveCommandFromClient(int client_fd, char *comm, size_t size) {
    bzero(comm, size);
    int received_command_bytes = read(client_fd, comm, size - 1);
    if (received_command_bytes < 0) {
        //printf("[server] Eroare la primirea comenzii de la client\n");
        return -1;
    }
    if (received_command_bytes == 0) return 0;

    return 1;
}

void updateClientsNumber(size_t count){
    printf("\033[s");
    printf("\033[1;1H");
    printf("\r\033[32m[server] Clienti conectati: %ld/%d\n\033[0m\n",count,MAX_CLIENTS);
    printf("\033[u");
    fflush(stdout);
}

bool verifUser(const char* _user) {
    pugi::xml_document doc;
    pugi::xml_parse_result usersFile = doc.load_file("utilizatori.xml");

    if (!usersFile) {
        printf("[server] Eroare la deschiderea fisierului de utilizatori\n");
        return false;
    }

    pugi::xml_node users = doc.child("utilizatori");

    for (pugi::xml_node user = users.child("utilizator"); user; user = user.next_sibling("utilizator")) {
        const char* stored_username = user.child("name").text().as_string();

        if (strcmp(stored_username, _user) == 0) {
            return true;  
        }
    }
    return false;
} 

bool verifParola(const char* username, const char* password) {
    pugi::xml_document doc;
    pugi::xml_parse_result usersFile = doc.load_file("utilizatori.xml");

    if (!usersFile) {
        printf("[server] Eroare la deschiderea fisierului de utilizatori\n");
        return false;
    }

    pugi::xml_node users = doc.child("utilizatori");

    for (pugi::xml_node user = users.child("utilizator"); user; user = user.next_sibling("utilizator")) {
        const char* stored_username = user.child("name").text().as_string();
        const char* stored_password = user.child("parola").text().as_string();

        if (strcmp(stored_username, username) == 0 && strcmp(stored_password, password) == 0) {
            return true;
        }
    }
    return false;
}

void conectare(int client_fd, const char* username) {
    pthread_mutex_lock(&users_mutex);

    if (client_user_count[client_fd] >= MAX_USERS_PER_CLIENT) {
        write(client_fd, "[server] Nu poti conecta mai multi utilizatori pe acelasi client.\n", strlen("[server] Nu poti conecta mai multi utilizatori pe acelasi client.\n"));
        pthread_mutex_unlock(&users_mutex);
        return;
    }

    if (active_users.find(username) != active_users.end()) {
        write(client_fd, "[server] Utilizatorul este deja conectat de pe alt client.\n", strlen("[server] Utilizatorul este deja conectat de pe alt client.\n"));
        pthread_mutex_unlock(&users_mutex);
        return;
    }
    pthread_mutex_unlock(&users_mutex);

    pugi::xml_document doc;
    pugi::xml_parse_result usersFile = doc.load_file("utilizatori.xml");

    if (!usersFile) {
        printf("[server] Eroare la deschiderea fisierului de utilizatori\n");
        write(client_fd, "[server] Eroare interna.\n", strlen("[server] Eroare interna.\n"));
        return;
    }

    pugi::xml_node users = doc.child("utilizatori");

    for (pugi::xml_node user = users.child("utilizator"); user; user = user.next_sibling("utilizator")) {
        const char* stored_username = user.child("name").text().as_string();
        const char* connection_status = user.child("conectat").text().as_string();

        if (strcmp(stored_username, username) == 0) {
            if (strcmp(connection_status, "1") == 0) {
                write(client_fd, "[server] Utilizatorul este deja conectat.\n", strlen("[server] Utilizatorul este deja conectat.\n"));
                //printf("[server] Utilizatorul %s este deja conectat.\n", username);
                return;
            }

            char password[50];
            bzero(password, sizeof(password));

            write(client_fd, "[server] Introduceti parola: ", strlen("[server] Introduceti parola: "));

            int received_password_bytes = recv(client_fd, password, sizeof(password) - 1, 0);
            if (received_password_bytes <= 0) {
                printf("[server] Eroare la primirea parolei de la client\n");
                return;
            }

            password[received_password_bytes] = '\0';

            if (verifParola(username, password)) {
                user.child("conectat").text() = "1";
                pthread_mutex_lock(&users_mutex);
                active_users[username] = client_fd;
                client_user_count[client_fd]++;
                pthread_mutex_unlock(&users_mutex);
                doc.save_file("utilizatori.xml");

                write(client_fd, "[server] Autentificare reusita!\n", strlen("[server] Autentificare reusita!\n"));
                //printf("[server] Utilizatorul %s s-a conectat cu succes.\n", username);
                return;
            } else {
                write(client_fd, "[server] Parola gresita!\n", strlen("[server] Parola gresita!\n"));
                //printf("[server] Parola incorecta pentru utilizatorul %s.\n", username);
                return;
            }
        }
    }

    write(client_fd, "[server] Utilizatorul nu a fost gasit in baza de date.\n", strlen("[server] Utilizatorul nu a fost gasit in baza de date.\n"));
}

void logout(int client_fd) {
    pthread_mutex_lock(&users_mutex);

    bool gasit=false;

    for (auto i = active_users.begin(); i != active_users.end(); ++i) {
        if (i->second == client_fd) {
            const std::string& username = i->first;

            pugi::xml_document doc;
            pugi::xml_parse_result usersFile = doc.load_file("utilizatori.xml");

            if (!usersFile) {
                //printf("[server] Eroare la deschiderea fisierului de utilizatori\n");
                write(client_fd, "[server] Eroare interna.\n", strlen("[server] Eroare interna.\n"));
                pthread_mutex_unlock(&users_mutex);
                return;
            }

            pugi::xml_node users = doc.child("utilizatori");

            for (pugi::xml_node user = users.child("utilizator"); user; user = user.next_sibling("utilizator")) {
                const char* stored_username = user.child("name").text().as_string();
                if (username == stored_username) {
                    user.child("conectat").text() = "0";
                    doc.save_file("utilizatori.xml");
                    break;
                }
            }

            active_users.erase(i);
            client_user_count[client_fd]--;
            write(client_fd, "[server] Deconectare reusita!\n", strlen("[server] Deconectare reusita!\n"));
            //printf("[server] Utilizatorul %s a fost deconectat.\n", username.c_str());
            gasit = true;
            break;
        }
    }

    if (!gasit) {
        write(client_fd, "[server] Nu sunt utilizatori conectati pe acest client.\n", strlen("[server] Nu sunt utilizatori conectati pe acest client.\n"));
    }

    pthread_mutex_unlock(&users_mutex);
}


bool isClientConnected(int client_fd) {
    pthread_mutex_lock(&users_mutex);
    bool connected = false;

    for (const auto& user : active_users) {
        if (user.second == client_fd) {
            connected = true;
            break;
        }
    }

    pthread_mutex_unlock(&users_mutex);
    return connected;
}

void informatiiTren(int client_fd, const char* tren_id) {
    pugi::xml_document doc;
    pugi::xml_parse_result trenuriFile = doc.load_file("trenuri.xml");

    if (!trenuriFile) {
        write(client_fd, "[server] Eroare la deschiderea fisierului de trenuri.\n", strlen("[server] Eroare la deschiderea fisierului de trenuri.\n"));
        return;
    }

    pugi::xml_node tren = doc.find_child_by_attribute("tren", "id", tren_id);

    if (!tren) {
        write(client_fd, "[server] Trenul nu a fost gasit.\n", strlen("[server] Trenul nu a fost gasit.\n"));
        return;
    }

    pugi::xml_node first_station = tren.child("statie");
    const char* plecare_statie = first_station.attribute("numeStatie").as_string();
    const char* plecare_ora = first_station.attribute("plecare").as_string();

    pugi::xml_node last_station = first_station;
    for (pugi::xml_node statie = first_station; statie; statie = statie.next_sibling("statie")) {
        last_station = statie;
    }
    const char* sosire_statie = last_station.attribute("numeStatie").as_string();
    const char* sosire_ora = last_station.attribute("sosire").as_string();

    int durata = tren.attribute("durata").as_int();
    int ore = durata / 60;
    int minute = durata % 60;
    std::string durataStr = std::to_string(ore) + "h" + std::to_string(minute) + "m";

    int numar_statii = 0;
    for (pugi::xml_node statie = first_station; statie; statie = statie.next_sibling("statie")) {
        numar_statii++;
    }
    std::string nrStatiiStr = std::to_string(numar_statii);

    char response[512];
    bzero(response, sizeof(response));

    strcat(response, "[server] Plecare: ");
    strcat(response, plecare_statie);
    strcat(response, " ");
    strcat(response, plecare_ora);
    strcat(response, "\n         Sosire: ");
    strcat(response, sosire_statie);
    strcat(response, " ");
    strcat(response, sosire_ora);
    strcat(response, "\n         Durata: ");
    strcat(response, durataStr.c_str());
    strcat(response, "\n         Numar de statii: ");
    strcat(response, nrStatiiStr.c_str());
    strcat(response, "\n");

    write(client_fd, response, strlen(response));
}

void trenuriDisponibile(int client_fd){
    pugi::xml_document doc;
    pugi::xml_parse_result trenuriFile = doc.load_file("trenuri.xml");

    if (!trenuriFile) {
        write(client_fd, "[server] Eroare la deschiderea fisierului de trenuri.\n", strlen("[server] Eroare la deschiderea fisierului de trenuri.\n"));
        return;
    }

    char msgTrenuri[1024];
    bzero(msgTrenuri, sizeof(msgTrenuri));

    strcat(msgTrenuri,"[server] ");

    for (pugi::xml_node tren = doc.child("tren"); tren; tren = tren.next_sibling("tren")) {
        const char* tren_id = tren.attribute("id").as_string();

        strcat(msgTrenuri, tren_id);
        strcat(msgTrenuri, "\n         ");
    }

    write(client_fd, msgTrenuri, strlen(msgTrenuri));
}

bool is_next_hour(const char* current_time, const char* next_hour_time, const char* sosire_time) {
    int current_hour, current_minute, next_hour, next_minute, sosire_hour, sosire_minute;
    sscanf(current_time, "%d:%d", &current_hour, &current_minute);
    sscanf(next_hour_time, "%d:%d", &next_hour, &next_minute);
    sscanf(sosire_time, "%d:%d", &sosire_hour, &sosire_minute);

    int current_time_in_minutes = current_hour * 60 + current_minute;
    int next_hour_in_minutes = next_hour * 60 + next_minute;
    int sosire_time_in_minutes = sosire_hour * 60 + sosire_minute;

    return sosire_time_in_minutes >= current_time_in_minutes && sosire_time_in_minutes <= next_hour_in_minutes;
}

void sosiri(int client_fd) {
    pugi::xml_document doc;
    pugi::xml_parse_result trenuriFile = doc.load_file("trenuri.xml");

    if (!trenuriFile) {
        write(client_fd, "[server] Eroare la deschiderea fisierului de trenuri.\n", strlen("[server] Eroare la deschiderea fisierului de trenuri.\n"));
        return;
    }

    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);

    char ora_curenta[6];
    strftime(ora_curenta, sizeof(ora_curenta), "%H:%M", tm_info);

    tm_info->tm_hour += 1;
    mktime(tm_info);
    
    char ora_urmatoare[6]; 
    strftime(ora_urmatoare, sizeof(ora_urmatoare), "%H:%M", tm_info);

    char msgSosiri[1024];
    bzero(msgSosiri, sizeof(msgSosiri));
    strcat(msgSosiri, "[server] Trenurile care vor sosi in urmatoarea ora:\n");

    bool trenuriGasite = false;

    for (pugi::xml_node tren = doc.child("tren"); tren; tren = tren.next_sibling("tren")) {
        for (pugi::xml_node statie = tren.child("statie"); statie; statie = statie.next_sibling("statie")) {
            const char* sosire_ora = statie.attribute("sosire").as_string();
            if (is_next_hour(ora_curenta, ora_urmatoare, sosire_ora)) {
                const char* tren_id = tren.attribute("id").as_string();
                const char* sosire_statie = statie.attribute("numeStatie").as_string();

                char response[256];
                snprintf(response, sizeof(response), "         %s In statia %s la ora %s\n", tren_id, sosire_statie, sosire_ora);
                strcat(msgSosiri, response);

                trenuriGasite = true;
            }
        }
    }

    if (!trenuriGasite) {
        bzero(msgSosiri, sizeof(msgSosiri));
        strcat(msgSosiri, "[server] Nu sunt trenuri care sa soseasca in urmatoarea ora.\n");
    }

    write(client_fd, msgSosiri, strlen(msgSosiri));
}

void plecari(int client_fd) {
    pugi::xml_document doc;
    pugi::xml_parse_result trenuriFile = doc.load_file("trenuri.xml");

    if (!trenuriFile) {
        write(client_fd, "[server] Eroare la deschiderea fisierului de trenuri.\n", strlen("[server] Eroare la deschiderea fisierului de trenuri.\n"));
        return;
    }

    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);

    char ora_curenta[6];
    strftime(ora_curenta, sizeof(ora_curenta), "%H:%M", tm_info);

    tm_info->tm_hour += 1;
    mktime(tm_info);

    char ora_urmatoare[6]; 
    strftime(ora_urmatoare, sizeof(ora_urmatoare), "%H:%M", tm_info);

    char msgPlecari[1024];
    bzero(msgPlecari, sizeof(msgPlecari));
    strcat(msgPlecari, "[server] Trenurile care vor pleca in urmatoarea ora:\n");

    bool trenuriGasite = false;

    for (pugi::xml_node tren = doc.child("tren"); tren; tren = tren.next_sibling("tren")) {
        for (pugi::xml_node statie = tren.child("statie"); statie; statie = statie.next_sibling("statie")) {
            const char* plecare_ora = statie.attribute("plecare").as_string();
            if (is_next_hour(ora_curenta, ora_urmatoare, plecare_ora)) {
                const char* tren_id = tren.attribute("id").as_string();
                const char* plecare_statie = statie.attribute("numeStatie").as_string();

                char response[256];
                snprintf(response, sizeof(response), "         %s In statia %s la ora %s\n", tren_id, plecare_statie, plecare_ora);
                strcat(msgPlecari, response);

                trenuriGasite = true;
            }
        }
    }

    if (!trenuriGasite) {
        bzero(msgPlecari, sizeof(msgPlecari));
        strcat(msgPlecari, "[server] Nu sunt trenuri care sa plece in urmatoarea ora.\n");
    }

    write(client_fd, msgPlecari, strlen(msgPlecari));
}

void intarziere(int client_fd, const char *tren_id) {
    char statie[50];
    int intarziere;

    write(client_fd, "Introdu statia: ", 16);
    read(client_fd, statie, sizeof(statie));
    statie[strcspn(statie, "\n")] = 0; 

    write(client_fd, "Introdu minute de intarziere: ", 30);
    char buffer[10];
    read(client_fd, buffer, sizeof(buffer));
    intarziere = atoi(buffer);

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("intarzieri.xml");

    if (!result) {
        write(client_fd, "Eroare la citirea fisierului XML.\n", 34);
        return;
    }

    pugi::xml_node tren = doc.find_node([&](pugi::xml_node node) {
        return strcmp(node.name(), "tren") == 0 && strcmp(node.attribute("id").value(), tren_id) == 0;
    });

    if (!tren) {
        write(client_fd, "Trenul specificat nu a fost gasit.\n", 35);
        return;
    }

    bool statieGasita = false;
    for (pugi::xml_node statieNode : tren.children("statie")) {
        if (strcmp(statieNode.attribute("numeStatie").value(), statie) == 0) {
            statieGasita = true;
            statieNode.attribute("intarziere").set_value(intarziere);
            doc.save_file("intarzieri.xml", " ", pugi::format_indent);

            char mesaj[256];
            sprintf(mesaj, "A fost adaugata o intarziere de %d min la trenul %s in statia %s\n", intarziere, tren_id, statie);
            write(client_fd, mesaj, strlen(mesaj));
            break;
        }
    }

    if (!statieGasita) {
        write(client_fd, "Statia specificata nu a fost gasita la acest tren.\n", 50);
    }
}

void sterge_intarziere(int client_fd, const char *tren_id_input) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("intarzieri.xml");

    if (!result) {
        write(client_fd, "Eroare la citirea fisierului XML.\n", 34);
        return;
    }

    bool trenGasit = false;
    for (pugi::xml_node tren : doc.children("tren")) {
        if (strcmp(tren.attribute("id").value(), tren_id_input) == 0) {
            trenGasit = true;

            bool modificat = false;
            for (pugi::xml_node statieNode : tren.children("statie")) {
                if (statieNode.attribute("intarziere")) {
                    statieNode.attribute("intarziere").set_value(0);
                    modificat = true;
                }
            }

            if (modificat) {
                doc.save_file("intarzieri.xml", "  ", pugi::format_indent);
                write(client_fd, "Toate intarzierile trenului au fost sterse.\n", 44);
            } else {
                write(client_fd, "Nu s-au gasit intarzieri pentru acest tren.\n", 45);
            }
            break;
        }
    }

    if (!trenGasit) {
        write(client_fd, "Trenul specificat nu a fost gasit.\n", 35);
    }
}

int ora_in_minute(const char* ora) {
    int hh = 0, mm = 0;
    sscanf(ora, "%d:%d", &hh, &mm);
    return hh * 60 + mm;
}

void minute_in_ora(int minute, char* buffer) {
    int hh = minute / 60;
    int mm = minute % 60;
    sprintf(buffer, "%02d:%02d", hh, mm);
}

void estimare_sosire(int client_fd, const char* tren_id) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("intarzieri.xml");

    if (!result) {
        write(client_fd, "Eroare la citirea fisierului XML.\n", 34);
        return;
    }

    pugi::xml_node tren = doc.find_node([&](pugi::xml_node node) {
        return strcmp(node.name(), "tren") == 0 && strcmp(node.attribute("id").value(), tren_id) == 0;
    });

    if (!tren) {
        write(client_fd, "Trenul specificat nu a fost gasit.\n", 35);
        return;
    }

    char mesaj[2048]; 
    strcpy(mesaj, "\n");

    int minute_estimate = 0; 
    int intarziereTotala = 0;

    for (pugi::xml_node statie = tren.child("statie"); statie; statie = statie.next_sibling("statie")) {
        const char* numeStatie = statie.attribute("numeStatie").value();
        const char* oraSosire = statie.attribute("sosire").value();
        const char* oraPlecare = statie.attribute("plecare").value();
        int intarziere = atoi(statie.attribute("intarziere").value());

        if (*oraSosire) {
            minute_estimate = ora_in_minute(oraSosire) + intarziere;
            intarziereTotala += intarziere;
        } else if (*oraPlecare) {
            minute_estimate = ora_in_minute(oraPlecare) + intarziere;
            intarziereTotala += intarziere;
        }

        char oraEstimata[6];
        minute_in_ora(minute_estimate, oraEstimata);

        char fiecareStatie[256];
        sprintf(fiecareStatie, "statia: %s | intarziere: %d | estimare: %s\n", numeStatie, intarziere, oraEstimata);

        strcat(mesaj, fiecareStatie);
    }

    char mesajIntarziereTotala[124];
    if(intarziereTotala==0)
        sprintf(mesajIntarziereTotala,"\nTrenul nu are intarzieri\n");
    else
        sprintf(mesajIntarziereTotala,"\nTrenul are o intarziere totala de %d minute\n",intarziereTotala);
        
    strcat(mesaj,mesajIntarziereTotala);
    write(client_fd, mesaj, strlen(mesaj));
}

void chose_command(int client_fd, char *comm) {
    if (strncmp(comm, "login ", 6) == 0) {
        char username[20];
        sscanf(comm + 6, "%s", username);
        if (verifUser(username)) conectare(client_fd, username);
        else write(client_fd, "[server] Utilizatorul nu este in baza de date\n", strlen("[server] Utilizatorul nu este in baza de date\n"));
    } 
    else if (strncmp(comm, "logout", 6) == 0) {
        logout(client_fd);
    }
    else if (strncmp(comm, "sosiri", 6) == 0) {
        if (isClientConnected(client_fd))
            sosiri(client_fd);
        else
            write(client_fd, "[server] Trebuie sa fii conectat pentru aceasta comanda\n", strlen("[server] Trebuie sa fii conectat pentru aceasta comanda\n"));
    }
    else if (strncmp(comm, "plecari", 7) == 0) {
        if (isClientConnected(client_fd))
            plecari(client_fd);
        else
            write(client_fd, "[server] Trebuie sa fii conectat pentru aceasta comanda\n", strlen("[server] Trebuie sa fii conectat pentru aceasta comanda\n"));
    }
    else if (strncmp(comm, "info", 4) == 0) {
        char tren_id[20];
        sscanf(comm + 5, "%s", tren_id);
        if (isClientConnected(client_fd))
            informatiiTren(client_fd, tren_id);
        else
            write(client_fd, "[server] Trebuie sa fii conectat pentru aceasta comanda\n", strlen("[server] Trebuie sa fii conectat pentru aceasta comanda\n"));
    }
    else if(strcmp(comm,"trenuri")==0){
        if(isClientConnected(client_fd))
            trenuriDisponibile(client_fd);
        else 
            write(client_fd, "[server] Trebuie sa fii conectat pentru aceasta comanda\n", strlen("[server] Trebuie sa fii conectat pentru aceasta comanda\n"));

    }
    else if (strncmp(comm, "intarziere", 10) == 0){
        char tren_id[64];
        sscanf(comm + 11, "%s", tren_id);
        if(isClientConnected(client_fd))
            intarziere(client_fd,tren_id);
        else 
            write(client_fd, "[server] Trebuie sa fii conectat pentru aceasta comanda\n", strlen("[server] Trebuie sa fii conectat pentru aceasta comanda\n"));
    }
    else if (strncmp(comm, "sterge-intarziere", 17) == 0){
        char tren_id[64];
        sscanf(comm + 18, "%s", tren_id);
        if(isClientConnected(client_fd))
            sterge_intarziere(client_fd,tren_id);
        else 
            write(client_fd, "[server] Trebuie sa fii conectat pentru aceasta comanda\n", strlen("[server] Trebuie sa fii conectat pentru aceasta comanda\n"));
    }
    else if (strncmp(comm, "estimare", 8) == 0){
        char tren_id[64];
        sscanf(comm + 9, "%s", tren_id);
        if(isClientConnected(client_fd))
            estimare_sosire(client_fd,tren_id);
        else 
            write(client_fd, "[server] Trebuie sa fii conectat pentru aceasta comanda\n", strlen("[server] Trebuie sa fii conectat pentru aceasta comanda\n"));
    }
    else if (strcmp(comm, "help") == 0) {
        char help_msg[1024];
        strcpy(help_msg, "\n");
        strcat(help_msg, "login <nume_utilizator>      autentificarea unui utilizator\n");
        strcat(help_msg, "trenuri                      afisarea trenurilor disponibile\n");
        strcat(help_msg, "info <id_tren>               informatii despre un anumit tren\n");
        strcat(help_msg, "sosiri                       trenurile care vor sosi in urmatoarea ora\n");
        strcat(help_msg, "plecari                      trenurile care vor pleca in urmatoarea ora\n");
        strcat(help_msg, "intarziere <id_tren>         adauga intarziere la o anumita statie a unui tren\n");
        strcat(help_msg, "sterge-intarziere <id_tren>  sterge intarzierile unui tren\n");
        strcat(help_msg, "estimare <id_tren>           afiseaza eventualele intarzieri ale unui tren\n");
        strcat(help_msg, "logout                       deconectarea utilizatorului logat curent\n");
        strcat(help_msg, "exit                         inchide conexiunea\n");
        write(client_fd, help_msg, strlen(help_msg));
    } 
    else if (strcmp(comm, "exit") == 0) {
        write(client_fd, "[server] S-a oprit conexiunea cu serverul\n", strlen("[server] S-a oprit conexiunea cu serverul\n"));
        logout(client_fd);
        close(client_fd);

        printf("[server] Activitatea clientului s-a oprit.\n");
        return; 
    }
    else {
        write(client_fd, "[server] Comanda necunoscuta\n", strlen("[server] Comanda necunoscuta\n"));
    }
}

void* client_concurrency(void *arg) {
    int client_fd = *(int*)arg;
    char command[256];

    pthread_mutex_lock(&users_mutex);
    client_user_count[client_fd] = 0;
    pthread_mutex_unlock(&users_mutex);

    pthread_mutex_lock(&id_mutex);
    int client_id = id++;
    pthread_mutex_unlock(&id_mutex);
    
    printf("[server] Client nou conectat (id: %d)\n",client_id);

    while (1) {
        int status = receiveCommandFromClient(client_fd, command, sizeof(command));

        if (status == 0) {
            printf("[server] Activitatea clientului s-a oprit.\n");
            logout(client_fd);
            break; 
        } 
        else if (status > 0) {
            chose_command(client_fd, command);
        }
        else break;
    }

    pthread_mutex_lock(&users_mutex);
    client_user_count.erase(client_fd);
    pthread_mutex_unlock(&users_mutex);

    close(client_fd);
    updateClientsNumber(client_user_count.size());
    return NULL;
}

int main() {

    struct sockaddr_in server, from;
    int sock, client, nr_maxim_descriptori;
    socklen_t len_sockaddr;
    struct timeval tv;

    printf("\033[2J");
    printf("\033[1;1H");
    printf("\033[32m[server] Clienti conectati: 0/%d\n\033[0m\n", MAX_CLIENTS);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("[server] Eroare la crearea socket-ului\n");
        return -1;
    }

    int optval = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    bzero(&server, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    if (bind(sock, (struct sockaddr*)&server, sizeof(struct sockaddr))== -1) {
        printf("[server] Eroare la bind\n");
        return -1;
    }

    if (listen(sock, MAX_CLIENTS)) {
        printf("[server] Eroare la listen\n");
        return -1;
    }

    fd_set active_descriptors;
    FD_ZERO(&active_descriptors);
    FD_SET(sock, &active_descriptors);
    nr_maxim_descriptori = sock;

    printf("Port de conectare: %d\n", PORT);
    fflush(stdout);

    while (1) {
        fd_set read_descriptors = active_descriptors;
        tv.tv_sec = 1;
        tv.tv_usec = 0;

        if (select(nr_maxim_descriptori + 1, &read_descriptors, NULL, NULL, &tv) < 0) {
            printf("[server] Eroare la select\n");
            return -1;
        }

        if (FD_ISSET(sock, &read_descriptors)) {
            len_sockaddr = sizeof(from);
            bzero(&from, sizeof(from));
            client = accept(sock, (struct sockaddr*)&from, &len_sockaddr);

            if (client < 0) {
                printf("[server] Eroare la accept\n");
            } else {
                pthread_mutex_lock(&threads_mutex);
                if (client_user_count.size() < MAX_CLIENTS) {
                    client_user_count[client] = 0;
                    pthread_create(&client_threads[client], NULL, client_concurrency, (void*)&client);
                    updateClientsNumber(client_user_count.size());
                    //printf("[server] Client nou conectat, clienti conectati: %ld/%d\n",client_user_count.size(),MAX_CLIENTS);
                    const char* msg = "[server] Conexiune acceptata\n";
                    write(client,msg,strlen(msg));
                }
                else{
                    const char* msg = "[server] Serverul este plin.\n";
                    pthread_mutex_unlock(&users_mutex);
                    write(client,msg,strlen(msg));
                    //printf("[server] Serverul este plin.\n");
                    close(client);
                }
                pthread_mutex_unlock(&threads_mutex);
            }
        }
    }

    close(sock);
    return 0;
}
