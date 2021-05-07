#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#define ROWS 6 //set rows for the char array
#define COLS 7 //set column for the char array 

//calling the methods 
void printgame_grid(char *game_grid);//print board
int playersTurn(char *game_grid, const char*, int player);//count the players turn
int WinnerType(char *game_grid);//counts the index for the playing pieces to know if theres four in a row
int connectFour(char *game_grid, int, int, int, int);//checks that the four in a row match to the same game piece to know if its a win

int main(){
   
   char game_grid[ROWS * COLS];//defines the game board 6 by 7
   const char *GAME_PIECES = "XO";//defines the game pieces X or O 
  
   memset(game_grid, ' ', ROWS * COLS);//used to fill the grid with 42 empthy spaces

   int turn, gameOver = 0;

   for(turn = 0; turn < ROWS * COLS && !gameOver; turn++){//counts the turns as long as the game isnt over
      printgame_grid(game_grid);  
		
		//the modulo of the turn number by 2 gives us the player number depending if its odd or even
      while(!playersTurn(game_grid, GAME_PIECES, turn % 2)){
		 //prints the board again if the coloumn choosen is full and doesnt skip the players turn 
		 printgame_grid(game_grid);   
         puts("This column is full, please select another\n");
      }
      gameOver = WinnerType(game_grid);//checks a winner every turn 
   } 
   printgame_grid(game_grid);
	
	//checks if the game is a tie of single win 
   if(turn == ROWS * COLS && !gameOver){
      puts("It's a tie!");
   } else {
      turn--;
      printf("Congradulations Player %d  is the winner! \n They played with (%c)\n", turn % 2 + 1, GAME_PIECES[turn % 2]);//not the player who just took turn the other thats why you + 1
   }

   return 0;

}
void printgame_grid(char *game_grid){//prints the game grid 
   int r, c;//rows and coloumns

   puts("\n    Connect Four Game \n");
   for(r = 0; r < ROWS; r++){
      for(c = 0; c < COLS; c++){
         printf("| %c ",  game_grid[COLS * r + c]);
      }
      puts("|");
      puts("-----------------------------");

   }
   puts("  1   2   3   4   5   6   7\n");

}
int playersTurn(char *game_grid, const char *GAME_PIECES, int player){//determines which players turn it is 
   int r, c = 0;//rows and coloumns
   
   //prompts player 1 to choose first - player is 0 so player 1 = X as their game piece
   printf("Player %d (%c):\nEnter a number 1 - 7: ", player + 1, GAME_PIECES[player]);
   
   //gets the input from the player on where they want to place a game piece 
   while(1)
   { 
	  //checks that the user input is a number and not out of bounds  
	  if(1 != scanf("%d", &c) || c < 1 || c > 7 )
	  {
         while(getchar() != '\n');//gets the input 
         puts("Number is invalid! Please try again!");
      } 
	  else
	  { 
         break;
      }
   }
   c--; //once it gets number it takes 1 away

	//determines where the game piece will land and whether is X or O depending on the current turn
   for(r = ROWS - 1; r >= 0; r--)
   {
      if(game_grid[COLS * r + c] == ' ')
	  {
         game_grid[COLS * r + c] = GAME_PIECES[player];
         return 1;
      }
   }
   return 0;

}

int WinnerType(char *game_grid){//determines if the game is won
	int r, c, index, count = 0;
	const int W = 1;
	const int H = 7;
	const int D_RIGHT = 6, D_LEFT = 8;
	
	//Diagonal Win 
	for(r = 0; r < ROWS - 3; r++)
	{
		for(c = 0; c < COLS; c++)
		{
			index = COLS * r + c;
			if(count <= 3 && connectFour(game_grid, index, index + D_LEFT, index + D_LEFT * 2, index + D_LEFT * 3)
			|| count >= 3 && connectFour(game_grid, index, index + D_RIGHT, index + D_RIGHT * 2, index + D_RIGHT * 3))
			{
				return 1;
			}
			count++;
		}
		  count = 0;
	}
	
	//Horizontal Win
	for(r = 0; r < ROWS; r++){
       for(c = 0; c < COLS - 3; c++){
          index = COLS * r + c;
          if(connectFour(game_grid, index, index + W, index + W * 2, index + W * 3)){
             return 1;
          }
       }
    }
	
	//Vertical Win
	for(r = 0; r < ROWS - 3; r++){
		for(c = 0; c < COLS; c++){
			index = COLS * r + c;
			if(connectFour(game_grid, index, index + H, index + H * 2, index + H * 3)){
				return 1;
			}
		}
	}	
	
	return 0;
}
	
int connectFour(char *game_grid, int a, int b, int c, int d){
    return (game_grid[a] == game_grid[b] && game_grid[b] == game_grid[c] && game_grid[c] == game_grid[d] && game_grid[a] != ' ');

}

	
	
	
	
		