/* --------------Some Information-----------------
   Down  = kiDown
   Right = kiRight
   Up    = kiUp
   Left  = 75  
   ESC   = 27
   s=115   S=83
   Horizontal Distance = 76 Characters
   Vertical Distance = 17 Lines
   Coordinates of Score (14,21)       Single Player
   Coordinates of Time  (73,21)       Single Player
   Coordinates of Player (16,21)      Player VS Computer
   Coordinates of Time (40,21)      Player VS Computer
   Coordinates of Computer (66,21)      Player VS Computer
   -------------About Data Memmbers-----------------
   C for Class
   q for Object
   i for int
   c for char
   qp for object pointer
   cp for char pointer
   qa for object array
   ki for constant int
*/
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<exception>
#include<fstream>
#include<ctime>                //for radom number generating (for srand())
using namespace std;
char cTempDir, cDoThis;   
enum EDir{kiDown=80,kiLeft=75,kiRight=77,kiUp=72,kiEscape=27};   //enum of constant directions
//=========================== gotoxy() ==================================//
void gotoxy(int x, int y) {
     COORD coord;
     coord.X = x;
     coord.Y = y;
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//============================= CLocation ================================//
class CLocation {
public:
      int x,y;
      void show (int face) {
           if (face==0) {                                                   
               gotoxy(x,y); 
               cout<<"D";
           }
           else {
           gotoxy(x,y);
           cout<<"\xDB";
           }
      }
      void hide () {
           gotoxy(x,y);
           cout<<" ";
      }
      void set(int x0,int y0)
      {
           x=x0;
           y=y0;
      }
      bool operator==(CLocation &);
};
//======================= Comparison Operator ==========================//
bool CLocation::operator==(CLocation & temp) {
     if (x==temp.x && y==temp.y) {
        return 1;
     }
     else return 0;
}
//=========================== Boundary Class ===========================//
class CBoundary : public CLocation {
public:       
       int iVirt;
       int iHori;
       int iSignal;
       //Boundary Arrays for User
       CLocation *qpLeftBound;
       CLocation *qpRightBound;
       CLocation *qpUpBound;
       CLocation *qpDownBound;
       //Boundary Arrays for Computer
       CLocation *qpComLeftBound;
       CLocation *qpComRightBound;
       CLocation *qpComUpBound;
       CLocation *qpComDownBound; 
       //No-Orgumnet Constructor
       CBoundary () {
                iVirt=17;
                iHori=76;
                iSignal=0;
       //----------------- User Boundaries -----------------//
                qpLeftBound = new CLocation[iVirt];
                qpRightBound = new CLocation[iVirt];     //DMA is used for making array having index
                qpUpBound = new CLocation[iHori];        // as a variable
                qpDownBound = new CLocation[iHori];
       //----------------- Computer Boundaries -----------------//
                qpComLeftBound = new CLocation[iVirt];
                qpComRightBound = new CLocation[iVirt];     //DMA is used for making array having index
                qpComUpBound = new CLocation[iHori];        // as a variable
                qpComDownBound = new CLocation[iHori];
       }
       //____________User Boundary Setting_______________//
       //Set Left Boundary for both snakes
       void setLeftBoundary () 
       {
            for (int i=0; i<iVirt; i++) 
            {
                qpLeftBound[i].set(2,i+2);
                qpComLeftBound[i].set(3,i+2);
            }
       }
       //Set Right Boundary for both snakes    
       void setRightBoundary () 
       {
            for (int i=0; i<iVirt; i++) 
            {
                qpRightBound[i].set(kiRight,i+2);
                qpComRightBound[i].set(76,i+2);
            }
       }
       //Set Upper Boundary for both snakes
       void setUpBoundary () 
       {
            for (int i=0; i<iHori; i++) 
            {
                qpUpBound[i].set(2+i,1);
                qpComUpBound[i].set(2+i,2);
            }
       }
       //Set Down Boundary for both snakes
       void setDownBoundary () 
       {
            for (int i=0; i<iHori; i++) 
            {
                qpDownBound[i].set(2+i,19);
                qpComDownBound[i].set(2+i,18);
            }
       }
       //Show Single Player Game Boundary
       void showSingleBoundary () {
            cout<<"  ";
            HANDLE hConsole;
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 480);                          //Yellow Color Code=480
            for (int i=0; i<24; i++) {
                   cout<<'\xB0';
            }
            cout<<"A Snake Game in OOP using C++"; 
            for (int i=0; i<24; i++) {
                cout<<'\xB0';
            }
            SetConsoleTextAttribute(hConsole, 8);                          //Dark Gray Color Code=8
            cout<<"\n  "<<'\xC9';
            for (int i=0; i<75; i++) {
                cout<<'\xCD';
            }
            cout<<'\xBB'<<"\n"<<"  "<<'\xBA';
            for (int i=0; i<75; i++) {
                cout<<" ";
            }
            cout<<'\xBA';
            for (int j=0; j<16; j++) {
                cout<<"\n"<<"  "<<'\xBA';
                for (int i=0; i<75; i++) {
                    cout<<" ";
                }
                cout<<'\xBA';
            }
            cout<<"\n"<<"  "<<'\xC8';
            for (int i=0; i<75; i++) {
                cout<<'\xCD';
            }
            cout<<'\xBC';
            cout<<"\n  "<<'\xC9';
            for (int i=0; i<75; i++) {
                cout<<'\xCD';
            }
            cout<<'\xBB'<<"\n"<<"  "<<'\xBA';
            SetConsoleTextAttribute(hConsole, 271);                          //White Color Code=271
            cout<<"   Score: "<<"\t\t\t\t\t\t\tTime:         ";
            SetConsoleTextAttribute(hConsole, 8);                          //Dark Gray Color Code=8
            cout<<'\xBA';
            cout<<"\n  "<<'\xC8';
            for (int i=0; i<75; i++) {
                cout<<'\xCD';
            }
            cout<<'\xBC';
            cout<<"\n  ";
            SetConsoleTextAttribute(hConsole, 480);                     //Yellow Color Code=480
            for (int i=0; i<10; i++) {
                cout<<'\xB0';
            }
            cout<<"NUST School of Electrical Engineering & Computer Sciences"; 
            for (int i=0; i<10; i++) {
                cout<<'\xB0';
            }
            SetConsoleTextAttribute(hConsole, 13);             //Pink Color Code=13
            gotoxy(25,21);
            cout<<"     Current Key: ";
       }
       //Show Player VS Computer Game Boundary
       void showPlayerCompBoundary () {
            cout<<"  ";
            HANDLE hConsole;
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 480);                          //Yellow Color Code=480
            for (int i=0; i<24; i++) {
                   cout<<'\xB0';
            }
            cout<<"A Snake Game in OOP using C++"; 
            for (int i=0; i<24; i++) {
                cout<<'\xB0';
            }
            SetConsoleTextAttribute(hConsole, 8);                          //Dark Gray Color Code=8
            cout<<"\n  "<<'\xC9';
            for (int i=0; i<75; i++) {
                cout<<'\xCD';
            }
            cout<<'\xBB'<<"\n"<<"  "<<'\xBA';
            for (int i=0; i<75; i++) {
                cout<<" ";
            }
            cout<<'\xBA';
            for (int j=0; j<16; j++) {
                cout<<"\n"<<"  "<<'\xBA';
                for (int i=0; i<75; i++) {
                    cout<<" ";
                }
                cout<<'\xBA';
            }
            cout<<"\n"<<"  "<<'\xC8';
            for (int i=0; i<75; i++) {
                cout<<'\xCD';
            }
            cout<<'\xBC';
            cout<<"\n  "<<'\xC9';
            for (int i=0; i<75; i++) {
                cout<<'\xCD';
            }
            cout<<'\xBB'<<"\n"<<"  "<<'\xBA';
            SetConsoleTextAttribute(hConsole, 271);                          //White Color Code=271
            cout<<"   Player:                  Time:                  Computer:               ";
            SetConsoleTextAttribute(hConsole, 8);                          //Dark Gray Color Code=8
            cout<<'\xBA';
            cout<<"\n  "<<'\xC8';
            for (int i=0; i<75; i++) {
                cout<<'\xCD';
            }
            cout<<'\xBC';
            cout<<"\n  ";
            SetConsoleTextAttribute(hConsole, 480);                     //Yellow Color Code=480
            for (int i=0; i<10; i++) {
                cout<<'\xB0';
            }
            cout<<"NUST School of Electrical Engineering & Computer Sciences"; 
            for (int i=0; i<10; i++) {
                cout<<'\xB0';
            }
       }
       //Game Over Screen For Both Games
       void gameOverScreen () {
            HANDLE hConsole;
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            cout<<"  ";
            SetConsoleTextAttribute(hConsole, 480);                     //Yellow Color Code=480
            for (int i=0; i<24; i++) {
                   cout<<'\xB0';
            }
            cout<<"A Snake Game in OOP using C++"; 
            for (int i=0; i<24; i++) {
                cout<<'\xB0';
            }
            SetConsoleTextAttribute(hConsole, 8);                          //Dark Gray Color Code=8
            cout<<"\n  "<<'\xC9';
            for (int i=0; i<75; i++) {
                cout<<'\xCD';
            }
            cout<<'\xBB'<<"\n"<<"  "<<'\xBA';
            for (int i=0; i<75; i++) {
                cout<<" ";
            }
            cout<<'\xBA';
            for (int j=0; j<19; j++) {
                cout<<"\n"<<"  "<<'\xBA';
                for (int i=0; i<75; i++) {
                    cout<<" ";
                }
                cout<<'\xBA';
            }
            cout<<"\n"<<"  "<<'\xC8';
            for (int i=0; i<75; i++) {
                cout<<'\xCD';
            }
            cout<<'\xBC'<<"\n  ";
            SetConsoleTextAttribute(hConsole, 480);           //Yellow Color Code=480
            cout<<"Press Any Key To Continue...";
       }
       //Welcome Screen
       void welcomeScreen () {
            HANDLE hConsole;
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            system("cls");
            SetConsoleTextAttribute(hConsole, 480);        //Yellow Color Code=480
            gotoxy(7,0);
            cout<<"   NUST School of Electrical Engineering & Computer Sciences   "; 
            cout<<"\n";
            SetConsoleTextAttribute(hConsole, 47);     //Green & White Color Code=47
            gotoxy(19,1);
            cout<<"      A Snake Game in OOP using C++      "; 
            SetConsoleTextAttribute(hConsole, 8);             //Gray Color Code=8
            for (int i=6; i<14; i++) {
                gotoxy(43,i);
                cout<<'\xB3';
            }
            gotoxy(28,3);
            SetConsoleTextAttribute(hConsole, 27);             //Blue Color Code=27
            cout<<"  Semester Project  ";
            SetConsoleTextAttribute(hConsole, 12);           //Red Color Code=12
            gotoxy(1,6);
            cout<<"Submitted By: ";
            gotoxy(46,8);
            cout<<"Submitted To: ";
            SetConsoleTextAttribute(hConsole, 11);          //Light Blue Color Code=11
            gotoxy(48,10);
            cout<<"Mr. Qasim Muhammad Rajpoot";
            SetConsoleTextAttribute(hConsole, 15);              //White Color Code=15
            gotoxy(1,8);
            cout<<"(Group Leader)";
            SetConsoleTextAttribute(hConsole, 3);           //Dark Blue-Green Color Code=3
            gotoxy(16,8);
            cout<<"Wajahat Karim";
            SetConsoleTextAttribute(hConsole, 6);            //Dark Yellow Color Code=6
            gotoxy(38,8);
            cout<<"291";
            SetConsoleTextAttribute(hConsole, 15);            //White Color Code=15
            gotoxy(47,8);
            SetConsoleTextAttribute(hConsole, 3);              //Dark Blue Color Code=3
            gotoxy(16,10);
            cout<<"Sheeraz Ahmed";
            SetConsoleTextAttribute(hConsole, 6);            //Dark Yellow Color Code=6
            gotoxy(38,10);
            cout<<"288";
            SetConsoleTextAttribute(hConsole, 3);              //Dark Blue Color Code=3
            gotoxy(16,12);
            cout<<"Muhammad Usman Habib";
            SetConsoleTextAttribute(hConsole, 6);            //Dark Yellow Color Code=6
            gotoxy(38,12);
            cout<<"285";
            SetConsoleTextAttribute(hConsole, 8);            //Dark Yellow Color Code=8
            for (int i=0; i<79; i++) {
                gotoxy(i,14);
                cout<<'\xC4';
            }
            SetConsoleTextAttribute(hConsole, 8);            //Dark Yellow Color Code=8
            for (int i=0; i<79; i++) {
                gotoxy(i,5);
                cout<<'\xC4';
            }
            gotoxy(43,14);
            cout<<'\xC1';
            gotoxy(43,5);
            cout<<'\xC2';
            SetConsoleTextAttribute(hConsole, 13);             //Pink Color Code=13
            gotoxy(31,15);
            cout<<"<Game Options>";
            SetConsoleTextAttribute(hConsole, 15);             //White Color Code=15
            gotoxy(2,17);
            cout<<"1: ";
            SetConsoleTextAttribute(hConsole, 2);             //blue-Green Color Code=3
            gotoxy(5,17);
            cout<<"Play New Single Player Game";
            SetConsoleTextAttribute(hConsole, 15);             //White Color Code=15
            gotoxy(2,18);
            cout<<"2: ";
            SetConsoleTextAttribute(hConsole, 2);             //blue-Green Color Code=3
            gotoxy(5,18);
            cout<<"Play New Player VS Computer Game";
            SetConsoleTextAttribute(hConsole, 8);             //Gray Color Code=8
            gotoxy(43,18);
            cout<<'\xDA'<<'\xC4';
            for (int i=0; i<29; i++)
                cout<<'\xC4';
            cout<<'\xBF';
            gotoxy(43,19);
            cout<<'\xB3';
            gotoxy(43,20);
            cout<<'\xC0'<<'\xC4';
            for (int i=0; i<29; i++)
                cout<<'\xC4';
            cout<<'\xD9';
            SetConsoleTextAttribute(hConsole, 15);             //White Color Code=12
            gotoxy(45,19);
            cout<<"Note: ";
            SetConsoleTextAttribute(hConsole, 10);             //Green Color Code=10
            cout<<"To Save Game, Press 'S'";
            SetConsoleTextAttribute(hConsole, 8);             //Gray Color Code=8
            cout<<'\xB3';
            SetConsoleTextAttribute(hConsole, 15);             //White Color Code=15
            gotoxy(2,19);
            cout<<"3: ";
            SetConsoleTextAttribute(hConsole, 2);             //blue-Green Color Code=3
            gotoxy(5,19);
            cout<<"Play Saved Single Player Game";
            SetConsoleTextAttribute(hConsole, 15);             //White Color Code=15
            gotoxy(2,20);
            cout<<"4: ";
            SetConsoleTextAttribute(hConsole, 2);             //blue-Green Color Code=3
            gotoxy(5,20);
            cout<<"Play Saved Player VS Computer Game";
            SetConsoleTextAttribute(hConsole, 15);             //White Color Code=15
            gotoxy(2,21);
            cout<<"5: ";
            SetConsoleTextAttribute(hConsole, 2);             //blue-Green Color Code=3
            gotoxy(5,21);
            cout<<"High Score Table";
            SetConsoleTextAttribute(hConsole, 15);             //White Color Code=15
            gotoxy(2,22);
            cout<<"6: ";
            SetConsoleTextAttribute(hConsole, 2);             //blue-Green Color Code=3
            gotoxy(5,22);
            cout<<"Exit the Game\n\n";
            SetConsoleTextAttribute(hConsole, 7);             //Light White Color Code=7
            cout<<"Press Any Number to Play: ";
       }
       //Print Exception for Single Player
       char* what (char key) {
            HANDLE hConsole;
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            char* temp;
            SetConsoleTextAttribute(hConsole, 6);             //Light Green Color Code=2
            gotoxy(44,21);
            if (key==kiDown) { temp="Down        "; }
            else if (key==kiUp) { temp="Up          "; }
            else if (key==75) { temp="Left        "; }
            else if (key==kiRight) { temp="Right       "; }
            else if (key==83 || key==115) { temp="Game Saved!"; iSignal=1;}
            else if (key=='~') { temp="            "; }
            return temp;
       }
       //Show Time for Single Player
       void showTime (int a) 
       {
            if (a<10) 
            {
               gotoxy(74,21);
               cout<<" ";
            }
            gotoxy(73,21);
            cout<<a;
       }
       //Hide Time for Single Player
       void hideTime () 
       {
            for (int a=0; a<3; a++) 
            {
               gotoxy(a+73,21);
               cout<<" ";
            }
       }
       //Time Function for Single VS Computer Function
       void timeFunc(int m, int s) {
            HANDLE hConsole;
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 12);             //Red Color Code=12
            if (s<10) { gotoxy(45,21); cout<<" "; }
            gotoxy(38,21);
            cout<<m<<" : "<<s;
       }
};
//============================= Food Class =============================//
class CFood: public CLocation
{
public:
       CLocation qEatMe;
       void generateFood() 
       {
            time_t t;
            srand(time(&t));           //srand(int) seed the random number with the time
            const int MAX_x=73;
            const int MAX_y=16; 
            x =(rand() % MAX_x)+3;
            y =(rand() % MAX_y)+2;
            gotoxy(x,y);
            cout<<'\x1';
            qEatMe.set(x,y);
       }
};
//============================== Big Food ===============================//
class CBigFood: public CLocation 
{
public:
       CLocation qEatBigFood;
       void generateBigFood() 
       {
            time_t t1;
            srand(time(&t1));           //srand(int) seed the random number with the time
            const int max_x=73;
            const int max_y=15; 
            x =(rand() % max_x)+4;
            y =(rand() % max_y)+3;
            gotoxy(x,y);
            cout<<'\x5';
            qEatBigFood.set(x,y);
       }
};
//============================== User Snake =============================//
class CSnake: public CLocation
{
public:
       int iScore;
       int iLength;
       char cDir;
       CLocation qaLoc[100];
       //No-Orgument Constructor for Single Player
       CSnake () 
       {
             iLength=5;
             iScore=0;
             cDir=kiRight;
             qaLoc[0].set(15,10);
             qaLoc[1].set(14,10);
             qaLoc[2].set(13,10);
             qaLoc[3].set(12,10);
             qaLoc[4].set(11,10);
             qaLoc[5].set(10,10);
       }
       //Four Orgument Constructor for Computer Snake
       CSnake (int l, int cx, int cy, int direction) 
       {
             iLength=l;
             iScore=0;
             for (int i=iLength; i>=0; i--) 
             {
                qaLoc[i].set(i+cx,cy);
             }
             cDir=direction;
       }
       //One-Orgument Constructor for Operator Overloading ++
       CSnake (int l) {
             iLength=l;
       }
       //Show Snake Function
       void show()
       {
             for(int a=0; a<iLength; a++)
                qaLoc[a].show(a);
                qaLoc[iLength].hide();
       }
       //Moving Left any snake
       void left()
       {
            for(int b=iLength; b>0; b--)
             {
                qaLoc[b].x=qaLoc[b-1].x;
                qaLoc[b].y=qaLoc[b-1].y;
             }
             qaLoc[0].x--;
       }
       //Moving Right  any snake
       void right()
       {
            for(int b=iLength; b>0; b--)
             {
                qaLoc[b].x=qaLoc[b-1].x;
                qaLoc[b].y=qaLoc[b-1].y;
             }
             qaLoc[0].x++;
       }
       //Moving Down any snake
       void down()
       {
             for(int c=iLength; c>0; c--)
             {
                qaLoc[c].x=qaLoc[c-1].x;
                qaLoc[c].y=qaLoc[c-1].y;
             }
             qaLoc[0].y++;
       }
       //Moving Up any snake
       void up()
       {
             for(int c=iLength; c>0; c--)
             {
                qaLoc[c].y=qaLoc[c-1].y;
                qaLoc[c].x=qaLoc[c-1].x;
             }
             qaLoc[0].y--;
       }
       //Print Score any snake
       void printScore (int x0, int y0) 
       {
            gotoxy(x0,y0);
            cout<<iScore;
       }
       //Unary Operator ++
       CSnake operator++(int);
};
//============================ Unary Operator ++ ==========================//
CSnake CSnake::operator++(int) {
      CSnake temp(iLength);
      iLength++;
      iScore+=5;
      return temp;
} 
//============ Prototype for checking direction of compuer snake=============//
char directionCheckComp(char , CSnake , CFood ); 
//============================= High Score Class =========================//
class highScore {  
      public:
             char name[15];          //Player's Name
             int score;              //Player's Score
             //Initializing Variables
             void setData() {
                  char array[15]="No Name";
                         for (int i=0; i<15; i++) {
                             name[i]=array[i];
                         }
                         score=0;
             }
             //Getting Name from User
             void getData() {
                  cout<<"Name: ";
                  cin>>name;
             }
             //Printing Rank, Name & Score
             void printData(int dd) {
                  HANDLE hConsole;
                  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                  gotoxy(17,dd+7);
                  SetConsoleTextAttribute(hConsole, 15);  //White Color Code=15
                  cout<<dd+1;
                  gotoxy(26,dd+7);
                  SetConsoleTextAttribute(hConsole, 2);  //Light Green Color Code=2
                  cout<<name;
                  gotoxy(47,dd+7);
                  SetConsoleTextAttribute(hConsole, 3);   //Light Blue Color Code=3
                  cout<<score;
                  SetConsoleTextAttribute(hConsole, 7);   //Light White Color Code=7
             }
             //Operator Overloading = for equality
             highScore operator=(highScore);
};
//==================== Operator = Overloading ===============================//
highScore highScore::operator =(highScore hh) {
          score=hh.score;
          for (int i=0; i<15; i++) {
              name[i]=hh.name[i];
          }
}
//==================== High Score Table Class ==============================//
class highScoreTable {
      public:
             highScore hs[100];         //High Score table of 100 Records
             int countScore;            //Count Total Number of Entered Records
             //Zero-Orgument Constructor
             highScoreTable() {
                for (int i=0; i<100; i++) {
                    hs[i].setData();
                }
                countScore=0;
             }
             //One-Orgument Constructor
             highScoreTable(int hst) {
                countScore=hst;
             }
             //Printing High Score Table of Rop 15 Records
             void printTableShape() {
                  HANDLE hConsole;
                  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                  system("cls");
                  SetConsoleTextAttribute(hConsole, 480);        //Yellow Color Code=480
                  gotoxy(25,0);
                  cout<<"   High Score Table   "; 
                  cout<<"\n";
                  SetConsoleTextAttribute(hConsole, 47);     //Green & White Color Code=47
                  gotoxy(21,1);
                  cout<<"      Top Fifteen Scores      "; 
                  SetConsoleTextAttribute(hConsole, 8);             //Gray Color Code=8
                  gotoxy(15,4);
                  cout<<'\xDA';
                  for (int i=16; i<57; i++) {                //First Line 15
                      gotoxy(i,4);                           //Middle Line 39
                      cout<<'\xC4';                          //Last Line 57
                  }                                          //Second Line 20
                  cout<<'\xBF';
                  gotoxy(20,4); cout<<'\xC2';
                  gotoxy(39,4); cout<<'\xC2';
                  gotoxy(15,5); cout<<'\xB3';
                  gotoxy(20,5); cout<<'\xB3';
                  gotoxy(39,5); cout<<'\xB3';
                  gotoxy(57,5); cout<<'\xB3';
                  gotoxy(15,6); cout<<'\xC3';
                  for (int i=16; i<57; i++) {                
                      gotoxy(i,6);                           
                      cout<<'\xC4';                          
                  }
                  gotoxy(39,6); cout<<'\xC5';
                  gotoxy(20,6); cout<<'\xC5';
                  gotoxy(57,6); cout<<'\xB4';
                  for (int i=7; i<23; i++) {
                      gotoxy(15,i); cout<<'\xB3';
                      gotoxy(20,i); cout<<'\xB3';
                      gotoxy(39,i); cout<<'\xB3';
                      gotoxy(57,i); cout<<'\xB3';
                  }
                  gotoxy(15,22); cout<<'\xC0';
                  for (int i=16; i<57; i++) {                
                      gotoxy(i,22);                           
                      cout<<'\xC4';                          
                  }
                  gotoxy(39,22); cout<<'\xC1';
                  gotoxy(20,22); cout<<'\xC1';
                  gotoxy(57,22); cout<<'\xD9';
                  SetConsoleTextAttribute(hConsole, 14);    //Yellow Color Code=14
                  gotoxy(28,5); cout<<"Name";
                  gotoxy(46,5); cout<<"Score";
                  gotoxy(17,5); cout<<"S#";
             }
             //Operator Overloading ++ for Adding Score
             highScoreTable operator++(int); 
};
//=============== Unary Operator ++ For High Scores =================//
highScoreTable highScoreTable::operator++(int) {
      highScoreTable temp(countScore);
      countScore++;
      return temp;
}
//==================== Swap Function for Sorting =======================//
void swapScore(highScore &h1, highScore &h2) {
     if (h1.score > h2.score) {         //If First score is greater than
         highScore temp;                //second score, swap scores
         temp=h1;
         h1=h2;
         h2=temp;
     }
}
//=============================== Main Function ===========================//
int main () 
{
    //Making some useful variables
    highScore tempScore;
    highScoreTable myTable;
    char choice;             //User's choice to choose game from welcome screen
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);               //For Color
    CBoundary b;
    //Welcome Screen
    b.welcomeScreen();
    choice=getch();
    do {
        CSnake s1;             //Player Snake
        CSnake s2(5,40,8,75);  //Computer Snake
        CFood f1;              //Simple Food
        CBigFood g1;           //Special Food
        //Making Some Useful Variables
        bool hit=0, available=0, user=0, welcome=0, esc=0;
        int count=0, temp=50, min=1, sec=59, timer=0;
//___________________________Single Player Game_____________________________________//
    if (choice=='1')
    {               //START OF SINGLE PLAYER GAME              
SINGLE_PLAYER_GAME:
          hit=0, available=0, user=0, welcome=0, esc=0;
          count=0, temp=50;           //Initializing Variables
          system("cls");
          //User Boundary
          b.setLeftBoundary();
          b.setRightBoundary();
          b.setDownBoundary();
          b.setUpBoundary();
          b.showSingleBoundary();
          //User Snake
          SetConsoleTextAttribute(hConsole, 10);                    //Green Color Code = 10
          s1.show();
          s1.printScore(14,21);                                     //Showing Score
          //Food System
          SetConsoleTextAttribute(hConsole, 13);                    //Purple Color Code = 13
          f1.generateFood();                                        //Showing Food
          getch();                                                  //Ready to Play
          while (true) 
          {                  //START OF WHILE LOOP
             //User Snake Control Switch
             switch (s1.cDir)
             {
                 case kiDown:
                      s1.down();
                      break;
                 case kiLeft:
                      s1.left();
                      break;
                 case kiRight:
                      s1.right();
                      break;
                 case kiUp:
                      s1.up();
                      break;
             }
             SetConsoleTextAttribute(hConsole, 10);                      //Green Color Code = 10
             s1.show();
             Sleep(90);                                     //Wait 100 Mili Seconds
             try {      //Start Of Try
                 if (kbhit())                     //If User Pressed Any Key
                 {                                //Get That Key & Check it
                     cDoThis=getch();
                     if (cDoThis==kiUp || cDoThis==kiRight || cDoThis==kiDown || cDoThis==kiLeft) {
                        cTempDir=cDoThis;
                     }
                 }
                 //User Snake is Going Down, chance of left or right 
                 if(cTempDir==kiLeft && s1.cDir==kiDown) {  s1.cDir=kiLeft; throw cTempDir; }
                 if(cTempDir==kiRight && s1.cDir==kiDown) {  s1.cDir=kiRight; throw cTempDir; }
                 //User Snake Going Left, chance of up or down
                 if(cTempDir==kiDown && s1.cDir==kiLeft) {  s1.cDir=kiDown; throw cTempDir; }
                 if(cTempDir==kiUp && s1.cDir==kiLeft) {  s1.cDir=kiUp; throw cTempDir; }
                 //User Snake Going Up, chance of right or left
                 if(cTempDir==kiLeft && s1.cDir==kiUp) {  s1.cDir=kiLeft; throw cTempDir; }
                 if(cTempDir==kiRight && s1.cDir==kiUp) {  s1.cDir=kiRight; throw cTempDir; }
                 //User Snake Going Right, chance of up or down
                 if(cTempDir==kiUp && s1.cDir==kiRight) {  s1.cDir=kiUp; throw cTempDir; }
                 if(cTempDir==kiDown && s1.cDir==kiRight) {  s1.cDir=kiDown; throw cTempDir; }
                 if(cDoThis==kiEscape) { welcome=1; break; }
                 if(cDoThis=='s' || cDoThis=='S')  
                 {
          //============================Save File Single Player======================
                     //Saving Snake
                     ofstream outfile("Snake1.txt",ios::binary);
                     if( !outfile.good() )  {
                         cout<<"File could not be opened";    
                     }
                     outfile.write( reinterpret_cast<char*>(&s1), sizeof(s1) );
                     outfile.close();
                     throw cDoThis;
                 }
             }           //End of Try
             catch (char d) {                //Catch the Key Pressed by Player
                   cout<<b.what(d);          //Tell Which key is pressed?
                   if(b.iSignal==1) {        //If That is 's', then
                      b.iSignal=0;
                      cDoThis='~';
                      getch();               //Stop the Game
                   }
             }     
             //Checking Boundaries for User
             //Collision with Upper Horizontal Boundary for User
             for (int i=0; i<b.iHori; i++) {
              if(s1.qaLoc[0]==b.qpUpBound[i]) {  hit=1; user=0; break; }    //Break for loop
             } 
             if (hit==1) { break; }           //Break while loop
             //Collision with Right Vertical Boundary for User
             for (int i=0; i<b.iVirt; i++) {
               if(s1.qaLoc[0]==b.qpRightBound[i]) {  hit=1; user=0; break;}
             } 
             if (hit==1) { break; }
             //Collision with Lower Horizontal Boundary for User
             for (int i=0; i<b.iHori; i++) {
              if(s1.qaLoc[0]==b.qpDownBound[i]) {  hit=1; user=0; break; }
             } 
             if (hit==1) { break; }
             //Collision with Left Vertical Boundary for User
             for (int i=0; i<b.iVirt; i++) { 
              if(s1.qaLoc[0]==b.qpLeftBound[i]) {  hit=1; user=0; break; }
             }
             //Self Collision for User
             for (int i=1; i<s1.iLength; i++) {
              if (s1.qaLoc[0] == s1.qaLoc[i]) { hit=1; user=0; break; }
             }
             if (hit==1) { break; }
             //Eating Food for User
             if (s1.qaLoc[0] == f1.qEatMe )   //Snake has eaten food or not
             {
              s1++;          //Add 1 Unit to length
              if (s1.iLength==99) {
                 esc=1;           
                 break;
              }
              SetConsoleTextAttribute(hConsole, 13);                    //Purple Color Code = 13
              f1.generateFood();                //Generate New Food
              SetConsoleTextAttribute(hConsole, 268);                    //Red Color Code = 268
              s1.printScore(14,21);             //Print New Score
              count++;
              //If snake has eaten five simple foods, generate a special food
              if (count==5) { g1.generateBigFood(); available=1; count=0; }
             }
             //Showing Big Food for User
             if (available == 1) 
             {
              SetConsoleTextAttribute(hConsole, 268);                    //Red Color Code = 268
              b.showTime(temp);                            //Show Time for Special Food
              temp--;
              if (temp==0)                                 //If time has ended,
              {
                 g1.hide();                                //Hide food
                 b.hideTime();
                 available=0;
                 temp=50;
              }
             }
             //Eating Big Food for Users
             if (s1.qaLoc[0] == g1.qEatBigFood )      //snake has eaten big food or not??
             {
                int randNum =(rand() % 50);         
                s1.iScore = s1.iScore + randNum;    //Add score
                s1.printScore(14,21);               //Print score
                b.hideTime();                       
                available=0;
                temp=50;
             }
             //If new food is generated on body of user snake, 
             //then clear it and genrate new food
             for (int j=1; j<s1.iLength; j++) 
             {
                 if (f1.qEatMe == s1.qaLoc[j]) { f1.generateFood();  }
             }
          }           //END OF WHILE LOOP
          //Checking Which Screen to be Displayed
          if (hit==1) {              //If Snake has been collided with anything
             Sleep(1200);
             system("cls");
             b.gameOverScreen();
             gotoxy(35,12); 
             SetConsoleTextAttribute(hConsole, 12);                    //Red Color Code = 12
             cout<<"Game Over!"; 
             gotoxy(33,13); 
             SetConsoleTextAttribute(hConsole, 10);                    //Green Color Code = 10
             cout<<"Your Score:  "<<s1.iScore;
             SetConsoleTextAttribute(hConsole, 3);                //Green-Blue Color Code = 3
             gotoxy(33,15);
             tempScore.getData();              //Get Name
             tempScore.score=s1.iScore;         //Save Score
             myTable.hs[myTable.countScore]=tempScore;     //Send that record to array of records
             myTable++;
             for (int i=0; i<100; i++) {
                 for (int j=0; j<100; j++) {               //Sort the array
                     swapScore(myTable.hs[i],myTable.hs[j]);
                 }
             }
             //Saving High Score to File
             ofstream scorefile("HighScore.txt",ios::binary);
             if( !scorefile.good() )  {
                 cout<<"File could not be opened";    
             }
             scorefile.write( reinterpret_cast<char*>(&myTable), sizeof(highScoreTable) );
             scorefile.close();
             gotoxy(30,23);
             Sleep(500);
             getch();
          }
          else if (esc==1) {
                  esc=0;
                  Sleep(800);
                  system("cls");
                  b.gameOverScreen();
                  gotoxy(31,9); 
                  SetConsoleTextAttribute(hConsole, 10);                    //Green Color Code = 10
                  cout<<"Congratulations!";
                  gotoxy(20,11);
                  SetConsoleTextAttribute(hConsole, 13);                    //Purple Color Code = 13
                  cout<<"You Reached to Maximum Length of Snake!";
                  gotoxy(33,13); 
                  SetConsoleTextAttribute(hConsole, 10);                    //Green Color Code = 10
                  cout<<"Your Score:  "<<s1.iScore;
                  highScore tempScore;
                  HANDLE hConsole;
                  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                  SetConsoleTextAttribute(hConsole, 3);                //Green-Blue Color Code = 3
                  gotoxy(31,15);
                  tempScore.getData();              //Get Name
                  tempScore.score=s1.iScore;         //Save Score
                  myTable.hs[myTable.countScore]=tempScore;    //Add record to array of records
                  myTable.countScore++;
                  for (int i=0; i<10; i++) {
                      for (int j=0; j<10; j++) {               //Sort the array
                          swapScore(myTable.hs[i],myTable.hs[j]);
                      }
                  }
                  //Saving High Score to File
                  ofstream scorefile("HighScore.txt",ios::binary);
                  if( !scorefile.good() )  {
                      cout<<"File could not be opened";    
                  }
                  scorefile.write( reinterpret_cast<char*>(&myTable), sizeof(myTable) );
                  scorefile.close();
                  gotoxy(30,23);
                  Sleep(500);
          }
          system("cls");
      }                    //END OF SINGLE PLAYER GAME
//______________________________Player VS Computer Game_________________________________//
    else if (choice=='2')
    {                    //START OF PLAYER VS COMPUTER GAME   
PLAYER_VS_COMP_GAME:       
       hit=0, available=0, user=0, welcome=0, esc=0;      //Reseting Old Variables
       count=0, temp=50;                                  //for 2 player game
       min=1, sec=59, timer=0;                            //time variables
       system("cls");
       //Setting Boundary
       b.setLeftBoundary();
       b.setRightBoundary();
       b.setDownBoundary();
       b.setUpBoundary();
       b.showPlayerCompBoundary();
       //User Snake
       SetConsoleTextAttribute(hConsole, 10);                    //Green Color Code = 10
       s1.show();                        //Showing User Snake
       s1.printScore(16,21);
       //Computer Snake
       SetConsoleTextAttribute(hConsole, 11);                    //Light Blue Color Code = 11
       s2.show();                        //Showing Computer Snake
       s2.printScore(66,21);
       //Food System
       CFood f1;                         
       SetConsoleTextAttribute(hConsole, 13);                    //Purple Color Code = 13
       f1.generateFood();                //Showing Food
       CBigFood g1;
       getch();                          //Ready to play
       while (true) 
       {          //START OF WHILE LOOP
          //User Snake Control Switch
          switch (s1.cDir)
          {
                 case kiDown:
                      s1.down();
                      break;
                 case kiLeft:
                      s1.left();
                      break;
                 case kiRight:
                      s1.right();
                      break;
                 case kiUp:
                      s1.up();
                      break;
          }
          //Coumputer Snake Control Switch
          switch (s2.cDir)
          {
                 case kiDown: 
                      s2.down();
                      break;
                 case kiLeft: 
                      s2.left();
                      break;
                 case kiUp:
                      s2.up();
                      break;
                 case kiRight:
                      s2.right();
                      break; 
          }
          SetConsoleTextAttribute(hConsole, 10);                      //Green Color Code = 10
          s1.show();                        //Show User Snake
          SetConsoleTextAttribute(hConsole, 11);                      //Light Blue Color Code = 11
          s2.show();                        //Show Computer Snake
          Sleep(100);
          timer++;                          //Add 1 to timer
          if (timer==10) {
             timer=0;
             sec--;
             if(sec==0 & min>0) {
                min--;
                sec=60;
             }
          }
          b.timeFunc(min,sec);              //Show time 
          if(min==0 && sec==0) { hit=0; welcome=1; break; }
          if (kbhit()) {                //If any key is pressed, then get that key
             cDoThis=getch();           //save it in cDoThis
             if (cDoThis==kiUp || cDoThis==kiRight || cDoThis==kiDown || cDoThis==kiLeft ) {
                cTempDir=cDoThis;
             }
          }
          //User Snake is Going Down, chance of left or right 
          if(cTempDir==kiLeft && s1.cDir==kiDown) {  s1.cDir=kiLeft; }
          if(cTempDir==kiRight && s1.cDir==kiDown) {  s1.cDir=kiRight; }
          //User Snake is Going Left, chance of up or down 
          if(cTempDir==kiDown && s1.cDir==kiLeft) {  s1.cDir=kiDown; }
          if(cTempDir==kiUp && s1.cDir==kiLeft) {  s1.cDir=kiUp; }
          //User Snake is Going Up, chance of left or right 
          if(cTempDir==kiLeft && s1.cDir==kiUp) {  s1.cDir=kiLeft; }
          if(cTempDir==kiRight && s1.cDir==kiUp) {  s1.cDir=kiRight; }
          //User Snake is Going Right, chance of up or down 
          if(cTempDir==kiUp && s1.cDir==kiRight) {  s1.cDir=kiUp; }
          if(cTempDir==kiDown && s1.cDir==kiRight) {  s1.cDir=kiDown; }
          //If user has pressed ESC, break while loop
          if(cDoThis==kiEscape) { hit=0; esc=1; break; }
          if(cDoThis=='s' || cDoThis=='S')
          {
              //================= Save User Snake =================
              ofstream outfile1("Snake2.txt" , ios::binary);
              if( !outfile1.good() ){
              cout<<"File could not be opened";    
              }
              outfile1.write( reinterpret_cast<char*>(&s1), sizeof(s1) ); 
              outfile1.close();
              //================= Save Computer Snake =================
              ofstream outfile2("Snake3.txt" , ios::binary);
              if( !outfile2.good() ){
              cout<<"File could not be opened";    
              }
              outfile2.write( reinterpret_cast<char*>(&s2), sizeof(s2) ); 
              outfile2.close();
              cDoThis=='~';
              getch();         //Stop the game
          }
          //Check in which direction, computer has to go
          s2.cDir = directionCheckComp(s2.cDir,s2,f1);
          //Boundaries for User
          //Collision with Upper Horizontal Boundary for User
          for (int i=0; i<b.iHori; i++) {
              if(s1.qaLoc[0]==b.qpUpBound[i]) {  hit=1; user=0; break; }
          } 
          if (hit==1) { break; }
          //Collision with Right Vertical Boundary for User
          for (int i=0; i<b.iVirt; i++) {
               if(s1.qaLoc[0]==b.qpRightBound[i]) {  hit=1; user=0; break;}
          } 
          if (hit==1) { break; }
          //Collision with Lower Horizontal Boundary for User
          for (int i=0; i<b.iHori; i++) {
              if(s1.qaLoc[0]==b.qpDownBound[i]) {  hit=1; user=0; break; }
          } 
          if (hit==1) { break; }
          //Collision with Left Vertical Boundary for User
          for (int i=0; i<b.iVirt; i++) { 
              if(s1.qaLoc[0]==b.qpLeftBound[i]) {  hit=1; user=0; break; }
          } 
          //Checking Boundaries for Computer
          //Collision with Upper Horizontal Boundary for Computer
          for (int i=0; i<b.iHori; i++) {
              if(s2.qaLoc[0]==b.qpComUpBound[i] && s2.cDir==kiUp) {
                  if (i>=0 && i<70) { s2.cDir=kiRight; }   //If it has come on any boundary
                  else s2.cDir=kiLeft;                     //turn the direction
              }
          } 
          if (hit==1) { break; }
          //Collision with Right Vertical Boundary for Computer
          for (int i=0; i<b.iVirt; i++) {
               if(s2.qaLoc[0]==b.qpComRightBound[i] && s2.cDir==kiRight) {
                  if (i>=0 && i<8) { s2.cDir=kiDown; }
                  else s2.cDir=kiUp;
              }
          } 
          if (hit==1) { break; }
          //Collision with Lower Horizontal Boundary for Computer
          for (int i=0; i<b.iHori; i++) {
              if(s2.qaLoc[0]==b.qpComDownBound[i] && s2.cDir==kiDown) {
                  if (i>=0 && i<36) { s2.cDir=kiRight; }
                  else s2.cDir=kiLeft;
              }
          } 
          if (hit==1) { break; }
          //Collision with Left Vertical Boundary for Computer
          for (int i=0; i<b.iVirt; i++) { 
              if(s2.qaLoc[0]==b.qpComLeftBound[i] && s2.cDir==kiLeft) {
                  if (i>=0 && i<8) { s2.cDir=kiDown; }
                  else s2.cDir=kiUp;
              } 
          }
          //Self Collision for User
          for (int i=1; i<s1.iLength; i++) {
              if (s1.qaLoc[0] == s1.qaLoc[i]) { hit=1; user=0; break; }
          }
          if (hit==1) { break; }
          //Self Collision for Computer
          for (int i=1; i<s2.iLength; i++) {
              if (s2.qaLoc[0] == s2.qaLoc[i]) { hit=1; user=1; break; }
          }
          if (hit==1) { break; }
          //Eating Food for User
          if (s1.qaLoc[0] == f1.qEatMe )
          {
             s1++;
             SetConsoleTextAttribute(hConsole, 13);                    //Purple Color Code = 13
             f1.generateFood(); 
             SetConsoleTextAttribute(hConsole, 10);                    //Green Color Code = 10
             s1.printScore(16,21); 
             count++;
             if (count==5) { g1.generateBigFood(); available=1; count=0; }
          }
          //Eating Food for Computer
          if (s2.qaLoc[0] == f1.qEatMe ) 
          {
             s2++;
             SetConsoleTextAttribute(hConsole, 13);                    //Purple Color Code = 13
             f1.generateFood(); 
             SetConsoleTextAttribute(hConsole, 11);                    //Light Blue Color Code = 11
             s2.printScore(66,21);
          }
          //Showing Big Food for User
          if (available == 1) 
          {
             SetConsoleTextAttribute(hConsole, 268);                    //Red Color Code = 268
             b.showTime(temp);
             temp--;
             if (temp==0) 
             {
               g1.hide();
               b.hideTime();
               available=0;
               temp=50;
             }
          }
          //Eating Big Food for User
          if (s1.qaLoc[0] == g1.qEatBigFood ) 
          {
             int randNum =(rand() % 50);         
             s1.iScore = s1.iScore + randNum;
             s1.printScore(16,21);
             b.hideTime();
             available=0;
             temp=50;
          }
          //If food is generated on body of user snake, 
          //clear it and generate new food
          for (int j=1; j<s1.iLength; j++) 
          {
             if (f1.qEatMe == s1.qaLoc[j]) { f1.generateFood();  }
          }
          //If food is generated on body of computer snake, 
          //clear it and generate new food
          for (int j=1; j<s2.iLength; j++) 
          {
             if (f1.qEatMe == s2.qaLoc[j]) { f1.generateFood();  }
          }
       }          //END OF WHILE LOOP-------------------------------------
       //Check how game is ended
       if (hit==1) {       //by collision with anything
          if (user==0) {         //If user has lost game
             Sleep(1200);
             system("cls");
             b.gameOverScreen();
             gotoxy(35,9); 
             SetConsoleTextAttribute(hConsole, 12);                    //Red Color Code = 12
             cout<<"Game Over!";
             gotoxy(35,11);
             SetConsoleTextAttribute(hConsole, 13);                    //Purple Color Code = 13
             cout<<"You Lose!";
             gotoxy(30,23);
             Sleep(1200);
             getch();
          }
          else if (user==1) {                  //If user has won the game
             Sleep(1200);                 
             system("cls");
             b.gameOverScreen();
             gotoxy(31,9); 
             SetConsoleTextAttribute(hConsole, 10);                    //Green Color Code = 10
             cout<<"Congratulations!";
             gotoxy(34,11);
             SetConsoleTextAttribute(hConsole, 13);                    //Purple Color Code = 13
             cout<<"You Won!";
             gotoxy(30,23);
             Sleep(1200);
             getch();
          }
          hit=0;
          system("cls");
       }
       else if (welcome==1) {           //If Time has ended
            Sleep(1200);
            system("cls");
            b.gameOverScreen();
            gotoxy(35,9);
            cout<<"Time Over!";
            if (s1.iScore>s2.iScore) {     //If User's score is more
               gotoxy(36,11);
               SetConsoleTextAttribute(hConsole, 10);                    //Green Color Code = 10
               cout<<"You Won!";
               Sleep(1200);
            }
            else {
               gotoxy(36,11);             //If computer's score is more
               SetConsoleTextAttribute(hConsole, 13);                    //Purple Color Code = 13
               cout<<"You Lose!";
               gotoxy(30,23);
               Sleep(1200);
            }
            welcome=0;
            getch();
       }
       else if (esc==1) {                //If player has escaped game
            system("cls");
            b.welcomeScreen();
       }
    }          //END OF PLAYER VS COMPUTER GAME
//_______________________Play Saved Single Player Game_________________________________//
      else if (choice=='3')
      {
         //Loading User Snake for Single Player Game
         ifstream infile("snake1.txt", ios::binary);
         infile.read( reinterpret_cast<char*>(&s1), sizeof(s1) );  
         goto SINGLE_PLAYER_GAME;              //Start Game
      }
//______________________Play Saved Player VS Computer Game___________________________//
    else if(choice=='4')  {
         //Loading User Snake for Player VS Computer Game
         ifstream infile1("Snake2.txt", ios::binary);
         if( !infile1.good() )  {
              cout<<"File could not be opened";    
          }
          //Loading Computer Snake for Player VS Computer Game
         infile1.read( reinterpret_cast<char*>(&s1), sizeof(s1) );
         ifstream infile2("Snake3.txt", ios::binary);
         if( !infile2.good() )  {
              cout<<"File could not be opened";    
          }
         infile2.read( reinterpret_cast<char*>(&s2), sizeof(s2) );
         goto PLAYER_VS_COMP_GAME;          //Start Game
    }
//___________________________________Show High Score Table______________________________//
    else if (choice=='5') {
         //Loading High Scores from File
         ifstream inScorefile("HighScore.txt", ios::binary);
         inScorefile.read( reinterpret_cast<char*>(&myTable), sizeof(myTable) );
         system("cls");
         myTable.printTableShape();
         for (int i=0; i<15; i++) {
             myTable.hs[i].printData(i);
         }
         gotoxy(1,24);
         cout<<"Press Any Key to Continue...";
         getch();
    }
//_____________________________________Exit the Game____________________________________//                         
    else if (choice=='6') {
         exit(1);
    }
    b.welcomeScreen();
    choice=getch();
    } while(choice!='6');
}            //END OF MAIN FUNCTION

