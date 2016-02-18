#ifndef JOB_H
#define JOB_H

#include <string>
#include "types.h"

class Job {
	public:
		explicit Job(std::string description,
				uint16 processors, uint32 ticks);

		void tick();

		bool done() const;
		uint32 id() const;
		std::string description() const;
		uint16 processors() const;
		uint32 ticks() const;

		static uint32 max_id;

	private:
		uint32 j_id;
		std::string j_desc;
		uint16 j_procs;
		uint32 j_ticks;
};

#endif
