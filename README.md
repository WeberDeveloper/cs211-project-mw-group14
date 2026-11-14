# 2048

Use U, D, L, and R (enter lowercase) to move the tiles. Enter h for help
or e to exit. A move counts once if it slides or merges any tile. Each
merge adds the value of the resulting tile to the score.

Enter s to save or o to load. Saving writes to savegame.txt in the
program's working directory. Saving again replaces the previous save.
Loading restores the board, score, and successful move count. If the
save is missing or invalid, the current game is unchanged.

# Luhn Checksum

Asks for a 16 digit card number and checks whether it is valid.
The program reads a string from right to left and doubles every second digit.
Doubled digits that are greater than nine are subtracted by nine to stay within range (0 - 9).
All modified and unmodified digits are added and then checked for divisibility.
The card number is rejected if it contains white spaces or garbage values.
The test passes if the sum is divisible by 10.

After each check, enter y to check another card number or n to end the program.

# Group

- Group 25 (Formerly Group 14)
- https://github.com/WeberDeveloper/cs211-project-mw-group14


# Developers

- AsielDimas        - 2048 Save/Load system and code reorganization
- OscarVG8492       - Luhn Checksum Program
- WeberDeveloper    - 2048 game logic (move, win, lose conditions)