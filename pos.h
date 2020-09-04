#ifndef POS_H
#define POS_H


/* struct pos: represents a location on the game board (row & column, r & c) */
struct pos {
    unsigned int r, c;
};


/* pos: typedef for struct pos */
typedef struct pos pos;


/* make_pos: given a row number and a column number, creates and returns
a pos value */
pos make_pos(unsigned int r, unsigned int c);


#endif /* POS_H */
