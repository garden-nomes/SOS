#include "scheduler.h"

Scheduler::Scheduler(uint16 processors) : waitQueue(), runQueue(processors), max_id(0)
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
	Job* job = new Job(max_id++, description, processors, ticks);
	// if job is immediatly runnable, we can skip the waitqueue
	// NOTE: this version is non-preemptive: any job that can run already will have run
	// during tick()
	if (processors <= runQueue.freeProcessors())
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
	for (auto itr : runQueue.processors())
		os << "\t[" << itr->description() << "]";
	os << std::endl;
}
