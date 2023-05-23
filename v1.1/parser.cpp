#include <iostream>
#include <fstream>

#include "scanner.h"
#include "node.h"
#include "token.h"
#include "testTree.h"
#include "parser.h"

using namespace std;

int lineNumber = 0;
int levelNumber = 0;

string fileLine;

NodeT *root = nullptr;
NodeT *rootNode()
{
    return root;
}

/*
<S>      ->     Name Identifier Spot Identifier <R> <E>
<R>     ->     Place <A> <B> Home
<E>     ->     Show Identifier
<A>     ->    Name Identifier
<B>     ->    empty |  .   <C>. <B> | <D> <B>
<C>     ->    <F> | <G>
<D>     ->    <H> | <J> | <K> | <L>  | <E> | <F>
<F>     ->    {If   Identifier <T> <W> <D> } | { Do Again <D> <T> <W> }
<G>    ->     Here Number There
<T>    ->     <<  |  <-
<V>   ->     +|   %|   &
<H>   ->     /  <Z>
<J>   ->     Assign Identifier <D>
<K>   ->    Spot Number Show Number|  Move Identifer Show Identifier
<L>   ->    Flip Identifier
<W>   ->   Number<V>  Number  |   Number .
<Z>   ->     Identifier|  Number
*/

/* ====================================================================================================
* Function    :  S
* Definition  :  <S>      ->     Name Identifier Spot Identifier <R> <E>
==================================================================================================== */
NodeT *S(istream &in, Token &tk)
{
    // Create the node <R>
    NodeT *p = new NodeT('S');

    // check if token is name token
    p->level = levelNumber;
    if (tk.ch == "Name")
    {
        NodeT t(tk);
        
        // store in node
        p->c.push_back(t);
        tk = nextScan(in);

        // check for ID token
        if (tk.ID == 1002)
        {
            NodeT t(tk);

            // store in node
            p->c.push_back(t);
            tk = nextScan(in);

            // check if token is spot token
            if (tk.ch == "Spot")
            {
                NodeT t(tk);

                // store in node
                p->c.push_back(t);
                tk = nextScan(in);

                // check for ID token
                if (tk.ID == 1002)
                {
                    NodeT t(tk);

                    // store in node
                    p->c.push_back(t);
                    tk = nextScan(in);

                    NodeT *foo = R(in, tk);

                    // store in node
                    p->c.push_back(*foo);

                    foo = E(in, tk);
                    p->c.push_back(*foo);
                }
                else
                {
                    cout << "[ERROR] Unexpected token\n";
                    exit(-1);
                }
            }
            else
            {
                cout << "[ERROR] Unexpected token\n";
                exit(-1);
            }
        }
        else
        {
            cout << "[ERROR] Unexpected token\n";
            exit(-1);
        }
    }
    else
    {
        cout << "[ERROR] Unexpected token\n";
        exit(-1);
    }
    --levelNumber;
    return p;
}

/* ====================================================================================================
* Function    :  R
* Definition  :  <R>     ->     Place <A> <B> Home
==================================================================================================== */

NodeT *R(istream &in, Token &tk)
{
    // Create the node <R>
    NodeT *p = new NodeT('R');

    p->level = ++levelNumber;

    // check if token is place token
    if (tk.ch == "Place")
    {
        NodeT t(tk);

        // store in node
        p->c.push_back(t);
        tk = nextScan(in);

        NodeT *foo = A(in, tk);

        // store in node
        p->c.push_back(*foo);

        NodeT *foo1 = B(in, tk);


        // store in node
        p->c.push_back(*foo1);

        // check if token is home token
        if (tk.ch == "Home")
        {
            NodeT t(tk);

            // store in node
            p->c.push_back(t);
            tk = nextScan(in);
        }
    }
    else
    {
        cout << "[ERROR] Unexpected token\n";
        exit(-1);
    }
    --levelNumber;
    return p;
}

