#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <signal.h>

#define BUFF 1024
int sock;

void trimite_comanda_la_server(const char* _comanda){
    if(sock==-1)
        printf("[client] Eroare la socket\n");

    write(sock,_comanda,strlen(_comanda));
}

void delogare_utilizatori_ramasi_logati(int sig){
    printf("\n[client] Clientul a fost inchis fortat.\n");
    printf("[client] Utilizatorul ramas conectat pe acest client a fost deconectat.\n");

    if (sock != -1) {
        trimite_comanda_la_server("logout");
    }

    char raspunsServer[BUFF];
    bzero(raspunsServer,sizeof(raspunsServer));
    if(read(sock,raspunsServer,BUFF)<0){
        printf("[client] Eroare la primirea raspunsului de la server\n");
    }
    printf("%s\n",raspunsServer);

    close(sock);
    exit(0);
}

int main(int argc, char *argv[])
{
    int port;
    struct sockaddr_in server;
    sock = socket(AF_INET,SOCK_STREAM,0);

    if(argc!=3) {
        printf("[client]: Te rog foloseste : %s <adresa_server> <port>\n",argv[0]);
        return -1;
    }
    
    port = atoi(argv[2]);
    signal(SIGINT,delogare_utilizatori_ramasi_logati);

    while(true)
    {
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(argv[1]);
        server.sin_port = htons(port);

        if(connect(sock,(struct sockaddr*) &server,sizeof(struct sockaddr))==-1)
        {
            printf("[client] Nu s-a putut realiza conectarea la server\n");
            close(sock);
            return 0;
        }

        char checkMaxUserMsg[BUFF];
        bzero(checkMaxUserMsg, sizeof(checkMaxUserMsg));
        if (read(sock, checkMaxUserMsg, BUFF) > 0) {
            if(strcmp(checkMaxUserMsg,"[server] Serverul este plin.\n")==0){
                printf("%s\n", checkMaxUserMsg);
                exit(0);
                return 0;
            }
            else if (strstr(checkMaxUserMsg, "[server] Conexiune acceptată.\n") == 0) {
                printf("%s", checkMaxUserMsg);
            } 
        }
        
        printf("\n");
        printf("------------------------------------------------\n");
        printf("                Bine ati venit!\n");              
        printf("Pentru informatii despre comenzi folositi 'help'\n");
        printf("------------------------------------------------\n\n");

        while(true){
            char comanda[32];
            fgets(comanda,sizeof(comanda),stdin);
            comanda[strcspn(comanda,"\n")] = 0;
            trimite_comanda_la_server(comanda);

            char raspunsServer[BUFF];
            bzero(raspunsServer,sizeof(raspunsServer));
            if(read(sock,raspunsServer,BUFF)<0){
                printf("[client] Eroare la primirea raspunsului de la server\n");
            }

            printf("%s\n",raspunsServer);
            if(strncmp(raspunsServer,"[server] S-a oprit conexiunea cu serverul\n",strlen("[server] S-a oprit conexiunea cu serverul\n"))==0) exit(0);
        }
        break;
    }

    close(sock);
    
    return 0;
}

