#ifndef WAITQUEUE_H
#define WAITQUEUE_H

#include <queue>
#include <vector>
#include "job.h"

#define INITIAL_SIZE = 16

class JobCompare {
	public:
		bool operator(const Job* a, const Job* b) {
			return a->n_ticks < b->n_ticks;
		}
};


class WaitQueue {
	public:
		explicit WaitQueue() { }
		
		void insert(Job* job);
		Job* getJob(const unsigned short n_procs_available);

	private:
		std::priority_queue<Job*, std::vector, JobCompare> jobs;
};

#endif
