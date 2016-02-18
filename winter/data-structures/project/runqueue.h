#ifndef RUNQUEUE_H
#define RUNQUEUE_H

#include "job.h"
#include <vector>


class RunQueue {
	public:
		RunQueue(uint16 n_procs);
		~RunQueue();

		bool tick();
		void runJob(Job* job);
		uint16 freeProcessors() const;
		std::vector<Job*> processors() const;

	private:
		uint16 n_procs;
		uint16 n_procs_used;
		Job** jobs;
};

#endif
