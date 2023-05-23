#include "testScanner.h"


using namespace std;

// looking up the tokens
string name[] = {"Identifier", "Number", "Again keyword", "End keyword", "Start keyword", "Spot keyword",
                       "Move keyword", "If keyword", "Show keyword", "Integer keyword", "Do keyword", "Flip keyword",
                       "There keyword", "Name keyword", "Place keyword", "Assign keyword", "Home keyword",
                       "Relational Operator", "Other Operator", "Delimeter", "End of File", "Error"};


void print(token t) { //print the tokens
        cout << "Line number -->  " << t.lineNumber << " Token ID --> " << name[t.ID] << " Token -->  " << t.name << "\n";
}

void testScanner(FILE *fp) {
    int lookahead;

    int lineNumber = 1;


    while((lookahead = fgetc(fp)) != EOF) {
        ungetc(lookahead, fp);

        token t = scanner(fp, lineNumber);



        if(t.ID != ERRtk) {
            print(t);

        } else {
            print(t);
            return;
        }

    }

    fclose(fp);
}

