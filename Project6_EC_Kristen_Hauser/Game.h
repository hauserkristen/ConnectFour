// Prototype of Game Class
#include <string>
using namespace std;

class Game{
	private:
		static const int ROWS = 6;
		static const int COLS = 7;
		int turnNum;
		char playerName;
		char player1Name;
		char player2Name;
		char board[ROWS][COLS];

	public:
		Game();
		void randomizeFirstTurn();
		void setPlayer1Name(char a);
		void setPlayer2Name(char d);
		char getPlayer1Name();
		char getPlayer2Name();
		void setPlayerName(char s);
		int getTurnNum();
		char getPlayerTurn();
		void drawBoard();
		bool play(int ds);
		char checkWinner();
		void togglePlayer();
		bool isFull(int col);
		int compTurn();
		void clearData();
		void drawMainMenu();
		void draw1PMenu();
		void draw2PMenu();
};