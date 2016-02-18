#ifndef JOB_H
#define JOB_H

#include <string>
#include "types.h"

class Job {
	public:
		explicit Job(uint32 id, std::string description,
				uint16 processors, uint32 ticks);

		void tick();

		bool done() const;
		uint32 id() const;
		std::string description() const;
		uint16 processors() const;
		uint32 ticks() const;

	private:
		uint16 j_procs;
		uint32 j_id, j_ticks;
		std::string j_desc;
};

#endif