/* ====================================================================================================
* Function    :  E
* Definition  :  <E>     ->     Show Identifier
==================================================================================================== */
NodeT *E(istream &in, Token &tk)
{
    // Create the node <E>
    NodeT *p = new NodeT('E');

    p->level = ++levelNumber;

    // check if token is show token
    if (tk.ch == "Show")
    {
        NodeT t(tk);

        // store in node
        p->c.push_back(t);
        tk = nextScan(in);

        // check for ID token
        if (tk.ID == 1002)
        {
            NodeT t(tk);
            p->c.push_back(t);
            tk = nextScan(in);
        }
        else
        {
            cout << "[ERROR] Unexpected token\n";
            exit(-1);
        }
    }
    else
    {
        cout << "[ERROR] Unexpected token\n";
        exit(-1);
    }
    --levelNumber;
    return p;
}

/* ====================================================================================================
* Function    :  A
* Definition  :  <A>     ->    Name Identifier
==================================================================================================== */

NodeT *A(istream &in, Token &tk)
{
    // Create the node <A>
    NodeT *p = new NodeT('A');

    p->level = ++levelNumber;

    // check if token is name token
    if (tk.ch == "Name")
    {
        NodeT t(tk);


        // store in node
        p->c.push_back(t);
        tk = nextScan(in);

        // check for ID token
        if (tk.ID == 1002)
        {
            NodeT t(tk);

            // store in node
            p->c.push_back(t);
            tk = nextScan(in);
        }
        else
        {
            cout << "[ERROR] Unexpected token.\n";
            exit(-1);
        }
    }
    else
    {
        cout << "[ERROR] Unexpected token.\n";
        exit(-1);
    }
    --levelNumber;
    return p;
}

/* ====================================================================================================
* Function    :  B()
* Definition  :  <B>     ->    empty |  . <C>. <B> | <D> <B>
==================================================================================================== */
NodeT *B(istream &in, Token &tk)
{
    // Create the node <B>
    NodeT *p = new NodeT('B');

    p->level = ++levelNumber;

    // check for ID token
    if (tk.ch == ".")
    {
        NodeT t(tk);

        // store in node
        p->c.push_back(t);

        tk = nextScan(in);

        NodeT *foo = C(in, tk);

        // store in node
        p->c.push_back(*foo);

        // check for ID token
        if (tk.ch == ".")
        {
            NodeT t(tk);

            // store in node
            p->c.push_back(t);
            tk = nextScan(in);

            NodeT *foo = B(in, tk);

            // store in node
            p->c.push_back(*foo);
        }
        else
        {
            cout << "[ERROR] Unexpected token.\n";
            exit(-1);
        }
    }
    else if (tk.ch == "/") // check operator
    {

        NodeT *foo = D(in, tk);

        // store in node
        p->c.push_back(*foo);
    }
    else if (tk.ch == "Assign") // check if token is assign token
    {

        NodeT *foo = D(in, tk);

        // store in node
        p->c.push_back(*foo);
    }
    else if (tk.ch == "Spot" || tk.ch == "Move") // check if token is Spot or move token
    {

        NodeT *foo = D(in, tk);

        // store in node
        p->c.push_back(*foo);
    }
    else if (tk.ch == "Flip") // check if token is flip token
    {

        NodeT *foo = D(in, tk);

        // store in node
        p->c.push_back(*foo);
    }
    else if (tk.ch == "Show") // check if token is show token
    {

        NodeT *foo = D(in, tk);

        // store in node
        p->c.push_back(*foo);
    }
    else if (tk.ch == "{") // check operator
    {

        NodeT *foo = D(in, tk);

        // store in node
        p->c.push_back(*foo);
    }
    else
    {

        Token temporaryToken = tk;
        temporaryToken.ch = "Empty";
        NodeT t(temporaryToken);

        // store in node
        p->c.push_back(t);
    }
    --levelNumber;
    return p;
}

