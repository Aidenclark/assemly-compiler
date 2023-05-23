#include <iostream>
#include <stdlib.h>
#include <string>
#include <iterator>
#include <list>
#include "node.h"
#include "statSem.h"

using namespace std;

list<string> table; // symbol table

string identifier2; // will represent the second indentifier

string identifier1; // will represent the current indentifier


/* ====================================================================================================
Called after parser and reciving tree. If an error occurs then the type of error will be printed. 
Outputs the symbol table. 
==================================================================================================== */


/* ====================================================================================================
Iterator: https://www.cplusplus.com/reference/iterator/iterator/
==================================================================================================== */

void createIdentifier(string identifier)
{
    if (table.size() == 0)
    {
        table.push_back(identifier);

        // replace the previous identifier with the current identifier
        identifier2 = identifier;
    }
    else
    {


        for (list<string>::iterator i = std::begin(table); i != std::end(table); ++i)
        {

            if (identifier == (*i))
            {
                cout << "[ERROR] " << identifier << " identifier has already been defined.\n"

                "Terminating the program...\n";
                exit(-1);
            }
            else
            {
                // garbadge
                ;
            }
        }

        table.push_back(identifier);

        // replace the previous identifier with the current identifier
        identifier2 = identifier;
    }
}


void defineIdentifier(string identifier)
{
    int flag = 0;

    for (list<string>::iterator i = std::begin(table); i != std::end(table); ++i)
    {
        if (identifier == (*i))
        {
            flag = 1;
            break;
        }
        else
        {
            // garbadge
            ;
        }
    }
    if (flag == 0)
    {
        cout << "[ERROR] " << identifier << " identifier not defined before its usage.\n"
        
        "Terminating the program...\n";
        exit(-1);
    }
}


void staticSemantics(NodeT *p)
{
    if (p == nullptr)
    {
        return;
    }
    else
    {

        string entry;
        for (list<NodeT>::iterator i = std::begin(p->c); i != std::end(p->c); ++i)
        {


            entry = (*i).token.ch;

            if (entry == "Name")
            { // name identifier
                ++i;

                identifier1 = (*i).token.ch;

                // create identifier with the current identifier
                createIdentifier(identifier1);
            }
            else if (entry == "Spot")
            { // spot identifier
                ++i;

                identifier1 = (*i).token.ch;

                if ((*i).token.ID == 1002)
                {
                    // create identifier with the current identifier
                    createIdentifier(identifier1);
                }
                else
                {
                    // garbadge
                }
            }
            else if (entry == "Show")
            { // show identifier
                ++i;

                identifier1 = (*i).token.ch;

                if ((*i).token.ID == 1002)
                {

                    // replace the previous identifier with the current identifier
                    defineIdentifier(identifier1);
                }
                else
                {
                    // garbadge
                    ;
                }
            }
            else if (entry == "If")
            { // if identifier
                ++i;
                identifier1 = (*i).token.ch;

                // replace the previous identifier with the current identifier
                defineIdentifier(identifier1);
            }
            else if (entry == "Assign")
            { // assign identifier
                ++i;

                identifier1 = (*i).token.ch;

                // replace the previous identifier with the current identifier
                defineIdentifier(identifier1);
            }
            else if (entry == "Move")
            { // move identifier
                ++i;

                identifier1 = (*i).token.ch;

                // replace the previous identifier with the current identifier
                defineIdentifier(identifier1);
            }
            else if (entry == "Flip")
            { // flip identifier
                ++i;

                identifier1 = (*i).token.ch;

                // replace the previous identifier with the current identifier
                defineIdentifier(identifier1);
            }
            else if (entry == "/")
            { // / operator
                ++i;

                identifier1 = (*i).token.ch;

                if ((*i).token.ID == 1002)
                {
                    
                    // replace the previous identifier with the current identifier
                    defineIdentifier(identifier1);
                }
                else
                {
                    // garbadge
                    ;
                }
            }
            else
            {
                // dereference i
                staticSemantics(&(*i));
            }
        }
    }
}


// print the symbol table
void symbolTable()
{
    cout << "\nSYMBOL TABLE";
    cout << "\n============\n";
    for (list<string>::iterator i = std::begin(table); i != std::end(table); ++i)
    {
        cout << (*i) << endl;
    }
    cout << endl;
}