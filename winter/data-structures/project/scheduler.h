#ifndef SCHEDULER_H
#define SCHEDULER_H

class Scheduler {
	public:
		Scheduler();

		void Tick();
		void SubmitJob(string job_desc, unsigned short n_procs,
				unsigned n_ticks);

	private:
		WaitQueue waitQueue;
};

#endif
