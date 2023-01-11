#include <iostream>
#include <fstream>
#include <graphics.h>
#include <winbgim.h>
#include <windows.h>
#include <mmsystem.h>
#define DIM 650
#define LMAX 10

using namespace std;

ifstream citeste("culori.in");
ifstream fin("istoric.txt");
std::ofstream outfile;

int n,s,inceput,sfarsit;
int nr_citire=0;
int color1=9; //albastru
int color2=13; //rosu
int nr_culori=15;
int joc;
int player=3;
int replay=0;
int limbaj=0;
int h_accesat=0;
int k=1, muzica=0;

char M[LMAX][LMAX];
bool baza[LMAX][LMAX];

//toate functiile folosite
char tip_joc(); //determina daca e multiplayer sau singleplayer
char joc_multiplayer();
char joc_singleplayer();
void afisare_tabla(); //afiseaza in consola
void tabla_initiala();
void deseneaza_tabla();
bool citire_albastru();
bool citire_rosu();
bool Lee_albastru(); //verifica daca albastru(prima culoare) este in stare castigatoare
bool Lee_rosu();//verifica daca rosu(a doua culoare) este in stare castigatoare
bool deasupra(int &xx, int &yy,int xi,int xo,int yi,int yo); //cat timp este intre xi,xo,yi,yo
void bordare(int L[LMAX][LMAX]); //se foloseste la Lee
void bkt(int L[LMAX][LMAX],int l, int c, int lo, int co, int &sol); //se foloseste la Lee
void afla(int &i, int y); //afla pozitia unei casute stiind coordonatele- se afla coloana stiind x si linia stiind y
void meniu();
void play();
void lungime(); //iti alegi marimea tablei de joc
void alege_culori(); //alegi ce culori vrei sa folosesti
void citeste_culori(); //se citesc dintr-un fisier atasat perechile de culori si se pun in structul culori
void genereaza_albastru(); //miscarea calculatorului, cand te joci cu calculatorul si esti rosu
void genereaza_rosu(); //miscarea calculatorului, cand te joci cu calculatorul si esti albastru
void vezi_miscari();
void limba();
void ajutor();
void history();
void titlescreen();
void music();
void pune_beep();
void fundal_alb();
void tip_font(int marime, int color, char tip);


struct culori
{
    short int unu;
    short int doi;
} culoare[15];

struct istoric_miscari
{
    short int ii;
    short int jj;
} istoric[100];

struct jocuri_trecute
{
    int lg;
    int nr;
    int culoare1;
    int culoare2;
    istoric_miscari miscari_ordine[100];
} jocuri[100];

int main()
{
    initwindow(DIM,DIM);
    titlescreen();
    meniu();
    closegraph();
    return 0;
}

