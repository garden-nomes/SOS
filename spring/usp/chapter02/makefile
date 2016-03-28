CC = cc
COPS =-D_GNU_SOURCE
LINT = splint
LOPS = -x -u
REENT = -D_REENTRANT

all: argtest environ

argtest: argtest.c makeargv.c
	$(CC) $(COPS) -o argtest argtest.c makeargv.c

environ: environ.c
	$(CC) $(COPS) -o environ environ.c

lintall: lintargtest

lintargtest:
	$(LINT) $(LOPS) argtest.c makeargv.c

lintenviron:
	$(LINT) $(LOPS) environ.c

clean:
	rm -f *.o core wordaveragetest wordaveragetestbad bubblesorttest keeplog largearray largearrayinit showtimes environ argtest argtestfree getpathstest showtimestest


