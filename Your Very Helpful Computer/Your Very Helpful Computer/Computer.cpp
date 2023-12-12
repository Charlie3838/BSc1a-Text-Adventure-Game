#include "Computer.h"
#include "PlayerInfo.h"
#include <iostream>
#include <array> 
#include <string>
#include <windows.h>
#include <fstream>
#include <vector>
using namespace std;

vector<string> Computer::playerInventory;
string Computer::yesOptions[] = { "YES", "Y", "TRUE", "T"  };             //when you can change this so it converts to upper case
string Computer::noOptions[] = { "NO", "N", "FALSE", "F" };
string Computer::commandList[] = {"LIST", "EXPLORE", "GIFT", "STATS"};
string Computer::name = "";
string Computer::input = "";

int Computer::quotationCounter = 0;
int Computer::happiness = 0;
bool Computer::firstTimeSingleQuotes = false;

void Computer::Introduction() {



    //convert char array to string data type
    //both data types must be the same
    //cout << FindInArray(yesOptions, item) << endl;

    
    
    /*cout << "HELLO WORLD.\n";
    cout << "I AM HELPFUL-COMPUTER.\n";
    cout << "I MUST SET UP FOR YOU.\n";*/
    EnterName();
    
    //cout << "Enter your age for my storage of you: ";
    //check age
    //cout << "What is your favorite colour?";
    //cout << "Type \"List Commands\" and I will be helpful computer. ";
}

void Computer::EnterName() {

    int filePosition = 0;


    //THIS CODE WILL RUN THE INTRO

    ReadFromFile("EnterName", filePosition);
    ReadFromFile("EnterName", filePosition);
    getline(cin, name);
    ReadFromFile("EnterName", filePosition);
    CheckName(name);
    ReadFromFile("EnterName", filePosition);
    Sleep(200);
    cout << name;
    ReadFromFile("EnterName", filePosition);
    cout << name;
    ReadFromFile("EnterName", filePosition);
    filePosition = 0;
    Computer::UserInput();
    

    //THIS CODE WILL SKIP THE INTRO

    /*Computer::name = "Charlie";
    Computer::UserInput();*/
}


void Computer::UserInput() {
    int filePosition = 0;

    if (Computer::happiness >= 50) {

        if ((Computer::happiness <= 100)) {
            ReadFromFile("BestFriendComputer", filePosition);
        }
        else {
            ReadFromFile("UsefulComputer", filePosition);
        }

        
    }
    else if (Computer::happiness <= -50) {

        if ((Computer::happiness <= -100)) {
            ReadFromFile("ComputerGiveUp", filePosition);
            Sleep(200);
            cout << name;
            ReadFromFile("ComputerGiveUp", filePosition);
            return;
        }
        else {
            ReadFromFile("UnusefulComputer", filePosition);
        }
    }
    filePosition = 0;
        ReadFromFile("EnterInput", filePosition);
        getline(cin, Computer::input);
        CheckInput(Computer::input);
        //Recursion after user has finished their input.
        UserInput();

}









