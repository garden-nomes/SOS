Summary
=======

I built a scheduler that takes either interactive input or a list of jobs in csv format, and a processor count.  It then uses a shortest process next (SPN) scheduling algorithm with gang scheduling (all threads for a process run simultaneously) over a series of 'ticks' (abstract time quantums) until all the user quits (interactive mode) or all processes have finished (csv mode).

Design
------

The project consists of five class:
- **Job** - The fundamental resource of the scheduler, essentially a struct holding an id, description, processor requirement, and ticks to completion. Supports tick() (decrements ticks to completion) and isDone() (returns whether job has finished), as well as accessors for all fields.
- **RunQueue** - Maintains a list of processors as an array of Job pointers. Jobs can occupy multiple elements of the array, as each element of the array abstractly represents a processor.
- **WaitQueue** - Maintains a list of jobs waiting to run using the standard library's priority queue. However, the priority queue structure doesn't support iteration, so in order to find a job that can run using the current number of free processors, it uses a temporary stack (from the standard library) and pops jobs from the queue onto the stack, so it can re-push those jobs afterwards. A possible improvement on this design would be to maintain seperate queues for different job thread counts.
- **Scheduler** - Ties together RunQueue and WaitQueue, allows for submitting jobs and places them on either the RunQueue or WaitQueue.
- **Driver** - Handles simulation logic, including taking input from the user or loading a csv file.

Sample Output
-------------

jobs.csv:
```
0,job,2,4,
1,jobber,1,8,
1,another job,3,9,
3,jobly,2,6,
5,working hard,2,6,
5,its a job,1,2,
8,jobbest,3,2,
```

