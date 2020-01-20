/*
    Author: Daniel Pintado
    Date: 12/26/2019


    This winter i decided to do a project to further develop my skills. 
    This program is a game of Tic-Tac-Toe vs a computer that uses the Minimax
    Algorithm.
*/


//libraries
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <iomanip> 


using namespace std;

//function prototypes
void drawBoard(int board[3][3]);
void playerMove(int board[3][3]);
void computerMove(int board[3][3]);
int isGameOver(int board[3][3]);
void playerWon(int board[3][3]);
void computerWon(int board[3][3]);
void findBestMove(int board[3][3]);
int minimax(int board[3][3]);
int evalute(int board[3][3]);
bool movesLeft(int board[3][3]);


struct Move { //used for later
    int x, y;
};

int main() {

    srand(time(NULL)); // makes use of the computer's internal clock to control the choice of the seed.
    string players[2] = {"player" , "computer"}; //array of names
    string turn = players[rand() % 2]; //randomizes who is first and stores it into "turn" string. 
    int turnsTaken = 0; //counts the number of turns taken, maximum of 9 turns
    bool playerTurn = false; 
    bool computerTurn = false;
    cout << "TIC-TAC-TOE By Daniel Pintado " << endl;
    cout << "Player starting is: " << turn << endl;

    int rowTemp = 0;
    int colTemp = 0;

//checks who is the first turn
if(turn == "player") {
    playerTurn = true;
 } else {
    computerTurn = true;
    }
 
     int boardSize[3][3] = {}; //initialize board 
   

    //first move
    drawBoard(boardSize); //calls drawBoard
    if(playerTurn) {
        turnsTaken++; //counts first move
        playerMove(boardSize);
     } else if(computerTurn) { 
         turnsTaken++; //counts first move
         computerMove(boardSize);
     }


    drawBoard(boardSize); 
    while(isGameOver(boardSize) != 1 || isGameOver(boardSize) != 2) { //while isGameOver doesn't return 1 or 2
            if(playerTurn) { 
                turnsTaken++; //counts turn
            computerTurn = true;
            playerTurn = false;
            computerTurn = true;
             computerMove(boardSize); //calls computerMove
             drawBoard(boardSize); //draws board with new move
            } else if(computerTurn) { 
                turnsTaken++; //counts turn
                computerTurn = true;
                computerTurn = false;
                playerTurn = true;
                playerMove(boardSize); //calls playerMove
                drawBoard(boardSize); //draws board with new move
            }//end of else if
            if(turnsTaken == 9 && isGameOver(boardSize) == 0) { //if 9 turns taken and the game is still inProgress(returned 0)
                cout << "TIE GAME! " << endl;
                break; //its a tie game, break out of loop
            }
            if(isGameOver(boardSize) == 1 || isGameOver(boardSize) == 2) { //if either computer or player won
                break; //break
            }
        } //end of while loop
    //isGameOver(boardSize);
    return 0;
} //end of main


