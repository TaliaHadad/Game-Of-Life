/******************************************
* Talia Hadad
* 209049253
* 83-120-04
* Ex 3
******************************************/

#include<stdio.h>

#define MAX_HEIGHT_SIZE 70
#define MIN_HEIGHT_SIZE 10
#define MAX_WIDTH_SIZE 70
#define MIN_WIDTH_SIZE 10
#define PLAYER_COLOR 'R'
#define COMPUTER_COLOR 'G'
#define DEAD_COLOR '-'


void GetDimentions(int *width, int *height);
void InitLivingCells(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int i, int j, int* livingCellsR, int* livingCellsG);
int CheckNewCell(int x, int y, char *color, int width, int height);
void InitBoard(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int* width, int* height, int* livingCellsR, int* livingCellsG);
long long int GetNumOfGenerations();
void InitGame(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int* width, int* height, long long int* generations, int* livingCellsR, int* livingCellsG);
void PlayGame(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, long long int generations, int i, int j, int* livingCellsR, int* livingCellsG);
void CountNeighbours(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int i, int j, int* livingCellsR, int* livingCellsG);
void ComputerTurn(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int* x, int* y);
void ProcessBoard(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], char copyBoard[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height);
void PrintBoard(const char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int* livingCellsR, int* livingCellsG);
int CheckForAWin(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int i, int j, int livingCellsR, int livingCellsG);
void DeclaringVictory(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int i, int j, int livingCellsR, int livingCellsG);
void CaseVictoryInTurn(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int i, int j, int livingCellsR, int livingCellsG);

