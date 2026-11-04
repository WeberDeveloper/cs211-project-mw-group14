#include <iostream>
#include "2048_helper.h"
using namespace std;

int main()
{
	int size = 5;
	int board[5][5]{};
	//while getch == x loop for up down left right

	//cout << "Initial Board : [5x5] :" << endl;
	//print_board(board);

	char choice = 'u';	// initialized input
	bool valid = true;	// flags whether input is valid
	insert_random(board, size);

	while (choice != 'e')
	{

		if (valid)
			insert_random(board, size);
		print_board(board, size);

		cout << "Please enter choice:{u,d,l,r,e} for UP, DOWN, LEFT, RIGHT, Exit: " << endl;
		cout << "Choice: ";
		cin >> choice;

		valid = true;

		if (choice == 'u')
			move_board(board, size, 1);
		else if (choice == 'd')
			move_board(board, size, 3);
		else if (choice == 'l')
			move_board(board, size, 4);
		else if (choice == 'r')
			move_board(board, size, 2);
		else
			valid = false;


	}


	return 0;
}
