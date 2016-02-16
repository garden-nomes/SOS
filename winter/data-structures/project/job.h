#ifndef JOB_H
#define JOB_H

class Job {
	public:
		explicit Job(unsigned job_id, std::string job_desc,
				unsigned short n_job_procs, unsigned n_job_ticks) :
			id{job_id}, desc{job_desc}, n_procs{n_job_procs},
			n_ticks{n_job_ticks} { }

		unsigned id;
		std::string desc;
		unsigned short n_procs;
		unsigned n_ticks;

		bool done();
		void tick();
};

#endif
