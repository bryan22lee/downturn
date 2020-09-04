/* Downturn game implementation in C
 * Basically Connect 4 but with board rotations and gravity
 * Chanik Bryan Lee */

#include "logic.h"
#include <stdlib.h>
#include <stdio.h>

game* new_game(unsigned int run, unsigned int width, unsigned int height,
               enum type type) {
    game* newGame = (game*) malloc(sizeof(game));
    if (newGame == NULL) {
       fprintf(stderr, "board_new: newBoard malloc failed\n");
       exit(1);
    }
    newGame->run = run;
    newGame->b = board_new(width, height, type);
    /* Black moves first */
    newGame->next = BLACK_NEXT;
    return newGame;
}

void game_free(game* g) {
    board_free(g->b);
    free(g);
}

int same_boards(board* b1, board* b2) {
    int starter;
    starter = ((b1->width == b2->width) && (b1->height == b2->height));
    starter = (starter && (b1->type == b2->type));
    // cell** m1 = b1->u.matrix;
    // cell** m2 = b2->u.matrix;
    unsigned int i, j;
    /* assuming they have the same width and height, respectively */
    /* remark: equal_boards is short-circuiting */
    for (i=0; i<b1->height; i++) {
        for (j=0; j<b1->width; j++) {
            starter = (starter &&
                (board_get(b1, make_pos(i, j)) ==
                board_get(b1, make_pos(i, j))));
        }
    }
    return starter;
}

/* drop_piece: as specified in logic.h;
not responsible for changing the turn */
int drop_piece(game* g, unsigned int col) {
    /* if the column is already full */
    if (board_get(g->b, make_pos(0, col)) != EMPTY) {
        return 0; /* return false and do nothing */
    }
    /* g->b->height is number of rows */
    unsigned int i = (g->b->height - 1); /* by zero-based indexing */
    turn curr_enum = g->next; /* current turn */

    while (board_get(g->b, make_pos(i, col)) != EMPTY) {
        i--;
    }
    if (curr_enum == BLACK_NEXT) {
        board_set(g->b, make_pos(i, col), BLACK);
    } else {
        board_set(g->b, make_pos(i, col), WHITE);
    }
    /* below should return true (nonzero integer) */
    return (board_get(g->b, make_pos(i, col)) != EMPTY);
}

/* helper funtion board_drop described in logic.h */
void board_drop(board* b, unsigned int width, unsigned int height) {
    int k;
    cell curValue;
    for (int j = 0; j < width; j++) {
        for (int i = height-2; i >= 0; i--) {
            if (board_get(b, make_pos(i, j)) == EMPTY) continue;
            k = i;
            while (k != (height-1) && board_get(b, make_pos(k + 1, j)) == EMPTY) {
                k++;
            }
            curValue = board_get(b, make_pos(i, j));
            board_set(b, make_pos(i, j), EMPTY);
            board_set(b, make_pos(k, j), curValue);
        }
    }
}

/* twist: as specified in logic.h; not responsible for changing the turn */
void twist(game* g, direction d) {
    board* twisted;
    if (g->b->type == MATRIX) {
        twisted = board_new(g->b->height, g->b->width, MATRIX);
    } else {
        twisted = board_new(g->b->height, g->b->width, BITS);
    }

    unsigned int i, j;

    if (d == CW) {
        for (i=0; i<g->b->width; ++i) {
            for (j=0; j<g->b->height; ++j) {
                board_set(twisted, make_pos(i, j),
                board_get(g->b, make_pos(g->b->height - 1 - j, i)));
            }
        }
    } else { /* if (d == CCW) */
        for (i=0; i<g->b->width; ++i) {
            for (j=0; j<g->b->height; ++j) {
                board_set(twisted, make_pos(i, j),
                board_get(g->b, make_pos(j, g->b->width - 1 - i)));
            }
        }
    }
    /* drop all floating pieces to the bottom as if gravity affects them */
    board_drop(twisted, g->b->height, g->b->width);
    /* free the old board after creating new (twisted) board */
    board_free(g->b);
    /* assigned new (twisted) board to the board field in game g (g->b) */
    g->b = twisted;
}

/* returns 1 if the board is full, 0 otherwise */
int is_full(game* g) {
    unsigned int i, j;
    unsigned int width = g->b->width;
    unsigned int height = g->b->height;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            if (board_get(g->b, make_pos(i, j)) == EMPTY) return 0;
        }
    }
    return 1;
}

outcome game_outcome(game* g) {
    unsigned int run = g->run;
    unsigned int width = g->b->width;
    unsigned int height = g->b->height;
    unsigned int i, j, k;
    int blackWin = 0;
    int whiteWin = 0;

    /* checks for horizontal wins */
    for (i=0; i < height; i++) {
        for (j=0; (j+run-1) < width; j++) {
                if (board_get(g->b, make_pos(i, j)) == EMPTY) continue;
                for (k=1; k<run; k++) {
                    if (board_get(g->b, make_pos(i, j + k)) !=
                    board_get(g->b, make_pos(i, j))) break;
                }
                if (k == run) {
                    blackWin =
                    blackWin || (board_get(g->b, make_pos(i, j)) == BLACK);
                    whiteWin =
                    whiteWin || (board_get(g->b, make_pos(i, j)) == WHITE);
                }
        }
    }

    /* checks for vertical wins */
    for (j=0; j < width; j++) {
        for (i=0; (i+run-1) < height; i++) {
            if (board_get(g->b, make_pos(i, j)) == EMPTY) continue;
            for (k=1; k<run; k++) {
                if (board_get(g->b, make_pos(i + k, j)) !=
                board_get(g->b, make_pos(i, j))) {
                    break;
                }
            }
            if (k == run) {
                blackWin =
                blackWin || (board_get(g->b, make_pos(i, j)) == BLACK);
                whiteWin =
                whiteWin || (board_get(g->b, make_pos(i, j)) == WHITE);
            }
        }
    }

    /* checks for down-right diagonal wins */
    for (i=0; (i+run-1) < height; i++) {
        for (j=0; (j+run-1) < width; j++) {
                if (board_get(g->b, make_pos(i, j)) == EMPTY) continue;
                for (k=1; k<run; k++) {
                    if (board_get(g->b, make_pos(i + k, j + k)) !=
                        board_get(g->b, make_pos(i, j))) {
                            break;
                    }
                }
                if (k == run) {
                    blackWin =
                    blackWin || (board_get(g->b, make_pos(i, j)) == BLACK);
                    whiteWin =
                    whiteWin || (board_get(g->b, make_pos(i, j)) == WHITE);
                }
        }
    }

    /* checks for up-right diagonal wins */
    for (i=height-1; (i-run+2) > 0; i--) {
        for (j=0; (j+run-1) < width; j++) {
                if (board_get(g->b, make_pos(i, j)) == EMPTY) continue;
                for (k=1; k<run; k++) {
                    if (board_get(g->b, make_pos(i - k, j + k)) !=
                    board_get(g->b, make_pos(i, j))) {
                        break;
                    }
                }
                if (k == run) {
                    blackWin =
                    blackWin || (board_get(g->b, make_pos(i, j)) == BLACK);
                    whiteWin =
                    whiteWin || (board_get(g->b, make_pos(i, j)) == WHITE);
                }
        }
    }

    if (blackWin == 1 && whiteWin == 1) return DRAW;
    if (blackWin) return BLACK_WIN;
    if (whiteWin) return WHITE_WIN;
    if (!is_full(g)) return IN_PROGRESS;
    return DRAW;
}
