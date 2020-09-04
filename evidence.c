/* Unit tests */

#include "logic.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* evidence_make_pos : test make_pos */
void evidence_make_pos()
{   /* tests passed */
    printf("*** testing make_pos\n");

    pos t1 = make_pos(0, 0);
    pos t2 = make_pos(1, 0);
    pos t3 = make_pos(0, 1);
    pos t4 = make_pos(1, 1);
    pos t5 = make_pos(4, 7);
    pos t6 = make_pos(32, 49);
    pos t7 = make_pos(101, 362);

    printf("- expecting 0 0: %u %u\n", t1.r, t1.c);
    printf("- expecting 1 0: %u %u\n", t2.r, t2.c);
    printf("- expecting 0 1: %u %u\n", t3.r, t3.c);
    printf("- expecting 1 1: %u %u\n", t4.r, t4.c);
    printf("- expecting 4 7: %u %u\n", t5.r, t5.c);
    printf("- expecting 32 49: %u %u\n", t6.r, t6.c);
    printf("- expecting 101 362: %u %u\n", t7.r, t7.c);
}

/* evidence_board_new : test board_new (includes board_free) */
void evidence_board_new()
{
    printf("*** testing board_new (includes board_free)\n");
    /* BELOW (error test): expecting error for now (it worked) */
    /*
    board* board0 = board_new(5, 10, BITS);
    board_free(board0);
    */

    /* bits representation test cases below */
    board* board1 = board_new(5, 10, BITS);
    board* board2 = board_new(7, 11, BITS);
    board* board3 = board_new(20, 20, BITS);
    board* board4 = board_new(1, 1, BITS);

    printf("- expecting 5, 10: %u, %u\n",
    board1->width, board1->height);
    printf("- expecting 7, 11: %u, %u\n",
    board2->width, board2->height);
    printf("- expecting 20, 20: %u, %u\n",
    board3->width, board3->height);
    printf("- expecting 1, 1: %u, %u\n",
    board4->width, board4->height);

    unsigned int i, j;
    unsigned int l = 0;
    unsigned int k = 0;
    unsigned int x;

    printf("board1 below:\n");
    for (i=0; i<board1->height; i++) {
        x = board1->u.bits[l];
        for (j=0; j<board1->width; j++) {
            printf("%d", (x & 0x3));
            k++;
            if (k == 16) {
                l++;
                k = 0;
            }
            x = (x << 2);
        }
        printf("\n");
    }

    printf("board2 below:\n");
    for (i=0; i<board2->height; i++) {
        x = board2->u.bits[l];
        for (j=0; j<board2->width; j++) {
            printf("%d", (x & 0x3));
            k++;
            if (k == 16) {
                l++;
                k = 0;
            }
            x = (x << 2);
        }
        printf("\n");
    }

    printf("board3 below:\n");
    for (i=0; i<board3->height; i++) {
        x = board3->u.bits[l];
        for (j=0; j<board3->width; j++) {
            printf("%d", (x & 0x3));
            k++;
            if (k == 16) {
                l++;
                k = 0;
            }
            x = (x << 2);
        }
        printf("\n");
    }

    printf("board4 below:\n");
    for (i=0; i<board4->height; i++) {
        x = board4->u.bits[l];
        for (j=0; j<board4->width; j++) {
            printf("%d", (x & 0x3));
            k++;
            if (k == 16) {
                l++;
                k = 0;
            }
            x = (x << 2);
        }
        printf("\n");
    }

    board_free(board1);
    board_free(board2);
    board_free(board3);
    board_free(board4);
}

/* evidence_board_show : test board_show */
void evidence_board_show()
{
    printf("*** testing board_show\n");

    board* board1 = board_new(15, 10, BITS);
    board* board2 = board_new(24, 24, BITS);
    board* board3 = board_new(70, 29, BITS);
    board* board4 = board_new(1, 1, BITS);

    printf("eyeball (visual) tests below (they passed)\n");
    printf("\n");
    board_show(board1);
    printf("\n");
    board_show(board2);
    printf("\n");
    board_show(board3);
    printf("\n");
    board_show(board4);
    printf("\n");

    board_free(board1);
    board_free(board2);
    board_free(board3);
    board_free(board4);
}

