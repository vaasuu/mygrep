#include <iostream>
#include <string>
using namespace std;

void simpleSearch();

int main(int argc, char *argv[]){   // get arguments from binary ran from cli


    if (argc == 1) // if no arguments provided, ask the user for input
    {
        simpleSearch();
    }
}

void simpleSearch(){
    string stringToSearchFrom, stringToSearch;
    double position;

    cout << "Give a string from which to search for: ";
    getline(cin, stringToSearchFrom);
    cout << "Give search string: ";
    getline(cin, stringToSearch);

    position = stringToSearchFrom.find(stringToSearch); //returns index for needle in haystack if found OR return string::npos (max value)

    if (position != string::npos) // check for match, if found, print strings and index
        {
            cout << "\n" << '"' << stringToSearch << '"' << " found in \"" << stringToSearchFrom << '"' << " in position " << position << endl;
        }
    else // if no match, print NOT found
        {
            cout << "\n" << '"' << stringToSearch << '"' << " NOT found in \"" << stringToSearchFrom << '"' << endl;
        } 
}