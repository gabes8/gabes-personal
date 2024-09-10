#include "game.h"

//Group: gas8, arivana2
//
//this code makes a 2048 game that is interactive and can be played
//by the user using keys w,a,s,d from the keyboard to move tiles and
//combine them to acheive the highest score. This program is made using
//a game struct containing many attributes in the game and pointers
//to edit and identify those attributes in the game struct.

game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
	mygame->rows=rows;
	mygame->cols=cols;
	mygame->score = 0;
	for(int i=0;i<rows*cols;i++){
		mygame->cells[i] = -1;
	}

    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
	(*_cur_game_ptr)->rows=new_rows;
        (*_cur_game_ptr)->cols=new_cols;
        (*_cur_game_ptr)->score = 0;
        for(int i=0;i<new_rows*new_cols;i++){
                (*_cur_game_ptr)->cells[i] = -1;
        }


	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
	if(cur_game->cols<col || cur_game->rows<row || row<0 || col < 0){
		return NULL;
	}
	cell * curcell;
	curcell= &cur_game->cells[row*(cur_game->cols) + col];
	return curcell;
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
//moving code
int rownum = cur_game->rows;									//declare variables to help with shortening code
int colnum = cur_game->cols;
int valid = 0;											//validity of move variable

for(int i = 0; i<rownum;i++){ 									//loops through all elements in square
	for(int j = 0;j<colnum;j++){
		if(i-1>=0){									//checks to see if row 'above' is in bounds
			for(int m=i-1; m>=0; m--){						//loop to move every element up as far as they can go
				if(*get_cell(cur_game,m,j)==-1){				//checks to see if element 'above' is 'empty'
					if(*get_cell(cur_game,i,j)!=-1){			//checks to make sure element isn't 'empty' as well to check for validity
						valid=1;
					}
					*get_cell(cur_game,m,j) = *get_cell(cur_game,m+1,j);	//replaces value 'above' current value with the current value
					*get_cell(cur_game,m+1,j) = -1;				//empties current value spot
				}
			}
		}
	}
}

//merging code
for(int i= 0; i<rownum; i++){									//loops through all elements in square for merging
	for(int j = 0; j<colnum; j++){
			
			int above = i-1;							//sets above variable to value of row above
				if(above>=0 && *get_cell(cur_game,above,j) == *get_cell(cur_game,i,j) && *get_cell(cur_game,i,j)!=-1 ){ //checks to see if row above is in bounds,same value as current and that the currenrt value isn't 'empty'
					*get_cell(cur_game,above,j) *= 2; 			//multiplies value 'above' by 2 to signify addition
					cur_game->score += *get_cell(cur_game,above,j);		//increases score by new value after merging
					valid = 1;						//marks move as valid
					for(int move = i; move<rownum-1;move++){		//loop to move all elements up after merging
						*get_cell(cur_game,move,j) = *get_cell(cur_game,move+1,j);//sets current value to the value below it
					}
					*get_cell(cur_game,rownum-1,j) = -1;			//makes last row empty
				}
	}
}
    return valid;										//returns validity
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
int rownum = cur_game->rows;                                                                    //declare variables to help with shortening code
int colnum = cur_game->cols;
int valid = 0;                                                                                  //validity of move variable

for(int i = rownum-1; i>=0;i--){                                                                   //loops through all elements in square
        for(int j = colnum-1;j>=0;j--){
                if(i+1<rownum){                                                                     //checks to see if row 'below' is in bounds
                        for(int m=i+1; m<rownum; m++){                                              //loop to move every element down as far as they can go
                                if(*get_cell(cur_game,m,j)==-1){                                //checks to see if element 'below' is 'empty'
                                        if(*get_cell(cur_game,i,j)!=-1){                      //checks to make sure element isn't 'empty' as well to check for validity
                                                valid=1;
                                        }
                                        *get_cell(cur_game,m,j) = *get_cell(cur_game,m-1,j);    //replaces value 'below' with the current value
                                        *get_cell(cur_game,m-1,j) = -1;                         //empties current value spot
                                }
                        }
                }
        }
}

//merging code
for(int i= rownum-1; i>=0; i--){                                                                   //loops through all elements in square for merging
        for(int j = colnum-1; j>=0; j--){

                        int below = i+1;                                                        //sets below variable to value of row below
                                if(below<rownum && *get_cell(cur_game,below,j) == *get_cell(cur_game,i,j) && *get_cell(cur_game,i,j)!=-1 ){ //checks to see if row before is in bounds,same value as current and that the currenrt value isn't 'empty'
                                        *get_cell(cur_game,below,j) *= 2;                       //multiplies value 'below' by 2 to signify addition
                                        cur_game->score += *get_cell(cur_game,below,j);         //increases score by new value after merging
                                        valid = 1;                                              //marks move as valid
				       	for(int move = i; move>0;move--){                //loop to move all elements down after merging
                                                *get_cell(cur_game,move,j) = *get_cell(cur_game,move-1,j);//sets current value to the value above it
                                        }
                                        *get_cell(cur_game,0,j) = -1;                    //makes first row empty
                                }
        }
}
    return valid;                                                                               //returns validity

};

