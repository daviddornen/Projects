#include <iostream>
#include <cstring>
#include <graphics.h>
#include <cmath>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>

void draw_Tabla(int x);
void draw_Tabla2(int x);
void draw_Piesa();
void Menu();
void Play_4x4();
void Play_4x4_Load();
void Play_5x5();
void Play_5x5_Load();
void Play_6x6();
void Play_6x6_Load();
void Play_7x7();
void Play_7x7_Load();
void Play_8x8();
void Play_8x8_Load();

void initializareTabla(int x);
void initializareTabla_Load4x4(int x);
void initializareTabla_Load5x5(int x);
void initializareTabla_Load6x6(int x);
void initializareTabla_Load7x7(int x);
void initializareTabla_Load8x8(int x);

void alegePiesa(int x);
bool punerePiesa(int x);
void punerePiesa2(int x);
void punerePiesa_Computer(int x);

void PlayerVsComputer_Easy();
void PlayerVsComputer_Hard();
void PlayerVsComputer_GameMode();

void Play_4x4VsComputer();
void Play_5x5VsComputer();
void Play_6x6VsComputer();
void Play_7x7VsComputer();
void Play_8x8VsComputer();

int Tabla[10][10];
int Tabla4x4[10][10];
int Tabla5x5[10][10];
int Tabla6x6[10][10];
int Tabla7x7[10][10];
int Tabla8x8[10][10];

int n;
int jucator;
int cursorX, cursorY;
int piesaAleasa;
int marimeaAleasa;
bool ok;

using namespace std;

void startMenu()
{
     initwindow(1200,700);

     setcolor(WHITE);
     settextstyle(10, HORIZ_DIR, 5);
     outtextxy(450,50, "COLTUL NEGRU");

     settextstyle(10, HORIZ_DIR, 5);
     outtextxy(410,250, "CHOSE GAME MODE");

     setcolor(WHITE);
     rectangle(310,330,310+240,440);
     rectangle(640,330,730+160,440);

     settextstyle(10, HORIZ_DIR, 3);
     outtextxy(320,343, "     PLAYER");
     outtextxy(320,373, "       VS");
     outtextxy(320,403, "     PLAYER");

     settextstyle(10, HORIZ_DIR, 3);
     outtextxy(650,343, "     PLAYER");
     outtextxy(650,373, "       VS");
     outtextxy(650,403, "    COMPUTER");

     settextstyle(10, HORIZ_DIR, 3);
     outtextxy(810,610, "PINTILIE DAVID - MIHAIL");
     //outtextxy(880,640, "DOBOS ALBERT");

     while(true)
    {
        while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);
    if(cursorX>310 and cursorX<310+240 and cursorY>330 and cursorY<440)
    {
        closegraph();
        Menu();
    }
    if(cursorX>640 and cursorX<730+160 and cursorY>330 and cursorY<440)
    {
        closegraph();
        PlayerVsComputer_Easy();
    }
    }
}

void PlayerVsComputer_GameMode()
{
    initwindow(1200,700);

     setcolor(WHITE);
     settextstyle(10, HORIZ_DIR, 5);
     outtextxy(450,50, "COLTUL NEGRU");

     settextstyle(10, HORIZ_DIR, 5);
     outtextxy(410,250, "CHOSE DIFFICULTY");

     setcolor(WHITE);
     rectangle(310,330,310+240,440);
     rectangle(640,330,730+160,440);

     settextstyle(10, HORIZ_DIR, 4);
     outtextxy(320,371, "    EASY");

     settextstyle(10, HORIZ_DIR, 4);
     outtextxy(650,371, "    HARD");

      while(true)
    {
        while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);
    if(cursorX>310 and cursorX<310+240 and cursorY>330 and cursorY<440)
    {
        closegraph();
        PlayerVsComputer_Easy();
    }
    if(cursorX>640 and cursorX<730+160 and cursorY>330 and cursorY<440)
    {
        closegraph();
        //PlayerVsComputer_Hard();
    }
    }
}

void PlayerVsComputer_Easy()
{
    initwindow(1200,700);

    setcolor(WHITE);
    settextstyle(10, HORIZ_DIR, 5);
    outtextxy(450,50, "COLTUL NEGRU");

    setcolor(WHITE);
    rectangle(20,20,150,70);
    settextstyle(10, HORIZ_DIR, 4);
    outtextxy(45,30, "BACK");

    //for(int i=100;i<=1100;i+=50)
      //  line(i,0,i,700);

        setcolor(WHITE);
    for(int i=100;i<1100;i+=210)
    {
        rectangle(i,350,i+160,440);
    }

    setcolor(WHITE);
    settextstyle(10, HORIZ_DIR, 5);
    outtextxy(250,250, "ALEGE MARIMEA TABLEI DE JOC");

    int boardsize_text=140;
    outtextxy(boardsize_text,375, "4x4");
    outtextxy(boardsize_text+210,375, "5x5");
    outtextxy(boardsize_text+420,375, "6x6");
    outtextxy(boardsize_text+630,375, "7x7");
    outtextxy(boardsize_text+840,375, "8x8");

    while(true)
    {
        while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);
        if(cursorX>20 and cursorX<150 and cursorY>20 and cursorY<70)
    {
        closegraph();
        startMenu();
    }
    if(cursorX>100 and cursorX<260 and cursorY>350 and cursorY<440)
    {
        closegraph();
        Play_4x4VsComputer();
    }
    if(cursorX>310 and cursorX<470 and cursorY>350 and cursorY<440)
    {
        closegraph();
        Play_5x5VsComputer();
    }
    if(cursorX>520 and cursorX<680 and cursorY>350 and cursorY<440)
    {
        closegraph();
        Play_6x6VsComputer();
    }
    if(cursorX>730 and cursorX<890 and cursorY>350 and cursorY<440)
    {
        closegraph();
        Play_7x7VsComputer();
    }
    if(cursorX>940 and cursorX<1100 and cursorY>350 and cursorY<440)
    {
        closegraph();
        Play_8x8VsComputer();
    }
    }
}

void Menu()
{
    initwindow(1200,700);

    setcolor(WHITE);
    settextstyle(10, HORIZ_DIR, 5);
    outtextxy(450,50, "COLTUL NEGRU");

    setcolor(WHITE);
    rectangle(20,20,150,70);
    settextstyle(10, HORIZ_DIR, 4);
    outtextxy(45,30, "BACK");

    //for(int i=100;i<=1100;i+=50)
      //  line(i,0,i,700);

        setcolor(WHITE);
    for(int i=100;i<1100;i+=210)
    {
        rectangle(i,350,i+160,440);
    }

    for(int i=100;i<1100;i+=210)
    {
        rectangle(i,450,i+160,490);
    }

    setcolor(WHITE);
    settextstyle(10, HORIZ_DIR, 5);
    outtextxy(250,250, "ALEGE MARIMEA TABLEI DE JOC");

    int boardsize_text=140;
    outtextxy(boardsize_text,375, "4x4");
    outtextxy(boardsize_text+210,375, "5x5");
    outtextxy(boardsize_text+420,375, "6x6");
    outtextxy(boardsize_text+630,375, "7x7");
    outtextxy(boardsize_text+840,375, "8x8");

    settextstyle(10, HORIZ_DIR, 4);
    int load_textY = 455;
    outtextxy(boardsize_text,load_textY, "Load");
    outtextxy(boardsize_text+210,load_textY, "Load");
    outtextxy(boardsize_text+420,load_textY, "Load");
    outtextxy(boardsize_text+630,load_textY, "Load");
    outtextxy(boardsize_text+840,load_textY, "Load");

    while(true)
    {
        while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);
        if(cursorX>20 and cursorX<150 and cursorY>20 and cursorY<70)
    {
        closegraph();
        startMenu();
    }
    if(cursorX>100 and cursorX<260 and cursorY>350 and cursorY<440)
    {
        closegraph();
        Play_4x4();
    }
    if(cursorX>310 and cursorX<470 and cursorY>350 and cursorY<440)
    {
        closegraph();
        Play_5x5();
    }
    if(cursorX>520 and cursorX<680 and cursorY>350 and cursorY<440)
    {
        closegraph();
        Play_6x6();
    }
    if(cursorX>730 and cursorX<890 and cursorY>350 and cursorY<440)
    {
        closegraph();
        Play_7x7();
    }
    if(cursorX>940 and cursorX<1100 and cursorY>350 and cursorY<440)
    {
        closegraph();
        Play_8x8();
    }
    if(cursorX>100 and cursorX<260 and cursorY>450 and cursorY<490)
    {
        closegraph();
        Play_4x4_Load();
    }
    if(cursorX>310 and cursorX<470 and cursorY>450 and cursorY<490)
    {
        closegraph();
        Play_5x5_Load();
    }
    if(cursorX>520 and cursorX<680 and cursorY>450 and cursorY<490)
    {
        closegraph();
        Play_6x6_Load();
    }
    if(cursorX>730 and cursorX<890 and cursorY>450 and cursorY<490)
    {
        closegraph();
        Play_7x7_Load();
    }
    if(cursorX>940 and cursorX<1100 and cursorY>450 and cursorY<490)
    {
        closegraph();
        Play_8x8_Load();
    }
    }
}

void PlayerVsComputer_win(int player)
{
    if(player == 1)
    {
       setcolor(YELLOW);
       settextstyle(10, HORIZ_DIR, 5);
       outtextxy(120,615, "JUCATORUL A CASTIGAT");

       setcolor(WHITE);
       rectangle(875,605,1095,665);
       settextstyle(10, HORIZ_DIR, 4);
       outtextxy(890,620, "PLAY AGAIN");

        while(true)
    {
        while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);
    if(cursorX>875 and cursorX<1095 and cursorY>605 and cursorY<665)
    {
        startMenu();
    }
    }
    }
   else
   {
       setcolor(YELLOW);
       settextstyle(10, HORIZ_DIR, 5);
       outtextxy(120,615, "CALCULATORUL A CASTIGAT");

       setcolor(WHITE);
       rectangle(875,605,1095,665);
       settextstyle(10, HORIZ_DIR, 4);
       outtextxy(890,620, "PLAY AGAIN");

        while(true)
    {
        while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);
    if(cursorX>875 and cursorX<1095 and cursorY>605 and cursorY<665)
    {
        startMenu();
    }
    }
   }
    getch();
    closegraph();
}

