#include "waitqueue.h"

WaitQueue::~WaitQueue() {
	while (!jobs.empty()) {
		delete jobs.top();
		jobs.pop();
	}
}

/**
 * insert: pushes a job onto the wait queue
 * Parameters:
 * 	(Job*) job : job to insert
 */
void WaitQueue::insert(Job* job) {
	if (job != NULL)
		jobs.push(job);
}

/**
 * getJob : returns a job that can run with current processor pool, and removes it from
 *          the queue.
 * Parameters:
 *   (integer) n_procs_available : number of free processors in the pool
 * Returns (Job*) : pointer to a job whose processor requirements are less than equal to the
 *                  current available processors.
 */

#include <list>
Job* WaitQueue::getJob(uint16 n_procs_available) {
	std::list<Job*> popped_jobs;	// maintain a list of checked jobs
	Job* job;

	// iterate through jobs until we find one that can run with current
	// available processors
	while (!jobs.empty()) {
		job = jobs.top();

		if (job->processors() <= n_procs_available) {
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
