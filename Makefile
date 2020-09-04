all: downturn tests

downturn: pos.h pos.c board.h board.c logic.h logic.c play.c
	clang -Wall -g -O0 -o downturn pos.c board.c logic.c play.c

tests: pos.h pos.c board.h board.c logic.h logic.c evidence.c
	clang -Wall -g -O0 -o tests pos.c board.c logic.c evidence.c

clean:
	rm -f downturn tests
