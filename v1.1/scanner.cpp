#include "scanner.h"
#include "token.h"

// for storing strings
string tokenIdentifiers[] = {"Keyword", "Identifier", "EOF", "Number", "Operator",
                            "Comment"};

//FSA declaration
const int Rows = 9;
const int Columns = 10;  

// Reworked FSA table from P1                                                                                                        
const int table[Rows][Columns] = {
                                    /*     0    1     2     3     4     5     6    7      8    9             */
                                    /*     a-z  A-Z   op[]   <     -    0-9    *    EOF    ws   ERR          */
                                    /*0*/ {1, 3, 4, 5, -1, 6, 7, 1003, 500, -1},                         /*S0*/       
                                    /*1*/ {2, 2, -1, -1, -1, 2, -1, -1, -1, -1},                         /*S1*/           
                                    /*2*/ {2, 2, 1002, 1002, 1002, 2, 1002, 1002, 1002, 1002},           /*S2*/          
                                    /*3*/ {3, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001},     /*S3*/           
                                    /*4*/ {1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005},  /*S4*/          
                                    /*5*/ {-1, -1, -1, 4, 4, -1, -1, -1, -1, -1},                        /*S5*/          
                                    /*6*/ {1004, 1004, 1004, 1004, 1004, 6, 1004, 1004, 1004, 1004},     /*S6*/          
                                    /*7*/ {7, 7, 7, 7, 7, 7, 8, -1, 7, -1},                              /*S7*/          
                                    /*8*/ {1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006}   /*S8*/
                                        }; 

/* ====================================================================================================
* Function    :  Scanner()
* Definition  :  pass line number and string
==================================================================================================== */
Token Scanner(string &fileString, int lineN)
{

    Token temporaryToken;

    temporaryToken = FSA(fileString, lineN);



    return temporaryToken;
}

char Look(string &str)
{

    char lookAhead = '\0';

    if (str.length() > 0)
    {
        lookAhead = str.at(0);

    }
    else
    {
        // do something here
    }

    return lookAhead;
}

/* ====================================================================================================
* Function    :  getCharacters()
* Definition  :  parse the string for nextChar
==================================================================================================== */
char getCharacters(string &str)
{

    char next = '\0';

    next = str.at(0);
    str.erase(0, 1);


    return next;
}

int getColumns(char currentChar)
{

    int colNum = 0;


    if (currentChar == ' ')
    {
        colNum = 8;
    }
    else if (isalpha(currentChar))
    {
        if (isupper(currentChar))
        {
            colNum = 1;
        }
        else
        {
            colNum = 0;
        }
    }
    else if (isdigit(currentChar))
    {
        colNum = 5;
    }
    else
    {
        for (int i = 0; i < 7; i++)
        {
            if (currentChar == operator1[i].at(0))
            {
                colNum = 2;
            }
        }
        if (colNum != 2)
        {
            if (currentChar == c2)
            {
                colNum = 3;
            }
            else if (currentChar == c3)
            {
                colNum = 4;
            }
            else if (currentChar == com)
            {
                colNum = 6;
            }
            else if (currentChar == '\0')
            {
                colNum = 7;
            }
            else
            {

                colNum = 9;
            }
        }
    }

    return colNum;
}

bool keywordCheck(string &str)
{
    int counter = 0;
    for (int i = 0; i < 14; i++)
    {
        if (str == keyword[i])
        {
            return true;
        }
        else
        {
            counter++;
        }
    }
    if (counter == 13)
    {
        return false;
    };
}

/* ====================================================================================================
* Function    :  FSA()
* Definition  :  asume the nextchar and use column index
==================================================================================================== */
Token FSA(string &fileString, int line)
{
    int state = 0; 
    int nextState;
    Token token;
    string s = "";
    char nextChar = '\0';
    int fsaCol = 0;

    token.line = line;

    while (fileString.length() > 0 && isspace(Look(fileString)))
    {
        char ws = '\0';
        ws = getCharacters(fileString);
    }
    if (fileString.length() == 0)
    {
        // end 
    }

    while (state != FINAL)
    {

        nextChar = Look(fileString);
        fsaCol = getColumns(nextChar);
        nextState = table[state][fsaCol];

        if (nextState < 0)
        {

            token.ID = nextState;
            token.ch = nextChar;
            return token;
        }
        else if (nextState >= 1000)
        { 
            if (nextState == KEYWORD_TK)
            { 
                
                int check = keywordCheck(s);
                if (check)
                {
                    
                    token.ID = nextState;
                    token.ch = s;
                    return token; 
                }
                else if (s == "Done")
                {
                    token.ID = 1007;
                    return token;
                }
                else
                {
                    
                    token.ID = -2;
                    token.ch = s;
                    return token;
                }
            }
            else if (nextState >= ID_TK && nextState <= CMT_TK)
            {
                token.ID = nextState;
                token.ch = s;

                return token;
            }
        }
        else if (nextState == 500)
        {
            fileString.erase(0);
            token.ID = 500;
            return token;
        }
        else
        { 
            state = nextState;
            char addChar = getCharacters(fileString);
            
            
            s = s + addChar;
            
            
        }
    }
    return token;
}