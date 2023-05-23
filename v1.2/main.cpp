#include <iostream>
#include <fstream>
#include "testScanner.h"

using namespace std;

FILE *fp;

int main(int argc, char *argv[])
{

    string filename;

    if (argc == 2)
    {

        filename = argv[1];
        // filename.append(".lan");

        fp = fopen(filename.c_str(), "r");
    }
    else if (argc == 1)
    { // read from the keyboard if no file specified
        string userInput;
        ofstream temporaryFile;

        filename = "temporaryFile";
        temporaryFile.open(filename.c_str());

        cout << "no file has been provided. Please enter in words:\n";
        while (cin >> userInput)
        { // read userInput

            temporaryFile << userInput << "\n"; // add them to the file
        }
        temporaryFile.close();

        fp = fopen(filename.c_str(), "r");
    }
    else
    {

        cout << "Error: Invalid userInput\n";
        return 1;
    }

    testScanner(fp); // call testscanner

    return 0;
}