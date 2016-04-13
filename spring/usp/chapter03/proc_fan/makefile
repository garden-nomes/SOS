CC = cc
COPS = -D_GNU_SOURCE -g

all: runsim testsim

runsim: runsim.c
	$(CC) $(COPS) -o runsim runsim.c restart.c

testsim: testsim.c
	$(CC) $(COPS) -o testsim testsim.c

clean:
	rm -rf *.o runsim testsim