void meniu()
{
    replay=0;
    fundal_alb();
    setcolor(DARKGRAY);
    line(DIM/2,1,DIM/2,DIM);
    tip_font(6,BLACK,'t');
    if(limbaj==1)
        outtextxy(215, 50, "Meniu");
    else
        outtextxy(230, 50, "Menu");
    bool gata=false;
    while(!gata)
    {
        tip_font(4,BLACK,'t');
        if(limbaj==1)
            outtextxy(265, 150, "Joaca");
        else if(limbaj==0)
            outtextxy(280, 150, "Play");
        else if(limbaj==2)
            outtextxy(265, 150, "Jugar");


        if(limbaj==1)
            outtextxy(255, 230, "Limba");
        else if(limbaj==0)
            outtextxy(223, 230, "Language");
        else if(limbaj==2)
            outtextxy(250, 230, "Idioma");

        if(limbaj==1)
            outtextxy(263, 310, "Sunet");
        else if(limbaj==0)
            outtextxy(253, 310, "Sound");
        else if(limbaj==2)
            outtextxy(250, 310, "Sonido");

        if(limbaj==1)
            outtextxy(257, 390, "Istoric");
        else if(limbaj==0)
            outtextxy(250, 390, "History");
        else if(limbaj==2)
            outtextxy(230, 390, "Historica");

        if(limbaj==1)
            outtextxy(260, 470, "Ajutor");
        else if(limbaj==0)
            outtextxy(275, 470, "Help");
        else if(limbaj==2)
            outtextxy(257, 470, "Ayuda");
        int xx,yy;
        xx=mousex();
        yy=mousey();
        if(xx>=265&&xx<=380&&yy>=150&&yy<=200) //dimensiuni scris din meniu - PLAY
        {
            tip_font(4,12,'t');
            if(limbaj==1)
                outtextxy(265, 150, "Joaca");
            else if(limbaj==0)
                outtextxy(280, 150, "Play");
            else if(limbaj==2)
                outtextxy(265, 150, "Jugar");
            gata=deasupra(xx,yy,265,380,150,200);
            if(gata==true)
                play();
        }
        else if(xx>=223&&xx<=400&&yy>=230&&yy<=280) //Language --se pun if-uri acolo unde e scris in engleza
        {
            tip_font(4,10,'t'); //marime,culoare
            if(limbaj==1)
                outtextxy(255, 230, "Limba");
            else if(limbaj==0)
                outtextxy(223, 230, "Language");
            else if(limbaj==2)
                outtextxy(250, 230, "Idioma");
            gata=deasupra(xx,yy,223,400,230,280);
            if(gata==true)
                limba();
        }
        else if(xx>=253&&xx<=363&&yy>=310&&yy<=360) //music/sound
        {
            tip_font(4,10,'t');//marime,culoare
            if(limbaj==1)
                outtextxy(263, 310, "Sunet");
            else if(limbaj==0)
                outtextxy(253, 310, "Sound");
            else if(limbaj==2)
                outtextxy(250, 310, "Sonido");
            gata=deasupra(xx,yy,253,363,310,360);
            if(gata==true)
                music();
        }
        else if(xx>=250&&xx<=400&&yy>=390&&yy<=440) //history
        {
            tip_font(4,13,'t');
            if(limbaj==1)
                outtextxy(257, 390, "Istoric");
            else if(limbaj==0)
                outtextxy(250, 390, "History");
            else if(limbaj==2)
                outtextxy(230, 390, "Historica");
            gata=deasupra(xx,yy,250,400,390,440);
            if(gata==true)
                history();
        }
        else if(xx>=260&&xx<=380&&yy>=470&&yy<=520) //help/ajutor
        {
            tip_font(4,9,'t');
            if(limbaj==1)
                outtextxy(260, 470, "Ajutor");
            else if(limbaj==0)
                outtextxy(275, 470, "Help");
            else if(limbaj==2)
                outtextxy(257, 470, "Ayuda");
            gata=deasupra(xx,yy,260,380,470,520);
            if(gata==true)
                ajutor();
        }
        else if(ismouseclick(WM_LBUTTONDOWN))
            clearmouseclick(WM_LBUTTONDOWN);

    }
}
void titlescreen()
{
    muzica=1;
    PlaySound(TEXT("OldBossa.wav"),NULL,SND_ASYNC | SND_LOOP);
    setactivepage(0);
    setbkcolor(WHITE);
    clearviewport();
    readimagefile("ss4.bmp", getmaxx()/2-204,getmaxy()/11,getmaxx()/2+204,getmaxy()/11+300);
    tip_font(7,DARKGRAY,'b');
    outtextxy(175,370,"BRIDG-IT");
    tip_font(4,DARKGRAY,'b');//dimensiune,culoare,tip
    outtextxy(195,460," PRESENTED BY ");
    outtextxy(33,495," CLARA SIMA & ROBERT BODOLICA ");
    Sleep(2000);
    clearviewport();
}
void ajutor()
{
    fundal_alb();
    tip_font(4,9,'b');
    outtextxy(250,10, "TUTORIAL");
    tip_font(3,9,'b');
    if (limbaj==1)
        outtextxy(5,10, "MENIU");
    else
        outtextxy(5,10, "MENU");
    if(limbaj==0)
    {
        outtextxy(5,55, "Bridg-It is a simple connection board game");
        outtextxy(5,75, "that was created around 1960 by a man named                               ");
        outtextxy(5,95, "David Gale.                                                                 ");
        outtextxy(5,125, "It is a two-player game and the board                                      ");
        outtextxy(5,145, "consists rectangular arrays of dots, one                                     ");
        outtextxy(5,165, "array for each player.                                                                    ");
        outtextxy(5,195, "The players move by alternately connecting                                            ");
        outtextxy(5,215, "two dots within their array to form a                                                   ");
        outtextxy(5,235, "line or bridge.");
        outtextxy(5,265, "The objective for player one is to build a                                                     ");
        outtextxy(5,285, "bridge from left to right and the objective                                              ");
        outtextxy(5,305, "for player two is to build a bridge from top                                                 ");
        outtextxy(5,325, "to bottom.                                                       ");
        outtextxy(5,355, "The player who is first to create a bridge                                 ");
        outtextxy(5,375, "that connects their opposite edges of the                                  ");
        outtextxy(5,395, "board, wins.                                          ");
        outtextxy(5,425, "The rules to play Bridg-It are as follows:                                        ");
        outtextxy(5,445, "players take turns connecting two adjacent                                        ");
        outtextxy(5,465, "dots of their own color with a bridge.                                        ");
        outtextxy(5,485, "Adjacent dots are considered to be dots                                       ");
        outtextxy(5,505, "directly above, below, to the right, or to                                      ");
        outtextxy(5,525, "the left of another dot with the same color.                           ");
        outtextxy(5,555, "A newly formed bridge cannot cross a bridge                                ");
        outtextxy(5,575, "already played  and whoever connects their                                    ");
        outtextxy(5,595, "opposite edges of the board first wins.                                      ");
    }
    else if(limbaj==1)
    {
        outtextxy(5,55, "Bridg-It un simplu joc de conectare, creat                             ");
        outtextxy(5,75, "in jurul anului 1960 de catre un om pe nume                          ");
        outtextxy(5,95, "David Gale.                                                                 ");
        outtextxy(5,125, "Este un joc cu doi jucatori, iar tabla consta                                  ");
        outtextxy(5,145, "din doua tablouri dreptunghiulare cu puncte,                                    ");
        outtextxy(5,165, "cate un tablou pentru fiecare jucator.                                                                   ");
        outtextxy(5,195, "Jucatorii se misca conectand alternativ doua                                          ");
        outtextxy(5,215, "puncte in cadrul tabloului lor pentru a forma                                                    ");
        outtextxy(5,235, "o linie sau un pod.");
        outtextxy(5,265, "Obiectivul pentru jucatorul unu este constru-                                                    ");
        outtextxy(5,285, "irea unui pod de la stanga la dreapta, iar                                            ");
        outtextxy(5,305, "obiectivul pentru jucatorul doi este sa con-                                                ");
        outtextxy(5,325, "struiasca un pod de sus in jos.                                                       ");
        outtextxy(5,355, "Jucatorul care este primul ce creeaza un pod                                  ");
        outtextxy(5,375, "care leaga marginile opuse ale tabloului de                                 ");
        outtextxy(5,395, "joc, castiga.                                         ");
        outtextxy(5,425, "Regulile pentru a juca Bridg-It sunt urmatoa-                                       ");
        outtextxy(5,445, "rele: juctorii fac ture conectand doua puncte                                       ");
        outtextxy(5,465, "adiacente de propria culoare cu un pod.                                        ");
        outtextxy(5,495, "Punctele adiacente sunt considerate puncte ca-                                     ");
        outtextxy(5,515, "re sunt direct deasupra, dedesubt, la dreapta                                     ");
        outtextxy(5,535, "sau la stanga unui alt punct cu aceeasi culoa-                          ");
        outtextxy(5,555, "re. Un pod nou format nu poate traversa un pod                                ");
        outtextxy(5,575, "deja format si cine reuseste sa conecteze mar-                                     ");
        outtextxy(5,595, "ginile opuse ale tabloului primul, castiga.                                 ");
    }
    else if(limbaj==2)
    {

        outtextxy(5,55, "Bridg-It es un juego de mesa de conexión                               ");
        outtextxy(5,75, "simple que fue creado alrededor de 1960 por                               ");
        outtextxy(5,95, "un hombre llamado David Gale.                                                                ");
        outtextxy(5,125, "Es un juego de dos jugadores y el tablero                                      ");
        outtextxy(5,145, "consta de dos conjuntos rectangulares de                                    ");
        outtextxy(5,165, "puntos, un conjunto para cada jugador.                                                                    ");
        outtextxy(5,195, "Los jugadores se mueven conectando                                            ");
        outtextxy(5,215, "alternativamente dos puntos dentro de su                                               ");
        outtextxy(5,235, "matriz para formar una línea o puente.");
        outtextxy(5,265, "El objetivo para el jugador uno es construir                                                     ");
        outtextxy(5,285, "un puente de izquierda a derecha y el                                               ");
        outtextxy(5,305, "objetivo para el jugador dos es construir                                                  ");
        outtextxy(5,325, "un puente de arriba a abajo fondo.                                                        ");
        outtextxy(5,355, "El jugador que es el primero en crear un                                  ");
        outtextxy(5,375, "puente que conecta sus bordes opuestos del                                   ");
        outtextxy(5,395, "tablero, gana.                                         ");
        outtextxy(5,425, "Las reglas para jugar Bridg-It son las                                         ");
        outtextxy(5,445, "siguientes: los jugadores se turnan para                                       ");
        outtextxy(5,465, "conectar dos puntos adyacentes de su propio                                        ");
        outtextxy(5,485, "color con un puente.                                       ");
        outtextxy(5,505, "Los puntos adyacentes se consideran puntos                                      ");
        outtextxy(5,525, "directamente encima, debajo, a la derecha o                             ");
        outtextxy(5,545, "a la izquierda de otro punto del mismo color.                               ");
        outtextxy(5,575, "Un puente recién formado no puede cruzar un                                    ");
        outtextxy(5,595, "puente ya jugado y el que conecta sus bordes                                     ");
        outtextxy(5,615, "opuestos del tablero primero gana.                                    ");


    }

    bool gata=false;
    while(!gata)
    {
        int x,y;
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();

        }
        if(x>=5&&x<=50&&y>=10&&y<=30)
        {
            pune_beep();
            meniu();
            gata=true;
        }
    }
}
void music()
{
    fundal_alb();
    tip_font(3,BLACK,'t');
    rectangle(150,150,500,400);
    if (limbaj==1)
        outtextxy(265, 200, "SUNET");
    else if(limbaj==0)
        outtextxy(255, 200, "SOUND");
    else if(limbaj==2)
        outtextxy(250, 200, "SONIDO");
    setcolor(GREEN);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
    if (limbaj==1)
        outtextxy(195, 300, "Pornit");
    else if(limbaj==0)
        outtextxy(220, 300, "ON");
    else if(limbaj==2)
        outtextxy(300, 270, "EN");

    setcolor(RED);
    if (limbaj==1)
        outtextxy(360, 300, "Oprit");
    else if(limbaj==0)
        outtextxy(365, 300, "OFF");
    else if(limbaj==2)
        outtextxy(230, 300, "APAGADO");
    tip_font(2,BLACK,'t'); //dimensiune,culoare, tip(triplex sau bold)
    if (limbaj==1)
        outtextxy(5,10, "MENIU");
    else
        outtextxy(5,10, "MENU");
    bool gata=false;
    while(!gata)
    {
        int x,y;
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
        }
        if(limbaj==1 || limbaj==0)
        {
            if(x>=195&&x<=300&&y>=300&&y<=350)
            {
                pune_beep();
                muzica=1;
                PlaySound(TEXT("OldBossa.wav"),NULL,SND_ASYNC | SND_LOOP);
                music();
            }
            if(x>=360&&x<=460&&y>=300&&y<=350)
            {
                pune_beep();
                muzica=0;
                PlaySound(NULL,0,0);
                music();

            }
        }
        else if(limbaj==2)
        {
            if(x>=300&&x<=330&&y>=270&&y<=300)
            {
                pune_beep();
                muzica=1;
                PlaySound(TEXT("OldBossa.wav"),NULL,SND_ASYNC | SND_LOOP);
                music();
            }
            if(x>=230&&x<=330&&y>=300&&y<=340)
            {
                pune_beep();
                muzica=0;
                PlaySound(NULL,0,0);
                music();

            }
        }
        if(x>=5&&x<=100&&y>=10&&y<=50)
        {
            pune_beep();
            meniu();
            gata=true;
        }
    }
}
void limba()
{
    fundal_alb();
    tip_font(3,BLACK,'t'); //dimensiune,culoare, tip(triplex sau bold)
    rectangle(80,100,570,500);
    if (limbaj==1)
        outtextxy(220, 200, "Alege limba");
    else if(limbaj==0)
        outtextxy(160, 200, "Choose the language");
    else if(limbaj==2)
        outtextxy(200, 200, "Elige el idioma");
    if (limbaj==1)
    {
        setcolor(13);
        outtextxy(256, 300, "Romana");
    }
    else if(limbaj==0)
    {
        setcolor(BLACK);
        outtextxy(247, 300, "Romanian");
    }
    else if(limbaj==2)
    {
        setcolor(BLACK);
        outtextxy(256, 300, "Rumana");
    }


    if (limbaj==1)
    {
        setcolor(BLACK);
        outtextxy(260, 350, "Engleza");
    }
    else if(limbaj==0)
    {
        setcolor(13);
        outtextxy(260, 350, "English");
    }
    else if(limbaj==2)
    {
        setcolor(BLACK);
        outtextxy(266, 350, "Inglesa");
    }

    if (limbaj==1)
    {
        setcolor(BLACK);
        outtextxy(255, 400, "Spaniola");
    }
    else if(limbaj==0)
    {
        setcolor(BLACK);
        outtextxy(260, 400, "Spanish");
    }
    else if(limbaj==2)
    {
        setcolor(13);
        outtextxy(250, 400, "Espanola");
    }


    tip_font(2,BLACK,'t'); //dimensiune,culoare, tip(triplex sau bold)
    if (limbaj==1)
        outtextxy(5,10, "MENIU");
    else
        outtextxy(5,10, "MENU");
    bool gata=false;
    while(!gata)
    {
        int x,y;
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
        }
        if(x>=247&&x<=356&&y>=300&&y<=350)
        {
            pune_beep();
            limbaj=1;
            limba();
            gata=true;
        }
        if(x>=260&&x<=360&&y>=350&&y<=400)
        {
            pune_beep();
            limbaj=0;
            limba();
            gata=true;
        }
        if(x>=260&&x<=360&&y>=400&&y<=450)
        {
            pune_beep();
            limbaj=2;
            limba();
            gata=true;
        }
        if(x>=5&&x<=100&&y>=10&&y<=50)
        {
            pune_beep();
            meniu();
            gata=true;
        }
    }
}

