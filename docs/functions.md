# Functions - deep dive

In this file, I will explain the goal of each method and how did I aproach every problem

On one note, this solution treats the sudoku board as 9 fields, with each one having 9 elements, that is the meaning of the firstly declared structure

## Solver

The solving algorithm is based on a backtrack, that is why we set the first configuration, try to advance and then proceed depending on the outcome

**1.** The method *setconfig* changes all the already present numbers to negative, so that the algorithm doesn't mess with them

**2.** The method *stepup* increments the number on which we stand by 1 if it can be done, otherwise it return information that it failed

**3.** The method *interference* checks if the numbers on the sudoku board are distributed according to the rules of sudoku, that means no duplicates in a row (method *doubleinrow*) no duplicates in a column (method *doubleincolumn*) and no duplicates in one field (method *doubleinfield*)

**4.** The method *counter* makes sure we don't overuse one of the numbers

**5.** The method *completeconfig* checks if we have solved the sudoku puzzle by counting all the numbers, if every number appears 9 times we are victorious

**6.** The method *writeout* writes the solved sudoku puzzle to the passed file

**7.** The method *stepback* sets the number on which we stand to 0, and the returns one step back, so that the algorithm tries a different path this time (this is because *stepup* will immediately increase the number on which it stands by one)