void win(int player)
{
    if(player == 1)
    {
       setcolor(YELLOW);
       settextstyle(10, HORIZ_DIR, 5);
       outtextxy(120,615, "JUCATORUL 1 A CASTIGAT");

       setcolor(WHITE);
       rectangle(875,605,1095,665);
       settextstyle(10, HORIZ_DIR, 4);
       outtextxy(890,620, "PLAY AGAIN");

        while(true)
    {
        while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);
    if(cursorX>875 and cursorX<1095 and cursorY>605 and cursorY<665)
    {
        startMenu();
    }
    }
    }
   else
   {
       setcolor(YELLOW);
       settextstyle(10, HORIZ_DIR, 5);
       outtextxy(120,615, "JUCATORUL 2 A CASTIGAT");

       setcolor(WHITE);
       rectangle(875,605,1095,665);
       settextstyle(10, HORIZ_DIR, 4);
       outtextxy(890,620, "PLAY AGAIN");

        while(true)
    {
        while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);
    if(cursorX>875 and cursorX<1095 and cursorY>605 and cursorY<665)
    {
        startMenu();
    }
    }
   }
    getch();
    closegraph();
}

void PlayerVsComputer_lose(int player)
{

    if(player == 1)
    {
       setcolor(YELLOW);
       settextstyle(10, HORIZ_DIR, 5);
       outtextxy(120,615, "CALCULATORUL A PIERDUT");

       setcolor(WHITE);
       rectangle(875,605,1095,665);
       settextstyle(10, HORIZ_DIR, 4);
       outtextxy(890,620, "PLAY AGAIN");

        while(true)
    {
        while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);
    if(cursorX>875 and cursorX<1095 and cursorY>605 and cursorY<665)
    {
        Menu();
    }
    }
    }
    else
    {
       setcolor(YELLOW);
       settextstyle(10, HORIZ_DIR, 5);
       outtextxy(120,615, "JUCATORUL A PIERDUT");

       setcolor(WHITE);
       rectangle(875,605,1095,665);
       settextstyle(10, HORIZ_DIR, 4);
       outtextxy(890,620, "PLAY AGAIN");

    while(true)
    {
        while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);
    if(cursorX>875 and cursorX<1095 and cursorY>605 and cursorY<665)
    {
        startMenu();
    }
    }
    }
    getch();
    closegraph();
}

void lose(int player)
{

    if(player == 1)
    {
       setcolor(YELLOW);
       settextstyle(10, HORIZ_DIR, 5);
       outtextxy(120,615, "JUCATORUL 1 A PIERDUT");

       setcolor(WHITE);
       rectangle(875,605,1095,665);
       settextstyle(10, HORIZ_DIR, 4);
       outtextxy(890,620, "PLAY AGAIN");

        while(true)
    {
        while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);
    if(cursorX>875 and cursorX<1095 and cursorY>605 and cursorY<665)
    {
        Menu();
    }
    }
    }
    else
    {
       setcolor(YELLOW);
       settextstyle(10, HORIZ_DIR, 5);
       outtextxy(120,615, "JUCATORUL 2 A PIERDUT");

       setcolor(WHITE);
       rectangle(875,605,1095,665);
       settextstyle(10, HORIZ_DIR, 4);
       outtextxy(890,620, "PLAY AGAIN");

    while(true)
    {
        while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);
    if(cursorX>875 and cursorX<1095 and cursorY>605 and cursorY<665)
    {
        startMenu();
    }
    }
    }
    getch();
    closegraph();
}
//-----------------------------------

