/* Downturn game implementation in C
 * Basically Connect 4 but with board rotations and gravity
 * Chanik Bryan Lee */

#ifndef LOGIC_H
#define LOGIC_H

#include "board.h"

/* enum turn: specifies which player's turn it is */
enum turn {
    BLACK_NEXT,
    WHITE_NEXT
};
/* typedef enum turn as turn */
typedef enum turn turn;

/* enum outcome: specifies the outcome (result) of a game,
(winner BLACK_WIN or WHITE_WIN, DRAW, or IN_PROGRESS) */
enum outcome {
    BLACK_WIN,
    WHITE_WIN,
    DRAW,
    IN_PROGRESS
};
/* typedef enum outcome as outcome */
typedef enum outcome outcome;

/* enum direction: specifies the direction - clockwise (CW) or
counterclockwise (CCW) - of a board rotation turn */
enum direction {
    CW, CCW
};
/* typedef enum direction as direction */
typedef enum direction direction;

/* struct game: struct specifying game state including run (number of pieces
in a row needed to win), board, and which
player's turn it (currently) is */
struct game {
    unsigned int run;
    board* b;
    turn next;
};
/* typedef struct game as game */
typedef struct game game;

/* new_game: creates/returns a new game with the given size, desired data
representation (matrix or bits), and run (number of pieces in a row
required to win) */
game* new_game(unsigned int run, unsigned int width, unsigned int height,
               enum type type);

/* game_free: given a game,
frees/deallocates a game and all its contents from memory */
void game_free(game* g);

/* equal_boards: for testing purposes, returns a Boolean on whether or not
the two input boards have the same field values (same boards?) */
int same_boards(board* b1, board* b2);

/* drop_piece: does not change the turn, but drops a piece belonging to
the player whose turn it is in the given (specified) column. Returns a Boolean
(true or false) depending on whether or not a piece was dropped */
int drop_piece(game* g, unsigned int col);

/* board_drop: given a board with matrix with "floating" pieces,
makes all pieces drop to the bottom of the board, as if affected by gravity */
void board_drop(board* b, unsigned int width, unsigned int height);

/* twist: given a game pointer and a direction (CW for clockwise or
CCW for counterclockwise), performs a rotation on the game and simulates
the resulting gravitational effects.
This function does not change the turn.*/
void twist(game* g, direction d);

/* is_full: returns 1 if the board is full, 0 otherwise */
int is_full(game* g);

/* game_outcome: returns the outcome (enum) of a completed game.
If not completed, reports that the game is still in progress. */
outcome game_outcome(game* g);

#endif /* LOGIC_H */
