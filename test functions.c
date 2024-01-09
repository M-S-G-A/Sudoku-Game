#include "stdio.h"
#include "stdlib.h"
#include "windows.h"
#include "stdbool.h"


void color(int text, int backgrnd){
	HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);  
	SetConsoleTextAttribute(console_color, backgrnd*16+text);
	//0-Black 1-Deep Blue 2-Green 3-Cyan 4-red 5-Purple 6-Brown 
	//7-LightGrey 8-DarkGrey 9-LightBlue 10-LightGreen 11-LightCyan 12-LightRed 13-LightPurple 14-Yellow 15-White
}

void gotoxy(int x, int y){
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD CursorPosition;
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void setcursor(bool visible, DWORD size) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

void frame(int x1, int x2, int y1, int y2){
	system("COLOR 0");
	int j=y1;
	
	while (j<=y2){
		for (int i = x1; i<x2; i++){
			gotoxy(i,j);
			printf("%c", 219);
		}
		j+=5;		
	}
	int i=x1;
	while (i<=x2){
		for (int j = y1; j<=y2; j++){
			gotoxy(i,j);
			printf("%c", 219);
		}
		i+=5;
	}
}

void ascii(){
	for (int i = 0; i<256; i++){
		printf("%d - %c\t", i);
		if (i%8 == 0){
			printf("\n");
		}
	}
}
//	color(0,0);
	
//	gotoxy(x1, y1);
//	printf("%c", 220);
//	gotoxy(x2, y1);
//	printf("%c", 220);
//	gotoxy(x1, y2);
//	printf("%c", 220);
//	gotoxy(x2, y2);
//	printf("%c", 220);


//int main(){
////	frame(5, 64, 5, 15, 1);  // blue = 1
////	char c;
////	
////	printf("Hello");
////	c = getchar();
////	printf("%d", c);
////	
////	color(0,7);  
//}