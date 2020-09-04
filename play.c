/* Downturn game implementation in C
 * Basically Connect 4 but with board rotations and gravity
 * Chanik Bryan Lee */

#include "logic.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/* inlist: is the specified string in the list of strings? */
int inlist(int argc, char *argv[], char* samp) {
    /* argv[0] is always a full path to the file */
    unsigned int i = 1;
    while (i < argc) {
        if (strcmp(argv[i], samp) == 0) {
            return (strcmp(argv[i], samp) == 0);
        }
        i++;
    }
    return 0;
}

/* return_index: assuming string is in list of strings, return its index */
unsigned int return_index(int argc, char* argv[], char* samp) {
    unsigned int i;
    /* skip index 0 since it is always a path - for slight efficiency */
    for (i=1; i<argc; i++) {
        if (strcmp(argv[i], samp) == 0) {
            return i;
        }
    }
    fprintf(stderr, "return_index: input string not in list\n");
    exit(1);
}

/* main : makes a new game and runs it (Game administration and interface) */
int main(int argc, char *argv[])/* argv is list of strings from command line */
{
    unsigned width, height, run;
    char* store;
    /* set -w, -h, and -r as given by command-line arguments.
    otherwise, set default values for them */
    if (inlist(argc, argv, "-w")) {
        width = (unsigned int)
        strtoul(argv[1 + return_index(argc, argv, "-w")], &store, 10);
    } else {
        width = 5; /* default setting */
    }
    /* raise an error if the user attempts to create a
    board exceeding 62 columns */
    if (width > 62) {
        printf("Error: Too many columns requested.\n");
        fprintf(stderr, "Error: Should be <= 62 columns.\n");
        exit(1);
    }
    if (inlist(argc, argv, "-h")) {
        height = (unsigned int)
        strtoul(argv[1 + return_index(argc, argv, "-h")], &store, 10);
    } else {
        height = 3; /* default setting */
    }
    if (inlist(argc, argv, "-r")) {
        run = (unsigned int)
        strtoul(argv[1 + return_index(argc, argv, "-r")], &store, 10);
    } else {
        run = 2; /* default setting */
    }

    /* matrix or bits implementation */
    game* workingGame;
    if (!inlist(argc, argv, "-m") && !inlist(argc, argv, "-b")) {
        fprintf(stderr, "play main: must specify either -m or -b\n");
        exit(1);
    }
    if (inlist(argc, argv, "-m")) {
        /* cannot spcify both -m and -b */
        if (inlist(argc, argv, "-b")) {
            fprintf(stderr, "play main: cannot specify both -m and -b\n");
            exit(1);
        }
        /* should be of odd index */
        if (return_index(argc, argv, "-m") % 2 == 0) { /* even case */
            printf("play main error:\n");
            fprintf(stderr,
            "-m should not be between letter and its corresponding number\n");
            exit(1);
        } else {
            workingGame = new_game(run, width, height, MATRIX);
        }
    }
    if (inlist(argc, argv, "-b")) {
        /* should be of odd index */
        if (return_index(argc, argv, "-b") % 2 == 0) { /* even case */
            printf("play main error:\n");
            fprintf(stderr,
            "-b should not be between letter and its corresponding number\n");
            exit(1);
        } else {
            workingGame = new_game(run, width, height, BITS);
        }
    }

    int truth;
    unsigned int conversion;

    while (game_outcome(workingGame) == IN_PROGRESS) {
        board_show(workingGame->b);
        printf("\n");
        char ch;
        if (workingGame->next == BLACK_NEXT) {
            printf("Black: ");
        } else {
            printf("White ");
        }
        /* discard newline (return) character instead of buffering it */
        scanf("%c%*c", &ch);

        if (ch == '<') {
            twist(workingGame, CCW);
        } else if (ch == '>') {
            twist(workingGame, CW);
        } else if (ch >= '0' && ch <= '9') {
            conversion = (unsigned int) ch - 48;
            if (conversion >= workingGame->b->width) {
                printf("Requested column is out of bounds - Try again.\n");
                continue;
            }
            truth = drop_piece(workingGame, conversion);
            if (truth == 0) {
                printf("Unable to drop the piece into the requested column\n");
                continue;
            }
        } else if (ch >= 'A' && ch <= 'Z') {
            conversion = (unsigned int) ch - 55;
            if (conversion >= workingGame->b->width) {
                printf("Requested column is out of bounds - Try again.\n");
                continue;
            }
            truth = drop_piece(workingGame, conversion);
            if (truth == 0) {
                printf("Unable to drop the piece into the requested column\n");
                continue;
            }
        } else if (ch >= 'a' && ch <= 'z') {
            conversion = (unsigned int) ch - 60;
            if (conversion >= workingGame->b->width) {
                printf("Requested column is out of bounds - Try again.\n");
                continue;
            }
            truth = drop_piece(workingGame, conversion);
            if (truth == 0) {
                printf("Unable to drop the piece into the requested column\n");
                continue;
            }
        } else {
            /* indistinguishable ? case - do not handle */
            /* input cannot be parsed, so state and go back to the step that
            prompts the user */
            printf("Input cannot be parsed (contains invalid characters)\n");
            continue;
        }
        /* If the game is not over, switch the turn to the other
        player and start the loop over */
        if (game_outcome(workingGame) != IN_PROGRESS) break;

        if (workingGame->next == BLACK_NEXT) {
            workingGame->next = WHITE_NEXT;
        } else {
            workingGame->next = BLACK_NEXT;
        }
        printf("\n");
    }

    printf("\n");
    printf("GAME CONCLUDED\n");
    board_show(workingGame->b);
    if (game_outcome(workingGame) == DRAW) {
        printf("DRAW: IT'S A TIE!\n");
    } else if (game_outcome(workingGame) == BLACK_WIN) {
        printf("BLACK_WIN: BLACK WINS!\n");
    } else {
        printf("WHITE_WIN: WHITE WINS!\n");
    }

    return 0;
}
