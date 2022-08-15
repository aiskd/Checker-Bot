/* Program to assist in the challenge of solving sudoku puzzles. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* these #defines provided as part of the initial skeleton */

#define NDIM 3		/* sudoku dimension, size of each inner square */
#define NDIG (NDIM*NDIM)
			/* total number of values in each row */
#define NGRP 3		/* number of sets each cell is a member of */
#define NSET (NGRP*NDIG)
			/* total number of sets in the sudoku */
#define NCLL (NDIG*NDIG)
			/* total number of cells in the sudoku */

#define ERROR	(-1)	/* error return value from some functions */

/* these global constant arrays provided as part of the initial skeleton,
   you may use them in your code but must not alter them in any way,
   regard them as being completely fixed. They describe the relationships
   between the cells in the sudoku and provide a basis for all of the
   sudoku processing loops */

/* there are 27 different different sets of elements that need to be
   checked against each other, this array converts set numbers to cells,
   that's why its called s2c */
int s2c[NSET][NDIM*NDIM] = {
	/* the first group of nine sets describe the sudoku's rows */
	{  0,  1,  2,  3,  4,  5,  6,  7,  8 },
	{  9, 10, 11, 12, 13, 14, 15, 16, 17 },
	{ 18, 19, 20, 21, 22, 23, 24, 25, 26 },
	{ 27, 28, 29, 30, 31, 32, 33, 34, 35 },
	{ 36, 37, 38, 39, 40, 41, 42, 43, 44 },
	{ 45, 46, 47, 48, 49, 50, 51, 52, 53 },
	{ 54, 55, 56, 57, 58, 59, 60, 61, 62 },
	{ 63, 64, 65, 66, 67, 68, 69, 70, 71 },
	{ 72, 73, 74, 75, 76, 77, 78, 79, 80 },
	/* the second group of nine sets describes the sudoku's columns */
	{  0,  9, 18, 27, 36, 45, 54, 63, 72 },
	{  1, 10, 19, 28, 37, 46, 55, 64, 73 },
	{  2, 11, 20, 29, 38, 47, 56, 65, 74 },
	{  3, 12, 21, 30, 39, 48, 57, 66, 75 },
	{  4, 13, 22, 31, 40, 49, 58, 67, 76 },
	{  5, 14, 23, 32, 41, 50, 59, 68, 77 },
	{  6, 15, 24, 33, 42, 51, 60, 69, 78 },
	{  7, 16, 25, 34, 43, 52, 61, 70, 79 },
	{  8, 17, 26, 35, 44, 53, 62, 71, 80 },
	/* the last group of nine sets describes the inner squares */
	{  0,  1,  2,  9, 10, 11, 18, 19, 20 },
	{  3,  4,  5, 12, 13, 14, 21, 22, 23 },
	{  6,  7,  8, 15, 16, 17, 24, 25, 26 },
	{ 27, 28, 29, 36, 37, 38, 45, 46, 47 },
	{ 30, 31, 32, 39, 40, 41, 48, 49, 50 },
	{ 33, 34, 35, 42, 43, 44, 51, 52, 53 },
	{ 54, 55, 56, 63, 64, 65, 72, 73, 74 },
	{ 57, 58, 59, 66, 67, 68, 75, 76, 77 },
	{ 60, 61, 62, 69, 70, 71, 78, 79, 80 },
};


/* there are 81 cells in a dimension-3 sudoku, and each cell is a
   member of three sets, this array gets filled by the function 
   fill_c2s(), based on the defined contents of the array s2c[][] */
int c2s[NCLL][NGRP];

void
fill_c2s() {
	int s=0, d=0, c;
	for ( ; s<NSET; s++) {
		/* record the first set number each cell is part of */
		for (c=0; c<NDIM*NDIM; c++) {
			c2s[s2c[s][c]][d] = s;
		}
		if ((s+1)%(NGRP*NDIM) == 0) {
			d++;
		}
	}
#if 0
	/* this code available here if you want to see the array
	   cs2[][] that gets created, just change that 0 two lines back
	   to a 1 and recompile */
	for (c=0; c<NCLL; c++) {
		printf("cell %2d: sets ", c);
		for (s=0; s<NGRP; s++) {
			printf("%3d", c2s[c][s]);
		}
		printf("\n");
	}
	printf("\n");
#endif
	return;
}

/* find the row number a cell is in, counting from 1
*/
int
rownum(int c) {
	return 1 + (c/(NDIM*NDIM));
}

/* find the column number a cell is in, counting from 1
*/
int
colnum(int c) {
	return 1 + (c%(NDIM*NDIM));
}

/* find the minor square number a cell is in, counting from 1
*/
int
sqrnum(int c) {
	return 1 + 3*(c/NSET) + (c/NDIM)%NDIM;
}

/* If you wish to add further #defines, put them below this comment,
   then prototypes for the functions that you add

   The only thing you should alter above this line is to complete the
   Authorship Declaration 
*/


/****************************************************************/


/****************************************************************/

#define N3SQR 27   /* number of cells in 3 squares */
#define ROWSET 8   /* the last set number that is a row */
#define COLSET 17  /* the last set number that is a column */
#define STARTSET -1 /* a number that is not a set  */

void print_sudoku(int sdk_values[]);
void stage2(int sdk_values[]);
void stage3(int sdk_values[]);
int strategy_one(int CLL, int sdk_values[]);
void print_moves(int row, int col, int val);
void horizontal_line();
void vertical_line();
void tadaa();
void print_strategyone();
	