/* ====================================================================================================
* Function    :  C()
* Definition  :  <C>     ->    <F> | <G>
==================================================================================================== */

NodeT *C(istream &in, Token &tk)
{
    // Create the node <C>
    NodeT *p = new NodeT('C');

    p->level = ++levelNumber;

    if (tk.ch == "{") // check operator
    {

        NodeT *foo = F(in, tk);

        // store in node
        p->c.push_back(*foo);


    }
    // check if token is here token
    else if (tk.ch == "Here")
    {

        NodeT *foo = G(in, tk);

        // store in node
        p->c.push_back(*foo);


    }
    else
    {
        cout << "[ERROR] Unexpected token.\n";
        exit(-1);
    }
    --levelNumber;
    return p;
}

/* ====================================================================================================
* Function    :  D()
* Definition  :  <D>     ->    <H> | <J> | <K> | <L>  | <E> | <F>
==================================================================================================== */
NodeT *D(istream &in, Token &tk)
{
    // Create the node <D>
    NodeT *p = new NodeT('D');

    p->level = ++levelNumber;

    if (tk.ch == "/") // check operator
    {

        NodeT *foo = H(in, tk);

        // store in node
        p->c.push_back(*foo);


    }
    // check if token is assign token
    else if (tk.ch == "Assign")
    {

        NodeT *foo = J(in, tk);
        
        // store in node
        p->c.push_back(*foo);


    }
    // check if token is spor or move token
    else if (tk.ch == "Spot" || tk.ch == "Move")
    {

        NodeT *foo = K(in, tk);

        // store in node
        p->c.push_back(*foo);


    }
    // check if token is flip token
    else if (tk.ch == "Flip")
    {

        NodeT *foo = L(in, tk);
        // store in node
        p->c.push_back(*foo);


    }
    // check if token is show token
    else if (tk.ch == "Show")
    {

        NodeT *foo = E(in, tk);

        // store in node
        p->c.push_back(*foo);


    }
    else if (tk.ch == "{") // check operator
    {

        NodeT *foo = F(in, tk);

        // store in node
        p->c.push_back(*foo);


    }
    else
    {
        cout << "[ERROR] Unexpected token.\n";
        exit(-1);
    }
    --levelNumber;
    return p;
}

/* ====================================================================================================
* Function    :  F()
* Definition  :  <F>     ->    {If   Identifier <T> <W> <D> } | { Do Again <D> <T> <W> }  NOTE: NOT DONE
==================================================================================================== */
NodeT *F(istream &in, Token &tk)
{
    // Create the node <F>
    NodeT *p = new NodeT('F');

    p->level = ++levelNumber;

    if (tk.ch == "{") // check operator
    {
        NodeT t(tk);

        // store in node
        p->c.push_back(t);
        tk = nextScan(in);

        // check if token is show token
        if (tk.ch == "If")
        {
            NodeT t(tk);

            // store in node
            p->c.push_back(t);
            tk = nextScan(in);


            if (tk.ID == 1002) // check ID token
            {
                NodeT t(tk);
            
                // store in node
                p->c.push_back(t);
                tk = nextScan(in);

                NodeT *foo = T(in, tk);

                // store in node
                p->c.push_back(*foo);

                foo = W(in, tk);

                // store in node
                p->c.push_back(*foo);

                foo = D(in, tk);

                // store in node
                p->c.push_back(*foo);



                if (tk.ch == "}") // check operator
                {
                    NodeT t(tk);

                    // store in node
                    p->c.push_back(t);
                    tk = nextScan(in);

                }
                else
                {
                    cout << "[ERROR] Unexpected token.\n";
                    exit(-1);
                }
            }
            else
            {
                cout << "[ERROR] Unexpected token.\n";
                exit(-1);
            }
        }
        // check if token is do token
        else if (tk.ch == "Do")
        {
            NodeT t(tk);

            // store in node
            p->c.push_back(t);
            tk = nextScan(in);

            // check if token is again token
            if (tk.ch == "Again")
            {
                NodeT t(tk);
                
                // store in node
                p->c.push_back(t);
                tk = nextScan(in);

                NodeT *foo = D(in, tk);

                // store in node
                p->c.push_back(*foo);

                foo = T(in, tk);

                // store in node
                p->c.push_back(*foo);

                foo = W(in, tk);

                // store in node
                p->c.push_back(*foo);



                if (tk.ch == "}") // eheck operator
                {
                    NodeT t(tk);

                    // store in node
                    p->c.push_back(t);
                    tk = nextScan(in);

                }
                else
                {
                    cout << "[ERROR] Unexpected token.\n";
                    exit(-1);
                }
            }
            else
            {
                cout << "[ERROR] Unexpected token.\n";
                exit(-1);
            }
        }
    }
    else
    {
        cout << "[ERROR] Unexpected token.\n";
        exit(-1);
    }
    --levelNumber;
    return p;
}

