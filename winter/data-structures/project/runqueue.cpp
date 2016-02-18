#include "runqueue.h"

RunQueue::RunQueue(uint16 processors) : n_procs(processors), n_procs_used(0) {
	jobs = new Job*[processors];
}

RunQueue::~RunQueue() {
	delete[] jobs;
}

/**
 * Tick: runs tick on all jobs, and frees up any completed jobs
 * Returns (bool) : whether any jobs completed
 */
bool done(Job* job) { return job->done(); }
bool RunQueue::tick() {
	bool completed = false;

	for (int i = 0; i < n_procs; i++) {
		jobs[i]->tick();

		if (jobs[i]->done()) {
			// free up resources
			n_procs_used -= jobs[i]->processors();
			delete jobs[i];
			jobs[i] = NULL;
			completed = true;
		}
	}

	return completed;
}

#include <exception>
class ProcessorException : std::exception {
	virtual const char* what() {
		return "Not enough free processors";
	}
};

/**
 * runJob: add a job to the run queue. May throw ProcessorException if there aren't
 *         enough available processors.
 * Parameters:
 *   (Job*) job : pointer to the job to add to the queue.
 */
void RunQueue::runJob(Job* job) {
	if (n_procs_used + job->processors() <= n_procs) {
		uint16 procs_needed = job->processors();
		for (int i = 0; i < n_procs && procs_needed > 0; ++i) {
			if (jobs[i] == NULL) {
				jobs[i] = job;
				--procs_needed;
			}
		}
		n_procs_used += job->processors();
	} else {
		throw ProcessorException();
	}
}

/**
 * freeProcessors
 * Returns (uint16) : number of free processors
 */
uint16 RunQueue::freeProcessors() const {
	return n_procs - n_procs_used;
}

/**
 * processors
 * Returns (std::vector<Job*>) : list of processors, either NULL or pointing to their
 *                               currently processing job
 */
std::vector<Job*> RunQueue::processors() const {
	return std::vector<Job*>(jobs, jobs + n_procs);
}