void lungime()
{
    fundal_alb();
    tip_font(3,BLACK,'t');
    rectangle(100,150,550,400);
    if(limbaj==1)
        outtextxy(180, 200, "Alege lungimea:");
    else if(limbaj==0)
        outtextxy(170, 200, "Choose the length:");
    else if(limbaj==2)
        outtextxy(180, 200, "Elige la longitud:");


    bool gata=false;
    while(!gata)
    {
        setcolor(BLACK);
        outtextxy(155, 300, "3");
        outtextxy(315, 300, "4");
        outtextxy(475, 300, "5");
        int xx,yy;
        xx=mousex();
        yy=mousey();
        if(xx>=155&&xx<=200&&yy>=300&&yy<=350)
        {
            setcolor(3);
            outtextxy(155, 300, "3");
            gata=deasupra(xx,yy,155,200,300,350);
            if(gata==true)
            {
                n=3;
                inceput=200;
            }

        }
        else if(xx>=315&&xx<=350&&yy>=300&&yy<=350)
        {
            setcolor(5);
            outtextxy(315, 300, "4");
            gata=deasupra(xx,yy,315,350,300,350);
            if(gata==true)
            {
                n=4;
                inceput=150;
            }
        }
        else if(xx>=475&&xx<=525&&yy>=300&&yy<=350)
        {
            setcolor(1);
            outtextxy(475, 300, "5");
            gata=deasupra(xx,yy,475,525,300,350);
            if(gata==true)
            {
                n=5;
                inceput=125;
            }
        }
        else if(ismouseclick(WM_LBUTTONDOWN))
            clearmouseclick(WM_LBUTTONDOWN);
    }
    s=n*2-1;
    sfarsit=inceput+s*50;
}

void citeste_culori()
{
    for(int i=1; i<=nr_culori; i++)
        citeste>>culoare[i].unu>>culoare[i].doi;
}

