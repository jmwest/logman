//
//  logman.cpp
//  EECS 281 Project 3
//
//  Created by John West on 3/17/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#include "logman.h"

#include <iostream>
#include <getopt.h>

using namespace std;

int main(int argc, char *argv[]) {

	ifstream file_stream;

	parse_command_line_input(argc, argv, file_stream);



	return 0;
}

void parse_command_line_input(int & argc, char *argv[], ifstream &file_stream) {
	static struct option longopts[] = {
		{"help",			no_argument,		NULL, 'h'},
		{NULL,				0,					NULL, 0},
	};
	int idx = 0;
	char c;

	// Use getopt to parse through command line input
	while ((c = getopt_long(argc, argv, "h", longopts, &idx)) != -1) {
		switch (c) {
			case 'h':
				cout << "Helpful help message" << endl;

				exit(0);

			default:
				break;
		} // switch
	} // while

	file_stream = ifstream(argv[1]);

	return;
} // parse_command_line_input

void input_master_log_file(ifstream &file_stream, TimestampTable* &time_table, CategoryTable* &cat_table, KeywordTable* &key_table) {
	

	return;
}

Log* create_log(string* &str) {
	string time = str->substr(0, 14);
	string cat;
	string mess;

	string* time_ptr = &time;
	string* cat_ptr = &cat;
	string* mess_ptr = &mess;

	return new Log(time_ptr, cat_ptr, mess_ptr);
}


