// Name:		Kristen Hauser
// Class:		CSCI 240
// Professor:	Ringenberg
// Date:		12/4/14

// Description:	This is a basic computer simulation of the game Connect 
//				Four. Two players alternate turns dropping tokens by 
//				choosing columns 1-7. The game continues until a winner is 
//				found by putting 4 of their tokens in a row, if no one wins
//				and the board is full it is a tie. Two modes can be played
//				single player or two player. Single player plays against a 
//				computer with minor AI. Two players can play against each
//				other. Each player can select their own token as a single 
//				character. After finishing a game, the user can select to 
//				play again. 

#include "Game.h"
#include <iostream>
#include <Windows.h>
using namespace std;

int main(){
	Game G;
	int  dropSpot;
	char winner = ' ';
	int gametype;
	char gameTypeChar;
	string gameTypeStr;
	char player1Char = '`';
	string player1Str;
	char player2Char = '`';
	string player2Str;
	char repeat = 'Y';
	string repeatstr;

	// Loop while the user wants to continue to play.
	while(repeat == 'Y' || repeat == 'y'){
		// Draw main menu
		G.drawMainMenu();

		// Data validation loop so the user chooses 1 or 2 for menu selection.
		do{
			cout << "Choose game option: ";
			getline(cin,gameTypeStr);

			// Checks length of string to make sure length is 1, which
			// corresponds to a single character.
			if(gameTypeStr.length() > 1){
				cout << "\nMust enter a single character.\n" << endl;
				gametype = -1;
			}

			// Takes character and put it into a char variable which is 
			// converted to an integer.
			if(gameTypeStr.length() == 1){
				gameTypeChar = gameTypeStr[0];
				gametype = gameTypeChar - '0';
			}

			// If intger is not 1 or 2, a message is displayed. 
			if(gametype != 1 && gametype != 2 && gametype != -1){
				cout << "\nChoose 1 to against a computer,"<< endl;
				cout << "or 2 to play against a friend.\n" << endl;
			}

		}while(gametype != 1 && gametype != 2);

		// Clear console.
		system("cls");

		// Begin two player game, if option 2 is selected.
		if(gametype == 2){
			G.draw2PMenu();

			// Read in player 1's token, check to make sure input is 
			// a single character.
			do{
				cout << "Choose character for Player 1's marker: ";
				getline(cin,player1Str);

				// Check string length is one.
				if(player1Str.length() > 1){
					cout << "\nMust enter a single character.\n" << endl;
					player1Char = '`';
				}

				// Convert string to char.
				if(player1Str.length() == 1){
					player1Char = player1Str[0];
					if(player1Char == '`'){
						cout << "\nCannot be the ` character.\n" << endl;
					}
				}

			}while(player1Char == '`');

			// Read in player 1's token, check to make sure input is 
			// a single character.
			do{
				cout << "\nChoose character for Player 2's marker: ";
				getline(cin,player2Str);

				// Check string length is one.
				if(player2Str.length() > 1){
					cout << "\nMust enter a single character." << endl;
					player1Char = '`';
				}
				// Convert string to char.
				if(player2Str.length() == 1){
					player2Char = player2Str[0];
					if(player2Char == '`'){
						cout << "\nCannot be the ` character.\n" << endl;
					}
				}
			}while(player2Char == '`');

			// Set player's token to entered characters.
			G.setPlayer1Name(player1Char);
			G.setPlayer2Name(player2Char);

			// Randomize first turn.
			G.randomizeFirstTurn();

			// Clear console.
			system("cls");

			// Loop while there is no winner.
			while(winner == ' '){
				cout << "Turn number " << G.getTurnNum() << endl;
				cout << "It is " << G.getPlayerTurn() << "\'s turn." << endl;
				cout << "Please select a number from 1-7" << endl;

				// Function to draw current playing board.
				G.drawBoard();

				// Read in dropspot
				cin >> dropSpot;

				// Loop to make sure input is a valid column number. 
				while(dropSpot-1 < 0 || dropSpot-1 > 6 || cin.fail()){

					// Check to see if input is an integer.
					if(cin.fail()){
						cout << "Must enter an integer." << endl;
						cin.clear();	
						cin.ignore(256,'\n');
						cin >> dropSpot;
					}
					// Check to see if input is between 0 and 6.
					else{
						cout << "Invalid move. Play again." << endl;
						cin >> dropSpot;
					}
				}

				// Play column inputed by user.
				while(!G.play(dropSpot-1)){
					cout << "Invalid move. Play again." << endl;
					cin >> dropSpot;
				}

				// Check for winner.
				winner = G.checkWinner();

				// Toggle player.
				G.togglePlayer();

				// Clear console.
				system("cls");
			}

			// Outputs winner or tie if one is found.
			if(winner != '`'){
				cout << winner << " wins!" << endl;
			}
			else{
				cout << "It's a tie." << endl;
			}
		}

		// Begin two player game, if option 2 is selected.
		if(gametype == 1){
			G.draw1PMenu();

			// Read in player 1's token, check to make sure input is 
			// a single character.
			do{
				cout << "Choose character for Player 1's marker: ";
				getline(cin,player1Str);

				// Check string length is one.
				if(player1Str.length() > 1){
					cout << "\nMust enter a single character.\n" << endl;
					player1Char = '`';
				}

				// Convert string to char.
				if(player1Str.length() == 1){
					player1Char = player1Str[0];
					if(player1Char == '`'){
						cout << "\nCannot be the ` character.\n" << endl;
					}
				}

			}while(player1Char == '`');

			// Sets computer token.
			if(player1Char == 'X'){
				player2Char = 'O';
			}
			else{
				player2Char = 'X';
			}
		}

		// Sets player's tokens.
		G.setPlayer1Name(player1Char);
		G.setPlayer2Name(player2Char);

		// Randomize first turn
		G.randomizeFirstTurn();

		// Clear console
		system("cls");

		// Loop while no winner is found.
		while(winner == ' '){
			cout << "Turn number " << G.getTurnNum() << endl;
			cout << "It is " << G.getPlayerTurn() << "\'s turn." << endl;
			cout << "Please select a number from 1-7" << endl;

			// Draw current board.
			G.drawBoard();

			// If player's turn, inputs column.
			if(G.getPlayerTurn() == player1Char){
				cin >> dropSpot;

				// Loop to check to make sure column is valid.
				while(dropSpot-1 < 0 || dropSpot-1 > 6 || cin.fail()){
						
					// Check to make sure an integer is inputted.
					if(cin.fail()){
						cout << "Must enter an integer." << endl;
						cin.clear();	
						cin.ignore(256,'\n');
						cin >> dropSpot;
					}
					// Check to make sure integer is between 0 and 6.
					else{
						cout << "Invalid move. Play again." << endl;
						cin >> dropSpot;
					}
				}
			}
			// Computers turn, to input column.
			else{
				dropSpot = G.compTurn() + 1;
			}
			
			// Place token in inputted column.
			while(!G.play(dropSpot-1)){
				if(G.getPlayerTurn() == player1Char){
					cout << "Invalid move. Play again." << endl;
					cin >> dropSpot;
				}
			}

			// Check for winner.
			winner = G.checkWinner();

			// Toggle player.
			G.togglePlayer();

			// Clear console.
			system("cls");
		}

		// Draw final board.
		G.drawBoard();

		// Output who wins or a tie.
		if(winner != '`' && winner == player1Char){
			cout << "Player wins!" << endl;
		}
		else if(winner != '`' && winner == player2Char){
			cout << "Computer wins!" << endl;
		}
		else{
			cout << "It's a tie." << endl;
		}
		repeat = ' ';
		cin.clear();
		cin.ignore(236,'\n');

		// Loop for valid input of a y or n, to continue
		// to play or not. 
		do{
	
			cout << endl;
			cout << "Play again? (Y/N)" << endl;
			getline(cin,repeatstr);

			// Check if string is 1 character.
			if(repeatstr.length() > 1){
				cout << "\nMust enter a single character." << endl;
				repeat = 'A';
			}
			// Converts string to char.
			if(repeatstr.length() == 1){
				repeat = repeatstr[0];
			}
		}while(repeat != 'Y' && repeat != 'y' && repeat != 'N' && repeat != 'n');

		// Clear console
		system("cls");

		// Reset local and class variables.
		winner = ' ';
		player1Char = '`';
		player2Char = '`';
		G.clearData();

	}

	cout << "Thanks for playing!" << endl;

}