void Play_4x4VsComputer()
{
    initwindow(1200,700);

       //for(int i = 0 ;i<=1200;i+=50)
       //line(0,i,1200,i);

       //for(int i = 0 ;i<=700;i+=50)
       //line(i,0,i,1200);

    piesaAleasa = 4;
    setcolor(WHITE);
    rectangle(20,20,150,70);
    settextstyle(10, HORIZ_DIR, 4);
    outtextxy(45,30, "BACK");

        marimeaAleasa=4;
        initializareTabla(marimeaAleasa);

    draw_Tabla(marimeaAleasa);
    //readimagefile("0.jpg", 150 + 50 * 12, 150, 150 + 50 * 11, 200);
    readimagefile("1.jpg", 150 + 50 * 13 + 10, 150, 150 + 50 * 12 + 10, 200);
    readimagefile("2.jpg", 150 + 50 * 14 + 20, 150, 150 + 50 * 13 + 20, 200);
    readimagefile("3.jpg", 150 + 50 * 15 + 30, 150, 150 + 50 * 14 + 30, 200);

            setcolor(YELLOW);
            outtextxy(720, 300, "Randul jucatorului");

            setcolor(YELLOW);
            outtextxy(710, 450, "Randul calculatorului");

    srand(time(0));
    jucator = (rand()%2) + 1;

    while(true)
    {
        if(jucator == 2)
        {

            while(!ismouseclick(WM_LBUTTONDOWN));
            getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);

    if(cursorX>150+50*13+10 and cursorX<150+50*14+10 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 1;
        cout<<"piesa aleasa este 1"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    else if(cursorX>150+50*14+20 and cursorX<150+50*15+20 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 2;
        cout<<"piesa aleasa este 2"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    else if(cursorX>150+50*15+30 and cursorX<150+50*16+30 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 3;
        cout<<"piesa aleasa este 3"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
    }
            setcolor(YELLOW);
            rectangle(700,290,1090,340);
            setcolor(BLACK);
            rectangle(700,440,1115,490);

            punerePiesa2(marimeaAleasa);
            delay(500);

        }

        else if(jucator == 1)
        {
            jucator = 2;
            setcolor(YELLOW);
            rectangle(700,440,1115,490);
            setcolor(BLACK);
            rectangle(700,290,1090,340);

            punerePiesa_Computer(marimeaAleasa);

        }

        int i,j;
        cout <<"\n\n";
        for (i=0; i<=marimeaAleasa+1; i++)
        {
            for (j=0; j<=marimeaAleasa+1; j++)
                cout << Tabla[i][j] << " ";
            cout << endl;
        }

        if(cursorX>20 and cursorX<150 and cursorY>20 and cursorY<70)
    {
        closegraph();
        startMenu();
    }
    }

}
void Play_5x5VsComputer()
{
    initwindow(1200,700);

        marimeaAleasa=5;
        initializareTabla(marimeaAleasa);

    setcolor(WHITE);
    rectangle(20,20,150,70);
    settextstyle(10, HORIZ_DIR, 4);
    outtextxy(45,30, "BACK");

    draw_Tabla(marimeaAleasa);
    //readimagefile("0.jpg", 150 + 50 * 12, 150, 150 + 50 * 11, 200);
    readimagefile("1.jpg", 150 + 50 * 13 + 10, 150, 150 + 50 * 12 + 10, 200);
    readimagefile("2.jpg", 150 + 50 * 14 + 20, 150, 150 + 50 * 13 + 20, 200);
    readimagefile("3.jpg", 150 + 50 * 15 + 30, 150, 150 + 50 * 14 + 30, 200);

    setcolor(YELLOW);
            outtextxy(720, 300, "Randul jucatorului");

            setcolor(YELLOW);
            outtextxy(710, 450, "Randul calculatorului");

    srand(time(0));
    jucator = (rand()%2) + 1;

    while(true)
    {
        if(jucator == 2)
        {

            while(!ismouseclick(WM_LBUTTONDOWN));
            getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);

    if(cursorX>150+50*13+10 and cursorX<150+50*14+10 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 1;
        cout<<"piesa aleasa este 1"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    else if(cursorX>150+50*14+20 and cursorX<150+50*15+20 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 2;
        cout<<"piesa aleasa este 2"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    else if(cursorX>150+50*15+30 and cursorX<150+50*16+30 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 3;
        cout<<"piesa aleasa este 3"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
    }
            setcolor(YELLOW);
            rectangle(700,290,1090,340);
            setcolor(BLACK);
            rectangle(700,440,1115,490);

            punerePiesa2(marimeaAleasa);

        }

        else if(jucator == 1)
        {
            jucator = 2;
            setcolor(YELLOW);
            rectangle(700,440,1115,490);
            setcolor(BLACK);
            rectangle(700,290,1090,340);

            punerePiesa_Computer(marimeaAleasa);

        }

        int i,j;
        cout <<"\n\n";
        for (i=0; i<=marimeaAleasa+1; i++)
        {
            for (j=0; j<=marimeaAleasa+1; j++)
                cout << Tabla[i][j] << " ";
            cout << endl;
        }

        if(cursorX>20 and cursorX<150 and cursorY>20 and cursorY<70)
    {
        closegraph();
        startMenu();
    }
    }

}

void Play_6x6VsComputer()
{
    initwindow(1200,700);

    setcolor(WHITE);
    rectangle(20,20,150,70);
    settextstyle(10, HORIZ_DIR, 4);
    outtextxy(45,30, "BACK");

        marimeaAleasa=6;
        initializareTabla(marimeaAleasa);

    draw_Tabla(marimeaAleasa);
    //readimagefile("0.jpg", 150 + 50 * 12, 150, 150 + 50 * 11, 200);
    readimagefile("1.jpg", 150 + 50 * 13 + 10, 150, 150 + 50 * 12 + 10, 200);
    readimagefile("2.jpg", 150 + 50 * 14 + 20, 150, 150 + 50 * 13 + 20, 200);
    readimagefile("3.jpg", 150 + 50 * 15 + 30, 150, 150 + 50 * 14 + 30, 200);

    setcolor(YELLOW);
            outtextxy(720, 300, "Randul jucatorului");

            setcolor(YELLOW);
            outtextxy(710, 450, "Randul calculatorului");

    srand(time(0));
    jucator = (rand()%2) + 1;

    while(true)
    {
        if(jucator == 2)
        {

            while(!ismouseclick(WM_LBUTTONDOWN));
            getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);

    if(cursorX>150+50*13+10 and cursorX<150+50*14+10 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 1;
        cout<<"piesa aleasa este 1"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    else if(cursorX>150+50*14+20 and cursorX<150+50*15+20 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 2;
        cout<<"piesa aleasa este 2"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    else if(cursorX>150+50*15+30 and cursorX<150+50*16+30 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 3;
        cout<<"piesa aleasa este 3"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
    }
            setcolor(YELLOW);
            rectangle(700,290,1090,340);
            setcolor(BLACK);
            rectangle(700,440,1115,490);

            punerePiesa2(marimeaAleasa);

        }

        else if(jucator == 1)
        {
            jucator = 2;
            setcolor(YELLOW);
            rectangle(700,440,1115,490);
            setcolor(BLACK);
            rectangle(700,290,1090,340);

            punerePiesa_Computer(marimeaAleasa);

        }

        int i,j;
        cout <<"\n\n";
        for (i=0; i<=marimeaAleasa+1; i++)
        {
            for (j=0; j<=marimeaAleasa+1; j++)
                cout << Tabla[i][j] << " ";
            cout << endl;
        }

        if(cursorX>20 and cursorX<150 and cursorY>20 and cursorY<70)
    {
        closegraph();
        startMenu();
    }
    }

}
void Play_7x7VsComputer()
{
    initwindow(1200,700);

    setcolor(WHITE);
    rectangle(20,20,150,70);
    settextstyle(10, HORIZ_DIR, 4);
    outtextxy(45,30, "BACK");

        marimeaAleasa=7;
        initializareTabla(marimeaAleasa);

    draw_Tabla(marimeaAleasa);
    //readimagefile("0.jpg", 150 + 50 * 12, 150, 150 + 50 * 11, 200);
    readimagefile("1.jpg", 150 + 50 * 13 + 10, 150, 150 + 50 * 12 + 10, 200);
    readimagefile("2.jpg", 150 + 50 * 14 + 20, 150, 150 + 50 * 13 + 20, 200);
    readimagefile("3.jpg", 150 + 50 * 15 + 30, 150, 150 + 50 * 14 + 30, 200);

    setcolor(YELLOW);
            outtextxy(720, 300, "Randul jucatorului");

            setcolor(YELLOW);
            outtextxy(710, 450, "Randul calculatorului");

    srand(time(0));
    jucator = (rand()%2) + 1;

    while(true)
    {
        if(jucator == 2)
        {

            while(!ismouseclick(WM_LBUTTONDOWN));
            getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);

    if(cursorX>150+50*13+10 and cursorX<150+50*14+10 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 1;
        cout<<"piesa aleasa este 1"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    else if(cursorX>150+50*14+20 and cursorX<150+50*15+20 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 2;
        cout<<"piesa aleasa este 2"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    else if(cursorX>150+50*15+30 and cursorX<150+50*16+30 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 3;
        cout<<"piesa aleasa este 3"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
    }
            setcolor(YELLOW);
            rectangle(700,290,1090,340);
            setcolor(BLACK);
            rectangle(700,440,1115,490);

            punerePiesa2(marimeaAleasa);

        }

        else if(jucator == 1)
        {
            jucator = 2;
            setcolor(YELLOW);
            rectangle(700,440,1115,490);
            setcolor(BLACK);
            rectangle(700,290,1090,340);

            punerePiesa_Computer(marimeaAleasa);

        }

        int i,j;
        cout <<"\n\n";
        for (i=0; i<=marimeaAleasa+1; i++)
        {
            for (j=0; j<=marimeaAleasa+1; j++)
                cout << Tabla[i][j] << " ";
            cout << endl;
        }

        if(cursorX>20 and cursorX<150 and cursorY>20 and cursorY<70)
    {
        closegraph();
        startMenu();
    }
    }

}
void Play_8x8VsComputer()
{
    initwindow(1200,700);

    setcolor(WHITE);
    rectangle(20,20,150,70);
    settextstyle(10, HORIZ_DIR, 4);
    outtextxy(45,30, "BACK");

        marimeaAleasa=8;
        initializareTabla(marimeaAleasa);

    draw_Tabla(marimeaAleasa);
    //readimagefile("0.jpg", 150 + 50 * 12, 150, 150 + 50 * 11, 200);
    readimagefile("1.jpg", 150 + 50 * 13 + 10, 150, 150 + 50 * 12 + 10, 200);
    readimagefile("2.jpg", 150 + 50 * 14 + 20, 150, 150 + 50 * 13 + 20, 200);
    readimagefile("3.jpg", 150 + 50 * 15 + 30, 150, 150 + 50 * 14 + 30, 200);

    setcolor(YELLOW);
            outtextxy(720, 300, "Randul jucatorului");

            setcolor(YELLOW);
            outtextxy(710, 450, "Randul calculatorului");

    srand(time(0));
    jucator = (rand()%2) + 1;

    while(true)
    {
        if(jucator == 2)
        {

            while(!ismouseclick(WM_LBUTTONDOWN));
            getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);

    if(cursorX>150+50*13+10 and cursorX<150+50*14+10 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 1;
        cout<<"piesa aleasa este 1"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    else if(cursorX>150+50*14+20 and cursorX<150+50*15+20 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 2;
        cout<<"piesa aleasa este 2"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    else if(cursorX>150+50*15+30 and cursorX<150+50*16+30 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 3;
        cout<<"piesa aleasa este 3"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
    }
            setcolor(YELLOW);
            rectangle(700,290,1090,340);
            setcolor(BLACK);
            rectangle(700,440,1115,490);

            punerePiesa2(marimeaAleasa);

        }

        else if(jucator == 1)
        {
            jucator = 2;
            setcolor(YELLOW);
            rectangle(700,440,1115,490);
            setcolor(BLACK);
            rectangle(700,290,1090,340);

            punerePiesa_Computer(marimeaAleasa);

        }

        int i,j;
        cout <<"\n\n";
        for (i=0; i<=marimeaAleasa+1; i++)
        {
            for (j=0; j<=marimeaAleasa+1; j++)
                cout << Tabla[i][j] << " ";
            cout << endl;
        }

        if(cursorX>20 and cursorX<150 and cursorY>20 and cursorY<70)
    {
        closegraph();
        startMenu();
    }
    }
}

//-----------------------------------
void Play_4x4()
{
    initwindow(1200,700);

       //for(int i = 0 ;i<=1200;i+=50)
       //line(0,i,1200,i);

       //for(int i = 0 ;i<=700;i+=50)
       //line(i,0,i,1200);

    piesaAleasa = 5;
    setcolor(WHITE);
    rectangle(20,20,150,70);
    settextstyle(10, HORIZ_DIR, 4);
    outtextxy(45,30, "BACK");

        marimeaAleasa=4;
        initializareTabla(marimeaAleasa);

    draw_Tabla(marimeaAleasa);
    //readimagefile("0.jpg", 150 + 50 * 12, 150, 150 + 50 * 11, 200);
    readimagefile("1.jpg", 150 + 50 * 13 + 10, 150, 150 + 50 * 12 + 10, 200);
    readimagefile("2.jpg", 150 + 50 * 14 + 20, 150, 150 + 50 * 13 + 20, 200);
    readimagefile("3.jpg", 150 + 50 * 15 + 30, 150, 150 + 50 * 14 + 30, 200);

    jucator = 2;

    while(true)
    {
        while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);

    if(cursorX>20 and cursorX<150 and cursorY>20 and cursorY<70)
    {
        closegraph();
        Menu();
    }
    do
    {
    /*
    if(cursorX>150+50*12 and cursorX<150+50*13 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 0;
        cout<<"piesa aleasa este 0 "<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    */
    if(cursorX>150+50*13+10 and cursorX<150+50*14+10 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 1;
        cout<<"piesa aleasa este 1"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    else if(cursorX>150+50*14+20 and cursorX<150+50*15+20 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 2;
        cout<<"piesa aleasa este 2"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    else if(cursorX>150+50*15+30 and cursorX<150+50*16+30 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 3;
        cout<<"piesa aleasa este 3"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
    }
    } while(piesaAleasa == 4);

            setcolor(YELLOW);
            outtextxy(790, 300, "Jucatorul 1");

            setcolor(YELLOW);
            outtextxy(790, 450, "Jucatorul 2");

        if(jucator == 2)
        {
            jucator = 1;
            setcolor(YELLOW);
            rectangle(780,290,1010,340);
            setcolor(BLACK);
            rectangle(780,440,1010,490);
        }

        else if(jucator == 1)
        {
            jucator = 2;
            setcolor(YELLOW);
            rectangle(780,440,1010,490);
            setcolor(BLACK);
            rectangle(780,290,1010,340);
        }

        do
        {
            ok=punerePiesa(marimeaAleasa);
        }
        while (!ok);

        int i,j;
        cout <<"\n\n";
        for (i=0; i<=marimeaAleasa+1; i++)
        {
            for (j=0; j<=marimeaAleasa+1; j++)
                cout << Tabla[i][j] << " ";
            cout << endl;
        }

        for(int i=0; i<=marimeaAleasa+1; i++)
        {
            for(j=0; j<=marimeaAleasa+1; j++)
                Tabla4x4[i][j] = Tabla[i][j];
        }

    }

}

void Play_4x4_Load()
{
    initwindow(1200,700);

       //for(int i = 0 ;i<=1200;i+=50)
       //line(0,i,1200,i);

       //for(int i = 0 ;i<=700;i+=50)
       //line(i,0,i,1200);

    piesaAleasa = 5;
    setcolor(WHITE);
    rectangle(20,20,150,70);
    settextstyle(10, HORIZ_DIR, 4);
    outtextxy(45,30, "BACK");


        marimeaAleasa=4;
        initializareTabla_Load4x4(marimeaAleasa);

        for(int i=0; i<=marimeaAleasa+1; i++)
        {
            for(int j=0; j<=marimeaAleasa+1; j++)
                Tabla[i][j] = Tabla4x4[i][j];
        }

    draw_Tabla(marimeaAleasa);
    //readimagefile("0.jpg", 150 + 50 * 12, 150, 150 + 50 * 11, 200);
    readimagefile("1.jpg", 150 + 50 * 13 + 10, 150, 150 + 50 * 12 + 10, 200);
    readimagefile("2.jpg", 150 + 50 * 14 + 20, 150, 150 + 50 * 13 + 20, 200);
    readimagefile("3.jpg", 150 + 50 * 15 + 30, 150, 150 + 50 * 14 + 30, 200);

    while(true)
    {
        while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);

    if(cursorX>20 and cursorX<150 and cursorY>20 and cursorY<70)
    {
        closegraph();
        Menu();
    }
    do
    {
    /*
    if(cursorX>150+50*12 and cursorX<150+50*13 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 0;
        cout<<"piesa aleasa este 0 "<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    */
    if(cursorX>150+50*13+10 and cursorX<150+50*14+10 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 1;
        cout<<"piesa aleasa este 1"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    else if(cursorX>150+50*14+20 and cursorX<150+50*15+20 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 2;
        cout<<"piesa aleasa este 2"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    else if(cursorX>150+50*15+30 and cursorX<150+50*16+30 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 3;
        cout<<"piesa aleasa este 3"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
    }
    } while(piesaAleasa == 4);

         setcolor(YELLOW);
            outtextxy(790, 300, "Jucatorul 1");

            setcolor(YELLOW);
            outtextxy(790, 450, "Jucatorul 2");

        if(jucator == 2)
        {
            jucator = 1;
            setcolor(YELLOW);
            rectangle(780,290,1010,340);
            setcolor(BLACK);
            rectangle(780,440,1010,490);
        }

        else if(jucator == 1)
        {
            jucator = 2;
            setcolor(YELLOW);
            rectangle(780,440,1010,490);
            setcolor(BLACK);
            rectangle(780,290,1010,340);
        }

        do
        {
            ok=punerePiesa(marimeaAleasa);
        }
        while (!ok);

        int i,j;
        cout <<"\n\n";
        for (i=0; i<=marimeaAleasa+1; i++)
        {
            for (j=0; j<=marimeaAleasa+1; j++)
                cout << Tabla[i][j] << " ";
            cout << endl;
        }

        for(int i=0; i<=marimeaAleasa+1; i++)
        {
            for(j=0; j<=marimeaAleasa+1; j++)
                Tabla4x4[i][j] = Tabla[i][j];
        }

    }

}
void Play_5x5()
{
    initwindow(1200,700);

        marimeaAleasa=5;
        initializareTabla(marimeaAleasa);

    setcolor(WHITE);
    rectangle(20,20,150,70);
    settextstyle(10, HORIZ_DIR, 4);
    outtextxy(45,30, "BACK");

    draw_Tabla(marimeaAleasa);
    //readimagefile("0.jpg", 150 + 50 * 12, 150, 150 + 50 * 11, 200);
    readimagefile("1.jpg", 150 + 50 * 13 + 10, 150, 150 + 50 * 12 + 10, 200);
    readimagefile("2.jpg", 150 + 50 * 14 + 20, 150, 150 + 50 * 13 + 20, 200);
    readimagefile("3.jpg", 150 + 50 * 15 + 30, 150, 150 + 50 * 14 + 30, 200);

    jucator = 2;

    while(true)
    {
        while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);

    if(cursorX>20 and cursorX<150 and cursorY>20 and cursorY<70)
    {
        closegraph();
        Menu();
    }
    do
    {
    /*
    if(cursorX>150+50*12 and cursorX<150+50*13 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 0;
        cout<<"piesa aleasa este 0 "<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    */
    if(cursorX>150+50*13+10 and cursorX<150+50*14+10 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 1;
        cout<<"piesa aleasa este 1"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    if(cursorX>150+50*14+20 and cursorX<150+50*15+20 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 2;
        cout<<"piesa aleasa este 2"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    if(cursorX>150+50*15+30 and cursorX<150+50*16+30 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 3;
        cout<<"piesa aleasa este 3"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
    }
    } while(piesaAleasa == 4);

         setcolor(YELLOW);
            outtextxy(790, 300, "Jucatorul 1");

            setcolor(YELLOW);
            outtextxy(790, 450, "Jucatorul 2");

        if(jucator == 2)
        {
            jucator = 1;
            setcolor(YELLOW);
            rectangle(780,290,1010,340);
            setcolor(BLACK);
            rectangle(780,440,1010,490);
        }

        else if(jucator == 1)
        {
            jucator = 2;
            setcolor(YELLOW);
            rectangle(780,440,1010,490);
            setcolor(BLACK);
            rectangle(780,290,1010,340);
        }
        do
        {
            ok=punerePiesa(marimeaAleasa);
        }
        while (!ok);

        int i,j;
        cout <<"\n\n";
        for (i=0; i<=marimeaAleasa+1; i++)
        {
            for (j=0; j<=marimeaAleasa+1; j++)
                cout << Tabla[i][j] << " ";
            cout << endl;
        }
        for(int i=0; i<=marimeaAleasa+1; i++)
        {
            for(j=0; j<=marimeaAleasa+1; j++)
                Tabla5x5[i][j] = Tabla[i][j];
        }
    }
}
void Play_5x5_Load()
{
    initwindow(1200,700);

        marimeaAleasa=5;
        initializareTabla_Load5x5(marimeaAleasa);

            for(int i=0; i<=marimeaAleasa+1; i++)
        {
            for(int j=0; j<=marimeaAleasa+1; j++)
                Tabla[i][j] = Tabla5x5[i][j];
        }

    setcolor(WHITE);
    rectangle(20,20,150,70);
    settextstyle(10, HORIZ_DIR, 4);
    outtextxy(45,30, "BACK");

    draw_Tabla2(marimeaAleasa);
    //readimagefile("0.jpg", 150 + 50 * 12, 150, 150 + 50 * 11, 200);
    readimagefile("1.jpg", 150 + 50 * 13 + 10, 150, 150 + 50 * 12 + 10, 200);
    readimagefile("2.jpg", 150 + 50 * 14 + 20, 150, 150 + 50 * 13 + 20, 200);
    readimagefile("3.jpg", 150 + 50 * 15 + 30, 150, 150 + 50 * 14 + 30, 200);

    while(true)
    {
        while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);

    if(cursorX>20 and cursorX<150 and cursorY>20 and cursorY<70)
    {
        closegraph();
        Menu();
    }
    do
    {
    /*
    if(cursorX>150+50*12 and cursorX<150+50*13 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 0;
        cout<<"piesa aleasa este 0 "<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    */
    if(cursorX>150+50*13+10 and cursorX<150+50*14+10 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 1;
        cout<<"piesa aleasa este 1"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    if(cursorX>150+50*14+20 and cursorX<150+50*15+20 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 2;
        cout<<"piesa aleasa este 2"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    if(cursorX>150+50*15+30 and cursorX<150+50*16+30 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 3;
        cout<<"piesa aleasa este 3"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
    }
    } while(piesaAleasa == 4);

         setcolor(YELLOW);
            outtextxy(790, 300, "Jucatorul 1");

            setcolor(YELLOW);
            outtextxy(790, 450, "Jucatorul 2");

        if(jucator == 2)
        {
            jucator = 1;
            setcolor(YELLOW);
            rectangle(780,290,1010,340);
            setcolor(BLACK);
            rectangle(780,440,1010,490);
        }

        else if(jucator == 1)
        {
            jucator = 2;
            setcolor(YELLOW);
            rectangle(780,440,1010,490);
            setcolor(BLACK);
            rectangle(780,290,1010,340);
        }

        do
        {
            ok=punerePiesa(marimeaAleasa);
        }
        while (!ok);

        int i,j;
        cout <<"\n\n";
        for (i=0; i<=marimeaAleasa+1; i++)
        {
            for (j=0; j<=marimeaAleasa+1; j++)
                cout << Tabla[i][j] << " ";
            cout << endl;
        }
    }
}
void Play_6x6()
{
    initwindow(1200,700);

    setcolor(WHITE);
    rectangle(20,20,150,70);
    settextstyle(10, HORIZ_DIR, 4);
    outtextxy(45,30, "BACK");

        marimeaAleasa=6;
        initializareTabla(marimeaAleasa);

    draw_Tabla(marimeaAleasa);
    //readimagefile("0.jpg", 150 + 50 * 12, 150, 150 + 50 * 11, 200);
    readimagefile("1.jpg", 150 + 50 * 13 + 10, 150, 150 + 50 * 12 + 10, 200);
    readimagefile("2.jpg", 150 + 50 * 14 + 20, 150, 150 + 50 * 13 + 20, 200);
    readimagefile("3.jpg", 150 + 50 * 15 + 30, 150, 150 + 50 * 14 + 30, 200);

    jucator = 2;

    while(true)
    {
        while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);

    if(cursorX>20 and cursorX<150 and cursorY>20 and cursorY<70)
    {
        closegraph();
        Menu();
    }do
    {
    /*
    if(cursorX>150+50*12 and cursorX<150+50*13 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 0;
        cout<<"piesa aleasa este 0 "<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    */
    if(cursorX>150+50*13+10 and cursorX<150+50*14+10 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 1;
        cout<<"piesa aleasa este 1"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    if(cursorX>150+50*14+20 and cursorX<150+50*15+20 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 2;
        cout<<"piesa aleasa este 2"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    if(cursorX>150+50*15+30 and cursorX<150+50*16+30 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 3;
        cout<<"piesa aleasa este 3"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
    }
    } while(piesaAleasa == 4);

         setcolor(YELLOW);
            outtextxy(790, 300, "Jucatorul 1");

            setcolor(YELLOW);
            outtextxy(790, 450, "Jucatorul 2");

        if(jucator == 2)
        {
            jucator = 1;
            setcolor(YELLOW);
            rectangle(780,290,1010,340);
            setcolor(BLACK);
            rectangle(780,440,1010,490);
        }

        else if(jucator == 1)
        {
            jucator = 2;
            setcolor(YELLOW);
            rectangle(780,440,1010,490);
            setcolor(BLACK);
            rectangle(780,290,1010,340);
        }

        do
        {
            ok=punerePiesa(marimeaAleasa);
        }
        while (!ok);

        int i,j;
        cout <<"\n\n";
        for (i=0; i<=marimeaAleasa+1; i++)
        {
            for (j=0; j<=marimeaAleasa+1; j++)
                cout << Tabla[i][j] << " ";
            cout << endl;
        }
        for(int i=0; i<=marimeaAleasa+1; i++)
        {
            for(j=0; j<=marimeaAleasa+1; j++)
                Tabla6x6[i][j] = Tabla[i][j];
        }

    }
}

void Play_6x6_Load()
{
    initwindow(1200,700);

    setcolor(WHITE);
    rectangle(20,20,150,70);
    settextstyle(10, HORIZ_DIR, 4);
    outtextxy(45,30, "BACK");

        marimeaAleasa=6;
        initializareTabla_Load6x6(marimeaAleasa);

        for(int i=0; i<=marimeaAleasa+1; i++)
        {
            for(int j=0; j<=marimeaAleasa+1; j++)
                Tabla[i][j] = Tabla6x6[i][j];
        }

    draw_Tabla(marimeaAleasa);
    //readimagefile("0.jpg", 150 + 50 * 12, 150, 150 + 50 * 11, 200);
    readimagefile("1.jpg", 150 + 50 * 13 + 10, 150, 150 + 50 * 12 + 10, 200);
    readimagefile("2.jpg", 150 + 50 * 14 + 20, 150, 150 + 50 * 13 + 20, 200);
    readimagefile("3.jpg", 150 + 50 * 15 + 30, 150, 150 + 50 * 14 + 30, 200);

    while(true)
    {
        while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);

    if(cursorX>20 and cursorX<150 and cursorY>20 and cursorY<70)
    {
        closegraph();
        Menu();
    }do
    {
    /*
    if(cursorX>150+50*12 and cursorX<150+50*13 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 0;
        cout<<"piesa aleasa este 0 "<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    */
    if(cursorX>150+50*13+10 and cursorX<150+50*14+10 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 1;
        cout<<"piesa aleasa este 1"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    if(cursorX>150+50*14+20 and cursorX<150+50*15+20 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 2;
        cout<<"piesa aleasa este 2"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    if(cursorX>150+50*15+30 and cursorX<150+50*16+30 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 3;
        cout<<"piesa aleasa este 3"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
    }
    } while(piesaAleasa == 4);

         setcolor(YELLOW);
            outtextxy(790, 300, "Jucatorul 1");

            setcolor(YELLOW);
            outtextxy(790, 450, "Jucatorul 2");

        if(jucator == 2)
        {
            jucator = 1;
            setcolor(YELLOW);
            rectangle(780,290,1010,340);
            setcolor(BLACK);
            rectangle(780,440,1010,490);
        }

        else if(jucator == 1)
        {
            jucator = 2;
            setcolor(YELLOW);
            rectangle(780,440,1010,490);
            setcolor(BLACK);
            rectangle(780,290,1010,340);
        }

        do
        {
            ok=punerePiesa(marimeaAleasa);
        }
        while (!ok);

        int i,j;
        cout <<"\n\n";
        for (i=0; i<=marimeaAleasa+1; i++)
        {
            for (j=0; j<=marimeaAleasa+1; j++)
                cout << Tabla[i][j] << " ";
            cout << endl;
        }

    }
}

void Play_7x7()
{
    initwindow(1200,700);

    setcolor(WHITE);
    rectangle(20,20,150,70);
    settextstyle(10, HORIZ_DIR, 4);
    outtextxy(45,30, "BACK");

        marimeaAleasa=7;
        initializareTabla(marimeaAleasa);

    draw_Tabla(marimeaAleasa);
    //readimagefile("0.jpg", 150 + 50 * 12, 150, 150 + 50 * 11, 200);
    readimagefile("1.jpg", 150 + 50 * 13 + 10, 150, 150 + 50 * 12 + 10, 200);
    readimagefile("2.jpg", 150 + 50 * 14 + 20, 150, 150 + 50 * 13 + 20, 200);
    readimagefile("3.jpg", 150 + 50 * 15 + 30, 150, 150 + 50 * 14 + 30, 200);

    jucator = 2;

    while(true)
    {
        while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);

    if(cursorX>20 and cursorX<150 and cursorY>20 and cursorY<70)
    {
        closegraph();
        Menu();
    }
    do
    {
    /*
    if(cursorX>150+50*12 and cursorX<150+50*13 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 0;
        cout<<"piesa aleasa este 0 "<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    */
    if(cursorX>150+50*13+10 and cursorX<150+50*14+10 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 1;
        cout<<"piesa aleasa este 1"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    if(cursorX>150+50*14+20 and cursorX<150+50*15+20 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 2;
        cout<<"piesa aleasa este 2"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    if(cursorX>150+50*15+30 and cursorX<150+50*16+30 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 3;
        cout<<"piesa aleasa este 3"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
    }
    } while(piesaAleasa == 4);

        do
        {
            ok=punerePiesa(marimeaAleasa);
        }
        while (!ok);

        int i,j;
        cout <<"\n\n";
        for (i=0; i<=marimeaAleasa+1; i++)
        {
            for (j=0; j<=marimeaAleasa+1; j++)
                cout << Tabla[i][j] << " ";
            cout << endl;
        }
        for(int i=0; i<=marimeaAleasa+1; i++)
        {
            for(j=0; j<=marimeaAleasa+1; j++)
                Tabla7x7[i][j] = Tabla[i][j];
        }


               setcolor(YELLOW);
            outtextxy(790, 300, "Jucatorul 1");

            setcolor(YELLOW);
            outtextxy(790, 450, "Jucatorul 2");

        if(jucator == 2)
        {
            jucator = 1;
            setcolor(YELLOW);
            rectangle(780,290,1010,340);
            setcolor(BLACK);
            rectangle(780,440,1010,490);
        }

        else if(jucator == 1)
        {
            jucator = 2;
            setcolor(YELLOW);
            rectangle(780,440,1010,490);
            setcolor(BLACK);
            rectangle(780,290,1010,340);
        }
    }
}
void Play_7x7_Load()
{
    initwindow(1200,700);

    setcolor(WHITE);
    rectangle(20,20,150,70);
    settextstyle(10, HORIZ_DIR, 4);
    outtextxy(45,30, "BACK");

        marimeaAleasa=7;
        initializareTabla_Load7x7(marimeaAleasa);


        for(int i=0; i<=marimeaAleasa+1; i++)
        {
            for(int j=0; j<=marimeaAleasa+1; j++)
                Tabla[i][j] = Tabla7x7[i][j];
        }

    draw_Tabla(marimeaAleasa);
    //readimagefile("0.jpg", 150 + 50 * 12, 150, 150 + 50 * 11, 200);
    readimagefile("1.jpg", 150 + 50 * 13 + 10, 150, 150 + 50 * 12 + 10, 200);
    readimagefile("2.jpg", 150 + 50 * 14 + 20, 150, 150 + 50 * 13 + 20, 200);
    readimagefile("3.jpg", 150 + 50 * 15 + 30, 150, 150 + 50 * 14 + 30, 200);

    while(true)
    {
        while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);

    if(cursorX>20 and cursorX<150 and cursorY>20 and cursorY<70)
    {
        closegraph();
        Menu();
    }
    do
    {
    /*
    if(cursorX>150+50*12 and cursorX<150+50*13 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 0;
        cout<<"piesa aleasa este 0 "<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    */
    if(cursorX>150+50*13+10 and cursorX<150+50*14+10 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 1;
        cout<<"piesa aleasa este 1"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    if(cursorX>150+50*14+20 and cursorX<150+50*15+20 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 2;
        cout<<"piesa aleasa este 2"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    if(cursorX>150+50*15+30 and cursorX<150+50*16+30 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 3;
        cout<<"piesa aleasa este 3"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
    }
    } while(piesaAleasa == 4);

        do
        {
            ok=punerePiesa(marimeaAleasa);
        }
        while (!ok);

        int i,j;
        cout <<"\n\n";
        for (i=0; i<=marimeaAleasa+1; i++)
        {
            for (j=0; j<=marimeaAleasa+1; j++)
                cout << Tabla[i][j] << " ";
            cout << endl;
        }
                setcolor(YELLOW);
            outtextxy(790, 300, "Jucatorul 1");

            setcolor(YELLOW);
            outtextxy(790, 450, "Jucatorul 2");

        if(jucator == 2)
        {
            jucator = 1;
            setcolor(YELLOW);
            rectangle(780,290,1010,340);
            setcolor(BLACK);
            rectangle(780,440,1010,490);
        }

        else if(jucator == 1)
        {
            jucator = 2;
            setcolor(YELLOW);
            rectangle(780,440,1010,490);
            setcolor(BLACK);
            rectangle(780,290,1010,340);
        }
    }
}

void Play_8x8()
{
    initwindow(1200,700);

    setcolor(WHITE);
    rectangle(20,20,150,70);
    settextstyle(10, HORIZ_DIR, 4);
    outtextxy(45,30, "BACK");

        marimeaAleasa=8;
        initializareTabla(marimeaAleasa);

    draw_Tabla(marimeaAleasa);
    //readimagefile("0.jpg", 150 + 50 * 12, 150, 150 + 50 * 11, 200);
    readimagefile("1.jpg", 150 + 50 * 13 + 10, 150, 150 + 50 * 12 + 10, 200);
    readimagefile("2.jpg", 150 + 50 * 14 + 20, 150, 150 + 50 * 13 + 20, 200);
    readimagefile("3.jpg", 150 + 50 * 15 + 30, 150, 150 + 50 * 14 + 30, 200);

    jucator = 2;

    while(true)
    {
        while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);

    if(cursorX>20 and cursorX<150 and cursorY>20 and cursorY<70)
    {
        closegraph();
        Menu();
    }
    do
    {
    /*
    if(cursorX>150+50*12 and cursorX<150+50*13 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 0;
        cout<<"piesa aleasa este 0 "<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    */
    if(cursorX>150+50*13+10 and cursorX<150+50*14+10 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 1;
        cout<<"piesa aleasa este 1"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    if(cursorX>150+50*14+20 and cursorX<150+50*15+20 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 2;
        cout<<"piesa aleasa este 2"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    if(cursorX>150+50*15+30 and cursorX<150+50*16+30 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 3;
        cout<<"piesa aleasa este 3"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
    }
    } while(piesaAleasa == 4);

         setcolor(YELLOW);
            outtextxy(790, 300, "Jucatorul 1");

            setcolor(YELLOW);
            outtextxy(790, 450, "Jucatorul 2");

        if(jucator == 2)
        {
            jucator = 1;
            setcolor(YELLOW);
            rectangle(780,290,1010,340);
            setcolor(BLACK);
            rectangle(780,440,1010,490);
        }

        else if(jucator == 1)
        {
            jucator = 2;
            setcolor(YELLOW);
            rectangle(780,440,1010,490);
            setcolor(BLACK);
            rectangle(780,290,1010,340);
        }

        do
        {
            ok=punerePiesa(marimeaAleasa);
        }
        while (!ok);

        int i,j;
        cout <<"\n\n";
        for (i=0; i<=marimeaAleasa+1; i++)
        {
            for (j=0; j<=marimeaAleasa+1; j++)
                cout << Tabla[i][j] << " ";
            cout << endl;
        }
        for(int i=0; i<=marimeaAleasa+1; i++)
        {
            for(j=0; j<=marimeaAleasa+1; j++)
                Tabla8x8[i][j] = Tabla[i][j];
        }
    }
}

void Play_8x8_Load()
{
    initwindow(1200,700);

    setcolor(WHITE);
    rectangle(20,20,150,70);
    settextstyle(10, HORIZ_DIR, 4);
    outtextxy(45,30, "BACK");

        marimeaAleasa=8;
        initializareTabla_Load8x8(marimeaAleasa);

        for(int i=0; i<=marimeaAleasa+1; i++)
        {
            for(int j=0; j<=marimeaAleasa+1; j++)
                Tabla[i][j] = Tabla8x8[i][j];
        }

    draw_Tabla(marimeaAleasa);
    //readimagefile("0.jpg", 150 + 50 * 12, 150, 150 + 50 * 11, 200);
    readimagefile("1.jpg", 150 + 50 * 13 + 10, 150, 150 + 50 * 12 + 10, 200);
    readimagefile("2.jpg", 150 + 50 * 14 + 20, 150, 150 + 50 * 13 + 20, 200);
    readimagefile("3.jpg", 150 + 50 * 15 + 30, 150, 150 + 50 * 14 + 30, 200);

    while(true)
    {
        while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);

    if(cursorX>20 and cursorX<150 and cursorY>20 and cursorY<70)
    {
        closegraph();
        Menu();
    }
    do
    {
    /*
    if(cursorX>150+50*12 and cursorX<150+50*13 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 0;
        cout<<"piesa aleasa este 0 "<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    */
    if(cursorX>150+50*13+10 and cursorX<150+50*14+10 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 1;
        cout<<"piesa aleasa este 1"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    if(cursorX>150+50*14+20 and cursorX<150+50*15+20 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 2;
        cout<<"piesa aleasa este 2"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
        setcolor(BLACK);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
    }
    if(cursorX>150+50*15+30 and cursorX<150+50*16+30 and cursorY>150 and cursorY<200)
    {
        piesaAleasa = 3;
        cout<<"piesa aleasa este 3"<<"\n";
        setcolor(YELLOW);
        rectangle(150+50*15+30-3, 150-3, 150+50*16+30+3,203);
        setcolor(BLACK);
        rectangle(150+50*12-3, 150-3, 150+50*13+3,203);
        rectangle(150+50*13+10-3, 150-3, 150+50*14+10+3,203);
        rectangle(150+50*14+20-3, 150-3, 150+50*15+20+3,203);
    }
    } while(piesaAleasa == 4);

         setcolor(YELLOW);
            outtextxy(790, 300, "Jucatorul 1");

            setcolor(YELLOW);
            outtextxy(790, 450, "Jucatorul 2");

        if(jucator == 2)
        {
            jucator = 1;
            setcolor(YELLOW);
            rectangle(780,290,1010,340);
            setcolor(BLACK);
            rectangle(780,440,1010,490);
        }

        else if(jucator == 1)
        {
            jucator = 2;
            setcolor(YELLOW);
            rectangle(780,440,1010,490);
            setcolor(BLACK);
            rectangle(780,290,1010,340);
        }

        do
        {
            ok=punerePiesa(marimeaAleasa);
        }
        while (!ok);

        int i,j;
        cout <<"\n\n";
        for (i=0; i<=marimeaAleasa+1; i++)
        {
            for (j=0; j<=marimeaAleasa+1; j++)
                cout << Tabla[i][j] << " ";
            cout << endl;
        }
    }
}

void draw_Piesa(int tip_piesa , int linie , int coloana)
{
    char fileName[10];

    switch(tip_piesa)
    {
    case 0:
        strcpy(fileName,"0.jpg");
        break;
    case 1:
        strcpy(fileName,"1.jpg");
        break;
    case 2:
        strcpy(fileName,"2.jpg");
        break;
    case 3:
        strcpy(fileName,"3.jpg");
        break;
    }
    readimagefile(fileName, 150 + 50 * coloana, 150 + 50 * linie, 150 + 50 * (coloana + 1) - 2, 150 + 50 * (linie + 1) - 2);
}

void draw_Tabla2(int marime_tabla)
{
    if(marime_tabla == 4)
    {
        for (int i=1; i<=marime_tabla; i++)
    {
        for (int j=1; j<=marime_tabla; j++)
        {
            piesaAleasa=Tabla4x4[i][j];
            if(i == marime_tabla and j == marime_tabla) break;
            draw_Piesa(piesaAleasa,i,j);
        }
    }
    }

    if(marime_tabla == 5)
    {
        for (int i=1; i<=marime_tabla; i++)
    {
        for (int j=1; j<=marime_tabla; j++)
        {
            piesaAleasa=Tabla5x5[i][j];
            if(i == marime_tabla and j == marime_tabla) break;
            draw_Piesa(piesaAleasa,i,j);
        }
    }
    }

    if(marime_tabla == 6)
    {
        for (int i=1; i<=marime_tabla; i++)
    {
        for (int j=1; j<=marime_tabla; j++)
        {
            piesaAleasa=Tabla6x6[i][j];
            if(i == marime_tabla and j == marime_tabla) break;
            draw_Piesa(piesaAleasa,i,j);
        }
    }
    }

    if(marime_tabla == 7)
    {
        for (int i=1; i<=marime_tabla; i++)
    {
        for (int j=1; j<=marime_tabla; j++)
        {
            piesaAleasa=Tabla7x7[i][j];
            if(i == marime_tabla and j == marime_tabla) break;
            draw_Piesa(piesaAleasa,i,j);
        }
    }
    }

    if(marime_tabla == 8)
    {
        for (int i=1; i<=marime_tabla; i++)
    {
        for (int j=1; j<=marime_tabla; j++)
        {
            piesaAleasa=Tabla8x8[i][j];
            if(i == marime_tabla and j == marime_tabla) break;
            draw_Piesa(piesaAleasa,i,j);
        }
    }
    }

}

void draw_Tabla(int marime_tabla)
{
    int i,j;
    for (i=1; i<=marime_tabla; i++)
    {
        for (j=1; j<=marime_tabla; j++)
        {
            piesaAleasa=Tabla[i][j];
            if(i == marime_tabla and j == marime_tabla) break;
            draw_Piesa(piesaAleasa,i,j);
        }
    }
}

void initializareTabla(int n)
{
    int i,j;
    for (i=1; i<=n; i++)
        for (j=1; j<=n; j++)
            Tabla[i][j]=0;
    Tabla[1][1] = 1;
    Tabla[n][n] = -1;

    //Bordare
    for(i = 1; i <= n; i++)
        Tabla[i][0] = -2;
    for(i = 1; i <= n; i++)
        Tabla[i][n+1] = -2;
    for(j = 1; j <= n; j++)
        Tabla[0][j] = -2;
    for(j = 1; j <= n; j++)
        Tabla[n+1][j] = -2;

}

void initializareTabla_Load4x4(int n)
{
    int i,j;
    for (i=1; i<=n; i++)
        for (j=1; j<=n; j++)
            Tabla[i][j]=0;
    Tabla4x4[1][1] = 1;
    Tabla4x4[n][n] = -1;

    //Bordare
    for(i = 1; i <= n; i++)
        Tabla4x4[i][0] = -2;
    for(i = 1; i <= n; i++)
        Tabla4x4[i][n+1] = -2;
    for(j = 1; j <= n; j++)
        Tabla4x4[0][j] = -2;
    for(j = 1; j <= n; j++)
        Tabla4x4[n+1][j] = -2;

}

void initializareTabla_Load5x5(int n)
{
    int i,j;
    for (i=1; i<=n; i++)
        for (j=1; j<=n; j++)
            Tabla[i][j]=0;
    Tabla5x5[1][1] = 1;
    Tabla5x5[n][n] = -1;

    //Bordare
    for(i = 1; i <= n; i++)
        Tabla5x5[i][0] = -2;
    for(i = 1; i <= n; i++)
        Tabla5x5[i][n+1] = -2;
    for(j = 1; j <= n; j++)
        Tabla5x5[0][j] = -2;
    for(j = 1; j <= n; j++)
        Tabla5x5[n+1][j] = -2;

}

void initializareTabla_Load6x6(int n)
{
    int i,j;
    for (i=1; i<=n; i++)
        for (j=1; j<=n; j++)
            Tabla[i][j]=0;
    Tabla6x6[1][1] = 1;
    Tabla6x6[n][n] = -1;

    //Bordare
    for(i = 1; i <= n; i++)
        Tabla6x6[i][0] = -2;
    for(i = 1; i <= n; i++)
        Tabla6x6[i][n+1] = -2;
    for(j = 1; j <= n; j++)
        Tabla6x6[0][j] = -2;
    for(j = 1; j <= n; j++)
        Tabla6x6[n+1][j] = -2;

}

void initializareTabla_Load7x7(int n)
{
    int i,j;
    for (i=1; i<=n; i++)
        for (j=1; j<=n; j++)
            Tabla[i][j]=0;
    Tabla7x7[1][1] = 1;
    Tabla7x7[n][n] = -1;

    //Bordare
    for(i = 1; i <= n; i++)
        Tabla7x7[i][0] = -2;
    for(i = 1; i <= n; i++)
        Tabla7x7[i][n+1] = -2;
    for(j = 1; j <= n; j++)
        Tabla7x7[0][j] = -2;
    for(j = 1; j <= n; j++)
        Tabla7x7[n+1][j] = -2;

}

void initializareTabla_Load8x8(int n)
{
    int i,j;
    for (i=1; i<=n; i++)
        for (j=1; j<=n; j++)
            Tabla[i][j]=0;
    Tabla8x8[1][1] = 1;
    Tabla8x8[n][n] = -1;

    //Bordare
    for(i = 1; i <= n; i++)
        Tabla8x8[i][0] = -2;
    for(i = 1; i <= n; i++)
        Tabla8x8[i][n+1] = -2;
    for(j = 1; j <= n; j++)
        Tabla8x8[0][j] = -2;
    for(j = 1; j <= n; j++)
        Tabla8x8[n+1][j] = -2;

}

void verificareDrum(int &directie, int linia, int coloana)
{
    int i = linia;
    int j = coloana;
    while(Tabla[i][j] != -1 && Tabla[i][j] != -2 && Tabla[i][j] != 0)
    {
        if(Tabla[i][j] == 1)
        {
            if(directie == 1)j++;
            if(directie == 2)j--;
            if(directie == 3)i++;
            if(directie == 4)i--;
            cout << linia << " " << coloana << " *" << directie <<"\n";
        }
        else if(Tabla[i][j] == 2)
        {
            if(directie == 1)
            {
                directie = 4;
                i--;
            }

            else  if(directie == 2)
            {
                directie = 3;
                i++;
            }

            else if(directie == 3)
            {
                directie = 2;
                j--;
            }

            else if(directie == 4)
            {
                directie = 1;
                j++;
            }
            cout << linia << " " << coloana << " " << directie <<"\n";

        }
        else if(Tabla[i][j] == 3)
        {
            if(directie == 1)
            {
                directie = 3;
                i++;
            }

            else if(directie == 2)
            {
                directie = 4;
                i--;
            }
            else if(directie == 3)
            {
                directie = 1;
                j++;
            }
            else if(directie == 4)
            {
                directie = 2;
                j--;
            }
            cout << linia << " " << coloana << " " << directie <<"\n";
        }

    }
    if(Tabla[i][j] == -1)
    {
        //bine = 0;
        cout<<"ai ajuns in coltul negru " << "\n";
        win(jucator);
    }


    if(Tabla[i][j] == -2)
    {
        //bine = 0;
        cout<<"ai iesit de pe tabla";
        lose(jucator);
    }
}

void verificareDrumC(int &directie, int linia, int coloana)
{
    int i = linia;
    int j = coloana;
    while(Tabla[i][j] != -1 && Tabla[i][j] != -2 && Tabla[i][j] != 0)
    {
        if(Tabla[i][j] == 1)
        {
            if(directie == 1)j++;
            if(directie == 2)j--;
            if(directie == 3)i++;
            if(directie == 4)i--;
            cout << linia << " " << coloana << " " << directie <<"\n";
        }
        else if(Tabla[i][j] == 2)
        {
            if(directie == 1)
            {
                directie = 4;
                i--;
            }

            else  if(directie == 2)
            {
                directie = 3;
                i++;
            }

            else if(directie == 3)
            {
                directie = 2;
                j--;
            }

            else if(directie == 4)
            {
                directie = 1;
                j++;
            }
            cout << linia << " " << coloana << " " << directie <<"\n";

        }
        else if(Tabla[i][j] == 3)
        {
            if(directie == 1)
            {
                directie = 3;
                i++;
            }

            else if(directie == 2)
            {
                directie = 4;
                i--;
            }
            else if(directie == 3)
            {
                directie = 1;
                j++;
            }
            else if(directie == 4)
            {
                directie = 2;
                j--;
            }
            cout << linia << " " << coloana << " " << directie <<"\n";
        }

    }
    if(Tabla[i][j] == -1)
    {
        PlayerVsComputer_win(jucator);
    }


    if(Tabla[i][j] == -2)
    {

        cout<<"ai iesit de pe tabla";
        PlayerVsComputer_lose(jucator);
    }
}

void directieInceput(int &directie, int linia, int coloana, int &confirm)
{
    confirm = 1;
    if(linia == 2 && coloana == 1 && Tabla[linia][coloana] != 0 && Tabla[1][2] == 0) directie = 3;
    else if(linia == 1 && coloana == 2 && Tabla[linia][coloana] != 0 && Tabla[2][1] == 0) directie = 1;
    else if(linia == 2 && coloana == 1 && Tabla[linia][coloana] == 2 && Tabla[1][2] == 0)
    {
        confirm = 0;
        PlayerVsComputer_lose(jucator);
    }
    else if(linia == 1 && coloana == 2 && Tabla[linia][coloana] == 2 && Tabla[2][1] == 0)
    {
        confirm = 0;
        PlayerVsComputer_lose(jucator);
    }
    else if(Tabla[linia][coloana] == 1 && Tabla[linia-1][coloana] == 1 && directie == 1) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia-1][coloana] == 1 && directie == 2) confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia-1][coloana] == 1 && directie == 1) confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia-1][coloana] == 1 && directie == 2) confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia-1][coloana] == 1 && directie == 1) confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia-1][coloana] == 1 && directie == 2) confirm = 0;

    else if(Tabla[linia][coloana] == 1 && Tabla[linia+1][coloana] == 1 && directie == 1) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia+1][coloana] == 1 && directie == 2) confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia+1][coloana] == 1 && directie == 1) confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia+1][coloana] == 1 && directie == 2) confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia+1][coloana] == 1 && directie == 1) confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia+1][coloana] == 1 && directie == 2) confirm = 0;

    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana-1] == 1 && directie == 3) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana-1] == 1 && directie == 4) confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia][coloana-1] == 1 && directie == 3) confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia][coloana-1] == 1 && directie == 4) confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia][coloana-1] == 1 && directie == 3) confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia][coloana-1] == 1 && directie == 4) confirm = 0;

    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana+1] == 1 && directie == 3) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana+1] == 1 && directie == 4) confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia][coloana+1] == 1 && directie == 3) confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia][coloana+1] == 1 && directie == 4) confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia][coloana+1] == 1 && directie == 3) confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia][coloana+1] == 1 && directie == 4) confirm = 0;

    else if(Tabla[linia][coloana] == 1 && Tabla[linia-1][coloana] == 2 && Tabla[linia-2][coloana]
            && directie == 1) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia-1][coloana] == 2 && Tabla[linia-2][coloana]
            && directie == 2) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia+1][coloana] == 2 && Tabla[linia+2][coloana]
            && directie == 1) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia+1][coloana] == 2 && Tabla[linia+2][coloana]
            && directie == 2) confirm = 0;

    else if(Tabla[linia][coloana] == 1 && Tabla[linia-1][coloana] == 3 && Tabla[linia-2][coloana]
            && directie == 1) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia-1][coloana] == 3 && Tabla[linia-2][coloana]
            && directie == 2) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia+1][coloana] == 3 && Tabla[linia+2][coloana]
            && directie == 1) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia+1][coloana] == 3 && Tabla[linia+2][coloana]
            && directie == 2) confirm = 0;

    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana-1] == 2 && Tabla[linia][coloana-2]
            && directie == 3) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana-1] == 2 && Tabla[linia][coloana-2]
            && directie == 4) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana+1] == 2 && Tabla[linia][coloana+2]
            && directie == 3) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana+1] == 2 && Tabla[linia][coloana+2]
            && directie == 4) confirm = 0;

    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana-1] == 3 && Tabla[linia][coloana-2]
            && directie == 3) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana-1] == 3 && Tabla[linia][coloana-2]
            && directie == 4) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana+1] == 3 && Tabla[linia][coloana+2]
            && directie == 3) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana+1] == 3 && Tabla[linia][coloana+2]
            && directie == 4) confirm = 0;

    else if(Tabla[linia][coloana] == 2 && Tabla[linia][coloana-1] == 1 && directie == 4)
        confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia][coloana-1] == 1 && directie == 3)
        confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia][coloana+1] == 1 && directie == 4)
        confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia][coloana+1] == 1 && directie == 3)
        confirm = 0;

    else if(Tabla[linia][coloana] == 2 && Tabla[linia-1][coloana] == 1 && directie == 1)
        confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia-1][coloana] == 1 && directie == 2)
        confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia+1][coloana] == 1 && directie == 1)
        confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia+1][coloana] == 1 && directie == 2)
        confirm = 0;

    else if(Tabla[linia][coloana] == 3 && Tabla[linia][coloana-1] == 1 && directie == 4)
        confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia][coloana-1] == 1 && directie == 3)
        confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia][coloana+1] == 1 && directie == 4)
        confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia][coloana+1] == 1 && directie == 3)
        confirm = 0;

    else if(Tabla[linia][coloana] == 3 && Tabla[linia-1][coloana] == 1 && directie == 1)
        confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia-1][coloana] == 1 && directie == 2)
        confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia+1][coloana] == 1 && directie == 1)
        confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia+1][coloana] == 1 && directie == 2)
        confirm = 0;

    else if(Tabla[linia][coloana] == 2 && Tabla[linia][coloana-1] == 3 && directie == 3)
        confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia][coloana-1] == 3 && directie == 4)
        confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia][coloana-1] == 2 && directie == 3)
        confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia][coloana-1] == 2 && directie == 4)
        confirm = 0;

    else if(Tabla[linia][coloana] == 2 && Tabla[linia-1][coloana] == 3 && directie == 1)
        confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia-1][coloana] == 3 && directie == 2)
        confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia-1][coloana] == 2 && directie == 1)
        confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia-1][coloana] == 2 && directie == 2)
        confirm = 0;

    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana-1] == 1 && directie == 1)
        confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana-1] == 1 && directie == 2)
        confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana+1] == 1 && directie == 1)
        confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana+1] == 1 && directie == 2)
        confirm = 0;

    else if(Tabla[linia][coloana] == 1 && Tabla[linia-1][coloana] == 1 && directie == 3)
        confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia-1][coloana] == 1 && directie == 4)
        confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia+1][coloana] == 1 && directie == 3)
        confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia+1][coloana] == 1 && directie == 4)
        confirm = 0;

    cout << linia << " "<< coloana << " " << directie << "\n";

}

