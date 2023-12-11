#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <ncurses/ncurses.h>
#include "Untitled3.h"

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
    gotoxy(60,23);
    for(int i =0; i<10; i++){
        cout<<x;
        Sleep(200);
    }
    gotoxy(60,23);
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

void gameover(){
	system("cls");
	cout<<endl;
	cout<<"\t\t--------------------------"<<endl;
	cout<<"\t\t-------- Game Over -------"<<endl;
	cout<<"\t\t--------------------------"<<endl<<endl;
	cout<<"\t\tPress Y/y to back to menu.  ";
	getch();

}
void tepi(){
    for(int i=0; i<SCREEN_HEIGHT; i++){
		for(int j=0; j<17; j++){
			gotoxy(0+j,i); cout<<"±";
			gotoxy(WIN_WIDTH-j,i); cout<<"±";
		}
	} 
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(SCREEN_WIDTH,i); cout<<"±";
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
	system("color C");
	tepi(); 
	updateScore();
	genEnemy(0);
	genEnemy(1);
	
	gotoxy(WIN_WIDTH + 7, 4); name[i];
	gotoxy(WIN_WIDTH + 7, 2);cout<<"Car Game";
	gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
	gotoxy(WIN_WIDTH + 6, 6);cout<<"----------";
	gotoxy(WIN_WIDTH + 7, 12);cout<<"Control ";
	gotoxy(WIN_WIDTH + 7, 13);cout<<"-------- ";
	gotoxy(WIN_WIDTH + 2, 14);cout<<" A Key - Left";
	gotoxy(WIN_WIDTH + 2, 15);cout<<" D Key - Right"; 
	
	gotoxy(18, 5);cout<<"Press any key to start";
	getch();
	endwin();
	gotoxy(18, 5);cout<<"                      ";
	
	while(1){
		if(kbhit()){
			char ch = getch();
			endwin();
			if( ch=='a' || ch=='A' ){
				if( carPos > 18 )
					carPos -= 4;
			}
			if( ch=='d' || ch=='D' ){
				if( carPos < 50 )
					carPos += 4;
			} 
			if(ch==27){
				break;
			}
		} 
		
		drawCar(); 
		drawEnemy(0); 
		drawEnemy(1); 
		if( collision() == 1  ){
			gameover();
		} 
		Sleep(50);
		eraseCar();
		eraseEnemy(0);
		eraseEnemy(1);   
		
		if( musuhY[0] == 10 )
			if( musuhFlag[1] == 0 )
				musuhFlag[1] = 1;
		
		if( musuhFlag[0] == 1 )
			musuhY[0] += 1;
		
		if( musuhFlag[1] == 1 )
			musuhY[1] += 1;
		 
		if( musuhY[0] > SCREEN_HEIGHT-4 ){
			resetEnemy(0);
			score++;
			updateScore();
		}
		if( musuhY[1] > SCREEN_HEIGHT-4 ){
			resetEnemy(1);
			score++;
			updateScore();
		}
	}
}
void visual(){
   gotoxy(31,10); cout << "=============================================================================";
   gotoxy(31,11); cout << "																				";
   gotoxy(31,12); cout << "																				";
   gotoxy(31,13); cout << "																				";
   gotoxy(31,14); cout << "																				";
   gotoxy(31,15); cout << "																				";
   gotoxy(31,16); cout << "																				";
   gotoxy(31,17); cout << "                                          						            ";
   gotoxy(31,18); cout << "                                     						                ";
   gotoxy(31,19); cout << "                                           						            ";
   gotoxy(31,20); cout << "==============================================================================\n";
}
void username(){
system("cls"); 
visual();
gotoxy(30,15); cout << "Enter Your Name (Surname) : ";
cin >> name[i];
global();
}

void home(){
    system("cls");
    system("color 2");
    visual();
    gotoxy(31,13); cout << "                                1. Start Game"; 
    gotoxy(31,14); cout << "                                2. Exit Game";
    gotoxy(31,17); cout << "                                  Option : ";
    cin >> option;
    	if(option==1){
            global(); //loading dulu 
    		username(); //masuk ke username
            return game();
    	}else if(option==2){
    		exit(0);
    	}else{
    		return home();
		}
    
}

int main(){
	initscr(); //Memulai ncuruses
	load();	//file header
	endwin(); //supaya ncurses dari header selesai
    home(); //masuk void
    game();
    return 0;
}
