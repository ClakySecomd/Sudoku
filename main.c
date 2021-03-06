#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef struct tbl{
    int el[9];
} field;
// sudoku puzzle contains
// 9 fields

field *sboard;
field *tmp;
// these are the main board
// and the variable used to
// copy values on the board

int BR;
// this will be use to see
// if the sudoku puzzle has
// an unique solution

void sprint(field *board)
{
    for(int i = 0;i < 9;i+=3)
    {
        for(int j = 0;j < 9;j+=3)
        {
            printf(" %d", board[i].el[j]);
            printf(" %d", board[i].el[j+1]);
            printf(" %d", board[i].el[j+2]);
  
            printf(" |");

            printf(" %d", board[i+1].el[j]);
            printf(" %d", board[i+1].el[j+1]);
            printf(" %d", board[i+1].el[j+2]);

            printf(" |");

            printf(" %d", board[i+2].el[j]);
            printf(" %d", board[i+2].el[j+1]);
            printf(" %d\n", board[i+2].el[j+2]);
        }

        if( i != 6 )
            printf("-----------------------\n");
    }
}
// this is used to print the
// values on the board

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

int doubleinfield(field *sudoku, int i)
{
    int br[10];

    for(int n = 0;n < 10;n++)
        br[n] = 0;
    
    for(int j = 0;j < 9;j++)
    {
        br[ abs(sudoku[i].el[j]) ]++;
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

    for(int c = 0;c < 3;c++)
    {
        for(int n = 0;n < 10;n++)
            a[n] = 0;

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
    int j, k;
    if( (i == 0) || (i == 3) || (i == 6) )
    {
        j = i + 1; k = i + 2;
    }

    else if( (i == 1) || (i == 4) || (i == 7) )
    {
        j = i - 1; k = i + 1;
    }

    else
    {
        j = i - 2; k = i - 1;
    }

    int a[10];


    for(int r = 0;r < 7;r+=3)
    {
        for(int n = 0;n < 10;n++)
            a[n] = 0;

        a[ abs(sudoku[i].el[r]) ]++;
        a[ abs(sudoku[i].el[r+1]) ]++;
        a[ abs(sudoku[i].el[r+2]) ]++;

        a[ abs(sudoku[j].el[r]) ]++;
        a[ abs(sudoku[j].el[r+1]) ]++;
        a[ abs(sudoku[j].el[r+2]) ]++;

        a[ abs(sudoku[k].el[r]) ]++;
        a[ abs(sudoku[k].el[r+1]) ]++;
        a[ abs(sudoku[k].el[r+2]) ]++;

        if( !counter(a, 1) )
            return 1;

    }

    return 0;
}

int interference(field *sudoku)
{
    for(int i = 0;i < 9;i++)
    {
        if( doubleinfield(sudoku, i) )
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

int countercompleteconfig(int a[])
{
    if(a[1] != 9 || a[2] != 9 || a[3] != 9 || a[4] != 9 || a[5] != 9
     || a[6] != 9 || a[7] != 9 || a[8] != 9 || a[9] != 9)
        return 0;

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
            br[ abs(sudoku[i].el[j]) ]++;
        
    }

    if( countercompleteconfig(br) )
        return 1;

    return 0;
}

void writeout(FILE *w)
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
            fprintf(w, " %d", abs( sboard[i].el[j]) );
            fprintf(w, " %d", abs( sboard[i].el[j+1]) );
            fprintf(w, " %d", abs( sboard[i].el[j+2]) );

            fprintf(w, " |");

            fprintf(w, " %d", abs( sboard[i+1].el[j]) );
            fprintf(w, " %d", abs( sboard[i+1].el[j+1]) );
            fprintf(w, " %d", abs( sboard[i+1].el[j+2]) );

            fprintf(w, " |");

            fprintf(w, " %d", abs( sboard[i+2].el[j]) );
            fprintf(w, " %d", abs( sboard[i+2].el[j+1]) );
            fprintf(w, " %d\n", abs( sboard[i+2].el[j+2]) );
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

int eos(int i, int lim)
{
    if( (lim == 1) || (lim == 2) )
        return (i == -1) || (i == 10);

    return i == -1;
}

void backtrack(field *sudoku, int lim)
{
    setconfig(sudoku);

    int i = 0, j = 0;
    BR = 0;

    while( (sudoku[i].el[j] < 0) && (i < 9) )
    {
        if(j == 8)
        {
            i++; j = 0;
        }
        else
            j++;
    }
    // preproccesing in case there are 
    // fixed numbers at the begining

    do
    {

        if( (i != 9) && stepup(sudoku, i, j) )
        {
            
            if( completeconfig(sudoku) )
            {
                BR++;
                
                if( BR == lim )
                    return;
                
            }

            if(j == 8)
            {
                i++; j = 0;
            }
            else
                j++;

            while( (sudoku[i].el[j] < 0) && (i < 9) )
            {
                if(j == 8)
                {
                    i++; j = 0;
                }
                else
                    j++;
            }
        }
        else
        {
            if(i == 9)
            {
                i = 8; j = 8;
            }

            stepback(sudoku, i, j);

            if(j == 0)
            {
                i--;
                j = 8;
            }

            else
                j--;

            while( (sudoku[i].el[j] < 0) && (i > -1) )
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
    } while ( !eos(i, lim) );
}

void copy()
{

    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 9;j++)
        {
            tmp[i].el[j] = sboard[i].el[j];
        }
    }

}

int isunique()
{
    copy();

    backtrack(tmp, 2);

    if(BR == 1)
        return 1;

    return 0;
}

int end(int in[])
{
    if( (in[0] == -1) && (in[1] == -1) && (in[2] == -1) )
        return 1;

    return 0;
}

void sread(field *sudoku, FILE *f)
{
    int i = 0, j = 0, br = 0;
    
    while(!feof(f))
    {
        if(br % 4 != 3){
            fscanf(f, "%d %d %d | %d %d %d | %d %d %d",
            &sboard[i].el[j], &sboard[i].el[j+1], &sboard[i].el[j+2],
            &sboard[i+1].el[j], &sboard[i+1].el[j+1], &sboard[i+1].el[j+2],
            &sboard[i+2].el[j], &sboard[i+2].el[j+1], &sboard[i+2].el[j+2]);

            j += 3;

            if( j == 9 )
            {
                i += 3;
                j = 0;
            }
        }
        else
            fscanf(f, "%*[^\n]\n");
    }
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

            sboard = malloc(9 * sizeof(field));
            tmp = malloc(9 * sizeof(field));

            sread(sboard, r);
            
            // solving sudoku with backtrack...
            
            backtrack(sboard, 1);
            
            writeout(w);
            printf("Found the solution successfully...\n");

            free(sboard);
            free(tmp);

            fclose(w);
            fclose(r);
        }
        // now the player can choose to play
        // the puzzle with this application
        // in that case on of the arguments
        // has to be a file to which we
        // can write the user's progress

        else if( (access(args[1], 0) == 0) ^ (access(args[2], 0) == 0) )
        {
            FILE *w;

            sboard = malloc(9 * sizeof(field));
            tmp = malloc(9 * sizeof(field));

            int bl;
            do{
                printf("Press 1 if you want grab the puzzle from the file\n");
                printf("Or press 2 to insert the values yourself...\n");
                scanf("%d", &bl);
                
            }while( (bl != 1) && (bl != 2) );
            bl--;
            
            if(bl)
            {
                printf("Enter the beginning configuration of the sudoku puzzle...\n");

                int tmp_value;
                for(int i = 0;i < 9;i++)
                {
                    for(int j = 0;j < 9;j++)
                    {
                        scanf("%d", &tmp_value);
                        
                        while( (tmp_value < 0) || (tmp_value > 9) )
                        {
                            printf("Inadequate value given... Try again...\n");
                            scanf("%d *[^\n]", &tmp_value);
                        }

                        sboard[i].el[j] = tmp_value;
                    }
                }
            }
            else{
                w = (access(args[1], 0) == 0)?fopen(args[1], "r"):fopen(args[2], "r");

                sread(sboard, w);

                fclose(w);
            }

            w = (access(args[1], 0) == 0)?fopen(args[1], "w"):fopen(args[2], "w");

            if(interference(sboard))
            {
                printf("This is not an adequate sudoku puzzle...\n");
            }
            else
            {
                printf("Now it's time to solve this puzzle. Good luck playerone...\n");
                printf("Enter numbers coresponding to first the field, the the element, then the value...\n");
                printf("To end this session type -1 -1 -1 . . .\n");

                int d[3];
                copy();

                do
                {
                    scanf("%d %d %d", &d[0], &d[1], &d[2]);
                    
                    if( (d[0] > -1) && (d[0] < 10) )
                    {
                        if( (d[1] > -1) && (d[1] < 10) )
                        {
                            if( (d[2] > -1) && (d[2] < 10) )
                            {
                                if(sboard[d[0]].el[d[1]] == 0){
                                    tmp[d[0]].el[d[1]] = d[2];

                                    if(interference(tmp)) {
                                        printf("Invalid move!\n");
                                        tmp[d[0]].el[d[1]] = 0;
                                    }
                                    else
                                        sboard[d[0]].el[d[1]] = d[2];
                                }
                                else
                                    printf("Invalid move!\n");
                            }
                        }
                    }
                    sprint(sboard);
                } while (!end(d));
                
                printf("Saving present progress...\n");

                writeout(w);
            }

            free(sboard);

            fclose(w);
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

        sboard = malloc(9 * sizeof(field));
        tmp = malloc(9 * sizeof(field));

        for(int i = 0;i < 9;i++)
        {
            for(int j = 0;j < 9;j++)
                sboard[i].el[j] = 0;
        }
    
        backtrack(sboard, lim);  

        // now we have a completed sudoku board
        // we need to remove some numbers from it

        int i = 0, j = 0;
        int p = 8, q = 8;
        int tmp1, tmp2;

        do
        {

            tmp1 = sboard[i].el[j];
            sboard[i].el[j] = 0;

            tmp2 = sboard[p].el[q];
            sboard[p].el[q] = 0;
            // we remove the mirrored pair

            if( !isunique() )
            { 
                sboard[i].el[j] = tmp1;
                sboard[p].el[q] = tmp2;
            }

            if(j == 8)
            {
                i++; j = 0;
            }
            else
                j++;

            if(q == 0)
            {
                p -= 3; q = 8;

                switch (p)
                {
                case -1:
                    p = 7;
                    break;

                case -2:
                    p = 6;
                    break;
                
                default:
                    break;
                }
            }
            else
            {
                q -= 3;

                switch (q)
                {
                case -1:
                    q = 7;
                    break;

                case -2:
                    q = 6;
                    break;
                
                default:
                    break;
                }                
            }

        } while ( i != 7 );

        writeout(w);
        printf("Created a puzzle successfully...\n");

        free(sboard);
        free(tmp);

        fclose(w);
    }
    else
    {
        // in this case we will print 
        // how can this application be called

        printf("GENERAL SYNTAX ERROR!   \n");
        printf("This application is called using the following template:\n");
        printf("./sudoku [player] [FILE] FILE\n");
        printf("String player is used to indicate that the user will be solving the puzzle\n");
        printf("Input file is optional, while the output file isn't...\n");
    }

    return 0;
}