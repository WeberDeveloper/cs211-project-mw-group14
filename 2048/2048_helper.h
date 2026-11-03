#include <iostream>
#include <random>
#include <iomanip>
using namespace std;

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
	switch (direction)
	{
		case 1:	// move up
			trans_x = 0, trans_y = 1;
										break;
		case 2:	// move right
			trans_x = -1, trans_y = 0;
			bound_x = 4; 				break;
		case 3: // move down
			trans_x = 0, trans_y = -1;
			bound_y = 4; 				break;
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
			}
			// moving tile can merge with leftMost tile
			else if (*bound_tile == *next_tile)
			{
				*bound_tile *= 2;
				*next_tile = 0;
				bound_x += trans_x, bound_y += trans_y;
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
				}
			}
		}

		next_x += trans_x, next_y += trans_y;
	}
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

	cout << "\t" << endl << endl;
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

	if (empty_count > 0)
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
}

