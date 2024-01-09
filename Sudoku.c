#include "stdio.h"
#include "test sudo.c"

void howtoplay();
void playgame();
void layout();
void gameover();
void challenge_mode();
void init_to_zero(int matrix[9][9]);
int finalcheck(int matrix[9][9]);

int difficulty;
int board[9][9];
int solution[9][9];
char name[30];
int choice;

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 30
#define WIN_WIDTH 70 

struct Position{
	int i;
	int j;
}pos;

int main(){
	
	
	system("COLOR F0");
	srand(time(NULL));
	
	while (1){	
	main:
		init_to_zero(board);
		init_to_zero(solution);
		choice = 0; difficulty = 0;
		
		system("cls");
		gotoxy(20,5); printf("Welcome to SUDOKU Classic Game!!");
		gotoxy(10, 14); printf("Select option: ");
		gotoxy(11, 15); printf("1 - Start New Game");
		gotoxy(11, 16); printf("2 - How to Play");
		gotoxy(11, 17); printf("3 - Quit");
		gotoxy(11, 18); printf("4 - Challenge mode");
		
		gotoxy(10, 20); printf("What's your choice? ");
		choice = getch() - '0';
		gotoxy(30, 20); printf("%d", choice);
//		scanf("%d", &choice);
		
		while (choice<1 || choice>4){
			gotoxy(10, 21); printf("Invalid choice. Try again: ");
			choice = getch() - '0';
			gotoxy(37, 21); printf("%d  ", choice);
//			scanf("%d", choice);
		}
		
		if (choice == 1){
			system("cls");
			gotoxy(10,5); printf("Select your level of difficulty: \n");
			gotoxy(11,6); printf("\t1 - Easy\n");
			gotoxy(11,7); printf("\t2 - Medium\n");
			gotoxy(11,8); printf("\t3 - Hard\n\n");
			gotoxy(85,24); printf("Press 'm' to go back to main menu");
			gotoxy(10,10); printf("Choice: ");
//			scanf("%d", &difficulty);

			difficulty = getch() - '0';
			gotoxy(18, 10); printf("%d", difficulty);
			if (difficulty == 61){
				goto main;
			}
			
			while(difficulty <1 || difficulty>3){
				gotoxy(10, 12); printf("Invalid Choice. Try again: ");
				difficulty = getch() - '0';
				gotoxy(37, 12); printf("%d  ", difficulty);
//				scanf("%d", &difficulty);
			}
			
			playgame();
		}
		
		else if (choice == 2){
			howtoplay();
		}
		
		else if (choice == 4){
			challenge_mode();
		}
		
		else{
			gotoxy(4,22); printf("SEE YOU SOON!!");
			return 0;
		}
	}
	
}

void init_to_zero(int matrix[9][9]){
	for (int i = 0; i<9; i++){
		for (int j = 0; j<9; j++){
			matrix[i][j] = 0;
		}
	}
}

void howtoplay(){
	system("cls");
	gotoxy(20,4); printf("-------------------------------");
	gotoxy(20, 5); printf("|\t      HOW TO PLAY \t  |");
	gotoxy(20,6); printf("-------------------------------");
	gotoxy(5, 10);
	printf("To solve this game you must complete the puzzle by filling every empty cell "); 
	gotoxy(6,11); printf("with any number from 1 to 9.");
	gotoxy(5, 13);
	printf("Watch out!! Each digit you enter should not repeat in the same row, column or block.");
	gotoxy(5,15); printf("In order to fill a  cell, you must enter its coordinates");
	gotoxy(6, 16); printf("~Coordinates are pairs of the form (x,y) where x and y vary from 0 to 8");
	gotoxy(6, 17); printf("~Each Horizontal line is a row and Vertical are Columns");
	gotoxy(6, 18); printf("~To help you understand, numbers from 0 to 8 have been displayed near the grid");
	gotoxy(6, 19); printf("~Those numbers represent the value of each row and column");
	gotoxy(6, 20); printf("~Thus, the 1st element of the 1st row(row 0) has coordinate (0,0)");
	gotoxy(6,21); printf("~The 4th of element of the 8th column(column 7) has coordinate (3,7) and so on.");
	gotoxy(5, 24); printf("Press any key to go to main menu.");
	getch();
}

