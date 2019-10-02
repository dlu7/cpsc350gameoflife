#include <iostream>
#include "Board.h"
#include <string>
#include <cstdlib>
#include <fstream>
#include <math.h>
#include <time.h>
#include <sstream>

using namespace std;
//constructor
GameOfLife::GameOfLife()
{
	int outputType = 0; // assign pause/display type
}

//destructor
GameOfLife::~GameOfLife()
{

}


void GameOfLife::CreateRandomBoard()
{
	double density = 0.0;

	int initialCells = 0;
	int randLength = 0;
	int randWidth = 0;
	int length;
	int width;

	//Input length
	cout << "What is the length of the board?" << endl;
	cin >> length;
	cout << endl;

	//Input width
	cout << "What is the width of your board?" << endl;
	cin >> width;
	cout << endl;

	//Import Density
	while (true) {
		cout << "Enter a density between 0 and 1." << endl;
		cin >> density;
		cout << endl;

		if ((density >= 0.0) && (density <= 1.0))
		{
			break;
		}
		else
		{
			cout << "That number is not between 0 and 1! Try again.";
		}
	}

	char** board = new char*[length];

	for (int i = 0; i < length; ++i)
	{
		board[i] = new char[width];
	}

	initialCells = round((length*width)*density);

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//sets up the entire board with empty slots
			board[i][j] = '-';
		}
	}
	//Calls time to create a truly random set of values
	srand(time(NULL));

	for (int k = 0; k < initialCells; k++)
	{
		randLength = rand() % (length);
		randWidth = rand() % (width);

		bool cellPlaced = false;

		while (!cellPlaced) {
			if (board[randLength][randWidth] == '-')
			{
				board[randLength][randWidth] = 'X';
				cellPlaced = true;
			}
			else
			{
				randLength = rand() % (length);
				randWidth = rand() % (width);
			}
		}
	}

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//sets up the entire board with empty slots
			cout << board[i][j];
		}
		cout << endl;
	}

	SelectMode(board); //<-- fix soon	YEEHAW
}

void GameOfLife::ImportMapFile()
{
	string fileToImport;

	cout << "What is the name of the .txt file you want to use? (include \".txt\")" << endl;
	cin >> fileToImport;
	cout << endl;

	ifstream inputStream;

	//Open up file user is reading
	inputStream.open(fileToImport.c_str());
	//initialize temporary measurements
	int tLength = 0;
	int tWidth = 0;

	int count = 0;

	string line = "";
	//while not the end of file
	while (!inputStream.eof())
	{ //get a line
		getline(inputStream, line);
		//if this is the first line
		if (count == 0) {

			tLength = atoi(line.c_str());
		}
		else if (count == 1) {

			tWidth = atoi(line.c_str());
		}
		else
		{
			break;
		}

		count++;
	}

	count = 0;

	char** board = new char*[tLength];


	for (int x = 0; x < tLength; ++x) {
		board[x] = new char[tWidth];
	}

	for (int x = 0; x < tLength; x++) {
		for (int y = 0; y <tWidth; y++) {
			board[x][y] = '-';
		}
	}

	inputStream.seekg(0, inputStream.beg);

	int row = 0;

	while (!inputStream.eof()) {

		getline(inputStream, line);

		if (count == 0) {

		}
		else if (count == 1) {

		}
		else {
			for (int x = 0; x < tWidth; x++) {
				char letter = line[x];
				board[row][x] = letter;
			}
			row++;
		}
		count++;
	}

	SelectMode(board);

}

///////////////
void GameOfLife::SelectMode(char**& board)
{
	int mode = 0;

	while (true)
	{

		cout << "Select game mode by number: '1'.Classic, '2'.Mirror, or '3'.Donut" << endl;
		cin >> mode;

		if (mode == 1)
		{
			cout << "Classic Mode Selected. \n";
			ClassicMode(board);
			break;
		}
		else if (mode == 2)
		{
			cout << "Mirror Mode Selected. \n";
			MirrorMode(board);
			break;
		}
		else if (mode == 3)
		{
			cout << "Donut Mode Selected. \n";
			DonutMode(board);
			break;
		}
		else
		{
			cout << "Wrong number, try again \n";
		}
	}
}


///Game Modes Below this 