int main()
{
	int * i = NULL;
	int * j = NULL;
	int width, height, livingCellsG, livingCellsR;
	long long int generations;
	char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE];
	InitGame(board, &width, &height, &generations, &livingCellsG, &livingCellsR);
	PlayGame(board, width, height, generations, &i, &j, &livingCellsG, &livingCellsR);

	system("pause");
	return 0;
}
/***************************************************************************************
Function name: GetDimentions
Input: ponters to width and height.
Output: None.
The function operation: The function will ask the user to insert height and width.
Check input after each input (after the width and after the height separately),
and ask again if the input is not legal.
****************************************************************************************/
void GetDimentions(int *width, int *height)
{
	printf("Welcome to the game of life!\nSettings:\n");
	printf("Enter width (10-70):\n");
	scanf("%d", width);
	//checks if the width inserted is valid
	while (*width < 10 || *width>70)
	{
		printf("Enter width (10-70):\n");
		scanf("%d", width);
	}

	printf("Enter height (10-70):\n");
	scanf("%d", height);
	//checks whether the inserted length is valid
	while (*height < 10 || *height>70)
	{
		printf("Enter height (10-70):\n");
		scanf("%d", height);
	}
}
/***************************************************************************************
Function name: InitLivingCells
Input: the board, height and width of the board, i, j, and pointers to livingCellsR and livingCellsG.
Output: None.
The function operation: The function will accept as a parameter the board,
its length and width, and will pick up from the user how many live cells) in total,
for the two players together he wants for them at the beginning of the game.
****************************************************************************************/
void InitLivingCells(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int i, int j, int* livingCellsR, int* livingCellsG)
{
	int s, livingCells, x, y;
	char color;
	printf("Enter number of living cells (0-%d):\n", width*height);
	scanf("%d", &livingCells);
	//checks whether the number of living cells inserted is valid
	while (livingCells < 0 || livingCells > (width*height))
	{
		printf("Enter number of living cells(0-%d):\n", width*height);
		scanf("%d", &livingCells);
	}

	//request from user to set live cells in the board
	for (s = 0; s < livingCells; s++)
	{
		printf("Enter x y and color (R/G):\n");
		scanf("%d %d %c", &x, &y, &color);
		//checks whether the cell the user has selected is already alive
		while (CheckNewCell(x, y, &color, width, height) == 0 || board[x][y] != '-')
		{
			printf("Enter x y and color (R/G):\n");
			scanf("%d %d %c", &x, &y, &color);
		}
		board[x][y] = color;
	}
	printf("\n");
	PrintBoard(board, width, height, livingCellsG, livingCellsR);
}
/***************************************************************************************
Function name: CheckNewCell
Input: the height and width of the board,x ,y ,pointers to color .
Output: return 0 - if the index of the cell is not in the limits of the boardand,
and allso if the input is not according to the game rules.
return 1 - if the index of the cell is in the limits of the boardand,
and allso according to the game rules.
The function operation: check if input of the players is according to the game rules.
****************************************************************************************/
int CheckNewCell(int x, int y, char *color, int width, int height)
{
	//check if the index of the cell is in the limits of the board
	if (x >= width || x < 0)
		return 0;

	if (y >= height || y < 0)
		return 0;

	//the board should contain upper case letters so if we have a lower input we need to convert the input
	if (*color == 'g')
		*color = COMPUTER_COLOR;

	if (*color == 'r')
		*color = PLAYER_COLOR;

	//check if the input is not according to the game rules
	if (*color != PLAYER_COLOR && *color != COMPUTER_COLOR)
		return 0;

	return 1;
}
/***************************************************************************************
Function name: InitBoard
Input: the board, pointers to the height the width and to livingCellsR and livingCellsG.
Output: None.
The function operation:
The function will first call the getDimentions function.
The function will then initialize the panel by placing the '-' character in each cell.
The function will then be called to initLivingCells to initialize the board with live cells.
****************************************************************************************/
void InitBoard(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int* width, int* height, int* livingCellsR, int* livingCellsG)
{
	int i, j;
	GetDimentions(width, height);
	//initialization of a game board with "-"
	for (i = 0; i < *height; i++)
		for (j = 0; j < *width; j++)
			board[i][j] = '-';

	//adds the input of the living cells from the user to the board
	InitLivingCells(board, *width, *height, i, j, livingCellsR, livingCellsG);
}
/***************************************************************************************
Function name: getNumOfGenerations
Input: NumOfGenerations- input of the number of live cells entered by the user
Output: num of generations.
The function operation:Ask the user to enter the maximum number of generations in the game, followed by the game
will be finish and the winner  will be calculated.
****************************************************************************************/
long long int GetNumOfGenerations()
{
    long long int NumOfGenerations;
	printf("\n");
	printf("Enter number of generations(>=0):\n");
	scanf("%lld", &NumOfGenerations);
	printf("\n");
	// check if the input of NumOfGenerations is according to the game rules 
	while (NumOfGenerations < 0)
	{
		printf("\n");
		printf("Enter number of generations(>=0):\n");
		scanf("%lld", &NumOfGenerations);
		printf("\n");
	}
	return NumOfGenerations;
}
/***************************************************************************************
Function name: InitGame
Input: the board, pointers to the height the width the genertions and to livingCellsR and livingCellsG.
Output: None.
The function operation: use the functions defined above to initialize the board and receive the number
Generations.
****************************************************************************************/
void InitGame(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int* width, int* height, long long int* generations, int* livingCellsR, int* livingCellsG)
{
	InitBoard(board, width, height, livingCellsR, livingCellsG);
	*generations = GetNumOfGenerations();
}
/***************************************************************************************
Function name: PlayGame
Input: the board, the height and the width of the board, generations, i, j, and pointers to livingCellsR and livingCellsG.
Output: None .
The function operation: cauclate the next genertion and print the bord. then give the players to make a move in turns.
after each move cauclate the next genertion, print the bord and also chake if the game is over or not.
****************************************************************************************/
void PlayGame(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, long long int generations, int i , int j, int* livingCellsR, int* livingCellsG)
{
	int k, row, col;
	char copyBoard[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], color;
	CheckForAWin(board, width, height, i, i, livingCellsR, livingCellsG);
	printf("Welcome to the game of life!\nThis is the initial board:\n");
	//calculates one generation ahead based on the initial generation and printing the board to the screen.
	ProcessBoard(board, copyBoard, width, height);
	PrintBoard(board, width, height, livingCellsG, livingCellsR);
	CheckForAWin(board, width, height, i, i, livingCellsR, livingCellsG);
	//loop to sum the number of live cells each player has
	for (k = 0; k < generations; k++)
	{
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				if (board[i][j] == 'R')
					livingCellsR++;
				else if (board[i][j] == 'G')
					livingCellsG++;
			}
		}
		// check if the number of living cells is zero
		if (livingCellsG == 0 || livingCellsR == 0)
			break;
		// if the number of living cells is bigger then zero
		else
		{
			//check the number of generations left to play
			if (k % 2 == 0)
			{
				printf("\n");
				printf("R is playing\nx y:\n");
				color = 'R';
				scanf("%d %d", &row, &col);
				//checks whether the cell the user has selected is already alive
				while (CheckNewCell(row, col, &color, width, height) == 0)
					scanf("%d %d", &row, &col);

				if (board[row][col] == 'G' || board[row][col] == '-')
				{
					board[row][col] = 'R';
					CaseVictoryInTurn(board, width, height, i, j, livingCellsR, livingCellsG);
					ProcessBoard(board, copyBoard, width, height);
					PrintBoard(board, width, height, livingCellsG, livingCellsR);
					CheckForAWin(board, width, height, i, j, livingCellsR, livingCellsG);
					//PrintBoard(board, width, height, livingCellsG, livingCellsR);
					printf("\n");
				}
				else if (board[row][col] == 'R')
				{
					board[row][col] = 'R';
					CaseVictoryInTurn(board, width, height, i, j, livingCellsR, livingCellsG);
					ProcessBoard(board, copyBoard, width, height);
					PrintBoard(board, width, height, livingCellsG, livingCellsR);
					CheckForAWin(board, width, height, i, j, livingCellsR, livingCellsG);
					//PrintBoard(board, width, height, livingCellsG, livingCellsR);
					printf("\n");
				}
			}
			else
			{
				printf("G is playing\n");
				ComputerTurn(board, width, height, &row, &col);
				printf("%d %d\n", row, col);
				board[row][col] = 'G';
				CaseVictoryInTurn(board, width, height, i, j, livingCellsR, livingCellsG);
				ProcessBoard(board, copyBoard, width, height);
				PrintBoard(board, width, height, livingCellsG, livingCellsR);
				CheckForAWin(board, width, height, i, j, livingCellsR, livingCellsG);
				//PrintBoard(board, width, height, livingCellsG, livingCellsR);
			}

		}
	}// end of for loop 
	printf("\n");

	// case k = generations, sum the number of live cells each player has to end the game
	if (k == (generations) || generations == 0)
	{
		DeclaringVictory(board, width, height, i, i, livingCellsR, livingCellsG);
		//PrintBoard(board, width, height, livingCellsG, livingCellsR);
	}
}
/*****************************************************************************************
Function name: CountNeighbours
Input: the board, the height and the width of the board, i, j, and pointers to livingCellsR and livingCellsG.
Output: None.
The function operation:gets a location on the board and checks how much neighbours
there is for that cell.
*****************************************************************************************/
void CountNeighbours(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int i, int j, int* livingCellsR, int* livingCellsG)
{
	*livingCellsG = 0;
	*livingCellsR = 0;
			// if staetments to count the neighbours
			//***********************************************************************
			if (board[((i - 1) + height) % height][((j - 1) + width) % width] == 'R')
				(*livingCellsR)++;
			else if (board[((i - 1) + height) % height][((j - 1) + width) % width] == 'G')
				(*livingCellsG)++;
			//************************************************************************
			if (board[((i - 1) + height) % height][(j + width) % width] == 'R')
				(*livingCellsR)++;
			else if (board[((i - 1) + height) % height][(j + width) % width] == 'G')
				(*livingCellsG)++;
			//**********************************************************************
			if (board[((i - 1) + height) % height][((j + 1) + width) % width] == 'R')
				(*livingCellsR)++;
			else if (board[((i - 1) + height) % height][((j + 1) + width) % width] == 'G')
				(*livingCellsG)++;
			//**********************************************************************
			if (board[(i + height) % height][((j - 1) + width) % width] == 'R')
				(*livingCellsR)++;
			else if (board[(i + height) % height][((j - 1) + width) % width] == 'G')
				(*livingCellsG)++;
			//***********************************************************************
			if (board[(i + height) % height][((j + 1) + width) % width] == 'R')
				(*livingCellsR)++;
			else if (board[(i + height) % height][((j + 1) + width) % width] == 'G')
				(*livingCellsG)++;
			//**********************************************************************
			if (board[((i + 1) + height) % height][((j - 1) + width) % width] == 'R')
				(*livingCellsR)++;
			else if (board[((i + 1) + height) % height][((j - 1) + width) % width] == 'G')
				(*livingCellsG)++;
			//**********************************************************************
			if (board[((i + 1) + height) % height][(j + width) % width] == 'R')
				(*livingCellsR)++;
			else if (board[((i + 1) + height) % height][(j + width) % width] == 'G')
				(*livingCellsG)++;
			//**********************************************************************
			if (board[((i + 1) + height) % height][((j + 1) + width) % width] == 'R')
				(*livingCellsR)++;
			else if (board[((i + 1) + height) % height][((j + 1) + width) % width] == 'G')
				(*livingCellsG)++;
}
/***************************************************************************************
Function name: ComputerTurn
Input: the board, the height and the width, and pointers to the computer next move location (x,y).
Output: None.
The function opration: cauclate the next move the computer will make.
****************************************************************************************/
void ComputerTurn(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int* x, int* y)
{
	int i, j;
	int localX[2] = { 0,0 }, localY[2] = { 0,0 };
	int flag[2] = { 0,0 };
	int playerNeighbours = 0, computerNeighbours = 0;
	char copyBoard[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE];

	//computer scans the board from the top left to the bottom right
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			CountNeighbours(board, width, height, i, j, &playerNeighbours, &computerNeighbours);
			//look for the first player cell with 2 or 3 neighbours, and return the location
			if (board[i][j] == PLAYER_COLOR && (playerNeighbours + computerNeighbours == 2 || playerNeighbours + computerNeighbours == 3))
			{
				*x = i;
				*y = j;
				return;
			}
			//look for the first dead cell with 2 or 3 neighbours that are mostly belong to the player, and remember it
			if (board[i][j] == DEAD_COLOR && playerNeighbours > computerNeighbours && !flag[0] &&
				(playerNeighbours + computerNeighbours == 2 || playerNeighbours + computerNeighbours == 3))
			{
				localX[0] = i;
				localY[0] = j;
				flag[0] = 1;
			}
			//look for the first player cell, and remember it
			if (board[i][j] == PLAYER_COLOR && !flag[1])
			{
				localX[1] = i;
				localY[1] = j;
				flag[1] = 1;
			}
		}
	}// end of for loop
	 // if we are here, we didn't found player cell with 2 or 3 neighbours
	 // if we found dead cell with 2 or 3 neighbours that are mostly belong to the player, we return the location
	if (flag[0])
	{
		*x = localX[0];
		*y = localY[0];
		return;
	}
	// if we are here, we didn't found dead cell with 2 or 3 neighbours that are mostly belong to the player
	// we return the location of the first player cell
	*x = localX[1];
	*y = localY[1];
}
/***************************************************************************************
Function name: ProcessBoard
Input: the board,copyBoard, width and height of the board.
Output: None.
The function operation:cauclate the next generation acording to the game rules .
****************************************************************************************/
void ProcessBoard(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], char copyBoard[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height)
{
	int livingCellsG, livingCellsR, i, j;
	//copy between boards
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			copyBoard[i][j] = board[i][j];
	
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			CountNeighbours(board, width, height, i, j, &livingCellsR, &livingCellsG);

			//promotes cells for the next generation according to the following rules:
			if ((livingCellsG + livingCellsR) >= 4 || (livingCellsG + livingCellsR) <= 1)
				copyBoard[i][j] = '-';
			else if (board[i][j] == '-' && (livingCellsG + livingCellsR) == 3)
			{
				if (livingCellsG < livingCellsR)
					copyBoard[i][j] = 'R';
				else
					copyBoard[i][j] = 'G';
			}
		}
	//copy from board to copyboard between generations 
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			board[i][j] = copyBoard[i][j];

}
/***************************************************************************************
Function name: printBoard
Input: the board, width of the board, height of the board and pointers to livinigCellsG and livinigCellsR.
Output: None.
The function operation: printing the game board.
****************************************************************************************/
void PrintBoard(const char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int* livingCellsR, int* livingCellsG)
{
	int i, j;
	// loop to print each cell in the game board
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
			printf("%c", board[i][j]);
		printf("\n");
	}
	CheckForAWin(board, width, height, i, j, livingCellsR, livingCellsG);
}
/***************************************************************************************
Function name: CheckOptioForAWin
Input: the board, width of the board, height of the board, i, j, livingCellsR, livingCellsG.
Output: return 0 in case there is no winer yet.
The function operation: check if there is a game winer already.
****************************************************************************************/
int CheckForAWin(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int i, int j, int livingCellsR, int livingCellsG)
{
	 livingCellsG = 0;
	 livingCellsR = 0;
	 // loop to the amount of living cells in the board
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (board[i][j] == 'R')
				livingCellsR++;
			else if (board[i][j] == 'G')
				livingCellsG++;
		}
	}
	// if staetments for announcing the end of the game
	if (livingCellsG == 0 && livingCellsR == 0)
		DeclaringVictory(board, width, height, i, j, livingCellsR, livingCellsG);
	else if (livingCellsG != 0 && livingCellsR == 0)
		DeclaringVictory(board, width, height, i, j, livingCellsR, livingCellsG);
	else if (livingCellsG == 0 && livingCellsR != 0)
		DeclaringVictory(board, width, height, i, j, livingCellsR, livingCellsG);
	else if (livingCellsG != 0 && livingCellsR != 0)
		return 0;
}
/***************************************************************************************
Function name: DeclaringVictory
Input: the board, width of the board, height of the board, i, j, livingCellsR, livingCellsG.
Output: None.
The function operation: check and print the game winer.
****************************************************************************************/
void DeclaringVictory(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int i, int j, int livingCellsR, int livingCellsG)
{
	livingCellsG = 0;
	livingCellsR = 0;
	// loop to the amount of living cells in the board
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (board[i][j] == 'R')
				livingCellsR++;
			else if (board[i][j] == 'G')
				livingCellsG++;
		}
	}
	// if staetments for announcing the end of the game
	if (livingCellsG > livingCellsR)
		printf("Game over! G is the winner :(");
	else if (livingCellsR > livingCellsG)
		printf("Game over! R is the winner :)");
	else if (livingCellsG == livingCellsR)
		printf("Game over! There is no winner :|");
	//exit(1);
	system("pause");
}
/***************************************************************************************
Function name: CaseVictoryInTurn
Input: the board, width of the board, height of the board, i, j, livingCellsR, livingCellsG.
Output: None.
The function operation: check and print the game winer.
****************************************************************************************/
void CaseVictoryInTurn(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int i, int j, int livingCellsR, int livingCellsG)
{
	livingCellsG = 0;
	livingCellsR = 0;
	// loop to the amount of living cells in the board
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (board[i][j] == 'R')
				livingCellsR++;
			else if (board[i][j] == 'G')
				livingCellsG++;
		}
	}
	// if staetments for announcing the end of the game
	if (livingCellsG == 0 && livingCellsR == 0)
	{
		PrintBoard(board, width, height, livingCellsG, livingCellsR);
		DeclaringVictory(board, width, height, i, j, livingCellsR, livingCellsG);
		exit(1);
	}
	else if (livingCellsG != 0 && livingCellsR == 0)
	{
		PrintBoard(board, width, height, livingCellsG, livingCellsR);
		DeclaringVictory(board, width, height, i, j, livingCellsR, livingCellsG);
		exit(1);
	}
	else if (livingCellsG == 0 && livingCellsR != 0)
	{
		PrintBoard(board, width, height, livingCellsG, livingCellsR);
		DeclaringVictory(board, width, height, i, j, livingCellsR, livingCellsG);
		exit(1);
	}
}