//=====================================================================================//
//Direction Check for Computer Snake
char directionCheckComp(char comp, CSnake s2, CFood f1) 
{
          int dif_x = f1.x - s2.qaLoc[0].x;   //horizontal distance from food
          int dif_y = f1.y - s2.qaLoc[0].y;   //vertical distance from food
          //Going Right & Up (Food Forward)
          if (s2.cDir==kiRight && dif_x>0 && dif_y<0) {
              comp=kiRight; 
          }
          if (s2.qaLoc[0].x == f1.x && comp==kiRight && dif_y<0) {
             comp=kiUp; 
          }
          //Going Right & Down (Food Forward)
          if (comp==kiRight && dif_x>0 && dif_y>0) {
             comp=kiRight; 
          }
          if (s2.qaLoc[0].x == f1.x && comp==kiRight && dif_y>0) {
             comp=kiDown; 
          }
          //Going Left & Up (Food Forward)
          if (comp==kiLeft && dif_x<0 && dif_y<0) {
                  comp=kiLeft; 
          }
          if (s2.qaLoc[0].x == f1.x && comp==kiLeft && dif_y<0) {
              comp=kiUp; 
          }
          //Going Left & Down (Food Forward)
          if (comp==kiLeft && dif_x<0 && dif_y>0) {
                  comp=kiLeft; 
          }
          if (s2.qaLoc[0].x == f1.x && comp==kiLeft && dif_y>0) {
              comp=kiDown; 
          }
          //Going Up & Left (Food Forward)
          if (comp==kiUp && dif_y<0 && dif_x<0) {
             comp=kiUp; 
          }
          if (s2.qaLoc[0].y == f1.y && comp==kiUp && dif_x<0) {
             comp=kiLeft; 
          }
          //Going Up & Right (Food Forward)
          if (comp==kiUp && dif_y<0 && dif_x>0) {
             comp=kiUp; 
          }
          if (s2.qaLoc[0].y == f1.y && comp==kiUp && dif_x>0) {
             comp=kiRight; 
          }
          //Going Down & Left (Food Forward)
          if (comp==kiDown && dif_y>0 && dif_x<0) {
             comp=kiDown; 
          }
          if (s2.qaLoc[0].y == f1.y && comp==kiDown && dif_x<0) {
             comp=kiLeft; 
          }
          //Going Down & Right (Food Forward)
          if (comp==kiDown && dif_y>0 && dif_x>0) {
             comp=kiDown; 
          }
          if (s2.qaLoc[0].y == f1.y && comp==kiDown && dif_x>0) {
             comp=kiRight; 
          }
          //++++++++++++++++++++++++++++++++++++++++//
          //Going Left & Up (Food Backward)
          if (comp==kiLeft && dif_y<0 && dif_x>0 ) {
             comp=kiUp; 
          }
          if (s2.qaLoc[0].y == f1.y && comp==kiUp && dif_x>0) {
             comp=kiRight; 
          }
          //Going Left & Down (Food Backward)
          if (comp==kiLeft && dif_y>0 && dif_x>0 ) {
             comp=kiDown; 
          }
          if (s2.qaLoc[0].y == f1.y && comp==kiDown && dif_x>0) {
             comp=kiRight; 
          }
          //Going Right & Up (Food Backward)
          if (comp==kiRight && dif_y<0 && dif_x<0 ) {
             comp=kiUp; 
          }
          if (s2.qaLoc[0].y == f1.y && comp==kiUp && dif_x<0) {
             comp=kiLeft; //return comp;
          }
          //Going Right & Down (Food Backward)
          if (comp==kiRight && dif_y>0 && dif_x<0 ) {
             comp=kiDown; 
          }
          if (s2.qaLoc[0].y == f1.y && comp==kiDown && dif_x<0) {
             comp=kiLeft; 
          }
          //Going Up & Left (Food Backward)
          if (comp==kiUp && dif_x<0 && dif_y>0 ) {
             comp=kiLeft; 
          }
          if (s2.qaLoc[0].x == f1.x && comp==kiLeft && dif_y>0) {
             comp=kiDown; 
          }
          //Going Up & Right (Food Backward)
          if (comp==kiUp && dif_x>0 && dif_y>0 ) {
             comp=kiRight; 
          }
          if (s2.qaLoc[0].x == f1.x && comp==kiRight && dif_y>0) {
             comp=kiDown; 
          }
          //Going Down & Left (Food Backward)
          if (comp==kiDown && dif_x<0 && dif_y<0 ) {
             comp=kiLeft; 
          }
          if (s2.qaLoc[0].x == f1.x && comp==kiLeft && dif_y<0) {
             comp=kiUp; 
          }
          //Going Down & Right (Food Backward)
          if (comp==kiDown && dif_x>0 && dif_y<0 ) {
             comp=kiRight; 
          }
          if (s2.qaLoc[0].x == f1.x && comp==kiRight && dif_y<0) { 
             comp=kiUp; 
          }
          return comp;
}
