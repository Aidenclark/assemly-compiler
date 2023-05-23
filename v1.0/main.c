#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node.h"
#include "buildtree.h"
#include "traversals.h"

// process command line arguments and make sure file
// is readable, error otherwise

// set up keyboard processing so that below the
// input method is not relevant

int main(int argc, char *argv[])
{

    // check number of arguments
    if (argc > 2)
    {
        printf("Too many arguments have been used");
    }

    /*
    Invocation: P0[filename]
    Filname can be optional, but if a filename is given then
    the program will read from the file
    */
    else if (argc < 2) // if there is two arguments then use the other as filename
    {
        int val; // values being read
        int i = 0;
        

        node_t *root = NULL; // define node in build tree
        FILE *fp; // file pointer
        

        int fileSize = 100; // set file size for characters

    

        // string replacement
        char levelorder_output[fileSize];
        char preorder_output[fileSize];
        char postorder_output[fileSize];

        char file_input[fileSize];
        char *filename = argv[1]; // take in file

        /*
        Program has to output three files named
        filename.levelorder, filename.preorder,
        and filename.postorder
        */
        char *file_rename1 = ".levelorder";
        char *file_rename2 = ".preorder";
        char *file_rename3 = ".postorder";

        char *file_rename4 = ".txt"; // data log

        // copy strings
        strcpy(levelorder_output, filename); // level order
        strcpy(preorder_output, filename);   // preorder
        strcpy(postorder_output, filename);  // postorder

        strcpy(file_input, filename); // data log

        // attach strings together
        strcat(levelorder_output, file_rename1); // level order
        strcat(preorder_output, file_rename2);   // preorder
        strcat(postorder_output, file_rename3);  // postorder

        strcat(file_input, file_rename4); // data log

        // FILE *fopen(const char* name,const char* mode);
        // read from FILE
        if ((fp = fopen(file_input, "r")) == NULL)
        {
            // print standard error
            fprintf(stderr,
                    "Error opening file.\n Fatal: Improper Usage\n Usage: P0 [filname]", file_input);
            return -1;
        }

        while (fscanf(fp, " %d ", &val) != EOF)
            root = insert(root, val, i);

        levelorder(root, levelorder_output);
        preorder(root, preorder_output);
        postorder(root, postorder_output);

        fclose(fp);
    }

    /*
    Invocation:
    Will read from the keyboard if no filename is given
    until simulated keyboard EOF (Ctrl + d)
    */
   
    else
    {

        int i = 0;
        int val; // values being read

        node_t *root = NULL; // define node in build tree


        printf("Input values to be read from the keyboard until simulated keyboard EOF (Ctrl + d)\n");

        while (scanf(" %d ", &val) != EOF)
            root = insert(root, val, i);

        levelorder(root, ".levelorder");
        preorder(root, ".preorder");
        postorder(root, ".postorder");
    }

    return 0;
}