/*
    This function draws the board at its current state.
    Letters will be used to represent the row to be selected
    and numbers represent the column to be selected, when user makes move.
*/
 void drawBoard(int size[3][3]) { 
    cout << setw(6) << "A";
    cout << setw(6) << "B";
    cout << setw(5) << "C";
    cout << endl;    
    cout << "  *----*----*----* " << endl;
     for(int row = 0; row < 3; row++) { //traverse through 2d array
               cout << left << row+1;
        for(int col = 0; col < 3; col ++) {
            switch(size[row][col]) 
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



/*
    playerMove takes in the board at its current state
    asks the player for what move they want to do and handles all the 
    possible errors and makes sure the choice is valid
*/
void playerMove(int size[3][3]) {

  //variables hold input
  char column; 
  int rowNumber;
  int row = 0, col = 0;

  //bool variables for validating if input is allowed
  bool validRow = false, validCol = false;
  bool validBox = false;
  
  cout << "Please enter move using coordinates on board with space in between: " << endl;
while(!validBox) {  //while its true that validBox is false
  cin >> column >> rowNumber;  //take in input
  while(!validCol) { //while its also true that validCol is false
    if(column == 'a' || column == 'A') { //if its A
        col = 0; //column is set interally to 0, first position
        validCol = true;  //validCol is set to true
    } else if(column == 'b' || column == 'B') {  //same process
        col = 1;
        validCol = true;
    } else if(column == 'c' || column == 'C') {
        col = 2;
        validCol = true;
    } else { //if its none of these, it is an incoreect column
        cout << "Invalid column, Please try again: " << endl; 
        cin >> column;
    }   
} //end of col validation

while(!validRow) { //while its true that row is false
    if(rowNumber == 1) { //if row is 1
        row = 0; //store it as 0 interally
        validRow = true; //set validRow to true
    } else if(rowNumber == 2) { //same process
        row = 1;
        validRow = true;
     } else if(rowNumber == 3) {
        row = 2;
        validRow = true;
      } else {
        cout << "Invalid row, Please try again: " << endl;
        cin >> rowNumber;
        } 
    }

    //validates that the box is empty
     if(size[row][col] == 0) { 
         validBox = true;
     } else {
         cout << "Box is already filled, please select another" << endl;
         validBox = false;
         validRow = false;
         validCol = false;
     }
    }
    size[row][col] = 1; //1 = 'X'
} //end of playerMove



/*
    computerMove takes in the board at its current state
    asks the computer for what move they want to do and handles all the 
    possible errors and makes sure the choice is valid
*/
void computerMove(int size[3][3]) {
char column;
  int rowNumber;
  int row = 0, col = 0;
  bool validRow = false, validCol = false;
  bool validBox = false;
  
  cout << "Please enter move using coordinates on board with space in between: " << endl;

  
while(!validBox) { //validates that the box isn't filled
  cin >> column >> rowNumber;
  while(!validCol) { //validates that a valid column is inputted
    if(column == 'a' || column == 'A') {
        col = 0;
        validCol = true;
    } else if(column == 'b' || column == 'B') {
        col = 1;
        validCol = true;
    } else if(column == 'c' || column == 'C') {
        col = 2;
        validCol = true;
    } else {
        cout << "Invalid column, Please try again: " << endl;
        cin >> column;
    }   
} //end of col validation

while(!validRow) { //validates that a valid row is inputted
    if(rowNumber == 1) { 
        row = 0;
        validRow = true;
    } else if(rowNumber == 2) {
        row = 1;
        validRow = true;
     } else if(rowNumber == 3) {
        row = 2;
        validRow = true;
      } else {
        cout << "Invalid row, Please try again: " << endl;
        cin >> rowNumber;
        } 
    } //end of row validation

    //makes sure box is empty
     if(size[row][col] == 0) {
         validBox = true;
     } else {
         cout << "Box is already filled, please select another" << endl;
         validBox = false;
         validRow = false;
         validCol = false;
     }
    }
    size[row][col] = 2; // 2 = 'O'

    // bool validBox = false;
    // int col, row;

    // while(!validBox) {
    //     row = rand() % 3;
    //     col = rand() % 3;
    //     if(board[row][col] == 0) {
    //         validBox = true;
    //     } else {
    //         cout << "Box taken.. choose another u dumb computer.." << endl;
    //         validBox = false;
    //     }
    // }
    // board[row][col] = 2;
}



/*
  determins if someone has won the game,
  returns 1 if playerWon, returns 2 in computerWon
  checks all columns, rows, and diagonals
*/
int isGameOver(int board[3][3]) { //return int, 1 = playerWon, 2 = Computer Won
int playerWon = 1, computerWon = 2, inProgress = 0;
bool someoneWon = false;

    //checks if playerWon
     for(int row = 0; row < 3; row++) { //traverse through the board
        //validate all columns
        if(board[0][0] == 1 && board[1][0] == 1 && board[2][0] == 1) {
            cout << "Player won!" << endl;
            someoneWon = true;
            return playerWon;
        }
        if(board[0][1] == 1 && board[1][1] == 1 && board[2][1] == 1) {
            cout << "Player won!" << endl;
            someoneWon = true;
            return playerWon;
        }
        if(board[0][2] == 1 && board[1][2] == 1 && board[2][2] == 1) {
            cout << "Player won!" << endl;
            someoneWon = true;
            return playerWon;
        }

        //validate all rows
        if(board[0][0] == 1 && board[0][1] == 1 && board[0][2] == 1) {
            cout << "Player won!" << endl;
            someoneWon = true;
            return playerWon;
        }
        if(board[1][0] == 1 && board[1][1] == 1 && board[1][2] == 1) {
            cout << "Player won!" << endl;
            someoneWon = true;
            return playerWon;
        }
        if(board[2][0] == 1 && board[2][1] == 1 && board[2][2] == 1) {
            cout << "Player won!" << endl;
            someoneWon = true;
            return playerWon;
        }

         //validates diagonale parts
        if(board[0][0] == 1 && board[1][1] == 1 && board [2][2] == 1) {
         cout << "Player won!" << endl;
         someoneWon = true;
         return playerWon;
        }
        if(board[2][0] == 1 && board[1][1] == 1 && board [0][2] == 1) {
         cout << "Player won!" << endl;
         someoneWon = true;
         return playerWon;  
        }
    } //end of traversing

    //checks if computerWon
    for(int row = 0; row < 3; row++) { //traverse through the board
        //validates ll columns
        if(board[0][0] == 2 && board[1][0] == 2 && board[2][0] == 2) {
            cout << "Computer won!" << endl;
            return computerWon;
        }
        if(board[0][1] == 2 && board[1][1] == 2 && board[2][1] == 2) {
            cout << "Computer won!" << endl;
            return computerWon;
        }
        if(board[0][2] == 2 && board[1][2] == 2 && board[2][2] == 2) {
            cout << "Computer won!" << endl;
            return computerWon;
        }
        
        //validates all rows
        if(board[0][0] == 2 && board[0][1] == 2 && board[0][2] == 2) {
            cout << "Computer won!" << endl;
            return computerWon;
        }
        if(board[1][0] == 2 && board[1][1] == 2 && board[1][2] == 2) {
            cout << "Computer won!" << endl;
            return computerWon;
        }
        if(board[2][0] == 2 && board[2][1] == 2 && board[2][2] == 2) {
            cout << "Computer won!" << endl;
            return computerWon;
        }

         //validates diagonale rows
        if(board[0][0] == 2 && board[1][1] == 2 && board [2][2] == 2) {
         cout << "Computer won!" << endl;
         return computerWon;
        }
        if(board[2][0] == 2 && board[1][1] == 2 && board [0][2] == 2) {
         cout << "Computer won!" << endl;
         return computerWon;
        }
    }
    return inProgress; //still inPorgress if it gets here
} //end of isGameOver


//used later for miniMax, ignore for now
bool movesLeft(int board[3][3]) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] == 0) {
                return true;
            }
        }
    }
    return false;
}


