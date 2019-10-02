#include <iostream> 
#include "Board.h"
#include <sstream> 
#include <fstream> 
using namespace std;

void GameOfLife::MirrorMode(char **&board)
{

	char** newBoard = board;
	int count = 0;
	int generation = 1;
	bool stable = false;

	while (!stable)
	{
		// for loops through both boards 
		DonutBoardScan(count, board, newBoard);

		//check to make sure the map is stable
		int stableCells = 0;
		cout << "Resetting cell count: \n";

		for (int y = 0; y < ::length; y++)
		{
			for (int x = 0; x < ::width; x++)
			{
				if (newBoard[y][x] == board[y][x])
				{//increase stable count
					stableCells++;
				}
			}
		}

		/////check to see if board stabilized
		int length;
		int width;
		if (stableCells == (length * width))
		{
			//stable -> will break loop and print
			stable = true;
			cout << "World is now stable. \n";
		}
		else
		{

			for (int x = 0; x < ::length; ++x)
			{
				for (int y = 0; y < ::width; ++y)
				{ //swap for next gen to start
					board[x][y] = newBoard[x][y];
				}
			}
			//next generation if not stable
			generation++;

		}

	} //END OF STABLE LOOP

	  //print final result
	PrintOutput(outputType, generation, newBoard);


}

void GameOfLife::MirrorBoardScan(int neighborCount, char **&board, char **&nextGen)
{

	for (int y = 0; y < ::length; ++y) {
		for (int x = 0; x < ::width; ++x) {
			neighborCount = 0;


			if (y == 0 && x == 0) {
				if (board[y + 1][x] == 'X') neighborCount += 2;
				if (board[y][x + 1] == 'X') neighborCount += 2;
				if (board[y + 1][x + 1] == 'X') neighborCount++;
				if (board[y][x] == 'X') neighborCount += 3;
			}
			else if (y == 0 && x == (::width - 1)) {
				if (board[y + 1][x] == 'X') neighborCount += 2;
				if (board[y][x - 1] == 'X') neighborCount += 2;
				if (board[y + 1][x - 1] == 'X') neighborCount++;
				if (board[y][x] == 'X') neighborCount += 3;
			}
			else if (y == (::length - 1) && x == (::width - 1)) {
				if (board[y - 1][x] == 'X') neighborCount += 2;
				if (board[y][x - 1] == 'X') neighborCount += 2;
				if (board[y - 1][x - 1] == 'X') neighborCount++;
				if (board[y][x] == 'X') neighborCount += 3;
			}
			else if (y == (::length - 1) && x == 0) {
				if (board[y - 1][x] == 'X') neighborCount += 2;
				if (board[y][x + 1] == 'X') neighborCount += 2;
				if (board[y - 1][x + 1] == 'X') neighborCount++;
				if (board[y][x] == 'X') neighborCount += 3;
			}
			else if (y == 0) {
				if (board[y + 1][x] == 'X') neighborCount++;
				if (board[y][x + 1] == 'X') neighborCount += 2;
				if (board[y + 1][x + 1] == 'X') neighborCount++;
				if (board[y][x - 1] == 'X') neighborCount += 2;
				if (board[y + 1][x - 1] == 'X') neighborCount++;
				if (board[y][x] == 'X') neighborCount++;
			}
			else if (x == 0) {
				if (board[y - 1][x] == 'X') neighborCount += 2;
				if (board[y + 1][x] == 'X') neighborCount += 2;
				if (board[y][x + 1] == 'X') neighborCount++;
				if (board[y + 1][x + 1] == 'X') neighborCount++;
				if (board[y - 1][x + 1] == 'X') neighborCount++;
				if (board[y][x] == 'X') neighborCount++;
			}
			else if (y == (::length - 1)) {
				if (board[y - 1][x] == 'X') neighborCount++;
				if (board[y][x + 1] == 'X') neighborCount += 2;
				if (board[y - 1][x + 1] == 'X') neighborCount++;
				if (board[y][x - 1] == 'X') neighborCount += 2;
				if (board[y - 1][x - 1] == 'X') neighborCount++;
				if (board[y][x] == 'X') neighborCount++;
			}
			else if (x == (::width - 1)) {
				if (board[y - 1][x] == 'X') neighborCount += 2;
				if (board[y + 1][x] == 'X') neighborCount += 2;
				if (board[y][x - 1] == 'X') neighborCount++;
				if (board[y + 1][x - 1] == 'X') neighborCount++;
				if (board[y - 1][x - 1] == 'X') neighborCount++;
				if (board[y][x] == 'X') neighborCount++;
			}
			else {
				if (board[y + 1][x] == 'X') neighborCount++;
				if (board[y][x + 1] == 'X') neighborCount++;
				if (board[y + 1][x + 1] == 'X') neighborCount++;
				if (board[y][x - 1] == 'X') neighborCount++;
				if (board[y - 1][x] == 'X') neighborCount++;
				if (board[y - 1][x - 1] == 'X') neighborCount++;
				if (board[y + 1][x - 1] == 'X') neighborCount++;
				if (board[y - 1][x + 1] == 'X') neighborCount++;
			}
			if (neighborCount < 2) {
				//Death 
				nextGen[y][x] = '-';
			}
			else if (neighborCount == 2) {
				//Stablized
				nextGen[y][x] = board[y][x];
			}
			else if (neighborCount == 3) {
				//Birth of Cell
				nextGen[y][x] = 'X';
			}
			else if (neighborCount > 3) {
				//Death
				nextGen[y][x] = '-';
			}
		}
	}
}