void directieInceputC(int &directie, int linia, int coloana, int &confirm)
{
    confirm = 1;
    if(linia == 2 && coloana == 1 && Tabla[linia][coloana] != 0 && Tabla[1][2] == 0) directie = 3;
    else if(linia == 1 && coloana == 2 && Tabla[linia][coloana] != 0 && Tabla[2][1] == 0) directie = 1;
    else if(linia == 2 && coloana == 1 && Tabla[linia][coloana] == 2 && Tabla[1][2] == 0)
    {
        confirm = 0;
        PlayerVsComputer_lose(jucator);
    }
    else if(linia == 1 && coloana == 2 && Tabla[linia][coloana] == 2 && Tabla[2][1] == 0)
    {
        confirm = 0;
        PlayerVsComputer_lose(jucator);
    }
    else if(Tabla[linia][coloana] == 1 && Tabla[linia-1][coloana] == 1 && directie == 1) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia-1][coloana] == 1 && directie == 2) confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia-1][coloana] == 1 && directie == 1) confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia-1][coloana] == 1 && directie == 2) confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia-1][coloana] == 1 && directie == 1) confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia-1][coloana] == 1 && directie == 2) confirm = 0;

    else if(Tabla[linia][coloana] == 1 && Tabla[linia+1][coloana] == 1 && directie == 1) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia+1][coloana] == 1 && directie == 2) confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia+1][coloana] == 1 && directie == 1) confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia+1][coloana] == 1 && directie == 2) confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia+1][coloana] == 1 && directie == 1) confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia+1][coloana] == 1 && directie == 2) confirm = 0;

    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana-1] == 1 && directie == 3) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana-1] == 1 && directie == 4) confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia][coloana-1] == 1 && directie == 3) confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia][coloana-1] == 1 && directie == 4) confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia][coloana-1] == 1 && directie == 3) confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia][coloana-1] == 1 && directie == 4) confirm = 0;

    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana+1] == 1 && directie == 3) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana+1] == 1 && directie == 4) confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia][coloana+1] == 1 && directie == 3) confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia][coloana+1] == 1 && directie == 4) confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia][coloana+1] == 1 && directie == 3) confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia][coloana+1] == 1 && directie == 4) confirm = 0;

    else if(Tabla[linia][coloana] == 1 && Tabla[linia-1][coloana] == 2 && Tabla[linia-2][coloana]
            && directie == 1) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia-1][coloana] == 2 && Tabla[linia-2][coloana]
            && directie == 2) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia+1][coloana] == 2 && Tabla[linia+2][coloana]
            && directie == 1) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia+1][coloana] == 2 && Tabla[linia+2][coloana]
            && directie == 2) confirm = 0;

    else if(Tabla[linia][coloana] == 1 && Tabla[linia-1][coloana] == 3 && Tabla[linia-2][coloana]
            && directie == 1) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia-1][coloana] == 3 && Tabla[linia-2][coloana]
            && directie == 2) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia+1][coloana] == 3 && Tabla[linia+2][coloana]
            && directie == 1) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia+1][coloana] == 3 && Tabla[linia+2][coloana]
            && directie == 2) confirm = 0;

    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana-1] == 2 && Tabla[linia][coloana-2]
            && directie == 3) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana-1] == 2 && Tabla[linia][coloana-2]
            && directie == 4) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana+1] == 2 && Tabla[linia][coloana+2]
            && directie == 3) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana+1] == 2 && Tabla[linia][coloana+2]
            && directie == 4) confirm = 0;

    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana-1] == 3 && Tabla[linia][coloana-2]
            && directie == 3) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana-1] == 3 && Tabla[linia][coloana-2]
            && directie == 4) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana+1] == 3 && Tabla[linia][coloana+2]
            && directie == 3) confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana+1] == 3 && Tabla[linia][coloana+2]
            && directie == 4) confirm = 0;

    else if(Tabla[linia][coloana] == 2 && Tabla[linia][coloana-1] == 1 && directie == 4)
        confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia][coloana-1] == 1 && directie == 3)
        confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia][coloana+1] == 1 && directie == 4)
        confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia][coloana+1] == 1 && directie == 3)
        confirm = 0;

    else if(Tabla[linia][coloana] == 2 && Tabla[linia-1][coloana] == 1 && directie == 1)
        confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia-1][coloana] == 1 && directie == 2)
        confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia+1][coloana] == 1 && directie == 1)
        confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia+1][coloana] == 1 && directie == 2)
        confirm = 0;

    else if(Tabla[linia][coloana] == 3 && Tabla[linia][coloana-1] == 1 && directie == 4)
        confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia][coloana-1] == 1 && directie == 3)
        confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia][coloana+1] == 1 && directie == 4)
        confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia][coloana+1] == 1 && directie == 3)
        confirm = 0;

    else if(Tabla[linia][coloana] == 3 && Tabla[linia-1][coloana] == 1 && directie == 1)
        confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia-1][coloana] == 1 && directie == 2)
        confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia+1][coloana] == 1 && directie == 1)
        confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia+1][coloana] == 1 && directie == 2)
        confirm = 0;

    else if(Tabla[linia][coloana] == 2 && Tabla[linia][coloana-1] == 3 && directie == 3)
        confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia][coloana-1] == 3 && directie == 4)
        confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia][coloana-1] == 2 && directie == 3)
        confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia][coloana-1] == 2 && directie == 4)
        confirm = 0;

    else if(Tabla[linia][coloana] == 2 && Tabla[linia-1][coloana] == 3 && directie == 1)
        confirm = 0;
    else if(Tabla[linia][coloana] == 2 && Tabla[linia-1][coloana] == 3 && directie == 2)
        confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia-1][coloana] == 2 && directie == 1)
        confirm = 0;
    else if(Tabla[linia][coloana] == 3 && Tabla[linia-1][coloana] == 2 && directie == 2)
        confirm = 0;

    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana-1] == 1 && directie == 1)
        confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana-1] == 1 && directie == 2)
        confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana+1] == 1 && directie == 1)
        confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia][coloana+1] == 1 && directie == 2)
        confirm = 0;

    else if(Tabla[linia][coloana] == 1 && Tabla[linia-1][coloana] == 1 && directie == 3)
        confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia-1][coloana] == 1 && directie == 4)
        confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia+1][coloana] == 1 && directie == 3)
        confirm = 0;
    else if(Tabla[linia][coloana] == 1 && Tabla[linia+1][coloana] == 1 && directie == 4)
        confirm = 0;


    cout << linia << " "<< coloana << " " << directie << "\n";

}

