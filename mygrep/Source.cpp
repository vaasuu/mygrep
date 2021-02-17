#include <iostream>
#include <string>
#include <string.h>
using namespace std;

void simpleSearch(const char*, const char*);
void askForInputAndSearch();

int main(int argc, char *argv[]){   // get arguments from binary ran from cli

    if (argc == 1) // if no arguments provided, ask the user for input
    {
        askForInputAndSearch();
    }
}

void askForInputAndSearch(){
    string stringToSearchFrom, stringToSearch;

    cout << "Give a string from which to search for: ";
    getline(cin, stringToSearchFrom);
    cout << "Give search string: ";
    getline(cin, stringToSearch);

    simpleSearch(stringToSearchFrom.c_str(), stringToSearch.c_str());
}

void simpleSearch(const char* stringToSearchFrom, const char* stringToSearch){
    
    const char* result = strstr(stringToSearchFrom, stringToSearch); // returns a pointer to the first occurrence of stringToSearch in stringToSearchFrom, or a null pointer if stringToSearch is not part of stringToSearchFrom

    if (result != NULL) // check for match, if found, print strings and index
        {
            int position = result-stringToSearchFrom; // calculate substring's index in bigstring
            cout << "\n" << '"' << stringToSearch << '"' << " found in \"" << stringToSearchFrom << '"' << " in position " << position << endl;
        }
    else // if no match, print NOT found
        {
            cout << "\n" << '"' << stringToSearch << '"' << " NOT found in \"" << stringToSearchFrom << '"' << endl;
        } 
}