/* evidence_board_get : test board_get */
void evidence_board_get()
{
    printf("*** testing board_get\n");

    board* board1 = board_new(5, 10, BITS);
    board* board2 = board_new(7, 11, BITS);
    board* board3 = board_new(20, 20, BITS);
    board* board4 = board_new(1, 1, BITS);

    /* bounds-checking error cases below (they worked) */
    /*
    board_get(board1, make_pos(15, 2));
    board_get(board2, make_pos(4, 19));
    */

    printf("For below tests, true indicates the returned cell is EMPTY ");
    printf("(as expected).\n");

    printf("- expecting nonzero integer (true): %d\n",
    (board_get(board1, make_pos(2, 3)) == EMPTY));
    printf("- expecting nonzero integer (true): %d\n",
    (board_get(board2, make_pos(10, 6)) == EMPTY));
    printf("- expecting nonzero integer (true): %d\n",
    (board_get(board3, make_pos(9, 14)) == EMPTY));
    printf("- expecting nonzero integer (true): %d\n",
    (board_get(board3, make_pos(0, 0)) == EMPTY));
    printf("- expecting nonzero integer (true): %d\n",
    (board_get(board3, make_pos(3, 2)) == EMPTY));
    printf("- expecting nonzero integer (true): %d\n",
    (board_get(board4, make_pos(0, 0)) == EMPTY));

    board_free(board1);
    board_free(board2);
    board_free(board3);
    board_free(board4);
}

/* evidence_board_set : test board_set */
void evidence_board_set()
{
    printf("*** testing board_set\n");

    board* board1 = board_new(5, 10, BITS);
    board* board2 = board_new(7, 11, BITS);
    board* board3 = board_new(1, 1, BITS);

    /* bounds-checking error cases below (they worked) */
    /*
    board_set(board1, make_pos(15, 2), BLACK);
    board_set(board2, make_pos(4, 19), WHITE);
    */

    board_set(board1, make_pos(0, 0), BLACK);
    printf("- expecting nonzero integer (true): %d\n",
    (board_get(board1, make_pos(0, 0)) == BLACK));
    printf("- expecting 0 (false): %d\n",
    (board_get(board1, make_pos(0, 0)) == EMPTY));
    printf("- expecting 0 (false): %d\n",
    (board_get(board1, make_pos(0, 0)) == WHITE));

    board_set(board2, make_pos(4, 5), WHITE);
    printf("- expecting nonzero integer (true): %d\n",
    (board_get(board2, make_pos(4, 5)) == WHITE));
    printf("- expecting 0 (false): %d\n",
    (board_get(board2, make_pos(4, 5)) == EMPTY));
    printf("- expecting 0 (false): %d\n",
    (board_get(board2, make_pos(4, 5)) == BLACK));

    board_set(board2, make_pos(4, 5), EMPTY);
    printf("- expecting nonzero integer (true): %d\n",
    (board_get(board2, make_pos(4, 5)) == EMPTY));
    printf("- expecting 0 (false): %d\n",
    (board_get(board2, make_pos(4, 5)) == BLACK));
    printf("- expecting 0 (false): %d\n",
    (board_get(board2, make_pos(4, 5)) == WHITE));

    board_set(board3, make_pos(0, 0), BLACK);
    printf("- expecting nonzero integer (true): %d\n",
    (board_get(board3, make_pos(0, 0)) == BLACK));
    printf("- expecting 0 (false): %d\n",
    (board_get(board3, make_pos(0, 0)) == EMPTY));
    printf("- expecting 0 (false): %d\n",
    (board_get(board3, make_pos(0, 0)) == WHITE));

    board_free(board1);
    board_free(board2);
    board_free(board3);
}

