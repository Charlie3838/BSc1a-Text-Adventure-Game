#include "Computer.h"
#include "PlayerInfo.h"
#include <iostream>
#include <array> 
#include <string>
using namespace std;


string yesOptions[] = { "YES", "Y", "TRUE", "T"  };             //when you can change this so it converts to upper case
string noOptions[] = { "NO", "N", "FALSE", "F" };

void Computer::Introduction() {
    //string yesOptions[] = { "yes", "y", "true", "t" };
    //string noOptions[] = { "no", "n", "false", "n" };

    //convert char array to string data type
    //both data types must be the same
    //cout << FindInArray(yesOptions, item) << endl;


    
    cout << "HELLO WORLD.\n";
    cout << "I AM HELPFUL-COMPUTER.\n";
    cout << "I MUST SET UP FOR YOU.\n";
    EnterName();
    
    //cout << "Enter your age for my storage of you: ";
    //check age
    //cout << "What is your favorite colour?";
    //cout << "Type \"List Commands\" and I will be helpful computer. ";
}

void Computer::EnterName() {
    string name;
    cout << "ENTER YOUR NAME SO I CAN STORE YOU:  ";
    
    getline(cin, name);
    cout << "I AM CHECKING NAME FOR YOU...\n";
    CheckName(name);
    cout << "HELLO " + name << endl;
}

void Computer::CheckName(string& _name) {
    string response;

    //if user inputs nothing
    if (_name.size() == 0) {
        cout << "YOU DID NOT GIVE ME NAME\n";
        cout << "DID YOU COMIT ERROR? ";
        //prompts user for a choice
        cin >> response;
        //if user said yes
        if (FindInArray(noOptions, noOptions, (response))) {
            cout << "I WILL NAME YOU\n";
            _name = "Place holder";
        }
        //if user said no
        else if (FindInArray(yesOptions, yesOptions, response)) {
            EnterName();
        }
        //if user said something else
        else {

        }
        

        
    }


    //if user inputs a long nametimes
    if (_name.size() >= 15) {
        cout << "YOUR NAME IS LONG";
        cout << "IS NAME ENTERED TRUE?";
    }

}

//using templates so that any array of any type can be checked.
template <typename T, int size> bool Computer::FindInArray(T _array[], T(&)[size], T item)
{
    for (int i = 0; i < size; i++) {
        //if item is check and is in array
        if (_array[i] == item) {
            return true;
        }       
    }
    return false;
}
    
    /*array<string, 4> yesOptions{ "yes", "y", "true", "t" };
    array<string, 4> noOptions{ "no", "n", "false", "n" };*/





    
    
    //int size = *(&array + 1) - array;


    //this works

    /*int testArray[] = { 1, 3, 5, 7, 9 };
    for (int i : testArray) {
        cout << "hi\n";
    }
    return true;*/




    //this does not

    //for every item in the array
    
    //for (T i; array) {
    //    //if item is check and is in array
    //    if (i == item) {
    //        return true;
    //    }
    //    //otherwise
    //    else {
    //        return false;
    //    }
    //}



    


    //return (x > y) ? x : y; //terenary operators (short if statement, if x > y, return x else return y)