/* ====================================================================================================
* Function    :  G()
* Definition  :  <G>    ->     Here Number There
==================================================================================================== */

NodeT *G(istream &in, Token &tk)
{
    // Create the node <G>
    NodeT *p = new NodeT('G');

    p->level = ++levelNumber;

    // check if token is here token
    if (tk.ch == "Here")
    {
        NodeT t(tk);

        // store in node
        p->c.push_back(t);
        tk = nextScan(in);


        if (tk.ID == 1004)
        {
            NodeT t(tk);

            // store in node
            p->c.push_back(t);
            tk = nextScan(in);

            // check if token is there token
            if (tk.ch == "There")
            {
                NodeT t(tk);

                // store in node
                p->c.push_back(t);
                tk = nextScan(in);

            }
            else
            {
                cout << "[ERROR] Unexpected token.\n";
                exit(-1);
            }
        }
        else
        {
            cout << "[ERROR] Unexpected token.\n";
            exit(-1);
        }
    }
    else
    {
        cout << "[ERROR] Unexpected token.\n";
        exit(-1);
    }
    --levelNumber;
    return p;
}

/* ====================================================================================================
* Function    :  T()
* Definition  :  <T>    ->     <<  |  <-
==================================================================================================== */
NodeT *T(istream &in, Token &tk)
{
    // Create the node <T>
    NodeT *p = new NodeT('T');

    p->level = ++levelNumber;

    if (tk.ch == "<<") // check operator
    {
        NodeT t(tk);

        // store in node
        p->c.push_back(t);
        tk = nextScan(in);

    }
    else if (tk.ch == "<-") // check operator
    {
        NodeT t(tk);
        // store in node
        p->c.push_back(t);
        tk = nextScan(in);

    }
    else
    {
        cout << "[ERROR] Unexpected token.\n";
        exit(-1);
    }
    --levelNumber;
    return p;
}

/* ====================================================================================================
* Function    :  V()
* Definition  :  <V>   ->     +|   %|   &
==================================================================================================== */
NodeT *V(istream &in, Token &tk)
{
    // Create the node <V>
    NodeT *p = new NodeT('V');

    p->level = ++levelNumber;

    if (tk.ch == "+") // check operator
    {
        NodeT t(tk);

        // store in node
        p->c.push_back(t);
        tk = nextScan(in);

    }
    else if (tk.ch == "%") // check operator
    {
        NodeT t(tk);

        // store in node
        p->c.push_back(t);
        tk = nextScan(in);

    }
    else if (tk.ch == "&") // check operator
    {
        NodeT t(tk);

        // store in node
        p->c.push_back(t);
        tk = nextScan(in);

    }
    else
    {
        cout << "[ERROR] Unexpected token.\n";
        exit(-1);
    }
    --levelNumber;
    return p;
}