void playgame(){
	 //Game state
	system("cls");
	int num, lives;
	
	gen_random_numbers(solution, 17);
	if (difficulty == 1){
		if (solveSudoku(solution, 0,0)){
		    copy(solution, board, 75);
		}
		lives = 5;
	}
		
	else if (difficulty == 2){
		if (solveSudoku(solution, 0,0)){
			copy(solution, board, 50);
		}
		lives = 3;
	}
	else{
		if (solveSudoku(solution, 0,0)){
			copy(solution, board, 20);
		}
		lives = 2;
	}
	
	gotoxy(15, 12); printf("Please, your first name: "); fgets(name, sizeof(name), stdin);
	gotoxy(15, 13); printf("Have fun !!");
	gotoxy(15,15); printf("Press any to key to start the game");
	getch();
	while(1){
		
		begin:
			system("cls");
			
			if (lives == 0){
				gameover();
				break;
			}
			
			layout();
		
		//Check the rate of copletionn of Sudoku	
		int filled = finalcheck(board);
		if (filled == 41 && difficulty!= 1 ){
			gotoxy(85, 10); printf("SUDOKU half-filled.");
			gotoxy(85, 11); printf("Keep pushing Champ!!");
			Sleep(2000);
			system("cls");
			goto play;
		}
		
		if (filled == 65){
			gotoxy(85, 10); printf("3/4 of the grid filled");
			gotoxy(85, 11); printf("Almost there Champ!!");
			Sleep(2000);
			system("cls");
			goto play;
		}
		
		if (filled == 81){
			system("cls");
			gotoxy(40, 10); printf("AWESOME VICTORY!!");
			gotoxy(40, 11); printf("You solved this SUDOKU!!");
			gotoxy(38, 13); printf("~~Always Keep your Mind Sharp~~");
			Sleep(3000);
			gotoxy(85, 18); printf("Press any key");
			getch();
			break;
		}
		play:
			layout();
			gotoxy(85,3); printf("Lives: %d", lives);
			gotoxy(85,5); printf("X_Coord: "); /*scanf("%d", &pos.i );*/ pos.i = getch() - '0';
			gotoxy(94, 5); printf("%d", pos.i);
			if (pos.i == 61){
				break;
			}
			
			gotoxy(85,6); printf("Y_Coord: "); /*scanf("%d", &pos.j);*/ pos.j =  getch() - '0';
			gotoxy(94, 6); printf("%d", pos.j);
			if (pos.j == 61){
				break;
			}
		
		while(pos.i<0 || pos.i>8 || pos.j<0 || pos.j>8){
			gotoxy(85,8); printf("Indices are between 0 and 8");
			Sleep(1000);
			system("cls");
			goto begin;
		}
		if (board[pos.j][pos.i] != 0){
			gotoxy(82,8); printf("Cell already filled. Choose another");
			Sleep(1000);
			system("cls");
			goto begin;
		}
		
		gotoxy(85,8); printf("Number: "); /*scanf("%d", &num);*/ num = getch() - '0';
		gotoxy(93, 8); printf("%d", num);
		Sleep(64);
		if (num == 61){
			break;
		}
		
		while(num<1 || num>9){
			gotoxy(85, 9); printf("Number must be between 1 and 9");
			lives -=1;
			Sleep(1000);
			system("cls");
			goto begin;
		}
			
		
//		if (is_valid(board, pos.j, pos.i, num)){
		if (solution[pos.j][pos.i] == num){
			board[pos.j][pos.i] = num;
			system("cls");
			goto begin;
		}
		
		if(solution[pos.j][pos.i] != num){
			gotoxy(85, 10); printf("Wrong number!!");
			lives -=1;
			Sleep(500);
			system("cls");
			goto begin;
//			
		}
	}
}

void layout(){
	gotoxy(1,0); printf("Player: %s", name);
	
	if (difficulty == 1){
		gotoxy(1,1); printf("Difficulty: Easy");
	}
	else if (difficulty == 2){
		gotoxy(1,1); printf("Difficulty: Medium");
	}
	else if(choice == 4){
		gotoxy(1,1); printf("Challenge Mode");
	}
	else if(difficulty == 3){
		gotoxy(1,1); printf("Difficulty: Hard");
	}
	
	display(board);
	gotoxy(30,1); printf("SUDOKU Classic");
	for (int i = 0; i<69 ; i++){
		gotoxy(80,i); printf("%c", 206);
	}
	gotoxy(85,24);printf("Press 'm' to go to main menu");
}

