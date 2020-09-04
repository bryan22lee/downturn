/* Downturn game implementation in C
 * Basically Connect 4 but with board rotations and gravity
 * Chanik Bryan Lee */

#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

board* board_new(unsigned int width, unsigned int height, enum type type) {
    /* bits representation case */
    if (type == BITS) {
        /* 2 bits per cell */
        unsigned int numCells = width * height;
        unsigned int numBits = numCells * 2;
        /* each unsigned int holds 32 bits */
        unsigned int numElements;
        if (numBits % 32 == 0) {
            numElements = numBits / 32;
        } else {
            /* default: truncating integer division */
            numElements = (unsigned int) (numBits / 32) + 1;
        }

        board* newBoard = (board*) malloc(sizeof(board));
        if (newBoard == NULL) {
            fprintf(stderr, "board_new: newBoard malloc failed\n");
            exit(1);
        }
        unsigned int* myArray =
        (unsigned int*) malloc(sizeof(unsigned int) * numElements);
        newBoard->u.bits = myArray;
        if (newBoard->u.bits == NULL) {
            fprintf(stderr, "board_new: newBoard->u.bits malloc failed\n");
            exit(1);
        }

        unsigned int i;
        for (i=0; i<numElements; i++) {
            newBoard->u.bits[i] = 0;
        }

        newBoard->width = width;
        newBoard->height = height;
        newBoard->type = BITS;
        return newBoard;
    }

    /* matrix representation case */
    board* newBoard = (board*) malloc(sizeof(board));
    if (newBoard == NULL) {
        fprintf(stderr, "board_new: newBoard malloc failed\n");
        exit(1);
    }
    newBoard->width = width;
    newBoard->height = height;
    newBoard->type = type;
    cell** q = (cell**) malloc(sizeof(cell*) * height);
    if (q == NULL) {
        fprintf(stderr, "board_new: q malloc failed\n");
        exit(1);
    }
    unsigned int i, j;
    for (i = 0; i < height; i++) {
        q[i] = (cell*) malloc(sizeof(cell) * width);
        if (q[i] == NULL) {
            fprintf(stderr, "board_new: q[i] malloc failed\n");
            exit(1);
        }
        for (j = 0; j < width; j++) {
            q[i][j] = EMPTY;
        }
    }
    newBoard->u.matrix = q;
    /* return malloced newBoard */
    return newBoard;
}

void board_free(board* b) {
    /* bits representation case */
    if (b->type == BITS) {
        free(b->u.bits);
        free(b);
    }

    /* matrix representation case */
    if (b->type == MATRIX) {
        unsigned int i; /* free all allocated space from malloc */
        for (i = 0; i < b->height; i++) {
            free(b->u.matrix[i]);
        }
        free(b->u.matrix);
        free(b);
    }
}

void board_show(board* b) {
    unsigned int i, j;

    /* bits representation case */
    if (b->type == BITS) {
        unsigned int x, a, c, l;

        unsigned int numCells = b->width * b->height;
        unsigned int numBits = numCells * 2;
        /* each unsigned int holds 32 bits */
        unsigned int numElements;
        if (numBits % 32 == 0) {
            numElements = numBits / 32;
        } else {
            /* default: truncating integer division */
            numElements = (unsigned int) (numBits / 32) + 1;
        }

        printf("  ");
        for (j=0; j<b->width; j++) {
            if (j < 10) {
                printf("%d", j);
            } else if (j < 36) {
                printf("%c", 'A' + (j - 10));
            } else if (j < 62) {
                printf("%c", 'a' + (j - 36));
            } else {
                printf("?");
            }
        }
        printf("  ");
        printf("\n");
        printf("\n");

        unsigned int h = 0;
        unsigned int y = 0;
        int welp = -1;
        unsigned int count = 0;
        int anotherOne = 0;

        /* 2 bits in binary, 11, which is 0x3 for hexadecimal,
        i.e. last two digits */
        /*
        00 is 0
        10 is 2 - white piece in a cell
        01 is 1 - black piece in a cell
        */
        for (x=0; x<numElements; x++) {
            c = b->u.bits[x];

            for (a=0; a<16; a++) {
                if (h < b->height) {
                    if (welp == -1) {
                        welp = 1;
                        if (h < 10) {
                            printf("%u", h);
                        } else if (h < 36) {
                            printf("%c", 'A' + (h - 10));
                        } else if (h < 62) {
                            printf("%c", 'a' + (h - 36));
                        } else {
                            printf("?");
                        }
                        printf(" ");
                    }
                }

                /* l is the current cell state */
                l = (c & 0x3);
                c = (c>>2);

                /* BELOW PRINTS CELL STATES */
                if (h < b->height) {
                    if (l == 0) {
                        printf("%c", '.');
                    } else if (l == 2) {
                        printf("%c", 'o');
                    } else {
                        printf("%c", '*');
                    }
                }

                y++;

                if (y % b->width == 0) {
                    printf(" ");
                    if (h < 10) {
                        printf("%u", h);
                    } else if (h < 36) {
                        printf("%c", 'A' + (h - 10));
                    } else if (h < 62) {
                        printf("%c", 'a' + (h - 36));
                    } else {
                        printf("?");
                    }
                    h++;
                    printf("\n");
                    welp = -1;
                }
                count++;
                if (count == b->width * b->height) {
                    anotherOne = 1;
                    break;
                }
            }
            if (anotherOne == 1) {
                break;
            }
        }
        printf("\n");
        printf("  ");
        for (j=0; j<b->width; j++) {
            if (j < 10) {
                printf("%u", j);
            } else if (j < 36) {
                printf("%c", 'A' + (j - 10));
            } else if (j < 62) {
                printf("%c", 'a' + (j - 36));
            } else {
                printf("?");
            }
        }
        printf("  ");
        printf("\n");
    }

    /* matrix representation case */
    if (b->type == MATRIX) {
        printf("  ");
        for (j=0; j<b->width; j++) {
            if (j < 10) {
                printf("%d", j);
            } else if (j < 36) {
                printf("%c", 'A' + (j - 10));
            } else if (j < 62) {
                printf("%c", 'a' + (j - 36));
            } else {
                printf("?");
            }
        }
        printf("  ");
        printf("\n");
        printf("\n");

        for (i=0; i<b->height; i++) {
            if (i < 10) {
                printf("%d", i);
            } else if (i < 36) {
                printf("%c", 'A' + (i - 10));
            } else if (i < 62) {
                printf("%c", 'a' + (i - 36));
            } else {
                printf("?");
            }
            printf(" ");
            for (j=0; j<b->width; j++) {
                if (b->u.matrix[i][j] == EMPTY) {
                    printf("%c", '.');
                } else if (b->u.matrix[i][j] == BLACK) {
                    printf("%c", '*');
                } else {
                    printf("%c", 'o');
                }
            }
            printf(" ");
            if (i < 10) {
                printf("%d", i);
            } else if (i < 36) {
                printf("%c", 'A' + (i - 10));
            } else if (i < 62) {
                printf("%c", 'a' + (i - 36));
            } else {
                printf("?");
            }
            printf("\n");
        }

        printf("\n");
        printf("  ");
        for (j=0; j<b->width; j++) {
            if (j < 10) {
                printf("%d", j);
            } else if (j < 36) {
                printf("%c", 'A' + (j - 10));
            } else if (j < 62) {
                printf("%c", 'a' + (j - 36));
            } else {
                printf("?");
            }
        }
        printf("  ");
        printf("\n");
    }
}

