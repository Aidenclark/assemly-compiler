#include <iostream>
#include "scanner.h"
#include "token.h"

/****************************************

Scanner should scan in file characters
and output one token

****************************************/




int stateTable[10][24] = { // state table
    {5, 6, 6, 7, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 2, 0, -99},
    {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1, 1000, 1000, 0},
    {1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 2, 1001, 0},
    {1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 0},
    {1003, 1003, 1003, 1003, 1003, 1003, 1003, 1003, 1003, 1003, 1003, 1003, 1003, 1003, 1003, 1003, 1003, 1003, 1003, 1003, 1003, 1003, 0},
    {9, 9, 9, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 0},
    {1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 0},
    {8, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2},
    {1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 0},
    {1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 0}};


token tokenSearch(int val, string words)
{ // look up tokens (state and instance)
    token t;

    for (int i = 0; i < 6; i++)
    {
        if (val == 1)
        {
            for (int j = 0; j < 15; j++)
            {
                if (keywords[j].name == words)
                {
                    t.ID = keywords[j].ID;
                    t.name = words;
                    t.lineNumber = 7;
                }
            }
        }

        if (finalState[i].key == val)
        {
            t.ID = finalState[i].name;
            t.name = words;
            t.lineNumber = 6;
        }
    }

    return t;
}





int search(char lookahead)
{ // looks up column on table
    for (int i = 0; i < 19; i++)
    {

        if (operators[i].key == lookahead)
        {
            return operators[i].val;
        }
    }

    if (isalpha(lookahead))
    {
        return 19;
    }
    else if (isdigit(lookahead))
    {
        return 20;
    }
    else if (isspace(lookahead))
    {
        return 21;
    }
    else if (lookahead == EOF)
    {
        return 22;
    }
    else
    {
        return 23;
    }
}





// method for scanning
token scanner(FILE *fp, int &lineNumber)
{ // returns one token at a time
    string wordString;
    
    token t;
    
    int lookahead, columnState;

    int state1 = 0; // will represent the current state
    int state2 = 0; // will represent the next state

    
    while (state1 < 1000 && state1 >= 0)
    { // check if the process is at the final state
        lookahead = fgetc(fp);

        if (lookahead == '*')
        { // check for comments

            cout << "Comment Detected\n";
            while (lookahead != '\n')
            {
                lookahead = fgetc(fp);
            }

            lineNumber++;
        }


        // move to the next state
        columnState = search(lookahead);
        state2 = stateTable[state1][columnState];


        if (state2 >= 1000 || state2 == -99)
        { // cehck for final state or end of file

            if (lookahead == '\n')
            {
                lineNumber++;
            }


            if (state2 == -99)
            { //EOF

                ungetc(lookahead, fp);
                t.ID = EOFtk;
                t.lineNumber = lineNumber;
                t.name = "EOF";

                return t;
                
            }
            else if (state2 >= 1000)
            { // final state

                t = tokenSearch(state2, wordString);
                t.lineNumber = lineNumber;
                ungetc(lookahead, fp);

                return t;

            }

            else
            { // error
                cout << "Erroron on line: " << lineNumber << " (value): " << static_cast<char>(lookahead) << "\n";
                t.ID = ERRtk;
                t.lineNumber = lineNumber;
                t.name = "Error";

                return t;
            }
        }
        else
        { // keep reading characters
            char val = static_cast<char>(lookahead);

            if (!isspace(val))
            {
                wordString += val;
            }

            
            state1 = state2;
        }
    }

    t.ID = ERRtk;

    t.lineNumber = lineNumber;

    t.name = "Scanner didn't do anything";

    return t;
}