/* main program controls all the action
*/
int
main(int argc, char *argv[]) {
	int sdk_values[NCLL];
	fill_c2s();
	
	/* Firstly, the input values are stored in an array. */
	for (int i =0; i< NCLL; i++){
		scanf("%d",&sdk_values[i]);
	}
	
	printf("\n");
	print_sudoku(sdk_values);
	stage2(sdk_values);
	stage3(sdk_values);
	print_sudoku(sdk_values);
	
	return 0;
}

/****************************************************************/

/* (Stage 1) prints the sudoku in the appropriate format */
void
print_sudoku(int sdk_values[]){
	int unknowns = 0;
	
	/* This iterates all the cells in the sudoku array and prints the 
	   values based on their cell positions; the unknown values are also
	   counted */
	for (int i = 0; i < NCLL; i++){
		if (sdk_values[i] == 0){
			printf(".");
			unknowns += 1;
		} else {
			printf("%d", sdk_values[i]);
		}
		if (((i+1)%NDIM==0) && ((i+1)%NDIG != 0)){
			vertical_line();
		} else if ((i+1)%N3SQR==0 && (i+1) != NCLL){
			horizontal_line();
		} else if ((i+1)%NDIG==0){ 
			printf("\n");
		} else {
			printf(" ");
		}
	}
	
	printf("\n%2d cells are unknown\n", unknowns);
	printf("\n");
	/* "ta daa!!!" will be printed once there are no more unknown values */
	if (unknowns == 0){
		tadaa();
	}
}

/****************************************************************/

/* (Stage 2) Checks if there are any duplicates 
    in any row/column/square */
void 
stage2(int sdk_values[]){
	int different_set = 0, violation = 0, current_set = STARTSET, freq;
	
	for (int set=0; set < NSET; set++){
		
		/* Counts the cell value frequency */
		for (int k=1; k<=NDIG; k++){
			freq = 0;
			for (int c=0; c<NDIG; c++){
				if (k == sdk_values[s2c[set][c]]){
					freq += 1;
				}
			}
			/* If duplicate is found, it will print depending on their set*/
			if (freq > 1){
				/* Checks if set is different */
				if (set != current_set){
					different_set += 1;
				}
				if (set <= ROWSET){
					printf("set %2d (row %d): %d instances of %d\n", set, 
						    set + 1, freq, k);
				} else if ( set <= COLSET) {
					printf("set %2d (col %d): %d instances of %d\n", set, 
						    set - ROWSET, freq, k);
				} else {
					printf("set %2d (sqr %d): %d instances of %d\n", set, 
						    set - COLSET, freq, k);
				}
				current_set = set;
				violation += 1; 
			}
		}	
	}
	if (violation != 0){
		printf("\n%d different sets have violations\n", different_set);
		printf("%d violations in total\n", violation);
		exit(EXIT_FAILURE);
	}
}

/****************************************************************/

/*(Stage 3) Implements strategy one until strategy one can no longer
   be used. */
void
stage3(int sdk_values[]){
	int total_moves = 1, sdk_copy[NCLL];
	
	while (total_moves > 0){
		total_moves = 0;
		/* sudoku values are copied to another array so the main sudoku array
		   won't be altered until all the possible moves are listed */
		for (int i=0; i<NCLL; i++){
			sdk_copy[i] = sdk_values[i];
		}
		/* applies strategy one to all cells */
		for (int i = 0; i<NCLL; i++){
			if (sdk_copy[i] == 0){
				if (strategy_one(i, sdk_copy)){
					total_moves += 1;
				}
			}
		}
		/* if no moves are done, it will stop implementing strategy one */
		if (total_moves == 0){
			return;
		}
		/* prints moves */
		print_strategyone();
		for (int i = 0; i<NCLL; i++){
			if (sdk_copy[i] == 0){
				if (strategy_one(i, sdk_copy)){
					print_moves(rownum(i),colnum(i),strategy_one(i, sdk_copy));
					sdk_values[i] = strategy_one(i, sdk_values);
				}
			}
		}
		printf("\n");
	}
}

/****************************************************************/

/* Finds any number from 1-9 that have not been used 
   in the row/column/square of that cell(CLL) */
int
strategy_one(int CLL, int sdk_values[]){
	int available_freq=0,available_value;
	int available_num[NDIG] = {1,2,3,4,5,6,7,8,9};
	int sets, cell_pos;

	/* Iterates through the sets of that cell and crosses out every number
	   that appears */
	for (int j=0; j<NGRP; j++){
		for (int k=0; k<NDIG; k++){
			sets = c2s[CLL][j];
			cell_pos = s2c[sets][k];
			if (sdk_values[cell_pos] != 0){
				available_num[sdk_values[cell_pos]-1] = 0;
			}
		}
	}
	/* Counts how many numbers left that are available */
	for (int num =0; num<NDIG; num++){
		if (available_num[num] != 0){
			available_freq += 1;
			available_value = available_num[num];
		}
	}
	/* If only 1 number is available, that number will be returned,
	   so it can be inputted into the main sudoku array */
	if (available_freq == 1){
		return available_value;
	} else {
		return 0;
	}
}

/****************************************************************/

void
print_moves(int row, int col, int val){
	printf("row %d col %d must be %d\n",row,col,val);
}

void
horizontal_line(){
	printf("\n------+-------+------\n");
}

void
vertical_line(){
	printf(" | ");
}

void
tadaa(){
	printf("ta daa!!!\n");
}

void 
print_strategyone(){
	printf("strategy one\n");
}

/****************************************************************/
/*algorithms are fun*/