int directie = 0;

void punerePiesa_Computer(int n)
{
    int liniaC, coloanaC, piesaAleasaC, corect , ok = 0;
    srand(time(0));
    while(ok == 0)
    {
        liniaC = (rand()%n) + 1;
        coloanaC = (rand()%n) + 1;
        piesaAleasaC = (rand()%2) + 2;
        if(Tabla[liniaC][coloanaC-1] > 0 || Tabla[liniaC][coloanaC+1] > 0 ||
                   Tabla[liniaC-1][coloanaC] > 0 || Tabla[liniaC+1][coloanaC] > 0)
                   {
                       if(Tabla[liniaC][coloanaC] == 0)
                       {
                       cout<<"AI ul a ales piesa "<<piesaAleasaC<<"\n";
                       ok = 1;
                       Tabla[liniaC][coloanaC] = piesaAleasaC;
                       draw_Piesa(piesaAleasaC,liniaC,coloanaC);
                       //PlaySound(TEXT("clicksound.wav"), NULL, SND_SYNC);
                       cout<<"pc ul pune piesa "<<piesaAleasaC<<" pe linia " << liniaC << " si coloana " << coloanaC<<"\n";
                       directieInceputC(directie, liniaC, coloanaC, corect);
                       if(corect == 1) verificareDrumC(directie, liniaC, coloanaC);
                       }
                   }
    }
}

