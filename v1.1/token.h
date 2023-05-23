#ifndef TOKEN_h
#define TOKEN_h

#include <iostream>
#include <string>

using namespace std;

struct Token
{
    int ID;       // toke IDs
    string ch;    // characters 
    int line;     // linenumber
};

enum tokenId
{
    KEYWORD_TK = 1001,
    ID_TK = 1002,
    EOF_TK = 1003,
    NUMBER_Tk = 1004,
    OPERATOR_TK = 1005,
    CMT_TK = 1006
};

extern string tokenIdentifiers[]; // priting EOF



static std::string keyword[] = {
    "Again", "If", "Assign", "Move", "Show",
    "Flip", "Name", "Home", "Do", "Spot",
    "Place", "Here", "There"
};



static std::string operator1[] = {
    "&",
    "+", 
    "/", 
    "%", 
    ".", 
    "{", 
    "}", 
    "<",
    "-",
    "*"
};
static char c2 = '<';
static char c3 = '-';
static char com = '*';

#endif