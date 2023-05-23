#ifndef PARSER_h
#define PARSER_h

#include <iostream>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <type_traits>

#include "node.h"
#include "token.h"


using namespace std;

/* ====================================================================================================
* Parser Functions
==================================================================================================== */
NodeT *rootNode();

NodeT *Parser(istream&); 

Token nextScan(istream&);


//BNF of the program

// <S>      ->     Name Identifier Spot Identifier <R> <E> 
NodeT* S(istream&, Token&);

// <R>     ->     Place <A> <B> Home
NodeT* R(istream&, Token&);

// <E>     ->     ShowIdentifier
NodeT* E(istream&, Token&);

// <A>     ->    NameIdentifier
NodeT* A(istream&, Token&);

// <B>     ->    empty |  .   <C>. <B> | <D> <B>
NodeT* B(istream&, Token&);

// <C>     ->    <F> | <G>
NodeT* C(istream&, Token&);

// <D>     ->    <H> | <J> | <K> | <L>  | <E> | <F>
NodeT* D(istream&, Token&);

// <F>     ->    {If   Identifier <T> <W> <D> } | { Do Again <D> <T> <W> }
NodeT* F(istream&, Token&);

// <G>    ->     Here Number There 
NodeT* G(istream&, Token&);

// <T>    ->     <<  |  <-
NodeT* T(istream&, Token&);

// <V>   ->     +|   %|   &
NodeT* V(istream&, Token&);

// <H>   ->     /  <Z>
NodeT* H(istream&, Token&);

// <J>   ->     Assign Identifier <D>
NodeT* J(istream&, Token&);

// <K>   ->    Spot Number Show Number|  Move Identifer Show Identifier
NodeT* K(istream&, Token&);

// <L>   ->    Flip Identifier
NodeT* L(istream&, Token&);

// <W>   ->   Number<V>  Number  |   Number .  
NodeT* W(istream&, Token&);

// <Z>   ->     Identifier|  Number
NodeT* Z(istream&, Token&);

# endif