int move_d(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
int rownum = cur_game->rows;                                                                    //declare variables to help with shortening code
int colnum = cur_game->cols;
int valid = 0;                                                                                  //validity of move variable

for(int i = rownum-1; i>=0;i--){                                                                   //loops through all elements in square
        for(int j = colnum-1;j>=0;j--){
                if(j+1<colnum){                                                                     //checks to see if col 'above' is in bounds
                        for(int m=j+1; m<colnum; m++){                                              //loop to move every element right as far as they can go
                                if(*get_cell(cur_game,i,m)==-1){                                //checks to see if element 'above' is 'empty'
                                        if(*get_cell(cur_game,i,j)!=-1){                      //checks to make sure element above isn't 'empty' as well to check for validity
                                                valid=1;
                                        }
                                        *get_cell(cur_game,i,m) = *get_cell(cur_game,i,m-1);    //replaces value 'above' current value with the current value
                                        *get_cell(cur_game,i,m-1) = -1;                         //empties current value spot
                                }
                        }
                }
        }
}

//merging code
for(int i= rownum-1; i>=0; i--){                                                                   //loops through all elements in square for merging
        for(int j = colnum-1; j>=0; j--){

                        int below = j+1;                                                        //sets above variable to value of col above
                                if(below<colnum && *get_cell(cur_game,i,below) == *get_cell(cur_game,i,j) && *get_cell(cur_game,i,j)!=-1 ){ //checks to see if col above is in bounds,same value as before and that the currenrt value isn't 'empty'
                                        *get_cell(cur_game,i,below) *= 2;                       //multiplies value 'above' by 2 to signify addition
                                        cur_game->score += *get_cell(cur_game,i,below);         //increases score by new value after merging
                                        valid = 1;                                              //marks move as valid
                                        for(int move = j; move>0;move--){                //loop to move all elements right after merging
                                                *get_cell(cur_game,i,move) = *get_cell(cur_game,i,move-1);//sets current value to the value below it
                                        }
                                        *get_cell(cur_game,i,0) = -1;                    //makes first col empty
                                }
        }
}
    return valid;                                                                               //returns validity
};

int move_a(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
int rownum = cur_game->rows;                                                                    //declare variables to help with shortening code
int colnum = cur_game->cols;
int valid = 0;                                                                                  //validity of move variable

for(int i = 0; i<rownum;i++){                                                                   //loops through all elements in square
        for(int j = 0;j<colnum;j++){
                if(j-1>=0){                                                                     //checks to see if col 'below' is in bounds
                        for(int m=j-1; m>=0; m--){                                              //loop to move every element left as far as they can go
                                if(*get_cell(cur_game,i,m)==-1){                                //checks to see if element 'below' is 'empty'
                                        if(*get_cell(cur_game,i,j)!=-1){                      //checks to make sure element below isn't 'empty' as well to check for validity
                                                valid=1;
                                        }
                                        *get_cell(cur_game,i,m) = *get_cell(cur_game,i,m+1);    //replaces value 'below' current value with the current value
                                        *get_cell(cur_game,i,m+1) = -1;                         //empties current value spot
                                }
                        }
                }
        }
}

//merging code
for(int i= 0; i<rownum; i++){                                                                   //loops through all elements in square for merging
        for(int j = 0; j<colnum; j++){

                        int above = j-1;                                                        //sets above variable to value of col below
                                if(above>=0 && *get_cell(cur_game,i,above) == *get_cell(cur_game,i,j) && *get_cell(cur_game,i,j)!=-1 ){ //checks to see if col below is in bounds,same value as current and that the currenrt value isn't 'empty'
                                        *get_cell(cur_game,i,above) *= 2;                       //multiplies value 'below' by 2 to signify addition
                                        cur_game->score += *get_cell(cur_game,i,above);         //increases score by new value after merging
                                        valid = 1;                                              //marks move as valid
                                        for(int move = j; move<colnum-1;move++){                //loop to move all elements left after merging
                                                *get_cell(cur_game,i,move) = *get_cell(cur_game,i,move+1);//sets current value to the value below it
                                        }
                                        *get_cell(cur_game,i,colnum-1) = -1;                    //makes last col empty
                                }
        }
}
    return valid;                                                                               //returns validity
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    int rownum = cur_game->rows;
    int colnum = cur_game->cols;
    int newgame = 0;
    game * real = make_game(rownum,colnum);
    for(int i = 0; i<rownum;i++){
    	for( int j =0; j<colnum;j++){
		real->cells[real->cols*i + j] = cur_game->cells[real->cols*i + j];
	}
    }
    newgame = move_w(real) || move_s(real) || move_a(real) || move_d(real);
    destroy_game(real);
    return newgame;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