//used later for miniMax, ignore for now
int evalute(int board[3][3]) {

    if(isGameOver(board) == 1) {
        return +10;
    } else if(isGameOver(board) == 2) {
        return -10;
    }

// for(int row = 0; row < 3; row++) {
//         //all columns
//         if(board[0][0] == 1 && board[1][0] == 1 && board[2][0] == 1) {
//             return +10;
//         }
//         if(board[0][1] == 1 && board[1][1] == 1 && board[2][1] == 1) {
//             return +10;
//         }
//         if(board[0][2] == 1 && board[1][2] == 1 && board[2][2] == 1) {
//           return +10;
//         }
//         //all rows
//         if(board[0][0] == 1 && board[0][1] == 1 && board[0][2] == 1) {
//             return +10;
//         }
//         if(board[1][0] == 1 && board[1][1] == 1 && board[1][2] == 1) {
//             return +10;
//         }
//         if(board[2][0] == 1 && board[2][1] == 1 && board[2][2] == 1) {
//            return +10;
//         }
//          //diagonale 
//         if(board[0][0] == 1 && board[1][1] == 1 && board [2][2] == 1) {
//            return +10;
//         }
//         if(board[2][0] == 1 && board[1][1] == 1 && board [0][2] == 1) {
//           return +10;
//         }
//     }

//     //computer won
//     for(int row = 0; row < 3; row++) {
//         //all columns
//         if(board[0][0] == 2 && board[1][0] == 2 && board[2][0] == 2) {
//             return -10;
//         }
//         if(board[0][1] == 2 && board[1][1] == 2 && board[2][1] == 2) {
//             return -10;

//         }
//         if(board[0][2] == 2 && board[1][2] == 2 && board[2][2] == 2) {
//            return -10;
//         }
//         //all rows
//         if(board[0][0] == 2 && board[0][1] == 2 && board[0][2] == 2) {
//             return -10;
//         }
//         if(board[1][0] == 2 && board[1][1] == 2 && board[1][2] == 2) {
//             return -10;
//         }
//         if(board[2][0] == 2 && board[2][1] == 2 && board[2][2] == 2) {
//             return -10;
//         }
//          //diagonale 
//         if(board[0][0] == 2 && board[1][1] == 2 && board [2][2] == 2) {
//             return -10;
//         }
//         if(board[2][0] == 2 && board[1][1] == 2 && board [0][2] == 2) {
//             return -10;
//         }
//     }
    return 0;
}//end of evaluate 



//used later for miniMax, ignore for now

int minimax(int board[3][3], int depth, bool isMax) {
    int currentScore = evalute(board);

    if(currentScore == 10) { //if playerWon, return it
        return currentScore;
    }

    if(currentScore == -10) { //if AI won, return it
        return currentScore;
    }

    if(movesLeft(board) == false) { //if there are no moves left and no winner, its a tie.
        return 0;
    }

    if(isMax) {
        int bestCase = -1000;

        for(int row = 0; row < 3; row++){ 
            for(int col = 0; col < 3; col++) {
                if(board[row][col] == 0) { //if its empty
                    //playerMakes move
                    board[row][col] = 'x'; //player 'x' 

                   bestCase = max(bestCase, 
                        minimax(board, depth+1, !isMax) ); 
  
                    // Undo the move 
                    board[row][col] = ' ';
                } 
            }
        }
        return bestCase;
    } else {

        int best = 1000;
        // Traverse all cells 
        for (int i = 0; i<3; i++) 
        { 
            for (int j = 0; j<3; j++) 
            { 
                // Check if cell is empty 
                if (board[i][j]==0) 
                { 
                    // Make the move 
                    board[i][j] = 'O'; 
  
                    // Call minimax recursively and choose 
                    // the minimum value 
                    best = min(best, 
                           minimax(board, depth+1, !isMax)); 
  
                    // Undo the move 
                    board[i][j] = ' '; 
                } 
            } 
        } 
        return best;
    }

    return 0;
}

//used later for miniMax, ignore for now

void findBestMove(int board[3][3]) {
    // bestMove = NULL
    // for each move in board :
    //     if current move is better than bestMove
    //         bestMove = current move
    // return bestMove
    int bestMove = 0;
    for(int row = 0; row < 3; row++) {
        for(int col = 0; col < 3; col++) {
            if(board[row][col] == 0) { //if its empty, then we can place something there

            }
        }
    }

}