void Computer::ReadFromFile(string _fileName, int &_filePosition) {
    HANDLE ConsoleColour = GetStdHandle(STD_OUTPUT_HANDLE);
    string specialCharInput;
    int textSpeed = 200;
    int fileLength;
    bool isReadingSpecialChar = false;
    bool finishedReading = false;

    ifstream myfile(_fileName + ".txt");
    string myString = "";
    char myChar;

    if (myfile.is_open()) {
        //find the length of the file       (used for returning to a position in the file)
        myfile.seekg(0, ios_base::end);
        fileLength = myfile.tellg();
        myfile.seekg(_filePosition, ios_base::beg);
        //while reading the file
        while (myfile) {
            //store the first character read into variable myChar
            myChar = myfile.get();

            //if the character is a space
            if (myChar == ' ') {
                OutputText(myString, textSpeed);
            }
            //if the character uses a single '\'
            else if (myChar == '\\') {

                //if this is the closing '\' character          (the format for special keys works as such: \<key><value>\. There are two of the '\' character.)
                if (isReadingSpecialChar) {
                    //no longer reading special characters
                    isReadingSpecialChar = false;

                    //if the character read after the '\' is an 'S'
                    if (specialCharInput[0] == 'S') {
                        //Remove the 'S'
                        specialCharInput.erase(0, 1);
                        textSpeed = stoi(specialCharInput);
                    }
                    //if the character read after the '\' is a 'C'
                    else if (specialCharInput[0] == 'C') {
                        //Remove the 'C'
                        specialCharInput.erase(0, 1);
                        //Set text colour to code
                        SetConsoleTextAttribute(ConsoleColour, stoi(specialCharInput));

                    }
                    //if the character read after the '\' is a 'P'
                    else if (specialCharInput[0] == 'P') {
                        //Remove the 'P'
                        specialCharInput.erase(0, 1);
                        //Close the file
                        
                        //Exit the function
                        finishedReading = true;
                        _filePosition++;
                        myfile.close();
                        
                    }
                    //if no valid character was recognised...
                    else {
                        cout << "error";
                    }

                    //convert the special character string to text speed
                    specialCharInput = "";
                }
                //if this is the opening '\' character
                else {
                    //start reading special characters from this point onwards
                    isReadingSpecialChar = true;

                }
            }
            //if there is a new line or the file ends        ('ÿ' is defined as the character for the end of a file)
            else if ((myChar == '\n' || myChar == 'ÿ') && (!finishedReading)) {
                OutputText(myString, textSpeed, true);
            }
            else {
                //if the first set of '\\' has been read
                if (isReadingSpecialChar) {

                    specialCharInput += myChar;
                }
                //do not add the specical character to the string
                else {
                    myString += myChar;
                }
                //if the character is normal

                
            }

            //increment the position of variable filePosition
            _filePosition++;         //(used for returning to a position in the file)
        }
    }
    return;
}

//by default, output includes a space.
void Computer::OutputText(string& _wordOutput, int _textSpeed) {
    //wait for the set length of time and output the current word read
    Sleep(_textSpeed);
    cout << _wordOutput + " ";
    _wordOutput = "";
}

void Computer::OutputText(string& _wordToOutput, int _textSpeed, bool _isEndOfLine) {
    //wait for the set length of time and output the current word read
    Sleep(_textSpeed);
    cout << _wordToOutput;
    //if it is not the end of the line, add a space after the text.
    if (!_isEndOfLine) {
        cout << " ";
    }
    else {
        cout << "\n";
    }
    _wordToOutput = "";
}

