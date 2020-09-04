/* Downturn game implementation in C
 * Basically Connect 4 but with board rotations and gravity
 * Chanik Bryan Lee */

#ifndef BOARD_H
#define BOARD_H

#include "pos.h"

/* enum cell: represents the contents of a given location on the board,
either occupied (black or white piece) or empty */
enum cell {
    EMPTY,
    BLACK,
    WHITE
};
/* typedef for enum cell as cell */
typedef enum cell cell;

/* union board_rep: either matrix of enum pointers representing the cells
on the board or a compact bits representation */
union board_rep {
    enum cell** matrix;
    unsigned int* bits;
};
/* typedef union board_rep as board_rep */
typedef union board_rep board_rep;
/* enum type: enumeration of type as either MATRIX or BITS */
enum type {
    MATRIX, BITS
};

/* struct board: board struct with fields specifying its width and height,
type of data for representing the baord, and the data itself to represent
the board (board_rep) */
struct board {
    unsigned int width, height;
    enum type type;
    board_rep u;
};
/* typedef struct board as board */
typedef struct board board;

/* board_new: creates and returns a fully-empty board of the desired size,
after input specification of the representation type (matrix or bits) */
board* board_new(unsigned int width, unsigned int height, enum type type);

/* board_free: fully frees the board and the internal representation
it is using */
void board_free(board* b);

/* board_show: prints the input board to the screen
(including row/column headers) */
void board_show(board* b);

/* board_get: retrieves cell information from within the given board */
cell board_get(board* b, pos p);

/* board_set: given board (pointer), a position, and a cell enumeration,
modifies the cell as desired within the board */
void board_set(board* b, pos p, cell c);

#endif /* BOARD_H */
