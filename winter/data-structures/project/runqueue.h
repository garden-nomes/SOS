#ifndef RUNQUEUE_H
#define RUNQUEUE_H

#include "job.h"
#include <vector>

class RunQueue {
	public:
		RunQueue(unsigned short n_procs);

		void Tick();
		void runJob(Job* job);
		unsigned short getFreeProcs() const;

	private:
		unsigned short n_procs;
		unsigned short n_procs_used;
		vector<Job*> jobs;
};

#endif