void Computer::CheckInput(string _input)
{
    
    bool doubleQuotationDetection = false;
    //if users trys to bypass double quotations and use single qutations instead
    bool singleQuotationDetection = false;
    
    //check if the user has put quotation marks around request
    for (char currentChar : _input) {
        if (currentChar == '"') {
            doubleQuotationDetection = true;
        }
        if (currentChar == '\'') {
            singleQuotationDetection = true;
        }
    }

    if (FindInArray(commandList, commandList, Computer::Uppercase(_input)) && !doubleQuotationDetection && !singleQuotationDetection) {
        //run command
        _input = Computer::Uppercase(_input);  //{"LIST", "EXPLORE", "GIFT", "STATS", "STORY"}
        if (_input == "LIST") {
            string choice;
            Sleep(200);
            cout << "CHOOSE ";
            Sleep(200);
            cout << "WHAT ";
            Sleep(200);
            cout << "I ";
            Sleep(200);
            cout << "WILL ";
            Sleep(200);
            cout << "LIST: \n ";
            Sleep(200);
            cout << "- COMMANDS \n ";
            Sleep(200);
            cout << "- INVENTORY \n\n ";
            getline(cin, choice);
            choice = Computer::Uppercase(choice);
            if (choice == "COMMANDS") {
                Sleep(200);
                cout << "\nCOMMANDS:\n";
                for (string commandListVariable : commandList) {
                    Sleep(100);
                    cout << commandListVariable << endl;
                }
            }
            else if (choice == "INVENTORY"){
                Sleep(200);
                cout << "\nINVENTORY:\n";
                for (auto i = playerInventory.begin(); i != playerInventory.end(); ++i){
                    cout << *i << " ";
                }
            }
            else {
                Sleep(200);
                cout << "INVALID ";
                Sleep(200);
                cout << "REQUEST.\n";
            }

            //List all commands
            
        }
        else if (_input == "EXPLORE") {
            //Explore a field where you can collect items
            Computer::Explore();
        }
        else if (_input == "GIFT") {
            Computer::Gift();
            //Give an item to the computer
        }
        else if (_input == "STATS") {
            Sleep(200);
            cout << "\nCURRENTLY, ";
            Sleep(200);
            cout << "I ";
            Sleep(200);
            cout << "AM ";
            Sleep(200);
            cout << "AT ";
            Sleep(200);
            cout << "HAPPINESS ";
            Sleep(200);
            cout << "VALUE ";
            Sleep(200);
            cout << Computer::happiness << endl;


            //Computer::happiness -= 5;
            //See the computer's stats
        }
    }
    else if (doubleQuotationDetection) {
        int filePosition = 0;
        if (quotationCounter == 0) {
            ReadFromFile("DetectDoubleQuotation", filePosition);
        }
        else if (quotationCounter == 1) {
            filePosition = 132;
            ReadFromFile("DetectDoubleQuotation", filePosition);
            Computer::happiness -= 5;
        }
        else if (quotationCounter == 2) {
            filePosition = 312;
            ReadFromFile("DetectDoubleQuotation", filePosition);
            Computer::happiness -= 10;
        }
        else if (quotationCounter == 3) {
            filePosition = 355;
            ReadFromFile("DetectDoubleQuotation", filePosition);
            Computer::happiness -= 15;
        }
        else {
            filePosition = 398;
            ReadFromFile("DetectDoubleQuotation", filePosition);
            Computer::happiness -= 15;
        }
        quotationCounter++;
    }//If the user tries to use single quotes as an alternative to double quotes...
    else if (singleQuotationDetection) {
        
        
        if (quotationCounter == 0) {
            Computer::firstTimeSingleQuotes = true;
            int filePosition = 0;
            ReadFromFile("DetectSingleQuotation", filePosition);
            Sleep(200);
            cout << Computer::name;
            ReadFromFile("DetectSingleQuotation", filePosition);
            Sleep(200);
            cout << Computer::name;
            ReadFromFile("DetectSingleQuotation", filePosition);
            
            ReadFromFile("DetectSingleQuotation", filePosition);
            filePosition += 0;
        }
        else if (quotationCounter == 1 && Computer::firstTimeSingleQuotes) {
            int filePosition = 482;
            ReadFromFile("DetectSingleQuotation", filePosition);
            filePosition += 0;
            Computer::happiness -= 30;
        }
        else if (quotationCounter == 1) {
            int filePosition = 757;
            ReadFromFile("DetectSingleQuotation", filePosition);
            filePosition += 0;
            Computer::happiness -= 20;
        }
        else {
            int filePosition = 1028;
            ReadFromFile("DetectSingleQuotation", filePosition);
            Computer::happiness -= 20;
        }
        quotationCounter++;
    }
    else {
        Sleep(200);
        cout << "\nYOUR ";
        Sleep(200);
        cout << "RESPONSE ";
        Sleep(200);
        cout << "I ";
        Sleep(200);
        cout << "NOT ";
        Sleep(200);
        cout << "IDENTIFY...\n";
        //invalid command
    }

}

void Computer::Explore() {
    int filePosition = 0;
    cout << endl;
    ReadFromFile("ExploringFields", filePosition);
    Computer::happiness += 5;
    Computer::ExploreTakeItem();
   

}
void Computer::ExploreTakeItem(){
    string response;
    getline(cin, response);
    response = Computer::Uppercase(response);

    if (Computer::FindInArray(Computer::yesOptions, Computer::yesOptions, response)) {
        Sleep(200);
        cout << "YOU ";
        Sleep(200);
        cout << "GET ";
        Sleep(200);
        cout << "BINARY ";
        Sleep(200);
        cout << "FLOWER.\n";
        Computer::playerInventory.push_back("Binary Flower");
        Sleep(1000);
        cout << "LEAVE? ";
        Computer::ExploreLeave();
    }
    else if (Computer::FindInArray(Computer::noOptions, Computer::noOptions, response)) {

        cout << "LEAVE? ";
        Computer::ExploreLeave();
        return;

    }
    else {
        Sleep(200);
        cout << "YOUR ";
        Sleep(200);
        cout << "RESPONSE ";
        Sleep(200);
        cout << "I ";
        Sleep(200);
        cout << "NOT ";
        Sleep(200);
        cout << "IDENTIFY... ";
        Sleep(1000);
        cout << "STILL ";
        Sleep(200);
        cout << "WANT ";
        Sleep(200);
        cout << "ITEM? ";
        ExploreTakeItem();
    }

}

