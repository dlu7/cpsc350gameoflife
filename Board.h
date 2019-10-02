#include <iostream>
#include <fstream>

using namespace std;

//global variables
extern int length;
extern int width;

class GameOfLife
{
public:
	int outputType;

	GameOfLife(); //Constructor
	~GameOfLife(); //Destructor

	void GameSetUp();
	void CreateRandomBoard();
	void ImportMapFile();
	void SelectMode(char**& board);
	void PrintOutput(int outputType, int countGen, char**& board);

	void ClassicMode(char**& board);
	void DonutMode(char**& board);
	void MirrorMode(char**& board);
	void ClassicBoardScan(int count, char**& board, char **&nextGen);
	void DonutBoardScan(int count, char**& board, char **&nextGen);
	void MirrorBoardScan(int count, char**& board, char **&nextGen);

};