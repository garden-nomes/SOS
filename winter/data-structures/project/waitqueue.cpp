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

Job* WaitQueue::getJob(uint16 n_procs_available) {
	std::list<Job*> popped_jobs;	// maintain a list of checked jobs
	Job* job;

	// iterate through jobs until we find one that can run with current
	// available processors
	while (!jobs.empty()) {
		job = jobs.top();
		jobs.pop();

		if (job->processors() <= n_procs_available) {
			// replace popped jobs
			while (!popped_jobs.empty()) {
				jobs.push(popped_jobs.back());
				popped_jobs.pop_back();
			}

			return job;
		} else {
			popped_jobs.push_back(job);
		}
	}

	// no job available to run
	while (!popped_jobs.empty()) {
		jobs.push(popped_jobs.back());
		popped_jobs.pop_back();
	}

	return NULL;
}

/**
 * printState: displays the current wait queue
 * Parameters:
 *   (ostream&) os : output stream to print to
 */
void WaitQueue::printState(std::ostream& os = std::cout) {
	if (!jobs.empty()) {
		std::list<Job*> popped_jobs;
		Job* job;

		for (int i = 0; !jobs.empty(); ++i) {
			job = jobs.top();
			os << "\t" << i << ": " << job->description();
			popped_jobs.push_back(job);
			jobs.pop();
		}

		while (!popped_jobs.empty()) {
			jobs.push(popped_jobs.back());
			popped_jobs.pop_back();
		}
	} else {
		os << "\t(empty)";
	}

	os << std::endl;
}

/**
 * empty
 * Returns (bool) : whether wait queue is empty
 */
bool WaitQueue::empty() const {
	return jobs.empty();
}