void alege_culori()
{
    fundal_alb();
    tip_font(3,BLACK,'t');
    if(limbaj==1)
        outtextxy(100, 100, "Alege culorile pe care le vrei");
    else if(limbaj==0)
        outtextxy(100, 100, "Choose the colors you want");
    else if(limbaj==2)
        outtextxy(100, 100, "Elige los colores que quieras");

    citeste_culori();
    int nr=1;
    for(int x=75; x<=475; x+=200)
        for(int y=200; y<=600; y+=100)
        {
            char s[5];
            //pun in s numarul de ordine al perechii de culori
            if(nr<=9)
            {
                s[0]=nr+'0';
                s[1]='\0';
            }
            else
            {
                s[0]=nr/10+'0';
                s[1]=nr%10+'0';
                s[2]='\0';
            }
            //color1
            setcolor(culoare[nr].unu); //scriu cu prima culoare din sir numarul
            if(nr>9)
                outtextxy(x-70, y-10, s);
            else
                outtextxy(x-65, y-10, s);
            setfillstyle(SOLID_FILL,culoare[nr].unu);
            circle(x,y,25); //desenez un cerc cu prima culoare
            fillellipse(x,y,25,25);//umplu cercul
            //color2
            setcolor(culoare[nr].doi); //setez a doua culoare
            setfillstyle(SOLID_FILL,culoare[nr].doi);  //setez a doua culoare
            circle(x+75,y,25); //desenez un cerc cu a doua culoare
            fillellipse(x+75,y,25,25); //umplu cercul
            nr++;
        }
    bool gasit=0;
    while(!gasit)
    {
        int x,y;
        if(ismouseclick(WM_LBUTTONDOWN))  //cand se apasa pe setul de culori ales
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
        }
        nr=1;
        for(int j=75; !gasit&&j<=475; j+=200) //cautam setul de culori
            for(int i=200; !gasit&& i<=600; i+=100)
            {
                if(x>=j-70&&x<=j+100&&y>=i-10&&y<=i+50)
                {
                    pune_beep();
                    color1=culoare[nr].unu;             //am gasit setul de culori
                    color2=culoare[nr].doi;
                    gasit=1;
                }
                nr++;
            }
    }
    setcolor(WHITE);
    setfillstyle(SOLID_FILL,WHITE); //culoare pt fundal
}

char tip_joc()
{
    player=3; //joc cu doua persoane, daca player e 1 persoana care e joaca e jucatorul 1, iar daca player e 2 persoana care joaca e jucatorul 2
    fundal_alb();
    tip_font(4,BLACK,'t');
    rectangle(60,150,590,400);
    if(limbaj==1)
        outtextxy(110, 200, "Numarul jucatorilor:");
    else if(limbaj==0)
        outtextxy(155, 200, "Players number:");
    else if(limbaj==2)
        outtextxy(110, 200, "Numero de jugadores:");
    char c;
    bool gata=false;
    while(!gata)
    {
        int xx,yy;
        xx=mousex();
        yy=mousey();
        setcolor(BLACK);
        outtextxy(255, 300, "1");
        outtextxy(375, 300, "2");
        if(xx>=255&&xx<=280&&yy>=300&&yy<=350)
        {
            setcolor(color1);
            outtextxy(255, 300, "1");
            gata=deasupra(xx,yy,255,280,300,350);
            if(gata==true)
            {
                joc=1; //joc cu un jucator
                return 's'; //singleplayer
            }

        }
        else if(xx>=375&&xx<=400&&yy>=300&&yy<=350)
        {
            setcolor(color2);
            outtextxy(375, 300, "2");
            gata=deasupra(xx,yy,375,400,300,350);
            if(gata==true)
            {
                joc=2; //joc cu un jucator
                return 'm'; //singleplayer
            }
        }
        else if(ismouseclick(WM_LBUTTONDOWN))
            clearmouseclick(WM_LBUTTONDOWN);
    }
}

void play()
{
    lungime();
    alege_culori();
    char tip=tip_joc(); //cu un jucator sau cu doi
    tabla_initiala(); //punem pionii care sunt mereu in matrice
    afisare_tabla();//afiseaza in consola
    fundal_alb();

    char castigator;
    if(tip=='m')
        castigator=joc_multiplayer(); //castigatorul jocului cu 2 persoane
    else
        castigator=joc_singleplayer(); //castigatorul jocului contra calculatorului
    if(castigator=='a') //daca castiga primul jucator
    {
        cout<< "A castigat albastrul.";
        setcolor(color1);
        setfillstyle(SOLID_FILL,color1);
        circle(50,50,25);
        fillellipse(50,50,25,25);
        tip_font(4,color1,'t');
        if(player==3)
        {
            if(limbaj==1)
                outtextxy(77, 50, " a castigat.                                     ");
            else if(limbaj==0)
                outtextxy(77, 50, " has won.                                     "); //culoarea a castigat(joc cu 2 persoane)
            else if(limbaj==2)
                outtextxy(77, 50, " ha ganado.                                     ");
        }
        else if(player==1)
        {
            if(limbaj==1)
                outtextxy(77, 50, " TU AI CASTIGAT! :)                                 ");
            else if(limbaj==0)
                outtextxy(77, 50, " YOU WON! :)                                 "); //joc cu o singura persoana care castiga
            else if(limbaj==2)
                outtextxy(77, 50, " TU GANASTE! :)                                 ");
        }
        else
        {
            if(limbaj==1)
                outtextxy(77, 50, "Calculatorul a castigat.                        ");
            else if(limbaj==0)
                outtextxy(77, 50, "The computer won.                        "); //joc cu o singura persoana care castiga
            else if(limbaj==2)
                outtextxy(77, 50, "La computadora ganó.                       ");
        }
        char s[15];
        if(limbaj==1)
            outtextxy(25,600, "Arata mutarile!");
        else if(limbaj==0)
            outtextxy(25,600, "Show me the moves!");
        else if(limbaj==2)
            {
                settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
                outtextxy(15,590, "Muéstrame  los             ");
                outtextxy(15,610, " movimientos!              ");
            }
        setcolor(color2);
    }
    else
    {
        cout<< "A castigat rosul.";
        setcolor(color2);
        setfillstyle(SOLID_FILL,color2);
        circle(50,50,25);
        fillellipse(50,50,25,25);
        tip_font(4,color2,'t');
        if(player==3)
        {
            if(limbaj==1)
                outtextxy(77, 50, " a castigat.                                     ");
            else if(limbaj==0)
                outtextxy(77, 50, " has won.                                     "); //culoarea a castigat(joc cu 2 persoane)
            else if(limbaj==2)
                outtextxy(77, 50, " ha ganado.                                     ");
        }
        else if(player==2)
        {
            if(limbaj==1)
                outtextxy(77, 50, " TU AI CASTIGAT! :)                                 ");
            else if(limbaj==0)
                outtextxy(77, 50, " YOU WON! :)                                 "); //joc cu o singura persoana care castiga
            else if(limbaj==2)
                outtextxy(77, 50, " TU GANASTE! :)                                 ");
        }
        else
        {
            if(limbaj==1)
                outtextxy(77, 50, "Calculatorul a castigat.                        ");
            else if(limbaj==0)
                outtextxy(77, 50, "The computer won.                        "); //joc cu o singura persoana care castiga
            else if(limbaj==2)
                outtextxy(77, 50, "La computadora ganó.                       ");
        }
        setcolor(color1);
        if(limbaj==1)
            outtextxy(25,600, "Arata mutarile!");
        else if(limbaj==0)
            outtextxy(25,600, "Show me the moves!");
        else if(limbaj==2)
            {
                settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
                outtextxy(15,590, "Muéstrame  los             ");
                outtextxy(15,610, " movimientos!              ");
            }
        setcolor(color2);


    }
    outfile.open("istoric.txt", std::ios_base::app); //dechidem fisierul
    outfile<<s<<' '<<nr_citire<<' '<<color1<<' '<<color2<<'\n';
    for(int i=1; i<=nr_citire; i++)
    {
        outfile<< istoric[i].ii << ' ' <<istoric[i].jj << '\n';
    }
    outfile << '\n';
    outfile.close(); //inchidem fisierul
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
    if(limbaj==1)
        outtextxy(490, 600, "Meniu");
    else
        outtextxy(490, 600, "Menu");
    while(1)
    {
        int x,y;
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
        }
        if(x>=490&x<=DIM&&y>=600&&y<=DIM)
        {
            pune_beep();
            fundal_alb();
            meniu();
            break;
        }
        else if(x>=15&&x<=470&&y>=590&&y<=DIM)
        {
            pune_beep();
            fundal_alb();
            replay=1;
            vezi_miscari();
            break;
        }
    }
}

