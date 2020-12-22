/*
    Author: Daniel Pintado
    Tic-tac-toe where the computer uses the minimax algorithm so that it is impossible to beat the 'ai'. The player can only tie against the computer or lose. 
*/

#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <iomanip>
#include <unistd.h>

using namespace std;

//function prototypes
void drawBoard(int board[3][3]); 
void playerMove(int board[3][3]);
void computerMove(int board[3][3]);
int isWinner(int board[3][3]);
int minimax(int board[3][3], bool maximizer, int depth, int* find_row, int *find_col);
void bestMove(int board[3][3]);
void reminaingMoves(int board[3][3]);

int main() {
    int totalTurns = 0;
    bool player_turn = true; //player is always first for now
    bool ai_turn = false;
    int turns_taken = 0; //total possible is 9 for a 3x3 board.

    cout << "TIC-TAC-TOE, can you beat this AI?" << endl;
    int board[3][3] = {}; //initalize board.


    drawBoard(board); //draws inital empty drawboard
   
    cout << endl << "Player, make the first move. " << endl;

    while(true) {
      playerMove(board);
      drawBoard(board);
      if(isWinner(board) != 0) { //check end state
          break;
      }
      computerMove(board);
      usleep(2000000);
      drawBoard(board);
      if(isWinner(board) != 0) {
          break;
      }
    }

    if(isWinner(board) == 1) cout << "Player won! " << endl;
    if(isWinner(board) == 2) cout << "Computer won! " << endl;
    if(isWinner(board) == 4) cout << "Tie game! " << endl;

}

/*
    This function draws the board at its current state.
    Letters will be used to represent the row to be selected
    and numbers represent the column to be selected, when user makes move.
*/
void drawBoard(int board[3][3]) {
    
    cout << "    A";
    cout << "    B";
    cout << "    C";
    cout << endl;
    cout << "  *----*----*----* " << endl;
    for(int row = 0; row < 3; row++) {
        cout << left << row+1;
        for(int col = 0; col < 3; col++){
            switch(board[row][col])
            {
                case 1: cout << " | x " ; //1 represents x
                break;
                case 2: cout << " | O " ; //2 represents O
                break;
                default: cout << " |   ";
                break;
            } //end of switch
        }
        cout << " |   ";
        cout << endl << "  *----*----*----*" << endl;
    }
} //end of drawBoard

int isWinner(int board[3][3]) {
    int playerWon = 1, computerWon = 2, inProgress = 0;

    for(int i = 0; i < 3; i++) {
        if(board[i][0] == 1 && board[i][1] == 1 && board[i][2] == 1) { //check if player won horizontally 
            return playerWon;
        }
        if(board[0][i] == 1 && board[1][i] == 1 && board[2][i] == 1) { //check if player won vertically 
            return playerWon;
        }

         if(board[i][0] == 2 && board[i][1] == 2 && board[i][2] == 2) { //check if computer won horizontally 
            return computerWon;
        }
        if(board[0][i] == 2 && board[1][i] == 2 && board[2][i] == 2) { //check if computer won vertically 
            return computerWon;
        }
    } //end of for loop
        //validates diagonale parts
        if(board[0][0] == 1 && board[1][1] == 1 && board [2][2] == 1) {
         //cout << "Player won!" << endl;
         return playerWon;
        }
        if(board[2][0] == 1 && board[1][1] == 1 && board [0][2] == 1) {
         //cout << "Player won!" << endl;
         return playerWon;
        }

        if(board[0][0] == 2 && board[1][1] == 2 && board [2][2] == 2) {
         return computerWon;
        }
        if(board[2][0] == 2 && board[1][1] == 2 && board [0][2] == 2) {
         return computerWon;
        }

    //check for a tie
    int totalMoves = 0;
    for(int row = 0; row < 3; row++) { //for each move
        for(int col = 0; col < 3; col++) {
            if(board[row][col] != 0) {
                totalMoves++;
            }
        }
    }
    if(totalMoves == 9) {
        //cout << "TIE GAME " << endl;
        return 4;
    }

    return inProgress; //still inPorgress if it gets here
}

void playerMove(int board[3][3]) {
    
    cout << "Enter position for 'x' using coordinates on board: " << endl;
    char column;
    int rowNum = 0;
    int row = 0, col = 0;
    cin >> column >> rowNum; //takes in column letter and row number.
    while(true) {
        column = (toupper(column));
        col = (int)column-65; //column index, converts letter to number representation on the board. 
        row = rowNum-1; //row index
        if(board[row][col] == 0) { //if it is an empty box
           board[row][col] = 1; //place 'x'
           break;
        } else {
            cout << "Box is occupied or out of bounds, choose again: " << endl;
            cin >> column >> rowNum;
        }
    }
    
}


void computerMove(int board[3][3]) {
    int row, col;
    minimax(board, false, 0, &row, &col); //calls minimax function to decide what is the best move to make
    cout << "Computers turn.." << endl;
    board[row][col] = 2; //places that move
}

int minimax(int board[3][3], bool maximizer, int depth, int* find_row, int *find_col) {
    int best_row = -1;
    int best_col = -1;

   if(isWinner(board) == 1) { //if the player wins
       return +10; //return +10
   }else if(isWinner(board) == 2) { //if ai wins, return -10
       return -10;
   } else if(isWinner(board) == 4) { //if its a tie, return 0
       return 0; 
   } 

   if(maximizer) { //if it is the maximizers turn (player)
       int bestMove = -10000;
     for(int row = 0; row < 3; row++) { //for each move
        for(int col = 0; col < 3; col++) {
            if(board[row][col] == 0) { //if its an available spot
                board[row][col] = 1; //place 'x' 
                int score = minimax(board, !maximizer, depth+1, find_row, find_col); //call recursive function
             if(score > bestMove) { //if the move is better
                  bestMove = score;  //new best move
              }
                board[row][col] = 0; //undo move
            }
          }
        }
        return bestMove;
    } else { //otherwise its the minimizers turn
        int bestMove = +1000000;
        for(int row = 0; row < 3; row++) {
         for(int col = 0; col < 3; col++) {
            if(board[row][col] == 0) { //if its an available spot
              board[row][col] = 2; //place '0'
              int score = minimax(board, !maximizer, depth+1, find_row, find_col);
              if(score < bestMove) {
                 bestMove = score; //find minimum
                  best_row = row;
                  best_col = col;
                }
                board[row][col] = 0;
            }
          }
        }
        *find_row = best_row; //store the best row found
        *find_col = best_col; //store the best column
        return bestMove; //return the score.

} //end 
