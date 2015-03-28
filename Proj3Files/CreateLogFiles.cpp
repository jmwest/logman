//
//  CreateLogFiles.cpp
//  EECS 281 Project 3
//
//  Created by John West on 3/27/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#include "CreateLogFiles.h"

#include <iostream>
#include <getopt.h>
#include <cstdlib>
#include <string>

string make_time_stamp();
string make_category();
string make_message();

int main(int argc, char *argv[]) {

	ofstream log_stream, cmnd_stream;
	ostringstream log_ss, cmnd_ss;

	int log_size = 0;
	int cmnd_size = 0;

	parse_command_line_input(argc, argv, log_stream, cmnd_stream, log_size, cmnd_size);

	make_log_file(log_ss, log_size);

	log_stream << log_ss.str();

	make_cmnd_file(cmnd_ss, log_size, cmnd_size);

	cmnd_stream << cmnd_ss.str();

	return 0;
}

void parse_command_line_input(int & argc, char *argv[], ofstream &log_stream, ofstream &cmnd_stream, int &log_size, int &cmnd_size) {
	static struct option longopts[] = {
		{"log",				required_argument,		NULL, 'l'},
		{"cmnd",			required_argument,		NULL, 'c'},
		{"log-size",		required_argument,		NULL, 's'},
		{"cmnd-size",		required_argument,		NULL, 'r'},
		{NULL,				0,						NULL, 0},
	};
	int idx = 0;
	char c;

	// Use getopt to parse through command line input
	while ((c = getopt_long(argc, argv, "l:c:s:r:", longopts, &idx)) != -1) {
		switch (c) {
			case 'l':
				if (!log_stream.is_open()) {
					log_stream.open(optarg);
				}
				else {
					cerr << "Error: You entered multiple log file names.\n";
					exit(1);
				}
				break;

			case 'c':
				if (!cmnd_stream.is_open()) {
					cmnd_stream.open(optarg);
				}
				else {
					cerr << "Error: You entered multiple cmnd file names.\n";
					exit(1);
				}
				break;

			case 's':
				if (!log_size) {
					log_size = atoi(optarg);
				}
				else {
					cerr << "Error: You entered multiple log sizes.\n";
					exit(1);
				}
				break;

			case 'r':
				if (!cmnd_size) {
					cmnd_size = atoi(optarg);
				}
				else {
					cerr << "Error: You entered multiple cmnd sizes.\n";
					exit(1);
				}
				break;

			default:
				break;
		} // switch
	} // while

	if (!log_stream.is_open()) {
		static const char* log_name = "log_file_out.txt";
		log_stream.open(log_name);
	}

	if (!cmnd_stream.is_open()) {
		static const char* cmnd_name = "cmnd_file_out.txt";
		cmnd_stream.open(cmnd_name);
	}

	if (!log_size) {
		log_size = 100000;
	}

	if (!log_size) {
		log_size = 1000;
	}

	return;
}

void make_log_file(ostringstream &log_ss, int &log_size) {

	for (int i = 0; i < log_size; ++i) {
		log_ss << make_time_stamp();

		log_ss << '|';

		log_ss << make_category() << '|';

		log_ss << make_message() << "\n";
	}

	return;
}

void make_cmnd_file(ostringstream &cmnd_ss, int &log_size, int &cmnd_size) {

	for (int i = 0; i < cmnd_size - 1; ++i) {
		int command = rand() % 12;

		switch (command) {
			case 0: {
				string one = make_time_stamp();
				string two;

				while (true) {
					two = make_time_stamp();

					if (one < two) {
						break;
					}
				}

				cmnd_ss << "t " << one << '|' << two;
				break;
			}
			case 1:
				cmnd_ss << "c " << make_category();
				break;

			case 2:
				cmnd_ss << "k " << make_message();
				break;

			case 3:
				cmnd_ss << "i " << rand() % log_size;
				break;

			case 4:
				cmnd_ss << 'r';
				break;

			case 5:
				cmnd_ss << "d " << rand() % log_size;
				break;

			case 6:
				cmnd_ss << "b " << rand() % log_size;
				break;

			case 7:
				cmnd_ss << "e " << rand() % log_size;
				break;

			case 8:
				cmnd_ss << 's';
				break;

			case 9:
				cmnd_ss << 'l';
				break;

			case 10:
				cmnd_ss << 'g';
				break;

			case 11:
				cmnd_ss << 'p';
				break;

			default:
				break;
		}

		cmnd_ss << "\n";
	}

	cmnd_ss << 'q';

	return;
}

string make_time_stamp() {

	string time;

	for (int j = 0; j < 5; ++j) {
		int t = rand() % 100;
		char t1, t2;
		
		if (t < 10) {
			t1 = '0';
			t2 = t + 48;
		}
		else {
			t1 = (t / 10) + 48;
			t2 = (t % 10) + 48;
		}
		
		time.push_back(t1);
		time.push_back(t2);
		
		if (j < 4) {
			time.push_back(':');
		}
	}

	return time;
}

string make_category() {

	static const char* cat_start = "Crumpety";

	int cat_size = rand() % 5;
	string cat = cat_start;
	
	for (int k = 0; k < cat_size; ++k) {
		char ins = (rand() % 95) + 32;
		
		if (ins == '|') {
			ins = '~';
		}
		
		cat.insert(cat.begin() + (rand() % cat.length()), ins);
	}

	return cat;
}

string make_message() {

	static const char* mess_start = "Thesecrumpets areyummy";

	int mess_size = 1 + (rand() % 17);
	string mess = mess_start;

	for (int l = 0; l < mess_size; ++l) {
		char ins = (rand() % 95) + 32;

		if (ins == '|') {
			ins = '~';
		}

		mess.insert(mess.begin() + (rand() % mess.length()), ins);
	}

	return mess;
}