/* evidence_new_game : test new_game (includes game_free) */
void evidence_new_game()
{
    printf("*** testing new_game (includes game_free)\n");

    game* game1 = new_game(4, 5, 10, BITS);
    game* game2 = new_game(7, 12, 12, BITS);
    game* game3 = new_game(3, 7, 9, BITS);

    printf("- expecting 4: %d\n", game1->run);
    printf("- expecting 7: %d\n", game2->run);
    printf("- expecting 3: %d\n", game3->run);

    printf("- expecting Boolean nonzero integer (true): %d\n",
    (game1->next == BLACK_NEXT));
    printf("- expecting Boolean nonzero integer (true): %d\n",
    (game2->next == BLACK_NEXT));
    printf("- expecting Boolean nonzero integer (true): %d\n",
    (game3->next == BLACK_NEXT));
    printf("- expecting Boolean 0 (false): %d\n",
    (game1->next == WHITE_NEXT));
    printf("- expecting Boolean 0 (false): %d\n",
    (game2->next == WHITE_NEXT));
    printf("- expecting Boolean 0 (false): %d\n",
    (game3->next == WHITE_NEXT));

    board* board1 = board_new(5, 10, BITS);
    board* board2 = board_new(12, 12, BITS);
    board* board3 = board_new(7, 9, BITS);

    printf("- expecting nonzero integer (Boolean true): %d\n",
    same_boards(game1->b, board1));
    printf("- expecting nonzero integer (Boolean true): %d\n",
    same_boards(game2->b, board2));
    printf("- expecting nonzero integer (Boolean true): %d\n",
    same_boards(game3->b, board3));
    printf("- expecting 0 (Boolean false): %d\n",
    same_boards(game1->b, board2));
    printf("- expecting 0 (Boolean false): %d\n",
    same_boards(game2->b, board3));
    printf("- expecting 0 (Boolean false): %d\n",
    same_boards(game1->b, board3));

    board_free(board1);
    board_free(board2);
    board_free(board3);

    game_free(game1);
    game_free(game2);
    game_free(game3);
}

/* evidence_drop_piece : test drop_piece */
void evidence_drop_piece()
{
    printf("*** testing drop_piece\n");

    game* game1 = new_game(4, 5, 10, BITS);
    game* game2 = new_game(7, 8, 12, BITS);
    game2->next = WHITE_NEXT; /* changing turns */
    game* game3 = new_game(3, 7, 7, BITS);
    /* to test to make sure dropped pieces go "on top" of already-
    dropped pieces */
    board_set(game3->b, make_pos(6, 0), BLACK);
    board_set(game3->b, make_pos(5, 0), WHITE);

    /* error cases below from bounds-checking in board_get and board_set */
    /* column bounds errors (they worked) */
    /*
    printf("- expecting bounds-checking error: %d\n",
    drop_piece(game1, 8));
    printf("- expecting bounds-checking error: %d\n",
    drop_piece(game2, 16));
    */

    /* test case 1 */
    /* current turn: BLACK_NEXT */
    printf("- expecting nonzero integer (Boolean true): %d\n",
    drop_piece(game1, 3));
    printf("- expecting nonzero integer (Boolean true): %d\n",
    (board_get(game1->b, make_pos(9, 3)) == BLACK));
    printf("- expecting 0 (Boolean false): %d\n",
    (board_get(game1->b, make_pos(9, 3)) == WHITE));
    printf("- expecting 0 (Boolean false): %d\n",
    (board_get(game1->b, make_pos(9, 3)) == EMPTY));

    /* test case 2 */
    /* current turn: WHITE_NEXT */
    printf("- expecting nonzero integer (Boolean true): %d\n",
    drop_piece(game2, 7));
    printf("- expecting nonzero integer (Boolean true): %d\n",
    (board_get(game2->b, make_pos(11, 7)) == WHITE));
    printf("- expecting 0 (Boolean false): %d\n",
    (board_get(game2->b, make_pos(11, 7)) == BLACK));
    printf("- expecting 0 (Boolean false): %d\n",
    (board_get(game2->b, make_pos(11, 7)) == EMPTY));

    /* test case 3 */
    /* to test to make sure dropped pieces go "on top" of already-
    dropped pieces */
    /* current turn: BLACK_NEXT */
    printf("- expecting nonzero integer (Boolean true): %d\n",
    drop_piece(game3, 0));
    printf("- expecting nonzero integer (Boolean true): %d\n",
    (board_get(game3->b, make_pos(4, 0)) == BLACK));
    printf("- expecting 0 (Boolean false): %d\n",
    (board_get(game3->b, make_pos(4, 0)) == WHITE));
    printf("- expecting 0 (Boolean false): %d\n",
    (board_get(game3->b, make_pos(4, 0)) == EMPTY));

    game_free(game1);
    game_free(game2);
    game_free(game3);
}