cell board_get(board* b, pos p) {
    /* bounds-checking below */
    if (p.r >= b->height) {
        fprintf(stderr,
            "board_get: input position row (p.r) out of bounds\n");
        exit(1);
    }
    if (p.c >= b->width) {
        fprintf(stderr,
            "board_get: input position column (p.c) out of bounds\n");
        exit(1);
    }

    /* bits representation case */
    if (b->type == BITS) {
        unsigned int i, j, k;
        /* initialize count to 0 */
        int count = 0;
        unsigned int dest = (p.r * b->width) + p.c;
        unsigned int numCells = b->width * b->height;
        unsigned int numBits = 2 * numCells;
        unsigned int* myArray = b->u.bits;
        /* each unsigned int holds 32 bits */
        unsigned int numElements;
        if (numBits % 32 == 0) {
            numElements = numBits / 32;
        } else {
            /* default: truncating integer division */
            numElements = (unsigned int) (numBits / 32) + 1;
        }
        for (i=0; i<numElements; i++) {
            j = myArray[i];
            for (k=0; k<16; k++) {
                if (count == dest) {
                    count = -1;
                    break;
                }
                j = (j>>2);
                count++;
            }
            if (count == -1) break;
        }
        /* least significant 2 bits */
        j = (j & 0x3);
        /*
        00 is 0
        10 is 2 - white piece in a cell
        01 is 1 - black piece in a cell
        */
        if (j == 2) {
            return WHITE;
        } else if (j == 1) {
            return BLACK;
        } else {
            return EMPTY;
        }
    }

    /* matrix representation case */
    return b->u.matrix[p.r][p.c];
}

void board_set(board* b, pos p, cell c) {
    /* bounds-checking below */
    if (p.r >= b->height) {
        fprintf(stderr,
            "board_set: input position row (p.r) out of bounds\n");
        exit(1);
    }
    if (p.c >= b->width) {
        fprintf(stderr,
            "board_set: input position column (p.c) out of bounds\n");
        exit(1);
    }

    /* bits representation case */
    if (b->type == BITS) {
        /* first, find appropriate array index that needs to be changed */
        unsigned int dest = (p.r * b->width) + p.c;

        /* truncating integer division */
        unsigned int arrayIndex = dest / 16;
        unsigned int bitNum = dest % 16;

        unsigned int delta;
        if (c == BLACK) {
            delta = 1;
        } else if (c == WHITE) {
            delta = 2;
        } else {
            delta = 0;
        }

        /* add enough zeros to lesser-significant digits as needed */
        unsigned int j;
        unsigned int inv_delta = 3;
        for (j=0; j<bitNum; j++) {
            delta = (delta<<2);
            inv_delta = (inv_delta<<2);
        }
        inv_delta = ~inv_delta;

        /* changes the cells that need to be changed to empty */
        b->u.bits[arrayIndex] = (b->u.bits[arrayIndex] & inv_delta);
        b->u.bits[arrayIndex] = (b->u.bits[arrayIndex] | delta);
    }

    /* matrix representation case */
    if (b->type == MATRIX) {
        b->u.matrix[p.r][p.c] = c;
    }
}
