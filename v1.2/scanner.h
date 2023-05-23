#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include <ctype.h>
#include <string>

using namespace std;

// enumerate tokens
enum tokenID {IDENTtk, NUMtk, AGAINtk, ENDtk, STARTtk, SPOTtk, MOVETK, IFtk, SHOWtk, INTtk, DOTK, FLIPtk,
    THEREtk, NAMEtk, PLACEtk, ASSIGNtk, HOMEtk, RELtk, OPtk, DELtk, EOFtk, ERRtk};


struct token { // token structure
    tokenID ID;
    string name;
    int lineNumber;
};

token scanner(FILE *fp, int &lineNumber);

#endif