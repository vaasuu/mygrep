#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
using namespace std;

void simpleSearch(const char*, const char*);
void askForInputAndSearch();
bool stringContainsChar(string str, string character);
char* strcasestr(const char* bigStr, const char* searchStr);

int main(int argc, char *argv[]){   // get arguments from binary ran from cli

    // handle too many arguments
    try
    {
        if (argc > 4)
            throw "Too many arguments. "; // throw exception
    }
    catch(const char* e)
    {
        cerr << "An exception occurred. ";
        cerr << e << endl;
        exit(1); // exit program
    }

    if (argc == 1) // if no arguments provided, ask the user for input
        askForInputAndSearch();

    else if (argc == 2) // Only one argument -> error 
    {
        cerr << "Illegal amount of arguments.";
    }
    
    else if (argc == 3) // if 3 arguments provided, like so `mygrep needle haystack.txt` 
    {
        char *stringToSearch = argv[1];
        char *filename = argv[2];

        // cout << stringToSearch << endl;
        // cout << filename << endl;

        string line;
        ifstream myfile;
        myfile.open(filename); // open file
        if (myfile.is_open())
        {
            while (!myfile.eof()) // read until end of file
            {
                getline(myfile, line);
                const char* result = strstr(line.c_str(), stringToSearch); // search line
                if (result != nullptr) // if line contains searched string
                    cout << line << endl; // print it
            }
        }
        else
            cerr << "Error opening file " << filename << endl; // print error
    }

    else if (argc == 4)
    {
        string options_arg = argv[1]; // options -oxyz
        char* stringToSearch = argv[2]; // needle
        char* filename = argv[3]; // haystack.txt

        if (!((options_arg[0] == '-') and (options_arg[1] == 'o'))) // if optionsarg doesn't start with '-o' print error
        {
            cerr << "Illegal use of arguments!" << endl;
            return 1;
        }
        
        string options = options_arg.substr(2,string::npos); // remove first 2 characters from options argument

        // set option booleans
        bool printOccuranceCount = false;
        bool printLineNumbers = false;
        bool ExcludeSearchLines = false;
        bool IgnoreCase = false;
        const char* result = nullptr;
        
        if (stringContainsChar(options, "l"))
            printLineNumbers = true;

        if (stringContainsChar(options, "o"))
            printOccuranceCount = true;
        
        if (stringContainsChar(options, "r"))
            ExcludeSearchLines = true;   
        
        if (stringContainsChar(options, "i"))
            IgnoreCase = true;   

        // cout << "Debug<<\n";
        // cout << " printOccuranceCount " << printOccuranceCount << endl;
        // cout << " printLineNumbers " << printLineNumbers << endl;
        // cout << " ExcludeSearchLines " << ExcludeSearchLines << endl;
        // cout << " IgnoreCase " << IgnoreCase << endl;

        // char* stringToSearch = "following"; // debug
        // char* filename = "../teht-anto/man_grep_plain_ASCII.txt"; // debug

        int currentLine = 0;
        int countOccurrences = 0;

        string line;
        ifstream myfile;
        myfile.open(filename);
        if (myfile.is_open()) // run if file can be opened
        {
            while (!myfile.eof()) // read untill end of file
            {
                getline(myfile, line); // get line of file
                currentLine++;

                if (IgnoreCase == true)
                    result = strcasestr(line.c_str(), stringToSearch); // if IgnoreCase, run with caseinsensitive search
                else
                    result = strstr(line.c_str(), stringToSearch); // else run casesensitive search
            
                if (ExcludeSearchLines == true) // if ExcludeSearchLines true, print lines without search string
                {
                    if (result == nullptr)
                    {
                        countOccurrences++; // increment countOccurrences var
                        if (printLineNumbers) // print line numbers
                            cout << currentLine << ": ";
                        cout << line << endl;
                    }
                }
                else
                {
                    if (result != nullptr) // if ExcludeSearchLines false, print lines with search string
                    {
                        countOccurrences++; // increment countOccurrences var

                        if (printLineNumbers) // print line numbers
                            cout << currentLine << ": ";
                        cout << line << endl;
                    }
                }
            }
            if (printOccuranceCount) // print line occurance count if wanted 
            {
                cout << "\nOccurrences of lines ";
                if (ExcludeSearchLines) // handle different wording for ExcludeSearchLines
                    cout << "not ";
                cout << "containing \""<< stringToSearch << "\": " << countOccurrences << endl;
            }
        }
        else
            cerr << "Error opening file " << filename << endl; // can't open file, print error
    }
}

// Asks user for needle (string) in haystack (string) and does a search on them
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

    if (result != nullptr) // check for match, if found, print strings and index
    {
            int position = result-stringToSearchFrom; // calculate substring's index in bigstring
            cout << "\n" << '"' << stringToSearch << '"' << " found in \"" << stringToSearchFrom << '"' << " in position " << position << endl;
    }
    else // if no match, print NOT found
        cout << "\n" << '"' << stringToSearch << '"' << " NOT found in \"" << stringToSearchFrom << '"' << endl;
}

bool stringContainsChar(string str, string character){
    if (str.find(character) != string::npos)
        return true;
    else
        return false;
}

char* strcasestr(const char* bigStr, const char* searchStr)
{
    // Allocate space for copy buffers for parameters:
    char* big_p = new char[strlen(bigStr) + 1];
    char* search_p = new char[strlen(searchStr) + 1];

    char* point_p;
    int offset;

    // Copy:
    strcpy(big_p, bigStr);
    strcpy(search_p, searchStr);

    // Convert each letter in big_p to lowercase:
    int i = 0;
    while (*(big_p + i) != '\0')
    {
        *(big_p + i) = tolower(*(big_p + i));
        i++;
    }

    // Same to search_p:
    i = 0;
    while (*(search_p + i) != '\0')
    {
        *(search_p + i) = tolower(*(search_p + i));
        i++;
    }

    // strstr can do case sensitive substring search but now both strings are lowercase =>
    // it is enough in here:
    point_p = strstr(big_p, search_p);
    offset = point_p - big_p;   // take the offset from found address to string beginning:

    delete[] big_p;
    delete[] search_p;

    // Return the point in parameter string or nullptr:
    return point_p != nullptr ? ( char * )bigStr + offset : point_p;
}