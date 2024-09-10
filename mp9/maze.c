#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
// Netids: gas8 bmikos2
/* paragraph:
 * 
 * In createMaze, we first have to access the file through a FILE* ptr, which we named `real`. From this file ptr, we use both fscanf and fgets to recieve both the value of the maze's height, the value of the maze's width, and the maze's characters itself. 
 * We initalize a maze_t* struct named `peace`, which will be used as the game board. To load in the game board into `peace`, we use fgets for each line.
 * We also create an array named `a` that will hold the characters passed through fgets then transfer the characters stored in that array into our previoudly created peace->cells[i][j].
 * We then loop through all the cells in peaces->cells (the cells of the gameboard initially stored within the maze(x).txt files) and find the one holding the value of 'S', which we then store its position in peace->startRow and peace->startColumn.
 *
 *For printmaze(), all we do is cycle through all lines and print them.
 * 
 *For the final function, we use recursive backtracking which will go through all paths and replace them with asterisks once 'E' is found. The last iteration of this recursive function will replace the starting cell's position with the value 'S', as it will be replaced by other parts of the function.\
 * 
 * */


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
	FILE* real;					//pointer to file
        real = fopen(fileName, "r");		
	int w;						//initialize variables for width and height
	int h;	
	
	fscanf(real, "%d %d", &w, &h);			//reads file to get dimensions of maze
	maze_t* peace= (maze_t*)malloc(sizeof(maze_t));	//allocates memory for the maze
	peace->width = w;				//sets maze width and height to detected width and height
	peace->height = h;
	peace->cells = (char **)malloc((peace->height) * sizeof(char *));//allocates memory for number of rows
	for(int i = 0; i<peace->height; i++){
		peace->cells[i]  = (char*) malloc((peace->width) * sizeof(char));//allocates memory for # of cols
	}
	char a[peace->width+4];		 //creates new array to read each row of file without \n
	fgets(a,10,real);		 //gets the first row of real and stores it into array a
	for(int i = 0; i< peace->height; i++){//loop to read in maze to cells of maze without \n
			fgets(a,peace->width+4 ,real);
			for(int j = 0; j<peace->width; j++){
				peace->cells[i][j] = a[j];
			}
	}
  	fclose(real);//close file
	for(int i = 0; i< peace->height;i++){ //loop to find start row and column
		for(int j = 0; j< peace->width;j++){
			if(peace->cells[i][j] == 'S'){
				peace->startRow = i;
				peace->startColumn = j;
			}
			if(peace->cells[i][j] == 'E'){
				peace->endRow =i;
				peace->endColumn = j;
			}
		}
	}
	// Your code here. Make sure to replace following line with your own code.
    return peace;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here. 
    	for(int i = 0; i < maze->height; i++){//loop to free memory allocated for column length
		free(maze->cells[i]);
	}
    	free(maze->cells);//free to free memory allocated for row length
	free(maze);//free the memory allocted for the memory
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
	for(int i =0; i<maze->height; i++){ //loop to print out maze
			printf("%s", maze->cells[i]);
			printf("\n");
	}

}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
	if(col < 0 || row < 0 || col>=maze->width || row>=maze->height){ //checks to see if row+col is inbounds
		return 0;
	}
	if(maze->cells[row][col] == '~'|| maze->cells[row][col] == '%'||maze->cells[row][col] == '*'){//checks to see if space is empty
		return 0;
	}	
	if(maze->cells[row][col] == 'E'){//checks to see if end of maze is reached
		return 1;
	}
	maze->cells[row][col] = '*';//sets current cell to *
	if(solveMazeDFS(maze,col-1,row)){//check left move
		if(row == maze->startRow && col == maze->startColumn){maze->cells[row][col] = 'S';}//once reaching the start after backtracing, set the start point back to S
		return 1;		
	}
	if(solveMazeDFS(maze,col+1,row)){//check right move
		if(row == maze->startRow && col == maze->startColumn){maze->cells[row][col] = 'S';}
		return 1;
	}
	if(solveMazeDFS(maze,col,row-1)){//check up move
                if(row == maze->startRow && col == maze->startColumn){maze->cells[row][col] = 'S';}
		return 1;
	}
	if(solveMazeDFS(maze,col,row+1)){//check down move
                if(row == maze->startRow && col == maze->startColumn){maze->cells[row][col] = 'S';}
		return 1;
	}
	if(maze->cells[row][col] != 'S'){maze->cells[row][col] = '~';}//if not solution mark as visited

     return 0;
}