/* evidence_twist : test twist */
void evidence_twist()
{
    printf("\n*** testing twist\n");
    printf("- visual (eyeball) tests below:\n");

    /* REMARK: WORKS FOR MATRIX VERSION */

    game* game1 = new_game(4, 5, 10, BITS);
    game* game2 = new_game(7, 8, 12, BITS);
    board_set(game2->b, make_pos(11, 0), BLACK);
    board_set(game2->b, make_pos(11, 2), WHITE);
    game* game3 = new_game(3, 9, 7, BITS);
    board_set(game3->b, make_pos(6, 0), BLACK);
    board_set(game3->b, make_pos(5, 0), WHITE);
    game* game4 = new_game(3, 5, 6, BITS);
    board_set(game4->b, make_pos(5, 0), BLACK);
    board_set(game4->b, make_pos(4, 0), WHITE);
    board_set(game4->b, make_pos(5, 3), WHITE);
    board_set(game4->b, make_pos(4, 3), BLACK);
    board_set(game4->b, make_pos(3, 3), BLACK);
    board_set(game4->b, make_pos(2, 3), BLACK);

    printf("\nBEFORE:\n");
    board_show(game1->b);
    printf("\nAFTER (CW):\n");
    twist(game1, CW);
    board_show(game1->b);
    printf("\nAFTER (CCW *2):\n");
    printf("Remark: (*2) above means the specified rotation was\n");
    printf("applied twice, such that the original matrix was rotated ");
    printf("only once.\n");
    twist(game1, CCW);
    twist(game1, CCW);
    board_show(game1->b);

    printf("\nBEFORE:\n");
    board_show(game2->b);
    printf("\nAFTER (CW):\n");
    twist(game2, CW);
    board_show(game2->b);
    printf("\nAFTER (CCW):\n");
    printf("Remark: the above remark does not hold for this ");
    printf("(or the subsequent) tests.\n");
    game_free(game2);
    game2 = new_game(7, 8, 12, BITS);
    board_set(game2->b, make_pos(11, 0), BLACK);
    board_set(game2->b, make_pos(11, 2), WHITE);
    twist(game2, CCW);
    board_show(game2->b);

    printf("\nBEFORE:\n");
    board_show(game3->b);
    printf("\nAFTER (CW):\n");
    twist(game3, CW);
    board_show(game3->b);
    printf("\nAFTER (CCW):\n");
    game_free(game3);
    game3 = new_game(3, 9, 7, BITS);
    board_set(game3->b, make_pos(6, 0), BLACK);
    board_set(game3->b, make_pos(5, 0), WHITE);
    twist(game3, CCW);
    board_show(game3->b);

    printf("\nBEFORE:\n");
    board_show(game4->b);
    printf("\nAFTER (CW):\n");
    twist(game4, CW);
    board_show(game4->b);
    printf("\nAFTER (CCW):\n");
    game_free(game4);
    game4 = new_game(3, 5, 6, BITS);
    board_set(game4->b, make_pos(5, 0), BLACK);
    board_set(game4->b, make_pos(4, 0), WHITE);
    board_set(game4->b, make_pos(5, 3), WHITE);
    board_set(game4->b, make_pos(4, 3), BLACK);
    board_set(game4->b, make_pos(3, 3), BLACK);
    board_set(game4->b, make_pos(2, 3), BLACK);
    twist(game4, CCW);
    board_show(game4->b);

    game_free(game1);
    game_free(game2);
    game_free(game3);
    game_free(game4);

    printf("\n THE VISUAL TESTS PASSED!\n\n");
}

