#include "waitqueue.h"

explicit WaitQueue::WaitQueue() : jobs(INITIAL_SIZE) { }

/* insert : pushes a job onto the wait queue
 * Parameters:
 * 	(Job*) job : job to insert */

void WaitQueue::insert(Job* job) {
	if (job != NULL)
		jobs.push(job);
}

/* getJob : returns a job that can run with current processor pool, and removes
 *         it from the queue.
 * Parameters:
 * 	(integer) n_procs_available : number of free processors in the pool
 * Returns: Job* : pointer to a job whose processor requirements are less than
 *                equal to the current available processors. */

#include <list>
Job* WaitQueue::getJob(unsigned short n_procs_available) {
	std::list<Job*> popped_jobs;
	Job* job;

	// iterate through jobs until we find one that can run with current
	// available processors
	while (!jobs.empty) {
		job = jobs.top();

		if (job->n_procs <= n_procs_available) {
			// replace popped jobs
			while (!popped_jobs.empty()) {
				jobs.push(popped_jobs.back());
				popped_jobs.pop_back();
			}

			return job;
		}

		popped_jobs.push_back(job);
		jobs.pop();
	}

	// no job available to run
	while (!popped_jobs.empty()) {
		jobs.push(popped_jobs.back());
		popped_jobs.pop_back();
	}

	return NULL;
}

