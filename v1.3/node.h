#ifndef NODE_h
#define NODE_h

#include <list>
#include "token.h"

using std::list;
using std::string;

/* ====================================================================================================
Label nodes and list the words of each node. 
Mark children
==================================================================================================== */


struct NodeT
{
    int level;
    char label; 
    Token token;

    // children
    list<NodeT> c;  // store operators and identifiers, etc..
    
    NodeT(const NodeT &rhs)
    {
        // rhs token ID
        this->token.ID = rhs.token.ID;
        // rhs token char
        this->token.ch = rhs.token.ch;

        // rhs label
        this->label = rhs.label;

        // rhs level
        this->level = rhs.level;

        // rhs child
        this->c = rhs.c;
    }

    NodeT(char value)
    {
        this->label = value;
    }

    NodeT(Token tk)
    {
        token = tk;
    }




}; 

#endif