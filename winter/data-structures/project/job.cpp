#include "job.h"

uint32 Job::max_id = 0;

Job::Job(std::string description, uint16 processors, uint32 ticks) :
	j_id(max_id++), j_desc(description), j_procs(processors), j_ticks(ticks)
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
	if (j_ticks > 0)
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
