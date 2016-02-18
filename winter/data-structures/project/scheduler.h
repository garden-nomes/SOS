#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string>
#include <iostream>
#include "types.h"
#include "waitqueue.h"
#include "runqueue.h"

class Scheduler {
	public:
		Scheduler(uint16 processors);

		void tick();
		void submitJob(std::string description, uint16 processors, uint32 ticks);
		void printState(std::ostream& os = std::cout);

	private:
		WaitQueue waitQueue;
		RunQueue runQueue;
		uint32 max_id;
};

#endif
