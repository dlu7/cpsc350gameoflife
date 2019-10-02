#include <iostream>
#include "Board.h"
#include <cstdio>
#include <fstream>
using namespace std;


int main()
{
	//////////
	GameOfLife game;

	int mapSetting = 0;

	while (true) {
		//How user wants to see the info
		cout << "How do you want the data displayed? (type the number: '1'.pause, '2'.enter, or '3'.file)" << endl;
		cin >> game.outputType;
		cout << endl;

		if (game.outputType == 1)
		{
			break;

		}
		else if (game.outputType == 2) {

			break;

		}
		else if (game.outputType == 3) {

			cout << "What file would you like print out to? (include '.txt') \n" << endl;
			string fileToOutput; //if they want to output to file
			ifstream out("output.txt");
			if (out.is_open())
			{
				cout << out.rdbuf();
				out.close();
			}
			break;

		}
		else {
			cout << "Try again.\n" << endl;
		}

	}


	//checks if wants to randomize or submit map
	while (true) {

		//If User wants Random map or File map
		cout << "Would you like to have a random board or submit your own file? (type the number: '1'.random or '2'.file)" << endl;
		cin >> mapSetting;
		cout << endl;
		//if chose random
		if (mapSetting == 1)
		{
			cout << "You have selected random." << endl;

			//map generator function -- fix later
			game.CreateRandomBoard();
			break;

		} //if chose file upload
		else if (mapSetting == 2) {

			game.ImportMapFile();
			break;

		}
		else {

			cout << "Does not compute, try again \n" << endl;

		}
	}

	////////////
}