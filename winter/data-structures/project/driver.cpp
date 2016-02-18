#include "driver.h"

void Driver::execute(string fname) {
	cout << title;

	initialize(fname);
	while (tick()) {
		cout << endl << " round " << ticks <<
			" -----------------------------------------------------" << endl;
		scheduler->tick();
		scheduler->printState();
		++ticks;
	}
	exit();
}

void Driver::initialize(string fname) {
	uint16 processors;
	string input;

	// read list of jobs from csv file
	if (!fname.empty()) {
		interactive_mode = true;

		ifstream infile;
		uint32 timing, j_ticks;
		uint16 j_processors;
		string j_description;

		cout << "opening " << fname << " for csv input... ";
		infile.open(fname);

		while (infile.good()) {
			try {
				// read timing
				getline(infile, input, ',');
				timing = stoul(input);
				// read job description
				getline(infile, j_description, ',');
				// read job processors
				getline(infile, input, ',');
				j_processors = stoul(input);
				// read job ticks
				getline(infile, input, ',');
				j_ticks = stoul(input);

				// calculate when to quit
				if (end < timing + ticks)
					end = timing + ticks;

				jobs.insert(make_pair(
					timing,
					new Job(j_description, j_processors, j_ticks)
				));
			} catch (exception e) {
				cout << e.what() << endl;
			}
		}

		cout << "done" << endl;
		processors = 4; // set arbitrarily for now
	} else {
		interactive_mode = false;

		// create scheduler
		cout << "enter number of processors: ";
		getline(cin, input);
		processors = stoul(input);
	}

	cout << "creating scheduler with " << processors << " processors... ";
	scheduler = new Scheduler(processors);
	cout << "done" << endl;

	ticks = 0;
}

bool Driver::tick() {
	if (interactive_mode) {
		// add any jobs scheduled for this round to the scheduler
		Job* job;
		auto ret = jobs.equal_range(ticks);
		for (auto itr = ret.first; itr != ret.second; ++itr) {
			job = itr->second;
			cout << "-> Job entered: " << job->description()
				<< ", needing " << job->processors()
				<< " processors for " << job->ticks() << " ticks." << endl;
			scheduler->submitJob(job);
		}

		// remove jobs from list
		jobs.erase(ticks);

		// pause for 1 second
		this_thread::sleep_for(chrono::seconds(1));

		// run until there's no more jobs
		return !jobs.empty() || !scheduler->empty();
	} else {
		return getInput();
	}
}

bool Driver::getInput() {
	string input;

	// take input
	cout << endl << "enter command (h for help): ";
	getline(cin, input);
	if (input.empty())
		input = last_command;
	else
		last_command = input;

	switch (input[0]) {
	case 'j':
		submitJob();
		return getInput();
	case 'h':
		printHelp();
		return getInput();
	case 'n':
		return true;
	case 'q':
		return false;
	default:
		cout << "unrecognized command: " << input << endl;
		return getInput();
	}
}

void Driver::exit() {
	cout << "Thanks, bye..." << endl;
	delete scheduler;
}

void Driver::submitJob() {
	string description;
	string input;
	uint16 processors;
	uint32 ticks;

	cout << "enter process name: ";
	getline(cin, description);
	
	cout << "enter number of processors the job needs to run: ";
	getline(cin, input);
	processors = stoul(input);

	cout << "enter number of ticks the job will take to complete: ";
	getline(cin, input);
	ticks = stoul(input);

	scheduler->submitJob(description, processors, ticks);
}

void Driver::printHelp() {
	string help = "commands:\n"
	              "  j - submit new job\n"
				  "  n - advance one tick\n"
	              "  q - quit\n"
	              "  h - print this help message\n"
				  "  [blank] - repeat last command\n";

	cout << help;
}

int main(int argc, char* argv[]) {
	Driver driver;
	if (argc < 2)
		driver.execute();
	else
		driver.execute(argv[1]);
}
