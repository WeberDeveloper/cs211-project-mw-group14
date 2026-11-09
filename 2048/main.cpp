#include <iostream>
#include "2048_helper.h"
using namespace std;

void print_help()
{
    cout << "u/d/l/r: move up/down/left/right; s: save; o: load; h: help; e: exit\n"
         << "Saving writes to savegame.txt in the working directory. "
         << "Saving again replaces the previous save.\n";
}

int main()
{
    GameState game{};
    insert_random(game.board);
    insert_random(game.board);
    print_help();

    while (true)
    {
        print_board(game.board);
        cout << "Score: " << game.score
             << " | Successful moves: " << game.moves << "\nChoice: ";

        char choice;
        if (!(cin >> choice) || choice == 'e')
            break;

        int direction;
        switch (choice)
        {
            case 'u': direction = 1; break;
            case 'r': direction = 2; break;
            case 'd': direction = 3; break;
            case 'l': direction = 4; break;
            case 's': save_game(game); continue;
            case 'o': load_game(game); continue;
            case 'h': print_help(); continue;
            default: cout << "Unknown command. Enter h for help.\n"; continue;
        }

        // Try the move on a copy so an overflow cannot leave a partial move.
        GameState next = game;
        if (move_board(next.board, direction, next.score))
        {
            if (next.moves == numeric_limits<long long>::max())
            {
                cerr << "Move count would exceed its supported range.\n";
                continue;
            }
            ++next.moves;
            insert_random(next.board);
            game = next;
        }
    }
}
