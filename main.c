#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

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
                sudoku[i].el[j] = -sudoku[i].el[j];
        }
    }
}

int counter(int a[], int i){
    if(a[1] > i || a[2] > i || a[3] > i || a[4] > i || a[5] > i
     || a[6] > i || a[7] > i || a[8] > i || a[9] > i)
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
        
        if( (i == 0) || (i == 4) || (i == 8) )
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

    for(int i = 0;i < 9;i+=3)
    {
        for(int j = 0;j < 9;j+=3)
        {
            fprintf(w, " %d", sudoku[i].el[j]);
            fprintf(w, " %d", sudoku[i].el[j+1]);
            fprintf(w, " %d", sudoku[i].el[j+2]);

            fprintf(w, " |");

            fprintf(w, " %d", sudoku[i+1].el[j]);
            fprintf(w, " %d", sudoku[i+1].el[j+1]);
            fprintf(w, " %d", sudoku[i+1].el[j+2]);

            fprintf(w, " |");

            fprintf(w, " %d", sudoku[i+2].el[j]);
            fprintf(w, " %d", sudoku[i+2].el[j+1]);
            fprintf(w, " %d\n", sudoku[i+2].el[j+2]);
        }

        if( i != 6 )
            fprintf(w, "-----------------------\n");
    }
}

void stepback(field *sudoku, int i, int j)
{
    if(sudoku[i].el[j] > 0)
        sudoku[i].el[j] = 0;
}

int eos(int i)
{
    return (i == -1) || (i == 10);
}

void backtrack(field *sudoku, int lim)
{
    setconfig(sudoku);

    int i = 0, j = 0, br = 0;
    do
    {
                
        if( stepup(sudoku, i, j) )
        {
            if( completeconfig(sudoku) )
            {
                br++;
                
                if( br == lim )
                    break;
            }

            j++;
            if(j == 9)
            {
                i++; j = 0;
            }

            while( sudoku[i].el[j] < 0 )
            {
                j++;

                if(j == 9)
                {
                    i++; j = 0;
                }
            }
        }
        else
        {
            stepback(sudoku, i, j);

            if(j == 0)
            {
                i--;
                j = 8;
            }

            else
                j--;

            while( sudoku[i].el[j] < 0)
            {
                if(j == 0)
                {
                    i--;
                    j = 8;
                }

                else
                    j--;
            }        
        }
    } while ( !eos(i) );
}

field *copy(field *sudoku)
{
    field *tmp = malloc(9 * sizeof(field));

    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 9;j++)
        {
            tmp[i].el[j] = sudoku[i].el[j];
        }
    }

    return tmp;
}

int isunique(field *sudoku)
{
    int br = 0;

    // now we need to count how
    // many solutions does this
    // sudoku puzzle have
    // if there is only one
    // it is unique

    field *testboard = copy(sudoku);

    backtrack(testboard, 2);

    if( interference(testboard) )
    {
        free(testboard);
        return 1;
    }

    free(testboard);
    return 0;
}

int main(int argc, char *args[])
{
    if( argc == 3 )
    {
        // in this case we have two file names
        // one file contains the puzzle
        // the other is uset to print the answer

        if( (access(args[1], 0) == 0) && (access(args[2], 0) == 0) )
        {
            FILE *r = fopen(args[1], "r");
            FILE *w = fopen(args[2], "w");

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
            
            backtrack(sudoku, 1);
            
            writeout(sudoku, w);
            printf("Found the solution successfully...\n");

            free(sudoku);

            fclose(w);
            fclose(r);
        }
    }
    else if( argc == 2 )
    {
        // in this case we have a one file
        // this file will be used to
        // print the puzzle the app created

        FILE *w = fopen(args[1], "w");

        srand(time(0));
        int lim = rand();

        field *sudoku = malloc(9 * sizeof(field));

        for(int i = 0;i < 9;i++)
        {
            for(int j = 0;j < 9;j++)
                sudoku[i].el[j] = 0;
        }

        backtrack(sudoku, lim);  

        // now we have a completed sudoku board
        // we need to remove some numbers from it

        int i, j;
        int tmp1, tmp2;

        do
        {
            i = rand() / 238609295;
            j = rand() / 238609295;

            tmp1 = sudoku[i].el[j];
            sudoku[i].el[j] = 0;

            tmp2 = sudoku[j].el[i];
            sudoku[j].el[i] = 0;
            // we remove the mirrored pair
        } while ( isunique(sudoku) );

        sudoku[i].el[j] = tmp1;
        sudoku[j].el[i] = tmp2;

        writeout(sudoku, w);
        printf("Created a puzzle successfully...\n");

        free(sudoku);

        fclose(w);
    }
    else
    {
        // in this case we will print 
        // how can this application be called

        printf("GENERAL SYNTAX ERROR!   \n");
        printf("This application is called using the following template:\n");
        printf("./sudoku [FILE] FILE\n");
        printf("Input file is optional, while the output file isn't...\n");
    }

    return 0;
}