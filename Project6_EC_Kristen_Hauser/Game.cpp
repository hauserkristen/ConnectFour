// Implementation of Game Class
#include "Game.h"
#include <string>
#include <iostream>
#include <Windows.h>
#include <cstdlib> 
#include <ctime> 
using namespace std;

// Constructor of game class. Intializes private variables.
Game::Game() {
	playerName = 'X';
	player1Name = 'X';
	player2Name = 'O';
	turnNum = 0;
	for(int i = 0; i  < ROWS; i++){
		for(int j = 0; j < COLS; j++){
			board[i][j] = ' ';
		}
	}
};

// Sets player 1's token.
void Game::setPlayer1Name(char a) { player1Name = a; };

// Sets player 2's token.
void Game::setPlayer2Name(char d) { player2Name = d; };

// Gets player 1's token.
char Game::getPlayer1Name() { return player1Name; };

// Gets player 1's token.
char Game::getPlayer2Name() { return player2Name; };

// Function to increment current turn number.
int Game::getTurnNum() { 
	turnNum++;
	return turnNum; };

// Gets current player's token.
char Game::getPlayerTurn() { return playerName; };

// Function to alternate current player's token.
void Game::togglePlayer() { 
	if(playerName == player1Name){
		playerName = player2Name;
	}
	else{
		playerName = player1Name;
	}
};

// Function to draw board using character array.
void Game::drawBoard() {
	// Handle to set console color attributes.
	HANDLE hStdout;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	
	cout << "\n  1   2   3   4   5   6   7  " << endl;
	// Sets background to yellow, and foreground to black.
	SetConsoleTextAttribute(hStdout, 224);
	cout << "-----------------------------" << endl;
	for(int i = 0; i < ROWS; i++){
		cout << "|";
		for(int j = 0; j < COLS; j++){
			// When token in array correspondes to player 1's token
			// foreground color is changed to blue.
			if(board[i][j] == player1Name){
				SetConsoleTextAttribute(hStdout, 233);
			}
			else{
				// When token in array correspondes to player 2's token
				// foreground color is changed to red.
				SetConsoleTextAttribute(hStdout, 236);
			}
			cout << ' ' <<  board[i][j] << ' ';
			// Sets background to yellow, and foreground to black again.
			SetConsoleTextAttribute(hStdout, 224);
			cout << "|";
		}
		cout << endl;
		cout << "-----------------------------" << endl;
	}
	// Restores background color to black and foreground color to white.
	SetConsoleTextAttribute(hStdout, 15);
};

// Function to drop token into designated column
bool Game::play(int ds) { 
	bool fullCheck = false;
	fullCheck = isFull(ds);

	// If token is out of bounds or column selected is full.
	if(ds < -1 || ds > COLS-1 || fullCheck == true){
		return false;
	}
	// If designated column is between 0 and 7 and column is not
	// full, drop current player's token into column of array at 
	// lowest position.
	for(int i = ROWS-1; i > -1 ; i--){
		if(board[i][ds] == ' '){
			board[i][ds] = playerName;
			break;
		}
	}
	return true; };

// Function to check if anyone has four in a row. 
char Game::checkWinner() { 
	int i;
    int j;
 
    // Horizontal Check
   for(i = ROWS - 1; i > -1; i--) {
        for(j = 0; j < COLS; j++) {
			if(j+3 < 7){
				if(board[i][j] == playerName && board[i][j+1] == playerName && board[i][j+2] == playerName && board[i][j+3] == playerName){
					return playerName;
				}
			}
		}
    }
 
    // Vertical Check
    for(i = ROWS - 1; i > -1; i--) {
        for(j = 0; j < COLS; j++) {
			if(i-3 > -1){
				if(board[i][j] == playerName && board[i-1][j] == playerName && board[i-2][j] == playerName && board[i-3][j] == playerName){
					return playerName;
				}
			}
		}
    }
 
	// Diagonal Check - Right
    for(i = ROWS - 1; i > -1; i--) {
        for(j = 0; j < COLS; j++) {
			if(i-3 > -1 && j+3 < 7){
				if(board[i][j] == playerName && board[i-1][j+1] == playerName && board[i-2][j+2] == playerName && board[i-3][j+3] == playerName){
					return playerName;
				}
			}
		}
    }

	// Diagnal Check - Left
    for(i = ROWS - 1; i > -1; i--) {
        for(j = 0; j < COLS; j++) {
			if(i-3 > -1 && j-3 >-1){
				if(board[i][j] == playerName && board[i-1][j-1] == playerName && board[i-2][j-2] == playerName && board[i-3][j-3] == playerName){
					return playerName;
				}
			}
		}
    }

	// If turn is 42, the board is full and the game is a tie.
	if(turnNum == 42){
		return '`';
	}


	return ' '; };

// Function to check if the column is full, but testing if the 
// top entry is full.
bool Game::isFull(int col){
	if(board[0][col] == ' '){
		return false;
	}
	return true;
}

// Function to set current player.
void Game::setPlayerName(char s){ playerName = s; }

// Function to randomize which player goes first.
void Game::randomizeFirstTurn(){
	int start;
	srand((unsigned)time(0));

	// Random number is 0 or 1.
	start = rand() % 2;

	if(start == 1){
		playerName  = player1Name;
	}
	else{
		playerName = player2Name;
	}
}

