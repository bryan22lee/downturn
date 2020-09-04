/* Downturn game implementation in C
 * Basically Connect 4 but with board rotations and gravity
 * Chanik Bryan Lee */

#include "pos.h"
#include <stdlib.h>
#include <stdio.h>

pos make_pos(unsigned int r, unsigned int c) {
    pos make; /* pos make = {r, c}; */
    make.r = r;
    make.c = c;
    return make;
}