void vezi_miscari()
{
    int i;
    tabla_initiala();
    deseneaza_tabla();
    for(i=1; i<=nr_citire; i++)
    {
        setbkcolor(WHITE);
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
        char s[15];
        if(limbaj==1)
            strcpy(s,"MUTARI: ");
        else if(limbaj==0)
            strcpy(s,"MOVES: ");
        else if(limbaj==2)
        {
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            strcpy(s,"MOVIMIENTOS: ");
        }
        if(limbaj==1 || limbaj==0)
        {
            s[7]= (i-1)/10+'0';
            if(s[7]=='0')
            {
                s[7]=(i-1)%10+'0';
                s[8]= '\0';
            }
            else
            {
                s[8]=(i-1)%10+'0';
                s[9]= '\0';
            }
        }
        else
        {
            s[12]= (i-1)/10+'0';
            if(s[12]=='0')
            {
                s[12]=(i-1)%10+'0';
                s[13]= '\0';
            }
            else
            {
                s[13]=(i-1)%10+'0';
                s[14]= '\0';
            }

        }

        outtextxy(25,600, s);
        if(i%2==1)
            M[istoric[i].ii][istoric[i].jj]= 'a';
        else
            M[istoric[i].ii][istoric[i].jj]= 'r';
        delay(400);
        deseneaza_tabla();
    }
    setbkcolor(WHITE);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
    char s[25];
    if(limbaj==1)
        strcpy(s,"NUMAR MUTARI: ");
    else if(limbaj==0)
        strcpy(s,"TOTAL MOVES: ");
    else if(limbaj==2)
    {
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
        strcpy(s,"MOVIMIENTOS TOTALES: ");
    }
    if(limbaj==1 || limbaj==0)
    {
        s[13]= nr_citire/10+'0';
        if(s[13]=='0')
        {
            s[13]=nr_citire%10+'0';
            s[14]= '\0';
        }
        else
        {
            s[14]=nr_citire%10+'0';
            s[15]= '\0';
        }
    }
    else
    {
        s[21]= nr_citire/10+'0';
        if(s[21]=='0')
        {
            s[21]=nr_citire%10+'0';
            s[22]= '\0';
        }
        else
        {
            s[22]=nr_citire%10+'0';
            s[23]= '\0';
        }
    }

    outtextxy(25,600, s);
    if(limbaj==1 || limbaj==0)
        outtextxy(50, 50, "CLICK!                      ");
    else
        outtextxy(50, 50, "CLIC!                      ");
    while(1)
    {
        int x,y;
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            pune_beep();
            break;
        }
    }
    fundal_alb();
    meniu();
}


void tabla_initiala()
{
    for(int i=1; i<=s; i++)
        for(int j=1; j<=s; j++) //punem peste tot 0
        {
            M[i][j]='\0';
            baza[i][j]=0;
        }
    for(int i=1; i<=s; i+=2)
        for(int j=2; j<=s; j+=2)
        {
            M[i][j]='a';
            M[j][i]='r';
            baza[i][j]=baza[j][i]=1;
        }

}
char joc_multiplayer()
{
    deseneaza_tabla();
    int drum_rosu=0;
    int drum_albastru=0;
    nr_citire=0;
    while(drum_rosu==0&&drum_albastru==0)
    {
        setbkcolor(WHITE);
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
        char s[15];
        if(limbaj==1)
            strcpy(s,"MUTARI: ");
        else if(limbaj==0)
            strcpy(s,"MOVES: ");
        else if(limbaj==2)
        {
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            strcpy(s,"MOVIMIENTOS: ");
        }
        if(limbaj==1 || limbaj==0)
        {
            s[7]= nr_citire/10+'0';
            if(s[7]=='0')
            {
                s[7]=nr_citire%10+'0';
                s[8]= '\0';
            }
            else
            {
                s[8]=nr_citire%10+'0';
                s[9]= '\0';
            }
        }
        else
        {
            s[12]= nr_citire/10+'0';
            if(s[12]=='0')
            {
                s[12]=nr_citire%10+'0';
                s[13]= '\0';
            }
            else
            {
                s[13]=nr_citire%10+'0';
                s[14]= '\0';
            }

        }
        outtextxy(25,600, s);
        nr_citire++;
        bool u=false; //initial nu avem undo
        if(nr_citire%2==1) //daca nr de ordine e impar atunci primul jucator trage linie
        {
            u=citire_albastru(); //daca u e false atunci nu avem undo
            if(!u&&Lee_albastru()) //daca nu avem undo si putem catiga cu configuratia curenta
                drum_albastru=1; //avem un drum complet -> se va iesi din while -> se  transmite castigatorul
        }
        else //daca e par, al doilea trage linie
        {
            u=citire_rosu();
            if(!u&&Lee_rosu())
                drum_rosu=1;
        }
        afisare_tabla();
        deseneaza_tabla();
    }
    if(drum_albastru==1)
        return 'a';
    else
        return 'r';
}

