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

int counter(int a[], int i){
    if(a[1] != i || a[2] != i || a[3] != i || a[4] != i || a[5] != i
     || a[6] != i || a[7] != i || a[8] != i || a[9] != i)
       return 0;

    return 1;
}

int doubleinfield(field x)
{
    int br[10];

    for(int i = 0;i < 10;i++)
        br[i] = 0;
    
    for(int j = 0;j < 9;j++)
    {
        br[ abs(x.el[j]) ]++;
    }

    if( counter(br, 1) )
        return 0;

    return 1;
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
    

    int a[10];

    for(int i = 0;i < 10;i++)
        a[i] = 0;

    for(int c = 0;c < 3;c++)
    {
        a[ abs(sudoku[i].el[c]) ]++;
        a[ abs(sudoku[i].el[c+3]) ]++;
        a[ abs(sudoku[i].el[c+6]) ]++;

        a[ abs(sudoku[j].el[c]) ]++;
        a[ abs(sudoku[j].el[c+3]) ]++;
        a[ abs(sudoku[j].el[c+6]) ]++;

        a[ abs(sudoku[k].el[c]) ]++;
        a[ abs(sudoku[k].el[c+3]) ]++;
        a[ abs(sudoku[k].el[c+6]) ]++;

        if( !counter(a, 1) )
            return 1;
    }

    return 0;
}

int doubleinrow(field *sudoku, int i)
{
    int j, k = i % 3;
    if( k == 0 )
    {
        j = i + 1; k = i + 2;
    }

    else if(k == 1)
    {
        j = i - 1; k = i + 1;
    }

    else
    {
        j = i - 2; k = i - 1;
    }

    int a[10];

    for(int i = 0;i < 10;i++)
        a[i] = 0;

    for(int c = 0;c < 7;c+=3)
    {
        a[ abs(sudoku[i].el[c]) ]++;
        a[ abs(sudoku[i].el[c+1]) ]++;
        a[ abs(sudoku[i].el[c+2]) ]++;

        a[ abs(sudoku[j].el[c]) ]++;
        a[ abs(sudoku[j].el[c+1]) ]++;
        a[ abs(sudoku[j].el[c+2]) ]++;

        a[ abs(sudoku[k].el[c]) ]++;
        a[ abs(sudoku[k].el[c+1]) ]++;
        a[ abs(sudoku[k].el[c+2]) ]++;

        if( !counter(a, 1) )
            return 1;
    }

    return 0;
}

int interference(field *sudoku)
{
    for(int i = 0;i < 9;i++)
    {
        if( doubleinfield(sudoku[i]) )
            return 1;
        
        if( (i == 5) || (i == 8) )
        {
            if( doubleincolumn(sudoku, i) )
                return 1;

            if( doubleinrow(sudoku, i) )
                return 1;
        }

    }

    return 0;
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
    } while( interference(sudoku) );
    
    // the goal here is to try all possibilities
    // by increasing the number on which we are
    // and then letting the program continue
    // with other numbers

    return 1;
}

int completeconfig(field *sudoku)
{
    int br[10];

    for(int i = 0;i < 10;i++)
        br[i] = 0;

    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 9;j++)
            br[ abs(sudoku[i].el[j])]++;
        
    }

    if( counter(br, 9) )
        return 1;

    return 0;
}

void writeout(field *sudoku, FILE *w)
{
    /*
    *  1 2 3 | 4 5 6 | 7 8 9
    *  1 2 3 | 4 5 6 | 7 8 9
    *  1 2 3 | 4 5 6 | 7 8 9
    *  ---------------------
    *  ... output like this ... 
    */
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
                fscanf(r, "%d", &sudoku[i].el[j]);
                fscanf(r, "%d", &sudoku[i].el[j+1]);
                fscanf(r, "%d", &sudoku[i].el[j+2]);

                fscanf(r, "%d", &sudoku[i+1].el[j]);
                fscanf(r, "%d", &sudoku[i+1].el[j+1]);
                fscanf(r, "%d", &sudoku[i+1].el[j+2]);

                fscanf(r, "%d", &sudoku[i+2].el[j]);
                fscanf(r, "%d", &sudoku[i+2].el[j+1]);
                fscanf(r, "%d", &sudoku[i+2].el[j+2]);

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
                    if( completeconfig(sudoku) )
                    {
                        writeout(sudoku, w);
                        break;
                    }

                    j++;
                    if(j == 9)
                    {
                        i++; j = 0;
                    }
                }
                else
                {
                    stepback(sudoku, i, j);

                    j--;
                    if(j < 0)
                    {
                        i--; j = 0;
                    }
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