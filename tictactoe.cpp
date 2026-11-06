#include <iostream>	//iostream lets me use cout 
#include <cstdlib>	//cstdlib lets me use rand-which generates a random number
#include <ctime>	//ctime lets me use time
#include <thread>	//thread lets X and O run separately
#include <chrono>	//chrono creats a time delay
#include <mutex>	//mutex lets only one thread access shared code at a time


bool gameOver = false;		//gameOver keeps track if the game ended or not
char currentTurn = 'X';		//keeps track of whose turn it is
int moveCount = 0;		//keeps track of how many moves been made
std::mutex boardMutex;		//protects shared board from both threads at once

void printBoard(char board[3][3]) {
	
	std::cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << std::endl;           //created first line in board	
	std::cout << "---+---+---" << std::endl; //create a divider on the board
	std::cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << std::endl;           //created the second line on board
	std::cout << "---+---+---" << std::endl;        //create another divider on the board
	std::cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << std::endl;           //created third and last line on board
}

bool checkWin(char board[3][3], char player) {		//bool gives true or false

	if (board[0][0] == player &&		//check rows
		board[0][1] == player &&
		board[0][2] == player) {

			return true;
	}

	if (board[1][0] == player &&
		board[1][1] == player &&
		board[1][2] == player) {

			return true;
	}

	if (board[2][0] == player &&
		board[2][1] == player &&
		board[2][2] == player) {

			return true;
	}

	if (board[0][0] == player &&		//check columns
		board[1][0] == player &&
		board[2][0] == player) {

			return true;
	}

	if (board[0][1] == player &&
		board[1][1] == player &&
		board[2][1] == player) {

			return true;
	}

	if (board[0][2] == player &&
		board[1][2] == player &&
		board[2][2] == player) {

			return true;
	}


	if (board[0][0] == player &&		//check diagonals
		board[1][1] == player &&
		board[2][2] == player) {

			return true;
	}

	if (board[0][2] == player &&
		board[1][1] == player &&
		board[2][0] == player) {

			return true;
	}

	return false;
}

void playerX(char board[3][3]) {

	while (true) {

		boardMutex.lock();		//lock the board so only X can access it

		if (gameOver) {
			boardMutex.unlock();
			break;
		}

		if (currentTurn != 'X') {
			boardMutex.unlock();
			continue;
		}

		int row = rand() % 3;
		int col = rand() % 3;

		while (board[row][col] != ' ') {
		row = rand() % 3;
		col = rand() % 3;

		}

		board[row][col] = 'X';		//put X in empty space
		moveCount++;			//add one to the move count
		printBoard(board);		//print the board while X has the mutex
		std::this_thread::sleep_for(std::chrono::seconds(1));	//wait 1 second

		if (checkWin(board, 'X')) {
			std::cout << "X wins" << std::endl;
			gameOver = true;	//tells both threads the game is over
		}
		else if (moveCount == 9) {
			std::cout << "Tie" << std::endl;
			gameOver = true;	//tells both threads the game is over
		}
		else {

			currentTurn = 'O';	//after X moves, it becomes O turn

		}

		boardMutex.unlock();		//unlock the board so O can access it

	}
}

void playerO(char board[3][3]) {

	while (true) {

		boardMutex.lock();		//lock the board so only O can access it

		if (gameOver) {
			boardMutex.unlock();
			break;
		}

		if (currentTurn != 'O') {	//if its not O turn
			boardMutex.unlock();		//unlock the board
			continue;			//go back and try again
		}

		int row = rand() % 3;
		int col = rand() % 3;

		while (board[row][col] != ' ') {
			row = rand() % 3;
			col = rand() % 3;
		}

		board[row][col] = 'O';		//put O in empty space
		moveCount++;			//add one to the move count
		printBoard(board);		//print the board while 0 has the mutex
		std::this_thread::sleep_for(std::chrono::seconds(1));	//wait 1 second

		if (checkWin(board, 'O')) {
			std::cout << "O wins" << std::endl;
			gameOver = true;	//tells both threads the game is over
		}
		else if (moveCount == 9) {
			std::cout << "Tie" << std::endl;
			gameOver = true;
		}
		else {
			currentTurn = 'X';	//after O moves, its X turn

		}

		boardMutex.unlock();		//unlock the board so X can access it
	}
}

int main() {
	srand(time(0));			//start random numbers diff each time

	char board[3][3];		//creating a 3 by 3 tictactoe board
	for (int row = 0; row < 3; row++) {	//start at row 0, go until 3, increase by 1
		for (int col = 0; col < 3; col++) {	//do same thing for column
			board[row][col] = ' ';		//each space will be empty
		}
	}

	std::thread xThread(playerX, board);	//create thread for X and give it the board
	std::thread oThread(playerO, board);	//create thread for O and give it the board

	xThread.join();		//wait for X thread to finish
	oThread.join();		//wait for O thread to finish


	return 0;
}
