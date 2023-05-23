#ifndef SCANNER_h
#define SCANNER_h

#include <iostream>
#include <stdlib.h>
#include <string>
#include <cctype>
#include "token.h"

using namespace std;

#define ERR -1
#define INITIAL 0
#define FINAL 1000

Token Scanner(string&, int);
Token FSA(string&, int);


char Look(string&);
char getCharacters(string&);

int getColumns(char);

bool keywordCheck(string&);


#endif