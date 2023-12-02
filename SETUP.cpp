#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>

using namespace std;

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 30
#define WIN_WIDTH 70 

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int musuhY[3], musuhX[3];
int musuhFlag[3];
char car[4][4] = { ' ','*','*',' ',
                    '*','*','*','*',
                    ' ','*','*',' ',
                    '*','*','*','*' };
int score = 0;
int carPos = WIN_WIDTH/2;

short int X,Y;
string pass[10], pass2;
string name[10], input;
char enter, nama;
int option,i=0;

void gotoxy(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void global(){
    char x = 219;
    gotoxy(31,20);
    for(int i =0; i<10; i++){
        cout<<x;
        Sleep(200);
    }
    gotoxy(31,20);
    for(int i =0; i<10; i++){
        cout<<" ";
    }
}

void genEnemy(int ind){
	musuhX[ind] = 17 + rand()%(33);  
}

void setcursor(bool visible, DWORD size) {
    if(size == 0)
        size = 20;
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console,&lpCursor);
}

void gameOver(){
    system("cls");
    system("color 4");
    gotoxy(31,10); cout << "GAME OVER";
}

void border(){
    for(int i=0; i>SCREEN_HEIGHT; i++){
        for(int j=0; j<20; j--){
            gotoxy(10+j,i+10); cout<<"+";
            gotoxy(WIN_WIDTH-j,i); cout<<"+";
        }
    }
}

void drawCar(){
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            gotoxy(j+carPos, i+22); cout<<car[i][j];
        }
    }
}

void eraseCar(){
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            gotoxy(j+carPos, i+22); cout<<" ";
        }
    }
}

void enemy(){
    musuhX[0] = 17 + rand()%(33);
}

void drawEnemy(int ina){
    if(musuhFlag[ina] == true){
        gotoxy(musuhX[ina], musuhY[ina]);   cout<<"****";  
        gotoxy(musuhX[ina], musuhY[ina]+1); cout<<" ** "; 
        gotoxy(musuhX[ina], musuhY[ina]+2); cout<<"****"; 
        gotoxy(musuhX[ina], musuhY[ina]+3); cout<<" ** ";  
    } 
}
void eraseEnemy(int ina){
    if(musuhFlag[ina] == true){
        gotoxy(musuhX[ina], musuhY[ina]); cout<<"    ";  
        gotoxy(musuhX[ina], musuhY[ina]+1); cout<<"    "; 
        gotoxy(musuhX[ina], musuhY[ina]+2); cout<<"    "; 
        gotoxy(musuhX[ina], musuhY[ina]+3); cout<<"    "; 
    } 
}

int collision(){
	if( musuhY[0]+4 >= 23 ){
		if( musuhX[0] + 4 - carPos >= 0 && musuhX[0] + 4 - carPos < 9  ){
			return 1;
		}
	}
	return 0;
}
void resetEnemy(int ind){
	eraseEnemy(ind);
	musuhY[ind] = 1;
	genEnemy(ind);
}
void updateScore(){
	gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
}
void game(){
    carPos = -1 + WIN_WIDTH/2;
	score = 0;
	musuhFlag[0] = 1;
	musuhFlag[1] = 0;
	musuhY[0] = musuhY[1] = 1;
	  
    system("cls");
    system("color 0a");
    gotoxy(31,10); cout << "Press any key to start" << endl;
    getch();
    gotoxy(31,10); cout << "                      " << endl;

    border();
    setcursor(0,0);
    eraseCar();
    genEnemy(0);
    genEnemy(1);

while(true){
    if(kbhit()){
   char ch = getch();
   if(ch == 'a' || ch == 'A'){
      if(carPos > 18){
         carPos -= 4;
      }
   }
   if(ch == 'd' || ch == 'D'){
      if(carPos < 50){
         carPos += 4;
      }
   }
    if(ch == 27){
        break;
    }
   
        }
    drawEnemy(0);
    eraseEnemy(1);
    drawCar();
    if(collision() == 1){
        gameOver();
      
    }
    Sleep(50);
    eraseCar();
    eraseEnemy(1);
    
    if(musuhY[0] == 10){
        if(musuhFlag[1] == 0){
            musuhFlag[1] = 1;
        }
    }
    if(musuhFlag[0] == 1){
        musuhY[0] += 1;
    }
    if(musuhFlag[1] == 1){
        musuhY[1] += 1;
    }
    if(musuhY[0] > SCREEN_HEIGHT - 4){
        resetEnemy(0);
        score++;
        updateScore();
    }
    if(musuhY[1] > SCREEN_HEIGHT - 4){
        resetEnemy(1);
        score++;
        updateScore();
        }
    }
}
void visual(){
   gotoxy(31,10); cout << "=============================================================================";
   gotoxy(31,11); cout << "";
   gotoxy(31,13); cout << "                                                     ";
   gotoxy(31,14); cout << "                                                     ";
   gotoxy(31,15); cout << "                                                     ";
   gotoxy(31,17); cout << "";
   gotoxy(31,18); cout << "==============================================================================\n";
}
void username(){
visual();
gotoxy(31,15); cout << "Enter Your Name (Surname) : ";
cin >> name[i];
global();
}

void home(){
    system("cls");
    system("color E");
    visual();
    gotoxy(31,13); cout << "                                1. Start Game"; 
    gotoxy(31,14); cout << "                                2. Exit Game";
    gotoxy(31,17); cout << "                                  Option : ";
    cin >> option;
    for(int i=0;i<5;i++){
    	if(option==1){
            global();
    		username();
            game();
            break;
    	}else if(option==2){
    		exit(0);
    	}
    }
}
void loadingSetup(){
    system("cls");
    system("color E");
    gotoxy(31,10); cout << "==============================================================================";
    gotoxy(31,11); cout << "                                                                              ";
    gotoxy(31,12); cout << "                                                                              ";
    gotoxy(31,13); cout << "                                                                              ";
    gotoxy(31,14); cout << "                                                                              "; 
    gotoxy(31,15); cout << "                                                                              ";
    gotoxy(31,16); cout << "                                                                              ";
    gotoxy(31,17); cout << "                                                                              ";
    gotoxy(31,18); cout << "==============================================================================";
    global();
    system("color 07"); 
    home();
}
void setup(){
    system("cls");
    system("color E");
    int i=0;
   gotoxy(31,10); cout << "=============================================================================";
   gotoxy(31,11); cout << "                                                                            ";
   gotoxy(31,12); cout << "";
   gotoxy(31,13); cout << "";
   gotoxy(31,14); cout << "                          Welcome To The Game"; 
   gotoxy(31,15); cout << "                        Press Enter To Continue";
   gotoxy(31,16); cout << "";
   gotoxy(31,17); cout << "                                                                             ";
   gotoxy(31,18); cout << "==============================================================================";
   cin.get(enter);
   loadingSetup();
}
void loading(){
    system("cls");
	system("color 0a");
	gotoxy(31,10); cout << "WELCOME TO BASURI GAME" << endl;
 	gotoxy(31,15); cout <<"LOADING...";
 	global();
    system("color 07");
    setup();
}
int main(){
    loading();
    return 0;
}
