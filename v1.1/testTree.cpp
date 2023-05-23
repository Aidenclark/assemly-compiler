#include <iostream>
#include <stdlib.h>
#include <string>

#include "node.h"
#include "testTree.h"

using namespace std;

void testTree(NodeT *p)
{
    if (p == nullptr)
    {
        return;
    }
    else
    {

        int temporaryToken;

        temporaryToken = p->level + 1;

        cout << p->label << endl;

        for (NodeT s : p->c)
        {

            for (int i = 0; i < temporaryToken; i++)
            {
                cout << "  ";
            }
            if (s.c.size() == 0)
            {
                if (s.token.ID == 1002)
                {
                    cout << "Identifier " << s.token.ch << endl;
                }
                else if (s.token.ID == 1004)
                {
                    cout << "Number " << s.token.ch << endl;
                }
                else
                {
                    cout << s.token.ch << endl;
                }
            }
            else
            {
                testTree(&s);
            }
        }
    }
}