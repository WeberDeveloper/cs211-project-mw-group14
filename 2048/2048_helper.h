#pragma once

#include <fstream>
#include <limits>
#include <sstream>
#include <string>
#include <iostream>
#include <random>
#include <iomanip>
using namespace std;

struct GameState
{
    int board[5][5]{};
    long long score = 0;
    long long moves = 0;
	bool lose = false;
};

// Returns true if a slide or merge changed the board.
// The caller supplies a temporary board and score in case a move overflows.
bool move_board(int board[][5], int direction, long long& score)
{

	bool changed = false;
	int bound_x{}, bound_y{};
	int trans_x{}, trans_y{};
	int move_blocked_index{};

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
				changed = true;
				*bound_tile = *next_tile;
				*next_tile = 0;
			}
			// moving tile can merge with leftMost tile
			else if (*bound_tile == *next_tile)
			{
				if (*bound_tile > numeric_limits<int>::max() / 2 ||
                    score > numeric_limits<long long>::max() - 2LL * *bound_tile)
                {
                    cerr << "\nMerge would exceed the supported tile or score range.\n";
                    return false;
                }
                *bound_tile *= 2;
                score += *bound_tile;
                changed = true;
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
					changed = true;
					*bound_tile = *next_tile;
					*next_tile = 0;
				}
			}
		}

		next_x += trans_x, next_y += trans_y;
	}
	return changed;
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
		}
		cout << "\t|" << endl;
		cout << "\t-----------------------------------------" << endl;
	}

	cout << "\t" << endl;
}

int count_empty(int board[][5], int numrows = 5)
{
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

	return empty_count;
}


void insert_random(int board[][5], int numrows = 5)
{
	int r, c;
	int empty_count = count_empty(board, numrows);

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


bool check_merge(int board[][5])
{
	int* board_origin = &board[0][0];
		int* center_tile = board_origin;

		for (int i = 0; i < 25; ++i)
		{	
			// no right border and right tile matches with center tile
			if (((i + 1) % 5 != 0) && (*center_tile == *(center_tile + 1)))
				return true;
			// no left border and left tile matches with center tile
			else if ((i % 5 != 0) && (*center_tile == *(center_tile - 1)))
				return true;
			// no top border and top tile matches with center tile
			else if (((center_tile - 5 - board_origin) >= 0) && (*center_tile == *(center_tile - 5)))
				return true;
			// no bottom border and bottom tile matches with center tile
			else if (((center_tile + 5 - board_origin) <= 25) && (*center_tile == *(center_tile + 5)))
				return true;

			++center_tile;
		}
		return false;
}

bool check_lose(int board[][5])
{
	if (count_empty(board) == 0 && check_merge(board) == false)
		return true;
	
	return false;
}

bool check_win(int board[][5])
{
	int* tile = &board[0][0];

	for (int i = 0; i < 25; ++i)
	{
		if (*tile >= 2048)
			return true;

		++tile;
	}
	return false;
}


bool save_game(const GameState& game)
{
    ofstream file("savegame.txt");
    if (!file)
    {
        cerr << "\nCould not open savegame.txt for saving.\n";
        return false;
    }

    file << "CS211_2048_V1\n" << game.score << ' ' << game.moves << '\n';
    for (const auto& row : game.board)
    {
        for (int col = 0; col < 5; ++col)
        {
            if (col > 0)
                file << ' ';
            file << row[col];
        }
        file << '\n';
    }

    file.close();
    if (!file)
    {
        cerr << "\nCould not finish writing savegame.txt.\n";
        return false;
    }

    cout << "\nGame saved.\n";
    return true;
}

// Parse a whole whitespace-separated token, including checking its range.
template <typename Integer>
bool read_integer(istream& file, Integer& value)
{
    string token;
    if (!(file >> token))
        return false;

    istringstream number(token);
    return (number >> value) && number.eof();
}

bool load_game(GameState& game)
{
    ifstream file("savegame.txt");
    if (!file)
    {
        cerr << "\nCould not open savegame.txt for loading.\n";
        return false;
    }

    GameState saved{};
    string marker;
    if (!(file >> marker) || marker != "CS211_2048_V1")
    {
        cerr << "\nInvalid save: expected the CS211_2048_V1 marker.\n";
        return false;
    }

    if (!read_integer(file, saved.score) || saved.score < 0 ||
        !read_integer(file, saved.moves) || saved.moves < 0)
    {
        cerr << "\nInvalid save: expected two nonnegative integer counters in range.\n";
        return false;
    }

    for (int row = 0; row < 5; ++row)
    {
        for (int col = 0; col < 5; ++col)
        {
            int& tile = saved.board[row][col];
            if (!read_integer(file, tile) ||
                (tile != 0 && (tile < 2 || (tile & (tile - 1)) != 0)))
            {
                cerr << "\nInvalid or missing tile at row " << row + 1
                     << ", column " << col + 1 << ".\n";
                return false;
            }
        }
    }

    string extra;
    if (file >> extra)
    {
        cerr << "\nInvalid save: unexpected data after the 25 board cells.\n";
        return false;
    }
    if (file.bad() || !file.eof())
    {
        cerr << "\nCould not finish reading savegame.txt.\n";
        return false;
    }

    game = saved;

	// checks lose state of board
	if (check_lose(game.board))
		game.lose = true;
	else
		game.lose = false;

    cout << "\nGame loaded.\n";
    return true;
}
