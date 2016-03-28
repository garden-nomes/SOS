CC = cc
COPS =-D_GNU_SOURCE
LINT = splint
LOPS = -x -u
REENT = -D_REENTRANT

all: argtest

argtest: argtest.c makeargv.c
	$(CC) $(COPS) -o argtest argtest.c makeargv.c


lintall: lintargtest

lintargtest:
	$(LINT) $(LOPS) argtest.c makeargv.c

clean:
	rm -f *.o core wordaveragetest wordaveragetestbad bubblesorttest keeplog largearray largearrayinit showtimes environ argtest argtestfree getpathstest showtimestest