void punerePiesa2(int n)
{
    int linia, coloana, x, y, corect;
    int stanga = 200, sus = 200;
    int dreapta = 200 + 50 * n, jos = 200 + 50 * n;
            //clearmouseclick(WM_LBUTTONDOWN);
    //getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);
    cursorX = mousex();
    cursorY = mousey();
        if (cursorX>=stanga and cursorX<=dreapta and cursorY>=sus and cursorY<=jos)
        {
            linia=(cursorY-sus)/50+1;
            coloana=(cursorX-stanga)/50+1;
            if(piesaAleasa != 0)

            {
                if(Tabla[linia][coloana-1] > 0 || Tabla[linia][coloana+1] > 0 ||
                   Tabla[linia-1][coloana] > 0 || Tabla[linia+1][coloana] > 0)//pun piesele doar pe pozitii vecine
                    if (Tabla[linia][coloana] == 0)
                    {
                        Tabla[linia][coloana] = piesaAleasa;
                        draw_Piesa(piesaAleasa,linia,coloana);
                        //PlaySound(TEXT("clicksound.wav"), NULL, SND_SYNC);
                        directieInceputC(directie, linia, coloana, corect);
                        if(corect == 1) verificareDrumC(directie, linia, coloana);
                        jucator = 1;
                    }
            }
            else if(piesaAleasa == 0)
            {
                if(linia != 1 || coloana != 1)
                {
                    Tabla[linia][coloana] = 0;
                    verificareDrum(directie, linia, coloana);
                    draw_Piesa(0, linia, coloana);
                    //cout<<"-------------------------";
                }
            }
        }
}