/* ====================================================================================================
* Function    :  H()
* Definition  :  <H>   ->     /  <Z>
==================================================================================================== */
NodeT *H(istream &in, Token &tk)
{
    // Create the node <H>
    NodeT *p = new NodeT('H');

    p->level = ++levelNumber;

    if (tk.ch == "/") // check operator
    {
        NodeT t(tk);

        // store in node
        p->c.push_back(t);
        tk = nextScan(in);


        NodeT *foo = Z(in, tk);

        // store in node
        p->c.push_back(*foo);


    }
    else
    {
        cout << "[ERROR] Unexpected token.\n";
        exit(-1);
    }
    --levelNumber;
    return p;
}

/* ====================================================================================================
* Function    :  J
* Definition  :  <J>   ->     Assign Identifier <D>
==================================================================================================== */

NodeT *J(istream &in, Token &tk)
{
    // Create the node <J>
    NodeT *p = new NodeT('J');

    p->level = ++levelNumber;

    // check if token is assign token
    if (tk.ch == "Assign")
    {
        NodeT t(tk);

        // store in node
        p->c.push_back(t);
        tk = nextScan(in);

        if (tk.ID == 1002) // check ID token
        {
            NodeT t(tk);

            // store in node
            p->c.push_back(t);
            tk = nextScan(in);

            NodeT *foo = D(in, tk);

            // store in node
            p->c.push_back(*foo);

            tk = nextScan(in);

        }
        else
        {
            cout << "[ERROR] Unexpected token.\n";
            exit(-1);
        }
    }
    else
    {
        cout << "[ERROR] Unexpected token.\n";
        exit(-1);
    }
    --levelNumber;
    return p;
}

/* ====================================================================================================
* Function    :  K()
* Definition  :  <K>   ->    Spot Number Show Number|  Move Identifer Show Identifier
==================================================================================================== */
NodeT *K(istream &in, Token &tk)
{
    // Create the node <K>
    NodeT *p = new NodeT('K');

    p->level = ++levelNumber;

    // check if token is spot token
    if (tk.ch == "Spot")
    {
        NodeT t(tk);

        // store in node
        p->c.push_back(t);
        tk = nextScan(in);


        if (tk.ID == 1004) // check ID
        {
            NodeT t(tk);

            // store in node
            p->c.push_back(t);
            tk = nextScan(in);

            // check if token is show token
            if (tk.ch == "Show")
            {
                NodeT t(tk);

                // store in node
                p->c.push_back(t);
                tk = nextScan(in);


                if (tk.ID == 1004)
                {
                    NodeT t(tk);
                    // store in node
                    p->c.push_back(t);
                    tk = nextScan(in);

                }
                else
                {
                    cout << "[ERROR] Unexpected token.\n";
                    exit(-1);
                }
            }
            else
            {
                cout << "[ERROR] Unexpected token.\n";
                exit(-1);
            }
        }
    }
    // check if token is move token
    else if (tk.ch == "Move")
    {
        NodeT t(tk);

        // store in node
        p->c.push_back(t);
        tk = nextScan(in);


        if (tk.ID == 1002)
        {
            NodeT t(tk);


            // store in node
            p->c.push_back(t);
            tk = nextScan(in);

            // check if token is show token
            if (tk.ch == "Show")
            {
                NodeT t(tk);

                // store in node
                p->c.push_back(t);
                tk = nextScan(in);


                if (tk.ID == 1002) // heck ID token
                {
                    NodeT t(tk);

                    // store in node
                    p->c.push_back(t);
                    tk = nextScan(in);

                }
                else
                {
                    cout << "[ERROR] Unexpected token.\n";
                    exit(-1);
                }
            }
            else
            {
                cout << "[ERROR] Unexpected token.\n";
                exit(-1);
            }
        }
        else
        {
            cout << "[ERROR] Unexpected token.\n";
            exit(-1);
        }
    }
    else
    {
        cout << "[ERROR] Unexpected token.\n";
        exit(-1);
    }
    --levelNumber;
    return p;
}