void afisare_tabla()
{
    cout<< "  ";
    for(int i=1; i<=s; i++)
        cout<< i << ' '; //indici
    cout<< '\n';
    for(int i=1; i<=s; i++)
    {
        cout<< i << ' '; //indici
        for(int j=1; j<=s; j++)
            cout<< M[i][j] << ' ';
        cout<< '\n';
    }
    cout<< '\n';
}
void deseneaza_tabla()
{
    int x,y;
    tip_font(4,color2,'t');
    if(replay==0)
    {
        if(limbaj==1 || limbaj==0)
            outtextxy(480, 50, "UNDO");
        else
        {
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            outtextxy(400, 50, "DESHACER");
        }


    }
    citeste_culori();
    for(int i=1; i<=s; i++)
    {

        for(int j=1; j<=s; j++)
        {
            x=inceput+(2*j-1)*25;
            y=inceput+(2*i-1)*25;
            if(M[i][j]=='r')
            {
                setcolor(color2);
                setfillstyle(SOLID_FILL,color2);
                if(baza[i][j]==1) //este cerc rosu
                {
                    circle(x,y,25);
                    fillellipse(x,y,25,25);
                }
                else //este linie rosie
                {
                    if(M[i-1][j]=='r') // linie orizontala
                        bar(x-5,y-50,x+5,y+50);
                    else //este linie verticala
                        bar(x-50,y-5,x+50,y+5);

                }

            }
            else if(M[i][j]== 'a')
            {
                setcolor(color1);
                setfillstyle(SOLID_FILL,color1);
                if(baza[i][j]==1) //este cerc albastru
                {
                    circle(x,y,25);
                    fillellipse(x,y,25,25);
                }
                else //este linie albastra
                {
                    if(M[i-1][j]=='a') // linie orizontala
                        bar(x-5,y-50,x+5,y+50);
                    else //este linie verticala
                        bar(x-50,y-5,x+50,y+5);

                }
            }

        }
    }
}



bool citire_albastru()
{
    tip_font(4,color1,'t');
    setfillstyle(SOLID_FILL,color1);
    circle(50,50,25);
    fillellipse(50,50,25,25);
    if(limbaj==1)
        outtextxy(77, 50, "E randul tau.");
    else if(limbaj==0)
        outtextxy(77, 50, "It's your turn.");
    else if(limbaj==2)
        outtextxy(77, 50, "Es tu turno.");

    setcolor(color2);
    if(limbaj==1)
        outtextxy(490, 600, "Meniu");
    else
        outtextxy(490, 600, "Menu");
    int i,j;
    int x,y;
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
        }
        if(x>=inceput&&y>=inceput&&x<=sfarsit&&y<=sfarsit)
        {
            afla(i,y);
            afla(j,x);
            if(j>1&&j<s&&i>=1&&i<=s&&M[i][j]=='\0') //nu se citeste pe prima si ultima coloane din matrice
            {
                istoric[nr_citire].ii=i;
                istoric[nr_citire].jj=j;
                cout<< nr_citire<< ' ' <<istoric[nr_citire].ii<< ' ' <<istoric[nr_citire].jj<< '\n';
                M[i][j]='a';
                return false;
            }
        }
        else if(nr_citire>=2&&x>=500&&x<=600&&y>=50&&y<=100)  //Undo
        {
            setfillstyle(SOLID_FILL,WHITE);
            setcolor(WHITE);
            bar(0,0,DIM,DIM);
            nr_citire--;
            M[istoric[nr_citire].ii][istoric[nr_citire].jj]='\0';
            nr_citire--;
            if(joc==1&&nr_citire)
            {
                M[istoric[nr_citire].ii][istoric[nr_citire].jj]='\0';
                nr_citire--;
            }
            return true;
        }
        else if(x>=490&x<=DIM&&y>=600&&y<=DIM)
        {
            pune_beep();
            setfillstyle(SOLID_FILL,WHITE);
            bar(0,0,DIM,DIM);
            meniu();
            return true;
        }

    }

}

bool citire_rosu()
{
    tip_font(4,color2,'t');
    setfillstyle(SOLID_FILL,color2);
    circle(50,50,25);
    fillellipse(50,50,25,25);
    if(limbaj==1)
        outtextxy(77, 50, "E randul tau.");
    else if(limbaj==0)
        outtextxy(77, 50, "It's your turn.");
    else if(limbaj==2)
        outtextxy(77, 50, "Es tu turno.");
    if(limbaj==1)
        outtextxy(490, 600, "Meniu");
    else
        outtextxy(490, 600, "Menu");
    int i,j;
    int x,y;
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
        }
        if(x>=inceput&&y>=inceput&&x<=sfarsit&&y<=sfarsit)
        {
            afla(i,y);
            afla(j,x);
            if(j>=1&&j<=s&&i>1&&i<s&&M[i][j]=='\0') //nu se citeste pe prima si ultima linii din matrice
            {
                istoric[nr_citire].ii=i;
                istoric[nr_citire].jj=j;
                cout<< nr_citire<< ' ' <<istoric[nr_citire].ii<< ' ' <<istoric[nr_citire].jj<< '\n';
                M[i][j]='r';
                return false;
            }
        }
        else if(nr_citire>=2&&x>=500&&x<=600&&y>=50&&y<=100) //undo
        {
            setfillstyle(SOLID_FILL,WHITE);
            setcolor(WHITE);
            bar(0,0,DIM,DIM);
            nr_citire--;
            cout<< nr_citire<< ' ' <<istoric[nr_citire].ii<< ' ' <<istoric[nr_citire].jj<< '\n';
            M[istoric[nr_citire].ii][istoric[nr_citire].jj]='\0';
            nr_citire--;
            if(joc==1&&nr_citire)
            {
                M[istoric[nr_citire].ii][istoric[nr_citire].jj]='\0';
                nr_citire--;
            }

            return true;
        }
        else if(x>=490&x<=DIM&&y>=600&&y<=DIM)
        {
            pune_beep();
            setfillstyle(SOLID_FILL,WHITE);
            bar(0,0,DIM,DIM);
            meniu();
            return true;
        }
    }

}

void bordare(int L[LMAX][LMAX])
{
    for(int i=0; i<=n+1; i++)
        L[i][0]=L[i][n+1]=L[0][i]=L[n+1][i]=-1;
}

void bkt(int L[LMAX][LMAX], int l, int c, int lo, int co, int &sol)
{
    int l9,c9,k;
    int dl[]= {-1,0,1,0};
    int dc[]= {0,1,0,-1};

    if(l==lo&&c==co)
    {
        sol++;
    }
    else
    {
        for(k=0; sol==0&&k<4; k++)
        {
            l9=l+dl[k];
            c9=c+dc[k];
            if(L[l9][c9]==0)
            {
                L[l9][c9]=2;
                bkt(L,l9,c9,lo,co,sol);
                L[l9][c9]=0;
            }
        }
        L[l][c]=0;
    }
}

bool Lee_albastru()
{
    int L[LMAX][LMAX];
    bordare(L);
    for(int i=1; i<=s; i++)
        for(int j=1; j<=s; j++)
            if(M[i][j]=='a')
                L[i][j]=0;
            else
                L[i][j]=-1;

    int i,j,li,ci,lo,co;
    int sol=0;
    //verifica imaginea bi2
    for(i=2; sol==0&&i<=s; i+=2) // li ci - start M[1][i]
        for(j=2; sol==0&&j<=s; j+=2) // lo co - finish M[s-1][j]
        {
            li=1;
            ci=i;
            lo=s-1;
            co=j;
            L[li][ci]=2;
            bkt(L,li,ci,lo,co,sol);
            L[li][ci]=0;
        }

    if(sol==0)
        return false;
    else
        return true;
}