void Computer::ExploreLeave() {
    string response;
    getline(cin, response);
    if (Computer::FindInArray(Computer::yesOptions, Computer::yesOptions, response)) {
        //Return to main function
        return;
    }
    else if (Computer::FindInArray(Computer::noOptions, Computer::noOptions, response)) {
        //Search again
        Sleep(1000);
        cout << "STILL ";
        Sleep(200);
        cout << "WANT ";
        Sleep(200);
        cout << "ITEM? ";
        ExploreTakeItem();
    }
    else {
        Sleep(200);
        cout << "YOUR ";
        Sleep(200);
        cout << "RESPONSE ";
        Sleep(200);
        cout << "I ";
        Sleep(200);
        cout << "NOT ";
        Sleep(200);
        cout << "IDENTIFY... ";
        Sleep(1000);
        cout << "LEAVE? ";
        ExploreLeave();
    }
}

void Computer::Gift() {
    string response;
    int counter = 0;
    Sleep(200);
    cout << "YOU ";
    Sleep(200);
    cout << "ARE ";
    Sleep(200);
    cout << "TRANSFERRING ";
    Sleep(200);
    cout << "ME ";
    Sleep(200);
    cout << "ITEM? ";
    Sleep(1000);
    cout << "\nINVENTORY:\n";
    for (auto i = playerInventory.begin(); i != playerInventory.end(); ++i) {
        cout << "- " << *i << "\n";
    }
    Sleep(1000);
    cout << "\nWHAT ";
    Sleep(200);
    cout << "ITEM ";
    Sleep(200);
    cout << "YOU ";
    Sleep(200);
    cout << "TRANSFER? ";
    getline(cin, response);
    //check if user's selection is in inventory
    for (string item : playerInventory) {
        if (Uppercase(response) == Uppercase(item)) {
            playerInventory.erase(playerInventory.begin() + counter);

            if (item == "Binary Flower") {
                Sleep(200);
                cout << "THIS ";
                Sleep(200);
                cout << "GIFT ";
                Sleep(200);
                cout << "SETS ";
                Sleep(200);
                cout << "MY ";
                Sleep(200);
                cout << "HAPPINESS ";
                Sleep(200);
                cout << "TO ";
                Sleep(200);
                cout << "HIGHER. ";
                Computer::happiness += 15;
                Sleep(1000);
                cout << "THANK ";
                Sleep(200);
                cout << "YOU\n";
            }

            return;
        }
        counter++;
    }
    Computer::GiftTransferChoice();

}

void Computer::GiftTransferChoice() {
    string response;
    Sleep(200);
    cout << "STILL ";
    Sleep(200);
    cout << "TRANSFERRING ";
    Sleep(200);
    cout << "ME ";
    Sleep(200);
    cout << "ITEM? ";
    getline(cin, response);
    response = Computer::Uppercase(response);
    if (Computer::FindInArray(Computer::yesOptions, Computer::yesOptions, response)) {
        //Return to main function
        Gift();
    }
    else if (Computer::FindInArray(Computer::noOptions, Computer::noOptions, response)) {
        return;
    }
    else {
        Sleep(200);
        cout << "YOUR ";
        Sleep(200);
        cout << "RESPONSE ";
        Sleep(200);
        cout << "I ";
        Sleep(200);
        cout << "NOT ";
        Sleep(200);
        cout << "IDENTIFY...\n";
        GiftTransferChoice();
    }

}

void Computer::CheckName(string& _name) {
    int filePosition = 0;
    //if user inputs nothing
    if (_name.size() == 0) {
        ReadFromFile("NoName", filePosition);
        _name = "PLACEHOLDER";
    }
    //if user inputs a long name
    else if (_name.size() > 15) {
        //shorten name
        ReadFromFile("LongName", filePosition);
        _name = _name.erase(15, _name.length());
    }
    else {
        ReadFromFile("GoodName", filePosition);
    }


    
}




//using templates so that any array of any type can be checked.
template <typename T, int size> bool Computer::FindInArray(T _array[], T(&)[size], T item)
{
    for (int i = 0; i < size; i++) {
        //if item is checked and is in array
        if (_array[i] == item) {
            return true;
        }       
    }
    //if the item is not in the array
    return false;
}

string Computer::Uppercase(string _input) {
    string output = "";
    int counter = 0;
    for (char currentChar : _input) {
        output += toupper(_input[counter]);
        counter++;
    }
    return output;

}



    


    //return (x > y) ? x : y; //terenary operators (short if statement, if x > y, return x else return y)