output:
```
$ ./project jobs.csv 4
Data Structures, Student Originated Software (Winter 2016)
Noah Weiner's

                   _______  __   __  _______  _______  ______
                  |       ||  | |  ||       ||       ||    _ |
                  |  _____||  | |  ||    _  ||    ___||   | ||
                  | |_____ |  |_|  ||   |_| ||   |___ |   |_||_
                  |_____  ||       ||    ___||    ___||    __  |
                   _____| ||       ||   |    |   |___ |   |  | |
                  |_______||_______||___|    |_______||___|  |_|
 _______  _______  __   __  _______  ______   __   __  ___      _______  ______
|       ||       ||  | |  ||       ||      | |  | |  ||   |    |       ||    _ |
|  _____||       ||  |_|  ||    ___||  _    ||  | |  ||   |    |    ___||   | ||
| |_____ |       ||       ||   |___ | | |   ||  |_|  ||   |    |   |___ |   |_||
|_____  ||      _||       ||    ___|| |_|   ||       ||   |___ |    ___||    __  |
 _____| ||     |_ |   _   ||   |___ |       ||       ||       ||   |___ |   |  | |
|_______||_______||__| |__||_______||______| |_______||_______||_______||___|  |_|

opening jobs.csv for csv input... std::exception
done
creating scheduler with 4 processors... done


 round 0 -----------------------------------------------------
-> Job entered: job, needing 2 processors for 4 ticks.
Run Queue:
	[job]	[job]	[none]	[none]
Wait Queue:
	(empty)


 round 1 -----------------------------------------------------
-> Job entered: jobber, needing 1 processors for 8 ticks.
-> Job entered: another job, needing 3 processors for 9 ticks.
Run Queue:
	[job]	[job]	[jobber]	[none]
Wait Queue:
	0: another job


 round 2 -----------------------------------------------------
Run Queue:
	[job]	[job]	[jobber]	[none]
Wait Queue:
	0: another job


 round 3 -----------------------------------------------------
-> Job entered: jobly, needing 2 processors for 6 ticks.
Run Queue:
	[job]	[job]	[jobber]	[none]
Wait Queue:
	0: another job	1: jobly


 round 4 -----------------------------------------------------
Run Queue:
	[another job]	[another job]	[jobber]	[another job]
Wait Queue:
	0: jobly


 round 5 -----------------------------------------------------
-> Job entered: working hard, needing 2 processors for 6 ticks.
-> Job entered: its a job, needing 1 processors for 2 ticks.
Run Queue:
	[another job]	[another job]	[jobber]	[another job]
Wait Queue:
	0: jobly	1: working hard	2: its a job


 round 6 -----------------------------------------------------
Run Queue:
	[another job]	[another job]	[jobber]	[another job]
Wait Queue:
	0: working hard	1: jobly	2: its a job


 round 7 -----------------------------------------------------
Run Queue:
	[another job]	[another job]	[jobber]	[another job]
Wait Queue:
	0: jobly	1: working hard	2: its a job


 round 8 -----------------------------------------------------
-> Job entered: jobbest, needing 3 processors for 2 ticks.
Run Queue:
	[another job]	[another job]	[jobber]	[another job]
Wait Queue:
	0: working hard	1: jobly	2: its a job	3: jobbest


 round 9 -----------------------------------------------------
Run Queue:
	[another job]	[another job]	[its a job]	[another job]
Wait Queue:
	0: working hard	1: jobly	2: jobbest


 round 10 -----------------------------------------------------
Run Queue:
	[another job]	[another job]	[its a job]	[another job]
Wait Queue:
	0: jobly	1: working hard	2: jobbest


 round 11 -----------------------------------------------------
Run Queue:
	[another job]	[another job]	[its a job]	[another job]
Wait Queue:
	0: working hard	1: jobly	2: jobbest


 round 12 -----------------------------------------------------
Run Queue:
	[another job]	[another job]	[none]	[another job]
Wait Queue:
	0: working hard	1: jobly	2: jobbest


 round 13 -----------------------------------------------------
Run Queue:
	[another job]	[another job]	[none]	[another job]
Wait Queue:
	0: jobly	1: working hard	2: jobbest


 round 14 -----------------------------------------------------
Run Queue:
	[working hard]	[working hard]	[none]	[none]
Wait Queue:
	0: jobly	1: jobbest


 round 15 -----------------------------------------------------
Run Queue:
	[working hard]	[working hard]	[none]	[none]
Wait Queue:
	0: jobly	1: jobbest


 round 16 -----------------------------------------------------
Run Queue:
	[working hard]	[working hard]	[none]	[none]
Wait Queue:
	0: jobly	1: jobbest


 round 17 -----------------------------------------------------
Run Queue:
	[working hard]	[working hard]	[none]	[none]
Wait Queue:
	0: jobly	1: jobbest


 round 18 -----------------------------------------------------
Run Queue:
	[working hard]	[working hard]	[none]	[none]
Wait Queue:
	0: jobly	1: jobbest


 round 19 -----------------------------------------------------
Run Queue:
	[working hard]	[working hard]	[none]	[none]
Wait Queue:
	0: jobly	1: jobbest


 round 20 -----------------------------------------------------
Run Queue:
	[working hard]	[working hard]	[none]	[none]
Wait Queue:
	0: jobly	1: jobbest


 round 21 -----------------------------------------------------
Run Queue:
	[jobly]	[jobly]	[none]	[none]
Wait Queue:
	0: jobbest


 round 22 -----------------------------------------------------
Run Queue:
	[jobly]	[jobly]	[none]	[none]
Wait Queue:
	0: jobbest


 round 23 -----------------------------------------------------
Run Queue:
	[jobly]	[jobly]	[none]	[none]
Wait Queue:
	0: jobbest


 round 24 -----------------------------------------------------
Run Queue:
	[jobly]	[jobly]	[none]	[none]
Wait Queue:
	0: jobbest


 round 25 -----------------------------------------------------
Run Queue:
	[jobly]	[jobly]	[none]	[none]
Wait Queue:
	0: jobbest


 round 26 -----------------------------------------------------
Run Queue:
	[jobly]	[jobly]	[none]	[none]
Wait Queue:
	0: jobbest


 round 27 -----------------------------------------------------
Run Queue:
	[jobly]	[jobly]	[none]	[none]
Wait Queue:
	0: jobbest


 round 28 -----------------------------------------------------
Run Queue:
	[jobbest]	[jobbest]	[jobbest]	[none]
Wait Queue:
	(empty)


 round 29 -----------------------------------------------------
Run Queue:
	[jobbest]	[jobbest]	[jobbest]	[none]
Wait Queue:
	(empty)


 round 30 -----------------------------------------------------
Run Queue:
	[jobbest]	[jobbest]	[jobbest]	[none]
Wait Queue:
	(empty)


 round 31 -----------------------------------------------------
Run Queue:
	[none]	[none]	[none]	[none]
Wait Queue:
	(empty)


 round 32 -----------------------------------------------------
Run Queue:
	[none]	[none]	[none]	[none]
Wait Queue:
	(empty)
Thanks, bye...
```
