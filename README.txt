Dean Nunis
2324351
Assignment 2 - Game of Life


Description:
The game will start with prompting user to choose the world either from a flat file (with the assumption of there are equal number of colomn in all the rows) or to generate a random world with 30% probability of having alive cells(rest all will be dead cells).

The game will also promts user to choose a boundary mode 
1. Classic Mode
All the cell beyond boundaries will be treated as dead cells
2. Doughnut mode
All the cell beyond boundaries will be wrapping around the other side of the boundary.

The game also asks user if he wants to pause between each generation. If not, the world will be printed infinitely untill the board becomes empty.

Once all the details from user been collected, based on his options, board will be generated and enters into a indefinite loop (until empty board).

For each iteration, generates the next generation of the board state.

The generation of next generation board wil be follows the steps below.
1. If the number of neighbour alive cells are either 1 or 4, resetting the cell to dead (due to less population or dense population respectively).
2. If the number of neighbour alive cells are exactly 3, then creates a new born child.
3. If the number of neighbour alive cells are exactly 2, leave the state as it is.

The number of neighbours wil be calculated based on the boundary mode. 

