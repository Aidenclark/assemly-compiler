#ifndef STATSEM_h
#define STATSEM_h

#include <fstream>

using std::ofstream;

// static semantics function
void staticSemantics(NodeT*);

// create the identifier
void createIdentifier(string);

// define the identfifier
void defineIdentifier(string);

// will print the symbol table
void symbolTable();

#endif