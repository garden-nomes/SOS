#ifndef WAITQUEUE_H
#define WAITQUEUE_H

#include <queue>
#include <list>
#include <string>
#include <iostream>
#include "types.h"
#include "job.h"

class WaitQueue {
	public:
		~WaitQueue();
		
		void insert(Job* job);
		Job* getJob(uint16 n_procs_available);
		void printState(std::ostream& os);
		bool empty() const;

	private:

		// compare jobs on remaining ticks
		class JobCompare {
			public:
				bool operator()(const Job* a, const Job* b) {
					return a->ticks() < b->ticks();
				}
		};

		std::priority_queue<Job*, std::vector<Job*>, JobCompare> jobs;
};

#endif
