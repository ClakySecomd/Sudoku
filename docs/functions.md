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

**8.** The method *sprint* is used to print the current configuration on the sudoku board to the console

**9.** The method *countercompleteconfig* is a counter method which checks if all non-zero numbers appear on the board 9 times each

**10.** The method *eos* stands for End Of Search, and it stops backtrack from accessing unallocated space
- The reason why we don't stop the search when lim isn't 1 or 2 is because we don't want to stop the search before it tries all the possibilities, when it does it will fall back all the way to i = -1

**11.** The method *backtrack* has the goal of finding the lim-th solution of the given puzzle

**12.** The method *copy* copies the values from the board to the temporary variable

**13.** The method *isunique* checks if the current setting on the board has only 1 solution, since backtrack changes the values on the board it passes a dummy copy

**14.** The method *end* checks if the user has requested to end the player mode session