#include "driver.h"

void Driver::execute() {
	initialize();
	while (tick()) { scheduler->printState(); }
	exit();
}

void Driver::initialize() {
	uint16 processors;

	// create scheduler
	cout << title;
	cout << "enter number of processors: ";
	cin >> processors;
	cout << "creating scheduler with " << processors << " processors..." << endl;
	scheduler = new Scheduler(processors);
}

bool Driver::tick() {
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
		return tick();
	case 'h':
		printHelp();
		return tick();
	case 'n':
		return true;
	case 'q':
		return false;
	default:
		cout << "unrecognized command: " << input << endl;
		return tick();
	}
}

void Driver::exit() {
	cout << "Thanks, bye.................." << endl;
	delete scheduler;
}

void Driver::submitJob() {
	string description;
	uint16 processors;
	uint32 ticks;

	cout << "enter process name: ";
	cin >> description;
	
	cout << "enter number of processors the job needs to run: ";
	cin >> processors;

	cout << "enter number of ticks the job will take to complete: ";
	cin >> ticks;

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
	driver.execute();
}
