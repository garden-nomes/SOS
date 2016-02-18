#include "job.h"

Job::Job(uint32 id, std::string description, uint16 processors, uint32 ticks) :
	j_desc(description), j_id(id), j_ticks(ticks), j_procs(processors)
{ }

/**
 * Returns (bool) : whether the job has completed
 */
bool Job::done() const {
	return j_ticks <= 0;
}

/**
 * tick: decrements the tick the counter
 */
void Job::tick() {
	--j_ticks;
}

/**
 * Returns (uint32) : the id of the job
 */
uint32 Job::id() const {
	return j_id;
}

/**
 * Returns (string) : a human-friendly description the the job
 */
std::string Job::description() const {
	return j_desc;
}

/**
 * Returns (uint16) : the number of processors the job needs to run
 */
uint16 Job::processors() const {
	return j_procs;
}

/**
 * Returns (uint32) : the number of ticks the job has left before completion
 */
uint32 Job::ticks() const {
	return j_ticks;
}
