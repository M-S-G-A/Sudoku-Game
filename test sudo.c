#include "stdio.h"
#include "test functions.c"
#include "conio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "windows.h"
#include "time.h"



//#include <gtk.h>
bool row_check(int matrix[9][9], int row, int num);
bool col_check(int matrix[9][9], int col, int num);
bool cube_check(int matrix[9][9],int row, int col, int num);
void set_table(int x1, int x2, int y1,int y2);
void display(int matrix[9][9]);
bool is_valid(int matrix[9][9], int row, int col, int num);
bool solveSudoku(int matrix[9][9], int row, int col);
void gen_random_numbers(int matrix[9][9], int max);
void copy(int matrix1[9][9], int matrix2[9][9], int max);
void display_index();

//int main(){
//	system("COLOR F0");
//	srand(time(NULL));
//	int solution[9][9] = {0};
//	int board[9][9]={0};
//	
//	gen_random_numbers(board, 20);
//	display(board);
//	getch();
////	copy(board, solution);
////	
//	if (solveSudoku(board, 0,0)){
//		system("cls");
//		display(board);
//		printf("SUDOKU SOLVED!!");
//	}
//	else{
//		printf("No Solution!!");
//	}
//	return 0;	
//}

void display(int matrix[9][9]){
	int a= 10, b=5;
	gotoxy(a, b-1); printf("%c_____%c_____%c_____%c_____%c_____%c_____%c_____%c_____%c_____%c",220, 220,220,220,220,220,220,220,220,220);
    for (int i=0; i<9; i++){
    	gotoxy(a,b);
    	printf("%c", 219);
        for (int j=0; j<9; j++){
        	if (matrix[i][j] == 0){
        		printf("     %c", 219);
			}
			else{
				printf("  %d  %c", matrix[i][j],219);
			}	       		
		}
		gotoxy(a,b+1); printf("%c_____%c_____%c_____%c_____%c_____%c_____%c_____%c_____%c_____%c",219, 219,219,219,219,219,219,219,219,219);
		b+=2;
	}
	display_index();
}


void display_index(){
	int a = 13, b = 3;
	for (int i = 0; i<9; i++){
		gotoxy(a,b); printf("%d", i);
		a+=6; 
	}
	a = 8; b = 5;
	for (int i = 0; i<9; i++){
		gotoxy(a,b); printf("%d", i);
		b+=2;
	}
}

//void set_table(int x1, int x2, int y1,int y2){
//	int j = y1;
//	while (j<=y2){
//		for (int i = x1; i<x2; i++){
//			gotoxy(i,j);
//			printf("%c", 176);
//		}
//	j+=5;			
//	}
//	
//	int i=x1;
//	while (i<=x2){
//		for (int j = y1; j<y2+1; j++){
//			gotoxy(i,j);
//			printf("%c", 176);
//		}
//	i+=5;
//	}
//}

bool row_check(int matrix[9][9], int row, int num){
	for (int j=0; j<9; j++){
		if (matrix[row][j] == num){
			return false;
		}
	}
	return true;
}

bool col_check(int matrix[9][9], int col, int num){
	for (int i=0; i<9;i++){
		if (matrix[i][col] == num){
			return false;
		}
	}
	
	return true;
}

bool cube_check(int matrix[9][9], int row, int col, int num){
	int m = (row/3)*3,  n=(col/3)*3;
		for (int i=m; i<m+3; i++){
			for (int j=n; j<n+3; j++){
				if (matrix[i][j] == num){
					return false;
				}
			}
		}	
	return true;
}

bool solveSudoku(int matrix[9][9], int row, int col){
	if (row==9){
		return true;
	}
	if (col==9){
		return solveSudoku(matrix, row+1, 0);
	}
	if (matrix[row][col]!=0){
		return solveSudoku(matrix, row, col+1);
	}
	else{
		for(int num=1; num<=9; num++){
			if (is_valid(matrix, row, col, num)){
				matrix[row][col] = num;
//				system("cls");
//				display(matrix);
				if (solveSudoku(matrix, row, col+1)){
					return true;
				}
				matrix[row][col]=0;
//				system("cls");
//				display(matrix);
			}
		}
	return false;
	}
}
 
 bool is_valid(int matrix[9][9], int row, int col,  int num){
	return (row_check(matrix, row, num) && col_check(matrix, col, num) && cube_check(matrix, row, col, num));
}

//void gen_random_numbers(int matrix[9][9]){
//	int number, count=0;
//    for (int i = 0; i < 9; i++){
////    	while(count<=17){
//    		for (int j=0; j<9; j++){
//    			number = (rand()%9) + 1;
//				if (is_valid(matrix, i, j, number)){
//					matrix[(rand()+i)%9][(rand()+j)%9] = number;
//					count+=1;
//				}
//				if (count>17){
//					break;
//				}
//			}
////		}
//		if (count>17){
//			break;
//		}	
//	}
//}

void gen_random_numbers(int matrix[9][9], int max){
	int number,count=0;
	while (count<max){
		int i = rand()%9;
		int j= rand()%9;
    	number = (rand()%9) + 1;
		if (is_valid(matrix, i, j, number)){
			matrix[i][j] = number;
			count+=1;
		}
	}
}

void copy(int matrix1[9][9], int matrix2[9][9], int max){
	int count = 0;
	while (count<max){
		int i = rand()%9;
		int j = rand()%9;
		matrix2[i][j] = matrix1[i][j];
		count+=1;
	}
}