void gameover(){
	system("cls");
	gotoxy(10,5); printf("****GAME OVER****");
	gotoxy(5, 8); printf("Sorry, You lost %s.",name);
	gotoxy(5,9); printf("But this isn't the end Champ.");
	gotoxy(5,10); printf("Give it one more try!!");
	gotoxy(5, 12); printf("Press any key ");
	getch();
	
}

int finalcheck(int matrix[9][9]){
	int count=0; //Number of filled cells in the grid
	for (int i=0; i<9; i++){
		for (int j=0; j<9; j++){
			if (matrix[i][j] != 0){
				count+=1;
			}
		}
	}
	return count;
}

void challenge_mode(){
	 //Game state
	system("cls");
	int num, lives;
	int i, j;
	i = rand()%9;
	j = rand()%9;
	
	board[i][j] = rand()%9 + 1;
	solution[i][j] = board[i][j];
	if (solveSudoku(solution, 0,0)){
		lives = 1;
	}
	
	gotoxy(15, 12); printf("Please, your first name: "); fgets(name, sizeof(name), stdin);
	gotoxy(15, 14); printf("Your task here is to solve a 1-digit sudoku with only 1 life.");
	gotoxy(15, 15); printf("Good luck!!");
	gotoxy(15, 16); printf("You can do it %s", name);
	gotoxy(15,18); printf("Press any to key to start the game");
	getch();
	while(1){
	
		begin:
			system("cls");
			
			if (lives == 0){
				gameover();
				break;
			}
			
			layout();
			
			//Check completion of Sudoku
			int filled = finalcheck(board);
			if (filled == 41){
			gotoxy(85, 10); printf("SUDOKU half-filled.");
			gotoxy(85, 11); printf("Keep pushing Champ!!");
			Sleep(2000);
			system("cls");
			goto begin;
		}
		
		if (filled == 65){
			gotoxy(85, 10); printf("3/4 of the grid filled");
			gotoxy(85, 11); printf("Almost there Champ!!");
			Sleep(2000);
			system("cls");
			goto begin;
		}
		
		if (filled == 81){
			gotoxy(85, 10); printf("AWESOME VICTORY!!");
			gotoxy(85, 11); printf("You solved this SUDOKU!!");
			gotoxy(87, 12); printf("~~Always Keep your Mind Sharp~~");
			Sleep(3000);
			gotoxy(85, 18); printf("Press any key");
			getch();
			break;
		}
			
		gotoxy(85,3); printf("Lives: %d", lives);
		gotoxy(85,5); printf("X_Coord: "); /*scanf("%d", &pos.i );*/ pos.i = getch() - '0';
		gotoxy(94, 5); printf("%d", pos.i);
		if (pos.i == 61){
			break;
		}
			
		gotoxy(85,6); printf("Y_Coord: "); /*scanf("%d", &pos.j);*/ pos.j =  getch() - '0';
		gotoxy(94, 6); printf("%d", pos.j);
		if (pos.j == 61){
			break;
		}
		
		while(pos.i<0 || pos.i>8 || pos.j<0 || pos.j>8){
			gotoxy(85,8); printf("Indices are between 0 and 8");
			Sleep(1000);
			system("cls");
			goto begin;
		}
		
		if (board[pos.j][pos.i] != 0){
			gotoxy(82,8); printf("Cell already filled. Choose another");
			Sleep(1000);
			system("cls");
			goto begin;
		}
		
		gotoxy(85,8); printf("Number: "); /*scanf("%d", &num);*/ num = getch() - '0';
		gotoxy(93, 8); printf("%d", num);
		Sleep(200);
		if (num == 61){
			break;
		}
		
		while(num<1 || num>9){
			gotoxy(85, 9); printf("Number must be between 1 and 9");
			lives -=1;
			Sleep(1000);
			system("cls");
			goto begin;
		}
			
		
		
//		if (is_valid(board, pos.j, pos.i, num)){
		if (solution[pos.j][pos.i] == num){
			board[pos.j][pos.i] = num;
			system("cls");
			goto begin;
		}
		
		if(solution[pos.j][pos.i] != num){
			gotoxy(85, 10); printf("Wrong number!!");
			lives -=1;
			Sleep(500);
			system("cls");
			goto begin;
//			
		}
	}
	
}