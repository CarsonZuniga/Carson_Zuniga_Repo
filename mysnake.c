#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>

void startgame(const int x_dim, const int y_dim, const int head[2], const int food[2], int board[][x_dim]);
void init_game(const int x_dim, const int head[2], int board[][x_dim], int next_board[][x_dim]);
void print_board(const int x_dim, const int y_dim, int board[][x_dim]);
void copy_2D_array(const int x_dim, const int y_dim, int new_array[][x_dim], int old_array[][x_dim]);

int main(){
	int x_table_dimension, y_table_dimension;
	printf("Enter dimensions for Snake game (min 10, max 200): ");
	scanf("%d %d", &x_table_dimension, &y_table_dimension);

	if((x_table_dimension < 0 || x_table_dimension > 200) || (y_table_dimension < 0 || y_table_dimension > 200)){
		printf("Invalid Entry!\n");
		return 0;
	}
	

	printf("Dimensions: %d, %d. Enter seed: ", x_table_dimension, y_table_dimension);
	int seed;
	scanf("%d", &seed);
	printf("Seed: %d. Good luck! \n", seed);
	srand(seed);

	int x_start_rand = (rand() % (x_table_dimension - 2)) + 1, y_start_rand = (rand() % (y_table_dimension - 2)) + 1;		// min 1, max dim - 2
	int food_x = (rand() % (x_table_dimension - 2)) + 1, food_y = (rand() % (y_table_dimension - 2)) + 1;

	while(food_x == x_start_rand || food_y == y_start_rand){
		food_x = (rand() % (x_table_dimension - 2)) + 1;
		food_y = (rand() % (y_table_dimension - 2)) + 1;
	}

	int head[] = {y_start_rand, x_start_rand};
	int food[] = {food_y, food_x};

	int game_board[y_table_dimension][x_table_dimension];

	startgame(x_table_dimension, y_table_dimension, head, food, game_board);

	int next_board[y_table_dimension][x_table_dimension];
	copy_2D_array(x_table_dimension, y_table_dimension, next_board, game_board);

	init_game(x_table_dimension, head, game_board, next_board);


	

	initscr();
	curs_set(0);

	print_board(x_table_dimension, y_table_dimension, game_board);
	
	print_board(x_table_dimension, y_table_dimension, next_board);
	
	endwin();

	return 0;
}

void startgame(const int x_dim, const int y_dim, const int head[2], const int food[2], int board[][x_dim]) {
	int x_count, y_count;
	
	for(y_count = 0; y_count < y_dim; y_count++){
		for(x_count = 0; x_count < x_dim; x_count++){
			if(y_count == 0 || y_count == (y_dim - 1)){
				board[y_count][x_count] = 35;		// ascii #
			}
			else {
				if(x_count == 0 || x_count == (x_dim - 1)){
					board[y_count][x_count] = 35;	// ascii #
				}
				else {
					board[y_count][x_count] = 42;	// ascii * (asterisk)
				}
			}
		}
	}

	board[head[0]][head[1]] = 254;		// ascii square
	board[food[0]][food[1]] = 64;				// ascii @
}

void init_game(const int x_dim, const int head[2], int board[][x_dim], int next_board[][x_dim]) {
	int direction_val;		// 0 up, 1 right, 2 down, 3 left

	gen_direction:
	direction_val = rand() % 4;

	if(direction_val == 0){		// if direction == up
		if(board[head[0] - 1][head[1]] == 35){
			goto gen_direction;
		}
		else {
			next_board[head[0] - 1][head[1]] = 254;
			next_board[head[0]][head[1]] = 42;
		}
	}

	if(direction_val == 1){		// if direction == right
		if(board[head[0]][head[1] + 1] == 35){
			goto gen_direction;
		}
		else {
			next_board[head[0]][head[1] + 1] = 254;
			next_board[head[0]][head[1]] = 42;
		}
	}

	if(direction_val == 2){		// if direction == down
		if(board[head[0] + 1][head[1]] == 35){
			goto gen_direction;
		}
		else {
			next_board[head[0] + 1][head[1]] = 254;
			next_board[head[0]][head[1]] = 42;
		}
	}

	if(direction_val == 3){		// if direction == left
		if(board[head[0]][head[1] - 1] == 35){
			goto gen_direction;
		}
		else {
			next_board[head[0]][head[1] - 1] = 254;
			next_board[head[0]][head[1]] = 42;
		}
	}
}

void print_board(const int x_dim, const int y_dim, int board[][x_dim]) {
	clear();
	int x_count, y_count;
	for(y_count = 0; y_count < y_dim; y_count++){
		for(x_count = 0; x_count < x_dim; x_count++){
			printw("%c ", board[y_count][x_count]);
		}
		printw("\n");
	}
	refresh();
	sleep(1);
}

void copy_2D_array(const int x_dim, const int y_dim, int new_array[][x_dim], int old_array[][x_dim]) {
	int x_count, y_count;
	
	for(y_count = 0; y_count < y_dim; y_count++){
		for(x_count = 0; x_count < x_dim; x_count++){
			new_array[y_count][x_count] = old_array[y_count][x_count];
		}
	}
}