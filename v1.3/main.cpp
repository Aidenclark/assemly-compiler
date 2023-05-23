#include "parser.h"
#include "testTree.h"
#include "statSem.h"

using namespace std;

int main(int argc, char *argv[])
{

    // for files
    char *fileName;

    ifstream inputFile;

    // process command line arguments
    if (argc == 2)
    {
        fileName = argv[1];

        inputFile.open(fileName);

        Parser(inputFile);

        inputFile.close();
    }
    else if (argc > 2)
    {
        cout << "[ERROR] Too many arguements detected.\n";

        cout << "Invocation: ./statSem [filename]\n";
    }
    else
    { // read from keyboard
        cout << "Return 'Done' to finish checking tokens. \n";

        cout << "Reading from keyboard:\n";

        Parser(cin);
    }

    //testTree(rootNode());

    staticSemantics(rootNode()); // static semantics

    symbolTable(); // print the symbol table

    return 0;
}