/* ====================================================================================================
* Function    :  L
* Definition  :  <L>   ->    Flip Identifier
==================================================================================================== */
NodeT *L(istream &in, Token &tk)
{
    // Create the node <L>
    NodeT *p = new NodeT('L');

    p->level = ++levelNumber;

    // check if token is flip token
    if (tk.ch == "Flip")
    {
        NodeT t(tk);

        // store in node
        p->c.push_back(t);
        tk = nextScan(in);


        if (tk.ID == 1002) // check ID token 
        {
            NodeT t(tk);

            // store in node
            p->c.push_back(t);
            tk = nextScan(in);

        }
        else
        {
            cout << "[ERROR] Unexpected token.\n";
            exit(-1);
        }
    }
    else
    {
        cout << "[ERROR] Unexpected token\n";
        exit(-1);
    }
    --levelNumber;
    return p;
}

/* ====================================================================================================
* Function    :  W()
* Definition  : <W>   ->   Number<V>  Number  |   Number .
==================================================================================================== */
NodeT *W(istream &in, Token &tk)
{
    // Create the node <W>
    NodeT *p = new NodeT('W');

    p->level = ++levelNumber;

    if (tk.ID == 1004) // check ID token
    {
        NodeT t(tk);
        
        // store in node
        p->c.push_back(t);
        tk = nextScan(in);


        if (tk.ch == ".") // check operator
        {
            NodeT t(tk);

            // store in node
            p->c.push_back(t);
            tk = nextScan(in);

        } 
        // check operators
        else if (tk.ch == "+" || tk.ch == "%" || tk.ch == "&")
        {
            NodeT t(tk);

            // store in node
            p->c.push_back(t);
            tk = nextScan(in);

            NodeT *foo = V(in, tk);
            
            // store in node
            p->c.push_back(*foo);

            tk = nextScan(in);

            if (tk.ID == 1004) // check ID token
            {
                NodeT t(tk);

                // store in node
                p->c.push_back(t);
                tk = nextScan(in);

            }
            else
            {
                cout << "[ERROR] Unexpected token.\n";
                exit(-1);
            }
        }
        else
        {
            cout << "[ERROR] Unexpected token.\n";
            exit(-1);
        }
    }
    else
    {
        cout << "[ERROR] Unexpected token.\n";
        exit(-1);
    }
    --levelNumber;
    return p;
}

/* ====================================================================================================
* Function    :  Z()
* Definition  : <Z>   ->     Identifier|  Number
==================================================================================================== */
NodeT *Z(istream &in, Token &tk)
{
    // Create the node <Z>
    NodeT *p = new NodeT('Z');

    p->level = ++levelNumber;

    if (tk.ID == 1002) // check ID token
    {
        NodeT t(tk);

        // store in node
        p->c.push_back(t);
        tk = nextScan(in);

    }
    else if (tk.ID == 1004) // check ID token
    {
        NodeT t(tk);

        // store in node
        p->c.push_back(t);
        tk = nextScan(in);

    }
    else
    {
        cout << "[ERROR] Unexpected token.\n";
        exit(-1);
    }
    --levelNumber;
    return p;
}

/* ====================================================================================================
* Function    :  Parser()
* Definition  :  setupfile and check if contents in file
==================================================================================================== */
NodeT *Parser(istream &in)
{
    Token tk;

    if (in.eof())
    {
        cout << "[ERROR] File is empty\n";
        cout << "Terminating program...\n";
    }

    tk = nextScan(in);
    root = S(in, tk);

    return root;
}

/* ====================================================================================================
* Function    :  nextScan()
* Definition  :  determine whether input line or use the current input line and
                determine if end of file has been reached.
==================================================================================================== */

Token nextScan(istream &in)
{

    if (fileLine.length() == 0)
    {

        getline(in, fileLine);
        if (in.eof())
        {

        }
        lineNumber++;

    }
    return Scanner(fileLine, lineNumber);
}