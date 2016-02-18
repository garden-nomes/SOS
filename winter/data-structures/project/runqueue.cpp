#include "runqueue.h"

RunQueue::RunQueue(uint16 processors) : n_procs(processors), n_procs_used(0) {
	jobs = new Job*[processors];
	for (int i = 0; i < n_procs; ++i)
		jobs[i] = NULL;
}

RunQueue::~RunQueue() {
	delete[] jobs;
}

/**
 * Tick: runs tick on all jobs, and frees up any completed jobs
 * Returns (bool) : whether any jobs completed
 */
#include <unordered_set>
bool RunQueue::tick() {
	bool completed = false;	// whether any job has completed this round
	std::unordered_set<Job*> ticked_jobs(n_procs);	// keep track of tick()ed jobs

	for (int i = 0; i < n_procs; i++) {
		// tick each job once regarless of how many processors it holds
		if (jobs[i] != NULL && ticked_jobs.find(jobs[i]) == ticked_jobs.end()) {
			ticked_jobs.insert(jobs[i]);

			if (jobs[i]->done()) {
				Job* job = jobs[i];
				for (int j = 0; j < n_procs; ++j) {
					if (jobs[j] == job)
						jobs[j] = NULL;
				}

				n_procs_used -= job->processors();
				delete job;
				completed = true;
			} else {
				jobs[i]->tick();
			}
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
 * printState: display processor state
 * Parameters:
 *   (ostream&) os : output stream to print to
 */
void RunQueue::printState(std::ostream& os) const {
	for (int i = 0; i < n_procs; ++i)
			os << "\t[" << (jobs[i] == NULL ? "none" : jobs[i]->description()) << "]";
	os << std::endl;
}

/**
 * empty
 * Returns (bool) : whether run queue is empty
 */
bool RunQueue::empty() const {
	for (int i = 0; i < n_procs; ++i) {
		if (jobs[i] != NULL)
			return false;
	}

	return true;
}
