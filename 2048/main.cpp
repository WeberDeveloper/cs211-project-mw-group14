#include <iostream>
#include "2048_helper.h"
using namespace std;

int main()
{
	int size = 5;
	int board[5][5]{};

	char choice = 'u';	// initialized input
	bool valid_move_input = true;

	insert_random(board, size);

	while (choice != 'e')
	{

		if (valid_move_input)
			insert_random(board, size);
		print_board(board, size);
		
		// game is continuing
		if (board_no_more_moves == false)
		{
			cout << "Please enter choice:{u,d,l,r,e} for UP, DOWN, LEFT, RIGHT, Exit: " << endl;
			cout << "Choice: ";
			cin >> choice;

			valid_move_input = true;

			if (choice == 'u')
				move_board(board, size, 1);
			else if (choice == 'd')
				move_board(board, size, 3);
			else if (choice == 'l')
				move_board(board, size, 4);
			else if (choice == 'r')
				move_board(board, size, 2);
			else
				valid_move_input = false;
		}
		// no more moves!
		else
		{
			valid_move_input = false;
			cout << "Oh no! There are no more moves." << endl
				 << "Please enter choice {e, n} for Exit, New Game: ";
			cin >> choice;

			if (choice == 'n')
			{
				new_game(board, size);
				valid_move_input = true;
			}

		}


	}

	return 0;
}