void GameOfLife::ClassicMode(char **&board)
{
	char** newBoard = board;
	int count = 0;
	int generation = 1;
	bool stable = false;

	while (!stable)
	{
		ClassicBoardScan(count, board, newBoard);

		//check to make sure the map is stable
		int stableCells = 0;
		cout << "Resetting cell count: \n";

		for (int y = 0; y < length; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if (newBoard[y][x] == board[y][x])
				{
					//increase stable count
					stableCells++;
				}
			}
		}

		//check to see if board stabilized

		if (stableCells == length * width)
		{
			//stable
			stable = true;
			cout << "World is now stable. \n";
		}
		else
		{

			for (int i = 0; i < length; ++i)
			{
				for (int j = 0; j < width; ++j)
				{ //swap for next gen to start
					board[i][j] = newBoard[i][j];
				}
			}
			generation++;

		}

	} //END OF STABLE LOOP

	  //print final result
	PrintOutput(outputType, generation, newBoard);


} // end of method

void GameOfLife::ClassicBoardScan(int count, char **&board, char **&nextGen)
{
	for (int y = 0; y < length; y++)
	{
		for (int x = 0; x < width; x++)
		{
			count = 0;
			//bottom left corner
			if (y == 0 && x == 0)
			{
				if (board[y + 1][x] == 'X') count++;
				if (board[y][x + 1] == 'X') count++;
				if (board[y + 1][x + 1] == 'X') count++;
			}
			else if (y == 0 && x == (width - 1)) {
				if (board[y + 1][x] == 'X') count++;
				if (board[y][x - 1] == 'X') count++;
				if (board[y + 1][x - 1] == 'X') count++;
			}
			else if (y == (length - 1) && x == 0) {
				if (board[y - 1][x] == 'X') count++;
				if (board[y][x + 1] == 'X') count++;
				if (board[y - 1][x + 1] == 'X') count++;
			}
			else if (y == (length - 1) && x == (width - 1)) {
				if (board[y - 1][x] == 'X') count++;
				if (board[y][x - 1] == 'X') count++;
				if (board[y - 1][x - 1] == 'X') count++;
			}
			//Checks the Sides of the Board
			else if (y == 0) {
				if (board[y + 1][x] == 'X') count++;
				if (board[y][x + 1] == 'X') count++;
				if (board[y + 1][x + 1] == 'X') count++;
				if (board[y][x - 1] == 'X') count++;
				if (board[y + 1][x - 1] == 'X') count++;
			}
			else if (x == 0) {
				if (board[y - 1][x] == 'X') count++;
				if (board[y + 1][x] == 'X') count++;
				if (board[y][x + 1] == 'X') count++;
				if (board[y + 1][x + 1] == 'X') count++;
				if (board[y - 1][x + 1] == 'X') count++;
			}
			else if (y == (length - 1)) {
				if (board[y - 1][x] == 'X') count++;
				if (board[y][x + 1] == 'X') count++;
				if (board[y - 1][x + 1] == 'X') count++;
				if (board[y][x - 1] == 'X') count++;
				if (board[y - 1][x - 1] == 'X') count++;
			}
			else if (x == (width - 1)) {
				if (board[y - 1][x] == 'X') count++;
				if (board[y + 1][x] == 'X') count++;
				if (board[y][x - 1] == 'X') count++;
				if (board[y + 1][x - 1] == 'X') count++;
				if (board[y - 1][x - 1] == 'X') count++;
			}
			else {
				if (board[y + 1][x] == 'X') count++;
				if (board[y][x + 1] == 'X') count++;
				if (board[y + 1][x + 1] == 'X') count++;
				if (board[y][x - 1] == 'X') count++;
				if (board[y - 1][x] == 'X') count++;
				if (board[y - 1][x - 1] == 'X') count++;
				if (board[y + 1][x - 1] == 'X') count++;
				if (board[y - 1][x + 1] == 'X') count++;
			}

			if (count <2)
			{ //not enough neighbors
				nextGen[y][x] = '-';
			}
			else if (count == 2)
			{ //stable neighbors
				nextGen[y][x] = board[y][x];
			}
			else if (count == 3)
			{
				nextGen[y][x] = 'X';
			}
			else if (count > 3)
			{
				nextGen[y][x] = '-';
			}

		} // inner loop
	} // outer loop
}

void GameOfLife::PrintOutput(int outputType, int countGen, char**& board)
{
	bool enter = false;
	//If statement to pause the print to the terminal
	if (outputType == 1) {

		cout << "Generation: " << countGen << "\n";

		for (int i = 0; i < length; ++i) {
			for (int j = 0; j < width; ++j) {
				cout << board[i][j];
			}
			cout << "\n";
		}
		//Prints upon enter key
	}
	else if (outputType == 2) {

		cout << "Press enter key to continue \n" << endl;
		cin.get();

		if (cin.get()) {
			enter = true;
		}

		if (enter == true)
		{
			cout << "Generation: " << countGen << "\n";

			for (int i = 0; i < length; ++i) {
				for (int j = 0; j < width; ++j) {
					cout << board[i][j];
				}
				cout << "\n";
			}
		}
	}
}