/* evidence_game_outcome : test game_outcome */
void evidence_game_outcome()
{
    printf("\n*** testing game_outcome\n");
    printf("- visual (eyeball) tests below:\n");

    /* horizontal fail */
    game* game1 = new_game(4, 5, 10, BITS);
    printf("- expecting 0 (Boolean false): %d\n",
    (game_outcome(game1) == BLACK_WIN));
    printf("- expecting 0 (Boolean false): %d\n",
    (game_outcome(game1) == WHITE_WIN));
    printf("- expecting 0 (Boolean false): %d\n",
    (game_outcome(game1) == DRAW));
    printf("- expecting nonzero integer (Boolean true): %d\n",
    (game_outcome(game1) == IN_PROGRESS));

    /* horizontal win */
    game* game4 = new_game(3, 5, 6, BITS);
    board_set(game4->b, make_pos(5, 0), BLACK);
    board_set(game4->b, make_pos(4, 0), WHITE);
    board_set(game4->b, make_pos(5, 3), WHITE);
    board_set(game4->b, make_pos(4, 3), BLACK);
    board_set(game4->b, make_pos(3, 3), BLACK);
    board_set(game4->b, make_pos(2, 3), BLACK);
    twist(game4, CW);
    printf("- expecting nonzero integer (Boolean true): %d\n",
    (game_outcome(game4) == BLACK_WIN));

    /* added vertical win */
    game_free(game4);
    game4 = new_game(3, 5, 6, BITS);
    board_set(game4->b, make_pos(5, 0), BLACK);
    board_set(game4->b, make_pos(4, 0), WHITE);
    board_set(game4->b, make_pos(5, 3), WHITE);
    board_set(game4->b, make_pos(4, 3), BLACK);
    board_set(game4->b, make_pos(3, 3), BLACK);
    board_set(game4->b, make_pos(2, 3), BLACK);
    printf("- expecting nonzero integer (Boolean true): %d\n",
    (game_outcome(game4) == BLACK_WIN));
    printf("- expecting 0 (Boolean false): %d\n",
    (game_outcome(game4) == WHITE_WIN));
    printf("- expecting 0 (Boolean false): %d\n",
    (game_outcome(game4) == IN_PROGRESS));
    printf("- expecting 0 (Boolean false): %d\n",
    (game_outcome(game4) == DRAW));

    /* no wins, in progress */
    game* game3 = new_game(3, 9, 7, BITS);
    board_set(game3->b, make_pos(6, 0), BLACK);
    board_set(game3->b, make_pos(6, 0), WHITE);
    printf("- expecting nonzero integer (Boolean true): %d\n",
    (game_outcome(game3) == IN_PROGRESS));
    printf("- expecting 0 (Boolean false): %d\n",
    (game_outcome(game3) == BLACK_WIN));
    printf("- expecting 0 (Boolean false): %d\n",
    (game_outcome(game3) == WHITE_WIN));
    printf("- expecting 0 (Boolean false): %d\n",
    (game_outcome(game3) == DRAW));

    /* diagonal draw example */
    game_free(game4);
    game4 = new_game(2, 5, 6, BITS);
    board_set(game4->b, make_pos(5, 0), BLACK);
    board_set(game4->b, make_pos(4, 0), WHITE);
    board_set(game4->b, make_pos(5, 3), WHITE);
    board_set(game4->b, make_pos(4, 3), BLACK);
    board_set(game4->b, make_pos(3, 3), BLACK);
    board_set(game4->b, make_pos(2, 3), BLACK);
    twist(game4, CCW);
    printf("- expecting nonzero integer (Boolean true): %d\n",
    (game_outcome(game4) == DRAW));

    /* diagonal draw example */
    game_free(game4);
    game4 = new_game(2, 5, 6, BITS);
    board_set(game4->b, make_pos(5, 0), BLACK);
    board_set(game4->b, make_pos(4, 0), WHITE);
    board_set(game4->b, make_pos(5, 3), WHITE);
    board_set(game4->b, make_pos(4, 3), BLACK);
    board_set(game4->b, make_pos(3, 3), BLACK);
    board_set(game4->b, make_pos(2, 3), BLACK);
    twist(game4, CW);
    printf("- expecting nonzero integer (Boolean true): %d\n",
    (game_outcome(game4) == DRAW));

    printf("\n-Test for the sample matrix (board) below ");
    printf("(WHITE_WIN):\n");
    printf("(run = 2 in this case)\n");
    game* game2 = new_game(2, 8, 12, BITS);
    board_set(game2->b, make_pos(11, 0), BLACK);
    board_set(game2->b, make_pos(11, 2), WHITE);
    twist(game2, CCW);
    board_set(game2->b, make_pos(7, 10), WHITE);
    board_show(game2->b);
    printf("- expecting nonzero integer (Boolean true): %d\n",
    (game_outcome(game2) == WHITE_WIN));

    game_free(game1);
    game_free(game2);
    game_free(game3);
    game_free(game4);
}

/* main : run the evidence functions above (tests) */
int main(int argc, char *argv[])
{
    printf("CS 152 Project, Downturn Game\n");
    evidence_make_pos();
    evidence_board_new();
    evidence_board_show();
    evidence_board_get();
    evidence_board_set();
    evidence_new_game();
    evidence_drop_piece();
    evidence_twist();
    evidence_game_outcome();
    return 0;
}
