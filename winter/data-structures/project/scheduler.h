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
		void submitJob(Job* job);
		void printState(std::ostream& os = std::cout);
		bool empty();

	private:
		WaitQueue waitQueue;
		RunQueue runQueue;
};

#endif