bool punerePiesa(int n) // n = dimensiunea tablei
{
    int linia, coloana, x, y, corect;
    int stanga = 200, sus = 200;
    int dreapta = 200 + 50 * n, jos = 200 + 50 * n;
    bool ok = false;
    if(ismouseclick(WM_LBUTTONDOWN))
    {
            clearmouseclick(WM_LBUTTONDOWN);
    //getmouseclick(WM_LBUTTONDOWN, cursorX, cursorY);
    cursorX = mousex();
    cursorY = mousey();
        if (cursorX>=stanga and cursorX<=dreapta and cursorY>=sus and cursorY<=jos)
        {
            linia=(cursorY-sus)/50+1;
            coloana=(cursorX-stanga)/50+1;
            if(piesaAleasa != 0)
            {
                if(Tabla[linia][coloana-1] > 0 || Tabla[linia][coloana+1] > 0 ||
                   Tabla[linia-1][coloana] > 0 || Tabla[linia+1][coloana] > 0)//pun piesele doar pe pozitii vecine
                    if (Tabla[linia][coloana] == 0)
                    {
                        Tabla[linia][coloana] = piesaAleasa;
                        draw_Piesa(piesaAleasa,linia,coloana);
                        //PlaySound(TEXT("clicksound.wav"), NULL, SND_SYNC);
                        directieInceput(directie, linia, coloana, corect);
                        if(corect == 1) verificareDrum(directie, linia, coloana);
                        ok=true;
                    }
            }
            else if(piesaAleasa == 0)
            {
                if(linia != 1 || coloana != 1)
                {
                    Tabla[linia][coloana] = 0;
                    verificareDrum(directie, linia, coloana);
                    draw_Piesa(0, linia, coloana);
                    ok = true;
                    //cout<<"-------------------------";
                }
            }
        }
    }
    return ok;
}

int main()
{
    startMenu();

    getch(); closegraph();
    return 0;
}
