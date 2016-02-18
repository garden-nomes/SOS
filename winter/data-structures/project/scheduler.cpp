#include "scheduler.h"

Scheduler::Scheduler(uint16 processors) : waitQueue(), runQueue(processors)
{ }

/**
 * tick: calls tick on runQueue, submits new job if it can
 */
void Scheduler::tick() {
	if (runQueue.tick()) {
		// pop job off waitQueue and add to runQueue
		Job* job = waitQueue.getJob(runQueue.freeProcessors());
		if (job != NULL)
			runQueue.runJob(job);
	}
}

/**
 * submitJob: adds a job to the wait queue.
 * Parameters
 *   (string) description : description of the job for display
 *   (uint16) processors : number of processors the job needs
 *   (uint32) ticks : number of ticks the job will take to complete
 */
void Scheduler::submitJob(std::string description, uint16 processors, uint32 ticks) {
	Job* job = new Job(description, processors, ticks);
	submitJob(job);
}

/**
 * submitJob: same as above, takes a pointer
 * Parameters
 *   (Job*) job : pointer to job to insert
 */
void Scheduler::submitJob(Job* job) {
	// if job is immediatly runnable, we can skip the waitqueue
	// NOTE: this version is non-preemptive: any job that can run already will have run
	// during tick()
	if (job->processors() <= runQueue.freeProcessors())
		runQueue.runJob(job);
	else
		waitQueue.insert(job);
}

/**
 * printState: prints out a visual representation of the scheduler's current state,
 *             including waitQueue and runQueue.
 * Parameters
 *   os (std::ostream&) : output stream to write to, defaults to cout
 */
void Scheduler::printState(std::ostream& os) {
	os << "Run Queue:" << std::endl;
	runQueue.printState(os);
	os << "Wait Queue:" << std::endl;
	waitQueue.printState(os);
}

/**
 * empty
 * Returns (bool) : whether runQueue and waitQueue are empty
 */
bool Scheduler::empty() {
	return runQueue.empty() && waitQueue.empty();
}
