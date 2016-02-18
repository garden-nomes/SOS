#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>
#include <string>
#include <map>
#include <thread>
#include <chrono>
#include <fstream>
#include "types.h"
#include "scheduler.h"

using namespace std;

/**
 * Noah Weiner, Sudent Originated Software Data Structures Winter 2016 presents:
 */

string title =
"Data Structures, Student Originated Software (Winter 2016)\n"
"Noah Weiner's\n\n"
"                   _______  __   __  _______  _______  ______\n"
"                  |       ||  | |  ||       ||       ||    _ |\n"
"                  |  _____||  | |  ||    _  ||    ___||   | ||\n"
"                  | |_____ |  |_|  ||   |_| ||   |___ |   |_||_\n"
"                  |_____  ||       ||    ___||    ___||    __  |\n"
"                   _____| ||       ||   |    |   |___ |   |  | |\n"
"                  |_______||_______||___|    |_______||___|  |_|\n"
" _______  _______  __   __  _______  ______   __   __  ___      _______  ______ \n"
"|       ||       ||  | |  ||       ||      | |  | |  ||   |    |       ||    _ |\n"
"|  _____||       ||  |_|  ||    ___||  _    ||  | |  ||   |    |    ___||   | ||\n"
"| |_____ |       ||       ||   |___ | | |   ||  |_|  ||   |    |   |___ |   |_||\n"
"|_____  ||      _||       ||    ___|| |_|   ||       ||   |___ |    ___||    __  |\n"
" _____| ||     |_ |   _   ||   |___ |       ||       ||       ||   |___ |   |  | |\n"
"|_______||_______||__| |__||_______||______| |_______||_______||_______||___|  |_|\n\n";

class Driver {
public:
	void execute(string fname = "");

private:
	Scheduler* scheduler;
	string last_command;
	bool interactive_mode;
	multimap<uint32, Job*> jobs;
	uint32 ticks;
	uint32 end;

	void initialize(string fname);
	bool tick();
	void exit();
	bool getInput();
	void submitJob();
	void printHelp();
};


#endif
