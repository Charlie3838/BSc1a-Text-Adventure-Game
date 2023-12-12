#pragma once
#include <string>
#include <vector>
using namespace std;

class Computer
{
public:
	static vector<string> playerInventory;
	static string yesOptions[];       //when you can change this so it converts to upper case
	static string noOptions[];
	static string commandList[];
	static string name;
	static string input;
	static int quotationCounter;
	static int happiness;
	static bool firstTimeSingleQuotes;

	static void Introduction();
	static void UserInput();
	static void EnterName();
	static void Explore();
	static void ExploreTakeItem();
	static void ExploreLeave();
	static void Gift();
	static void GiftTransferChoice();
	static void CheckName(string &_name);
	static void ReadFromFile(string _fileName, int &_filePosition);
	static void OutputText(string &_wordOutput, int _textSpeed);
	static void OutputText(string &_wordOutput, int _textSpeed, bool _isEndOfLine);
	static string Uppercase(string _input);
	static void CheckInput(string _input);
	
	//static int GetArrLength(T(&)[size]);
	template <typename T, int size> static bool FindInArray(T _array[], T(&)[size], T item);

};

