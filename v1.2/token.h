#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <ctype.h>
#include <string>


struct alphatbet
{ // storing and looking up alphabet
    int key;
    int val;
};

/****************************************

Operators
&  +  /  %  .  {  }<<  <-

****************************************/

alphatbet operators[8] = { // look up characters
    {'&', 0},
    {'+', 1},
    {'/', 2},
    {'.', 3},
    {'{', 4},
    {'}', 5},
    {'<<', 6},
    {'<-', 7}};



typedef struct
{ // token id map
    int key;
    tokenID name;
} tokenMap;


/****************************************

Keywords
Again End Start Spot If Assign Move Show Flip Name Home
Do Spot Place Here There Integer

****************************************/

token keywords[15] = { // defines keywords
    {AGAINtk, "again", 0},
    {ENDtk, "end", 0},
    {STARTtk, "start", 0},
    {SPOTtk, "spot", 0},
    {MOVETK, "move", 0},
    {IFtk, "if", 0},
    {SHOWtk, "show", 0},
    {INTtk, "integer", 0},
    {DOTK, "do", 0},
    {FLIPtk, "flip", 0},
    {THEREtk, "there", 0},
    {NAMEtk, "name", 0},
    {PLACEtk, "place", 0},
    {ASSIGNtk, "assign", 0},
    {HOMEtk, "home", 0}};



tokenMap finalState[6] = { // final state tokens
    {-99, EOFtk},
    {1000, IDENTtk},
    {1001, NUMtk},
    {1002, OPtk},
    {1003, DELtk},
    {1004, RELtk}};




#endif