// Function for computer's turn. This function checks to see if 
// the computer's token can win and places a token there to win. 
// Next it checks if the opponent can win, and if they can places 
// a token to block them. Otherwise, the computer places a token
// randomly in a column 0-7 that is not full.
int Game::compTurn(){
	int i, j, ds;
	srand((unsigned)time(0));

	// Comp Win - Horizontal Check - Right
   for(i = ROWS - 1; i > -1; i--) {
        for(j = 0; j < COLS; j++) {
			if(j+3 < 7){
				if(board[i][j] == player2Name && board[i][j+1] == player2Name && board[i][j+2] == player2Name){
					if(board[i][j+3] == ' '){
						if(isFull(j+3) == false){
							return j+3;
						}
					}
				}
			}
		}
    }

   // Comp Win - Horizontal Check - Left
   for(i = ROWS - 1; i > -1; i--) {
        for(j = COLS; j < -1; j--) {
			if(j-3 > -1){
				if(board[i][j] == player2Name && board[i][j-1] == player2Name && board[i][j-2] == player2Name){
					if(j-1 > -1 && board[i][j-3] == ' '){
						if(isFull(j-3) == false){
							return j-3;
						}
					}
				}
			}
		}
    }
 
    // Comp Win - Vertical Check
    for(i = ROWS - 1; i > -1; i--) {
        for(j = 0; j < COLS; j++) {
			if(i-3 > -1){
				if(board[i][j] == player2Name && board[i-1][j] == player2Name && board[i-2][j] == player2Name){
					if(board[i-3][j] == ' '){
						if(isFull(j) == false){
							return j;
						}
					}
				}
			}
		}
    }

	// Comp Win - Diagonal Check - Right
    for(i = ROWS - 1; i > -1; i--) {
        for(j = 0; j < COLS; j++) {
			if(i-3 > -1 && j+3 < 7){
				if(board[i][j] == player2Name && board[i-1][j+1] == player2Name && board[i-2][j+2] == player2Name){
					if(board[i-2][j+3] != ' '){
						if(isFull(j+3) == false){
							return j+3;
						}
					}
				}
			}
		}
    }

	// Comp Win - Diagnal Check - Left
    for(i = ROWS - 1; i > -1; i--) {
        for(j = 0; j < COLS; j++) {
			if(i-3 > -1 && j-3 >-1){
				if(board[i][j] == player2Name && board[i-1][j-1] == player2Name && board[i-2][j-2] == player2Name){
					if(board[i-2][j-3] != ' '){
						if(isFull(j-3) == false){
							return j-3;
						}
					}
				}
			}
		}
    }


	// Block other Player - Horizontal Check - Right
   for(i = ROWS - 1; i > -1; i--) {
        for(j = 0; j < COLS; j++) {
			if(j+3 < 7){
				if(board[i][j] == player1Name && board[i][j+1] == player1Name && board[i][j+2] == player1Name){
					if(board[i][j+3] == ' '){
						if(isFull(j+3) == false){
							return j+3;
						}
					}
				}
			}
		}
    }

   // Block Other Player - Horizontal Check - Left
   for(i = ROWS - 1; i > -1; i--) {
        for(j = COLS; j < -1; j--) {
			if(j-3 > -1){
				if(board[i][j] == player1Name && board[i][j-1] == player1Name && board[i][j-2] == player1Name){
					if(j-1 > -1 && board[i][j-3] == ' '){
						if(isFull(j-3) == false){
							return j-3;
						}
					}
				}
			}
		}
    }
 
    // Block Other Player - Vertical Check
    for(i = ROWS - 1; i > -1; i--) {
        for(j = 0; j < COLS; j++) {
			if(i-3 > -1){
				if(board[i][j] == player1Name && board[i-1][j] == player1Name && board[i-2][j] == player1Name){
					if(board[i-3][j] == ' '){
						if(isFull(j) == false){
							return j;
						}
					}
				}
			}
		}
    }

	// Block Other Player - Diagonal Check - Right
    for(i = ROWS - 1; i > -1; i--) {
        for(j = 0; j < COLS; j++) {
			if(i-3 > -1 && j+3 < 7){
				if(board[i][j] == player1Name && board[i-1][j+1] == player1Name && board[i-2][j+2] == player1Name){
					if(board[i-2][j+3] != ' '){
						if(isFull(j+3) == false){
							return j+3;
						}
					}
				}
			}
		}
    }

	// Block Other Player - Diagnal Check - Left
    for(i = ROWS - 1; i > -1; i--) {
        for(j = 0; j < COLS; j++) {
			if(i-3 > -1 && j-3 >-1){
				if(board[i][j] == player1Name && board[i-1][j-1] == player1Name && board[i-2][j-2] == player1Name){
					if(board[i-2][j-3] != ' '){
						if(isFull(j-3) == false){
							return j-3;
						}
					}
				}
			}
		}
    }
	
	// Random drop selection, generates a random number between 0 and 7.
	ds = rand() % 7;
	while(isFull(ds) == true){
		ds = rand() % 7;
	}
		return ds;
}

// Functino to clear board and reset turn number to play again.
void Game::clearData() {
	turnNum = 0;
	for(int i = 0; i  < ROWS; i++){
		for(int j = 0; j < COLS; j++){
			board[i][j] = ' ';
		}
	}
}

// Function to draw main menu.
void Game::drawMainMenu(){	
		cout << "-----CONNECT FOUR GAME-----" << endl;
		cout << "|     Kristen Hauser      |" << endl;
		cout << "---------------------------" << endl;
		cout << "|    [1] Single Player    |" << endl;
		cout << "|    [2] Multi-Player     |" << endl;
		cout << "---------------------------" << endl;
}

// Function to draw 1 player menu header.
void Game::draw1PMenu(){
		cout << "-------------CONNECT FOUR GAME--------------" << endl;
		cout << "|            1 Player Version              |" << endl;
		cout << "--------------------------------------------" << endl;
			
}

// Function to draw 2 player menu header.
void Game::draw2PMenu(){
		cout << "-------------CONNECT FOUR GAME--------------" << endl;
		cout << "|            2 Player Version              |" << endl;
		cout << "--------------------------------------------" << endl;
}