bool Lee_rosu()
{
    int L[LMAX][LMAX];
    bordare(L);
    for(int i=1; i<=s; i++)
        for(int j=1; j<=s; j++)
            if(M[i][j]=='r')
                L[i][j]=0;
            else
                L[i][j]=-1;

    int i,j,li,ci,lo,co;
    int sol=0;
    //verifica imaginea bi2
    for(i=2; sol==0&&i<=s; i+=2) // li ci - start M[i][1]
        for(j=2; sol==0&&j<=s; j+=2) // lo co - finish M[s-1][j]
        {
            li=i;
            ci=1;
            lo=j;
            co=s-1;
            L[li][ci]=2;
            bkt(L,li,ci,lo,co,sol);
            L[li][ci]=0;
        }


    if(sol==0)
        return false;
    else
        return true;
}


void afla(int &i, int y)
{
    y-=inceput;
    i=y/50+1;
}
char player_number()
{
    fundal_alb();
    tip_font(3,BLACK,'t');
    rectangle(50,150,600,470);
    if(limbaj==1)
        outtextxy(135, 200, "Care jucator vrei sa fii?");
    else if(limbaj==0)
        outtextxy(60, 200, "Which player do you want to be?");
    else if(limbaj==2)
        outtextxy(135, 200, "¿Qué jugador quieres ser?");
    setcolor(color1);
    setfillstyle(SOLID_FILL,color1);
    fillellipse(230,310,25,25);
    if(limbaj==1)
        outtextxy(280, 300, "Jucator 1");
    else if(limbaj==0)
        outtextxy(280, 300, "Player 1");
    else if(limbaj==2)
        outtextxy(280, 300, "Jugador 1");

    setcolor(color2);
    setfillstyle(SOLID_FILL,color2);
    fillellipse(230,410,25,25);
    if(limbaj==1)
        outtextxy(280, 400, "Jucator 2");
    else if(limbaj==0)
        outtextxy(280, 400, "Player 2");
    else if(limbaj==2)
        outtextxy(280, 400, "Jugador 2");
    while(1)
    {
        int x,y;
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
        }
        if(x>=205&&x<=400&&y>=300&&y<=350)
        {
            pune_beep();
            player=1;
            return 'a';
        }
        else if(x>=205&&x<=400&&y>=400&&y<=450)
        {
            pune_beep();
            player=2;
            return 'r';
        }
    }
}

void genereaza_albastru()
{
    if(nr_citire==1)
    {
        int i,j;
        do
        {
            i=rand()%s+1;
            j=rand()%s+1;
            if(j==1)
                j++;
            if(j==s)
                j--;
        }
        while(M[i][j]);

        M[i][j]='a';
        istoric[nr_citire].ii=i;
        istoric[nr_citire].jj=j;
        return;

    }
    bool schimbare=0;
    for(int a=1; schimbare==0&&a<=s; a++)
        for(int b=1; schimbare==0&&b<=s; b++)
            if(!M[a][b])
            {
                M[a][b]='a';
                if(Lee_albastru())
                {
                    schimbare=1;
                    istoric[nr_citire].ii=a;
                    istoric[nr_citire].jj=b;
                    break;
                }
                else
                    M[a][b]='\0';
            }
    for(int a=1; schimbare==0&&a<=s; a++)
        for(int b=1; schimbare==0&&b<=s; b++)
            if(!M[a][b])
            {
                M[a][b]='r';
                if(Lee_rosu())
                {
                    M[a][b]='a';
                    schimbare=1;
                    istoric[nr_citire].ii=a;
                    istoric[nr_citire].jj=b;
                    break;
                }
                else
                    M[a][b]='\0';
            }
    if(!schimbare)
    {
        int i,j;
        i=istoric[nr_citire-1].ii;
        j=istoric[nr_citire-1].jj;
        if(M[i-1][j]=='r'||M[i+1][j]=='r') //rosie verticala
        {
            int dl[]= {-1,-1,1,1,2,-2,0};
            int dc[]= {-1,1,1,-1,0,0,2,-2};
            for(int a=0; a<8; a++)
            {
                int l9=i+dl[a];
                int c9=j+dc[a];
                if(!M[l9][c9]&&l9>1&&l9<s&&c9>1&&c9<s)
                {
                    M[l9][c9]= 'a';
                    istoric[nr_citire].ii=l9;
                    istoric[nr_citire].jj=c9;
                    break;
                }
            }
        }
        else //rosie orizontala
        {
            int dl[]= {0,0,-1,-1,1,1,2,-2};
            int dc[]= {2,-2,1,-1,1,-1,0,0};
            for(int a=0; a<8; a++)
            {
                int l9=i+dl[a];
                int c9=j+dc[a];
                if(!M[l9][c9]&&l9>1&&l9<s&&c9>1&&c9<s)
                {
                    M[l9][c9]= 'a';
                    istoric[nr_citire].ii=l9;
                    istoric[nr_citire].jj=c9;
                    break;
                }
            }
        }
    }
}

void genereaza_rosu()
{
    bool schimbare=0;
    for(int a=1; schimbare==0&&a<=s; a++)
        for(int b=1; schimbare==0&&b<=s; b++)
            if(!M[a][b])
            {
                M[a][b]='r';
                if(Lee_rosu())
                {
                    schimbare=1;
                    istoric[nr_citire].ii=a;
                    istoric[nr_citire].jj=b;
                    break;
                }
                else
                    M[a][b]='\0';
            }
    for(int a=1; !schimbare&&a<=s; a++)
        for(int b=1; !schimbare&&b<=s; b++)
            if(!M[a][b])
            {
                M[a][b]='a';
                if(Lee_albastru())
                {
                    M[a][b]='r';
                    schimbare=1;
                    istoric[nr_citire].ii=a;
                    istoric[nr_citire].jj=b;
                    break;
                }
                else
                    M[a][b]='\0';
            }
    if(!schimbare)
    {
        int i=istoric[nr_citire-1].ii;
        int j=istoric[nr_citire-1].jj;
        if(M[i-1][j]=='a'||M[i+1][j]=='a') //albastra verticala
        {
            int dl[]= {2,-2,0,0,-1,-1,1,1};
            int dc[]= {0,0,2,-2,-1,1,1,-1};
            for(int a=0; a<8; a++)
            {
                int l9=i+dl[a];
                int c9=j+dc[a];
                if(!M[l9][c9]&&l9>1&&l9<s&&c9>1&&c9<s)
                {
                    M[l9][c9]= 'r';
                    istoric[nr_citire].ii=l9;
                    istoric[nr_citire].jj=c9;
                    break;
                }
            }
        }
        else //albastra orizontala
        {
            int dl[]= {-1,-1,1,1,0,0,2,-2};
            int dc[]= {1,-1,1,-1,2,-2,0,0};
            for(int a=0; a<8; a++)
            {
                int l9=i+dl[a];
                int c9=j+dc[a];
                if(!M[l9][c9]&&l9>1&&l9<s&&c9>1&&c9<s)
                {
                    M[l9][c9]= 'r';
                    istoric[nr_citire].ii=l9;
                    istoric[nr_citire].jj=c9;
                    break;
                }
            }
        }
    }

}


