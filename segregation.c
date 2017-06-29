/*
Author: Tousif Chowdhury 
Segragation project
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include<getopt.h>
#include "display.h"


//method declaration
int makeBoard(int, char** );
int size, satisfaction;
//char board[][size];

//Make the struct for the move 

typedef struct unhappy { 
	int row; 
	int col; 
	char sign; 
	

}unhappy;

/*making the board
need to make sure to display the right things when you have less than 5, more 
than 39 and if you have no command line.
*/  

/*
Checks the neighbors of the board, and then checks if it is a plus or a minus.
*/


float getHappy(char board[][size], int row, int col){	
	//bool isHappy;	
	int happiness, totalNeighbors, numMinus, numPlus, hella; 
	char characters = board[row][col];
	hella = 0;


        //top
        if(board[row-1][col] == '+'){
                numPlus ++;
                totalNeighbors ++;
        }
        if(board[row-1][col] == '-'){
                numMinus ++;
                totalNeighbors ++;
        }

        //top left
        if(board[row-1][col-1] == '+'){
                numPlus ++;
                totalNeighbors ++;
        }
        if(board[row-1][col-1] == '-'){
                numMinus ++;
                totalNeighbors ++;
        }


        //top right
        if(board[row-1][col+1] == '+'){
                numPlus ++;
                totalNeighbors ++;
        }
        if(board[row-1][col+1] == '-'){
                numMinus ++;
                totalNeighbors ++;
        }

        //left
        if(board[row][col-1] == '+'){
                numPlus ++;
                totalNeighbors ++;
        }
        if(board[row][col-1] == '-'){
                numMinus ++;
                totalNeighbors ++;
        }



	
	//bottom right

        if(board[row+1][col+1] == '-'){
                numMinus ++;
                totalNeighbors ++;
        }


        if(board[row+1][col+1] == '+'){
                numPlus ++;
                totalNeighbors ++;
        }
	

	//bottom
	if(board[row+1][col] == '+'){
                numPlus ++;
                totalNeighbors ++;
        }
        if(board[row+1][col] == '-'){
                numMinus ++;
                totalNeighbors ++;
        }

//right
	if(board[row][col+1] == '+'){
		numPlus ++; 
		totalNeighbors ++;
	}

	if(board[row][col+1] == '-'){
               	numMinus ++;
                totalNeighbors ++;
        }

        //bottom left
        if(board[row-1][col-1] == '+'){
                numPlus ++;
                totalNeighbors ++;
        }
        if(board[row-1][col-1] == '-'){
                numMinus ++;
                totalNeighbors ++;
        }


//Adds up the total neighbors 
 
	if(totalNeighbors != 0){
		if(characters == '+'){
			float hella = numPlus/totalNeighbors;
		}
		if(characters == '-'){
			float hella = numMinus/totalNeighbors;
		}
	}
	return hella; 
}


        
  /*

Implements the move function to move the characters around 
  */


void move(char board[][size]){
	int row, col;
	int count =0;
	struct unhappy movelist[size * size];
	
        for(row = 0; row<size; row++){
                for(col = 0; col < size; col++){
			if(getHappy(board,row, col) < satisfaction){
				movelist[count].row = row; 
				movelist[count].col = col;
				movelist[count].sign = board[row][col];
				count ++;			
			} 
		}
	}
	int counter = 0;		
	while(counter < count){
                row = rand();
                row %= size;
                col = rand();
                col %= size;
                if(board[row][col] == '.'){
                        board[row][col] = movelist[counter].sign;
			board[movelist[counter].row][movelist[counter].col] = movelist[counter].sign;
			counter ++;
                }		

	}

}

//Makes the board 

int makeBoard (int argc, char* argv[]){

	int size, vacancy, proportion, row, col, iter;
	
	int opt;
        int tmpsize = 0;
        while ( (opt = getopt( argc, argv, "p:") ) != -1 ) {
        	switch ( opt ) {
			case 'p':
	    		tmpsize = (int)strtol( optarg, NULL, 10 );
            		break;
		}
	}
	iter = tmpsize;
	

	size = strtol(argv[2], NULL,10);
	satisfaction = strtol(argv[3], NULL,10)/100;
	vacancy = strtol(argv[4],NULL, 10);
	proportion = strtol(argv[5],NULL,10);
        

        int dimen = size*size; 

        int totalPeople = dimen - ((vacancy*dimen)/100);
        int richPeople = (totalPeople * proportion)/100;
        int poorPeople = totalPeople - richPeople;

/*	
	printf("\n");
	printf("This is the total people: %d",totalPeople);
 	printf("\n");
	printf("This is the vacany: %d",vacancy);
	printf("\n");
	printf("This is the proportion: %d",proportion);
	printf("\n"); 
	printf("This is the richPeople: %d", richPeople);
	printf("\n");
*/
	char board[size][size];	

    
	for(row = 0; row<size; row++){
		for(col = 0; col<size; col++){
			board[row][col] = '.';
		}
	}

	srand( 41 );
        int counter = 0; 
        while(counter<richPeople){
		row = rand();
		row %= size;
		col = rand();
		col %= size;
		if(board[row][col] != '+'){
			board[row][col] = '+'; 
			counter ++; 
		}                
        }

	
	counter = 0;
	while(counter<poorPeople){
                row = rand();
                row %= size;
                col = rand();
                col %= size;
                if(board[row][col] != '+' && board[row][col] != '-'){
                        board[row][col] = '-';
                        counter ++;
                }
        }


	int counts = 0;
	while(counts<= iter){
	
        //prints the board
	move(board);		
	for(row = 0; row<size; row++){
		for(col = 0; col < size; col++){
			printf("%c",board[row][col]);
		}
		puts(" ");
	}
	
	
	printf("cycles: %d",counts);
	printf("moves this cycle: ");
	printf("segregation measure: ");
	printf("size");
	
	counts ++;
	}

	return 0;
	
}


int main(int argc, char* argv[]){
	makeBoard(argc,argv);
	return 0; 

}





