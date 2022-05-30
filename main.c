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
            if( sudoku[i].el[j] != 0 )
            {
                sudoku[i].el[j] = -sudoku[i].el[j];
            }
        }
    }
}

int doubleinfield(field x)
{
    int br[10];
    
    for(int j = 0;j < 9;j++)
    {
        br[ abs(x.el[j]) ]++;
    }

    // make this into a counter method
    // and always pass it an array of elements
    // which needs to be checked for duplicates

    if(br[1] != 1 || br[2] != 1 || br[3] != 1 || br[4] != 1|| br[5] != 1
     || br[6] != 1 || br[7] != 1 || br[8] != 1 || br[9] != 1)
       return 1;

    return 0;
}

int doubleincolumn(field *sudoku, int i)
{
    int j, k;
    if( i < 3 )
    {
        j = i + 3; k = i + 6;
    }

    else if( i < 6 )
    {
        j = i - 3; k = i + 3;
    }

    else
    {
        j = i - 6; k = i - 3;
    }
    

    // we need a counter method
}

int interference(field *sudoku)
{
    for(int i = 0;i < 9;i++)
    {
        if( doubleinfield(sudoku[i]) )
            return 0;
        

        if( doubleincolumn(sudoku, i) )
            return 0;

        if( doubleinrow(sudoku, i) )
            return 0;

    }

    return 1;
}

int stepup(field *sudoku, int i, int j)
{
    if( sudoku[i].el[j] == 10 )
        return 0;
    //this is the end

    do
    {
        if( sudoku[i].el[j] >= 0 )
            sudoku[i].el[j]++;
        

        if( sudoku[i].el[j] == 10 )
        return 0;
    } while(interference(sudoku) );
    
    // the goal here is to try all possibilities
    // by increasing the number on which we are
    // and then letting the program continue
    // with other numbers

    return 1;
}

int main(int argc, char *args[])
{
    if( argc == 2 )
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

                if( j == 9 )
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
                
                if( stepup(sudoku, i, j) )
                {
                    if( completeconfig(sudoku, i, j) )
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
    else if( argc == 1 )
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