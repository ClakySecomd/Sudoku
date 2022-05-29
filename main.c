#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct tbl{
    int el[9];
} field;
// sudoku puzzle contains
// 9 fields


void setconfig(field *sudoku)
{
    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 9;j++){
            if(sudoku[i].el[j] != 0)
            {
                sudoku[i].el[j] = -sudoku[i].el[j];
            }
        }
    }
}

int stepup(field *sudoku, int i, int j)
{
    if(i == 9)
        return 1;
    //this is the end

    do
    {
        if( sudoku[i].el[j] >= 0 )
        {
            
        }
    } while (nointerference(sudoku));
    
}

int main(int argc, char *args[])
{
    if(argc == 2)
    {
        // in this case we have two file names
        // one file contains the puzzle
        // the other is uset to print the answer

        if( (access(args[0], 0) == 0) && (access(args[1], 0) == 0) )
        {
            FILE *r = fopen(args[0], "r");
            FILE *w = fopen(args[1], "w");

            field *sudoku = malloc(9 * sizeof(field));

            int i = 0, j = 0;
            while(!feof(r))
            {
                fscanf("%d", &sudoku[i].el[j]);
                fscanf("%d", &sudoku[i].el[j+1]);
                fscanf("%d", &sudoku[i].el[j+2]);

                fscanf("%d", &sudoku[i+1].el[j]);
                fscanf("%d", &sudoku[i+1].el[j+1]);
                fscanf("%d", &sudoku[i+1].el[j+2]);

                fscanf("%d", &sudoku[i+2].el[j]);
                fscanf("%d", &sudoku[i+2].el[j+1]);
                fscanf("%d", &sudoku[i+2].el[j+2]);

                j += 3;

                if(j == 9)
                {
                    i += 1;
                    j = 0;
                }
            }
            
            // after this segment we know
            // we are done with input

            // solving sudoku with backtrack...
            setconfig(sudoku);

            i = 0;  j = 0;
            do
            {
                int test = stepup(sudoku, i, j);
                if(test)
                {
                    if(completeconfig(sudoku, i, j))
                    {
                        process(sudoku, w);
                        break;
                    }
                }
                else
                {
                    stepback(sudoku, i, j);
                }
            } while (eos(sudoku));
            
        }
    }
    else if(argc == 1)
    {
        // in this case we have a one file
        // this file will be used to
        // print the puzzle the app created

        // creating puzzle algo...
    }
    else
    {
        // in this case we will print 
        // how can this application be called
    }

    return 0;
}