char joc_singleplayer()
{
    char c=player_number();
    setfillstyle(SOLID_FILL,WHITE);
    bar(0,0,DIM,DIM);
    deseneaza_tabla();
    int drum_rosu=0;
    int drum_albastru=0;
    nr_citire=0;
    while(drum_rosu==0&&drum_albastru==0)
    {
        setbkcolor(WHITE);
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
        char s[15];
        if(limbaj==1)
            strcpy(s,"MUTARI: ");
        else if(limbaj==0)
            strcpy(s,"MOVES: ");
        else if(limbaj==2)
        {
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            strcpy(s,"MOVIMIENTOS: ");
        }
        if(limbaj==1 || limbaj==0)
        {
            s[7]= nr_citire/10+'0';
        if(s[7]=='0')
        {
            s[7]=nr_citire%10+'0';
            s[8]= '\0';
        }
        else
        {
            s[8]=nr_citire%10+'0';
            s[9]= '\0';
        }
        }
        else
        {
            s[12]= nr_citire/10+'0';
        if(s[7]=='0')
        {
            s[12]=nr_citire%10+'0';
            s[13]= '\0';
        }
        else
        {
            s[13]=nr_citire%10+'0';
            s[14]= '\0';
        }
        }
        outtextxy(25,600, s);
        nr_citire++;
        bool u=false;
        if(nr_citire%2==1)
        {
            if(c=='a')
                u=citire_albastru();
            else
                genereaza_albastru();
            if(!u&&Lee_albastru())
                drum_albastru=1;
        }
        else
        {
            if(c=='r')
                u=citire_rosu();
            else
                genereaza_rosu();
            if(!u&&Lee_rosu())
                drum_rosu=1;
        }
        afisare_tabla();
        deseneaza_tabla();
    }
    if(drum_albastru==1)
        return 'a';
    else
        return 'r';
}

void history()
{
    h_accesat++;
    int ind;
    for(int i=1; i<=9; i+=2)
        for(int j=2; j<=9; j+=2)
        {
            baza[i][j]=baza[j][i]=1;
        }
    if(h_accesat==1)
    {
        while(fin>>jocuri[k].lg) //s
        {
            if(k==16)
            {
                jocuri[15].lg=jocuri[k].lg;
                for(int j=2; j<=15; j++)
                {
                    jocuri[j-1].nr=jocuri[j].nr;
                    jocuri[j-1].culoare1=jocuri[j].culoare1;
                    jocuri[j-1].culoare2=jocuri[j].culoare2;
                    for(int i=1; i<=jocuri[j].nr; i++)
                    {
                        jocuri[j-1].miscari_ordine[i].ii=jocuri[j].miscari_ordine[i].ii;
                        jocuri[j-1].miscari_ordine[i].jj=jocuri[j].miscari_ordine[i].jj;
                    }
                }
                k--;
            }
            fin>>jocuri[k].nr; //nr_citire
            fin>>jocuri[k].culoare1>>jocuri[k].culoare2; //culori
            cout<< k << ' '<<jocuri[k].culoare1<<' '<<jocuri[k].culoare2<< '\n';
            for(int i=1; i<=jocuri[k].nr; i++)
                fin>>jocuri[k].miscari_ordine[i].ii>>jocuri[k].miscari_ordine[i].jj; //miscari
            k++;
        }
        k--;
    }
    setcolor(WHITE);
    bar(0,0,DIM,DIM);
    setcolor(BLACK);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
    setbkcolor(WHITE);
    if(limbaj==1)
        outtextxy(200, 100, "Alege un joc");
    else if(limbaj==0)
        outtextxy(200, 100, "Choose a game");
    else if(limbaj==2)
        outtextxy(200, 100, "Elige un juego");



    int nr=1;
    for(int x=75; nr<=k&&x<=475; x+=200)
        for(int y=200; nr<=k&&y<=600; y+=100)
        {
            char s[5];
            //pun in s numarul de ordine al perechii de culori
            if(nr<=9)
            {
                s[0]=nr+'0';
                s[1]='\0';
            }
            else
            {
                s[0]=nr/10+'0';
                s[1]=nr%10+'0';
                s[2]='\0';
            }
            //color1
            setcolor(jocuri[nr].culoare1); //scriu cu prima culoare din sir numarul
            if(nr>9)
                outtextxy(x-70, y-10, s);
            else
                outtextxy(x-65, y-10, s);
            setfillstyle(SOLID_FILL,jocuri[nr].culoare1);
            circle(x,y,25); //desenez un cerc cu prima culoare
            fillellipse(x,y,25,25);//umplu cercul
            //color2
            setcolor(jocuri[nr].culoare2); //setez a doua culoare
            setfillstyle(SOLID_FILL,jocuri[nr].culoare2);  //setez a doua culoare
            circle(x+75,y,25); //desenez un cerc cu a doua culoare
            fillellipse(x+75,y,25,25); //umplu cercul
            nr++;
        }
    bool gasit=0;
    while(!gasit)
    {
        int x,y;
        if(ismouseclick(WM_LBUTTONDOWN))  //cand se apasa pe setul de culori ales
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
        }
        nr=1;
        for(int j=75; !gasit&&j<=475; j+=200) //cautam setul de culori
            for(int i=200; !gasit&& i<=600; i+=100)
            {
                if(x>=j-70&&x<=j+100&&y>=i-10&&y<=i+50)
                {
                    pune_beep();
                    ind=nr;
                    gasit=1;
                }
                nr++;
            }
    }
    s=jocuri[ind].lg;
    n=(s+1)/2;
    if(n==3)
        inceput=200;
    else if(n==4)
        inceput=150;
    else if(n==5)
        inceput=125;
    sfarsit=inceput+s*50;

    color1=jocuri[ind].culoare1;
    color2=jocuri[ind].culoare2;
    nr_citire=jocuri[ind].nr;
    for(int i=1; i<=jocuri[ind].nr; i++)
    {
        istoric[i].ii=jocuri[ind].miscari_ordine[i].ii;
        istoric[i].jj=jocuri[ind].miscari_ordine[i].jj;
    }

    fundal_alb();
    replay=1;
    vezi_miscari();


}

void pune_beep()
{
    if(muzica==1)
        Beep(500,200);
}

void fundal_alb()
{
    setcolor(WHITE); //culoare pt forma
    setfillstyle(SOLID_FILL,WHITE); //culoare pt fundal
    bar(0,0,DIM,DIM); //desenez fundalul alb
}

bool deasupra(int &xx, int &yy,int xi,int xo,int yi,int yo)
{
    bool gata=false;
    while(1) //afiseaza alta culoare cat timp se afla deasupra la play
    {
        xx=mousex();
        yy=mousey();
        if(!(xx>=xi&&xx<=xo&yy>=yi&&yy<=yo))
            break;
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            pune_beep();
            gata=true;
            break;
        }
    }
    return gata;
}

void tip_font(int marime, int color, char tip)
{
    if(tip=='t')
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, marime);  //font,directie,dimensiune scris
    else
        settextstyle(BOLD_FONT,HORIZ_DIR,marime);
    setbkcolor(WHITE); //culoarea din spatele scrisului
    setcolor(color);//culoarea scrisului
}
