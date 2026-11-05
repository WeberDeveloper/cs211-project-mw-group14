#include <iostream>
#include <random>
#include <iomanip>
using namespace std;

// global variables
bool board_changed = true;
bool board_no_more_moves = false;
int board_merge_score{};
int board_valid_moves_counted{};

// Moves all tiles in the board with a given direction, merging equal tiles according to 2048 game rules.
// Parameters:
//   board: a 2D array representing the game board (5x5).
//   numrows: the number of rows in the board (default is 5).
//	 direction: behavior in which tiles translate (default is left)
void move_board(int board[][5], int numrows = 5, int direction = 4)
{
	// init
	int bound_x{}, bound_y{};
	int trans_x{}, trans_y{};
	int move_blocked_index{};
	board_changed = false;

	switch (direction)
	{
		case 1:	// move up
			trans_x = 0, trans_y = 1;
															break;
		case 2:	// move right
			trans_x = -1, trans_y = 0;
			bound_x = 4; 									break;
		case 3: // move down
			trans_x = 0, trans_y = -1;
			bound_y = 4; 									break;
		case 4: // left
			trans_x = 1, trans_y = 0; 
															break;

	}
	int next_x = (bound_x + trans_x),
		next_y = (bound_y + trans_y);
	int* bound_tile = nullptr;
	int* next_tile  = nullptr;
	
	// loop through board
	for (int i = 0; i < 20; ++i)
	{
		// begins at next row/column if out of bounds
		if (next_x > 4)						// next row after moving left
		{
			next_x = 1, ++next_y;
			bound_x = 0, bound_y = next_y;
		}
		else if (next_x < 0)				// next row after moving right
		{
			next_x = 3, ++next_y;
			bound_x = 4, bound_y = next_y;	// next column after moving down
		}
		else if (next_y > 4)
		{
			++next_x, next_y = 1;
			bound_x = next_x, bound_y = 0;
		}
		else if (next_y < 0)				// next column after moving up
		{
			++next_x, next_y = 3;
			bound_x = next_x, bound_y = 4;
		}

		// update checking tiles
		bound_tile = &board[bound_y][bound_x];
		next_tile  = &board[next_y][next_x];

		if (*next_tile > 0)
		{
			// moving tile can move to open space
			if (*bound_tile == 0)
			{
				*bound_tile = *next_tile;
				*next_tile = 0;
				board_changed = true;
			}
			// moving tile can merge with leftMost tile
			else if (*bound_tile == *next_tile)
			{
				*bound_tile *= 2;
				board_merge_score += *bound_tile;	// increment score after merge
				*next_tile = 0;
				bound_x += trans_x, bound_y += trans_y;
				board_changed = true;
			}
			// moving tile does not match, it bumps into leftMost tile
			else			
			{
				bound_x += trans_x, bound_y += trans_y;
				bound_tile = &board[bound_y][bound_x];
				// slides into open space, if any
				if (*bound_tile == 0)
				{
					*bound_tile = *next_tile;
					*next_tile = 0;
					board_changed = true;
				}
			}
		}

		next_x += trans_x, next_y += trans_y;
	}

	// counts move and updates its status
	if (board_changed) ++board_valid_moves_counted;
}

void print_board(int board[][5], int numrows = 5)
{
	cout << endl << "\t-----------------------------------------" << endl;

	for (int r = 0; r < numrows; r++)
	{
		for (int c = 0; c < 5; c++)
		{
			if(board[r][c] > 0)
				cout << "\t|" << right << setw(6) << setfill(' ') << board[r][c];
			else
				cout << "\t|" << right << setw(6) << setfill(' ') << " ";

			//cout << board[r][c] << "\t|\t";
		}
		cout << "\t|" << endl;
		cout << "\t-----------------------------------------" << endl;
	}

	cout << "\t" << endl;
	cout << "SCORE: " << board_merge_score << " MOVES: " << board_valid_moves_counted << endl << endl;
}


void insert_random(int board[][5], int numrows = 5)
{
	int r, c;
	//count empty
	int empty_count = 0;
	for (int r = 0; r < numrows; r++)
	{
		for (int c = 0; c < 5; c++)
		{
			if (board[r][c] == 0)
				empty_count++;
		}
	}

	if (empty_count > 0 && board_changed)
	{
		while (true)
		{
			//generate random location r, c
			r = rand() % numrows;
			c = rand() % numrows;
			//check if empty
			if (board[r][c] == 0)
			{
				//add number randomly {2,4}
				board[r][c] = 2 * (1 + (rand() % 2));
				break;
			}
		}
	}
	else if (empty_count == 0)
	{
		int* center_tile = &board[0][0];
		board_no_more_moves = true;

		for (int i = 0; i < 10; ++i)
		{
			// when entering a new row, skip it
			if (i % 5 == 0)
				center_tile += 5;
			
			// no right border and right tile matches with center tile
			if (((i + 1) % 5 != 0) && (*center_tile == *(center_tile + 1)))
			{
				board_no_more_moves = false;
				break;
			}
			// no left border and left border matches with center tile
			if (((i - 1) % 5 != 0) && (*center_tile == *(center_tile - 1)))
			{
				board_no_more_moves = false;
				break;
			}
			// vertical tiles match center tile
			if (*center_tile == *(center_tile - 5) || *center_tile == *(center_tile + 5))
			{
				board_no_more_moves = false;
				break;
			}

			++center_tile;
		}
	}
}

// Zeros out entire board and inserts one random tile; The next random tile is from the main loop.
// Parameters:
//   board: a 2D array representing the game board (5x5).
//   numrows: the number of rows in the board (default is 5).
void new_game(int board[][5], int numrows = 5) {
	
	int* current_board_tile = &board[0][0];

	for (int i = 0; i < 25; ++i)
	{
		*current_board_tile = 0;
		++current_board_tile;
	}

	board_changed = true;
	board_no_more_moves = false;
	board_merge_score = 0; 
	board_valid_moves_counted = 0;

	insert_random(board, numrows);
}

