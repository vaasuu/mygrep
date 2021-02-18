#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
using namespace std;

void simpleSearch(const char*, const char*);
void askForInputAndSearch();
bool stringContainsChar(string str, string character);

int main(int argc, char *argv[]){   // get arguments from binary ran from cli

    bool printOccuranceCount = false;
    bool printLineNumbers = false;
    bool ExcludeSearchLines = false;
    bool IgnoreCase = false;

    if (argc == 1) // if no arguments provided, ask the user for input
    {
        askForInputAndSearch();
    }

    if (argc == 3) // if 3 arguments provided, like so `mygrep needle haystack.txt` 
    {
        char* stringToSearch = argv[1];
        char* filename = argv[2];

        // char* stringToSearch = "following"; // debug
        // char* filename = "../teht-anto/man_grep_plain_ASCII.txt"; // debug

        // cout << stringToSearch << endl;
        // cout << filename << endl;

        string line;
        ifstream myfile;
        myfile.open(filename);
        if (myfile.is_open())
        {
            while (!myfile.eof())
            {
                getline(myfile, line);
                const char* result = strstr(line.c_str(), stringToSearch);
                if (result != NULL)
                {
                    cout << line << endl;
                }
            }
        }
        else
        {
            cerr << "Error opening file " << filename << endl;
        }
    }

    if (argc == 4)
    {

        string options_arg = argv[1];
        char* stringToSearch = argv[2];
        char* filename = argv[3];

        string options = options_arg.substr(2,string::npos);

        
        if (stringContainsChar(options, "l"))
        {
            printLineNumbers = true;
        }
        if (stringContainsChar(options, "o"))
        {
            printOccuranceCount = true;
        }        

        // char* stringToSearch = "following"; // debug
        // char* filename = "../teht-anto/man_grep_plain_ASCII.txt"; // debug

        int currentLine = 0;
        int countOccurrences = 0;

        string line;
        ifstream myfile;
        myfile.open(filename);
        if (myfile.is_open())
        {
            while (!myfile.eof())
            {
                getline(myfile, line);
                currentLine++;
                const char* result = strstr(line.c_str(), stringToSearch);
                if (result != NULL)
                {
                    countOccurrences++;

                    if (printLineNumbers)
                    {
                        cout << currentLine << ": ";
                    }
                    
                    cout << line << endl;
                }
            }
            if (printOccuranceCount)
            {
                cout << "\nOccurrences of lines containing \""<< stringToSearch << "\": " << countOccurrences << endl;
            }
            
        }
        else
        {
            cerr << "Error opening file " << filename << endl;
        }
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

bool stringContainsChar(string str, string character){
    if (str.find(character) != string::npos)
        {
            return true;
        }
    else
    {
        return false;
    }
}