//
//  logman.cpp
//  EECS 281 Project 3
//
//  Created by John West on 3/17/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#include "logman.h"

#include <iostream>
#include <sstream>
#include <getopt.h>

void print_input_signal(ostringstream &ss);

void print_input_error(ostringstream &error_ss);

void sort_command_list(LogVec* &command_list);

using namespace std;

int main(int argc, char *argv[]) {

	ifstream file_stream;
	ostringstream ss, error_ss;

	TimestampTable time_table;
	CategoryTable cat_table;
	KeywordTable key_table;
	EntryIDTable entry_table;

	parse_command_line_input(argc, argv, file_stream);

	input_master_log_file(file_stream, time_table, cat_table, key_table, entry_table, ss);

	take_user_input(time_table, cat_table, key_table, entry_table, ss, error_ss);

	cout << ss.str();
	cerr << error_ss.str();

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

	file_stream.open(argv[1]);

	return;
} // parse_command_line_input

void input_master_log_file(ifstream &file_stream, TimestampTable &time_table, CategoryTable &cat_table, KeywordTable &key_table, EntryIDTable &entry_table, ostringstream &ss) {

	string str_in;
	int num_logs = 0;

	while (getline(file_stream, str_in)) {

		if (int(str_in.size()) > 0) {
			Log* wood = create_log(str_in);
			++num_logs;

			time_table.insert_time_log(wood);

			cat_table.insert_cat_log(wood);

			key_table.insert_word_log(wood);

			entry_table.insert_entry_log(wood);
		}
	}

	time_table.sort_time_logs();
	key_table.sort_key_logs();

	ss << num_logs << " entries loaded\n";

	return;
}

void take_user_input(TimestampTable &time_table, CategoryTable &cat_table, KeywordTable &key_table, EntryIDTable &entry_table, ostringstream &ss, ostringstream &error_ss) {

	LogVec excerpt_list;
	LogVec* command_results = nullptr;
	bool command_sorted = false;

	string user_input;

	bool take_input = true;
	while (take_input) {

		print_input_signal(ss);

		getline(cin, user_input);

		switch (user_input.at(0)) {
			// searching commands
			case 't': {
				timestamp_search(time_table, command_results, user_input, ss, error_ss);
				command_sorted = false;
				break;
			}
			case 'c': {
				category_search(cat_table, command_results, user_input, ss);
				command_sorted = false;
				break;
			}
			case 'k': {
				keyword_search(key_table, command_results, user_input, ss);
				command_sorted = false;
				break;
			}
			// excerpt list editing commands
			case 'i': {
				insert_log_entry(entry_table, excerpt_list, user_input);
				break;
			}
			case 'r': {
				if (!command_sorted) {
					sort_command_list(command_results);
					command_sorted = true;
				}

				insert_search_results(excerpt_list, command_results);
				break;
			}
			case 'd': {
				delete_log_entry(excerpt_list, user_input, error_ss);
				break;
			}
			case 'b': {
				move_to_beginning(excerpt_list, user_input, error_ss);
				break;
			}
			case 'e': {
				move_to_end(excerpt_list, user_input, error_ss);
				break;
			}
			case 's': {
				sort_excerpt_list(excerpt_list);
				break;
			}
			case 'l': {
				clear_excerpt_list(excerpt_list);
				break;
			}
			// output commands
			case 'g': {
				if (!command_sorted) {
					sort_command_list(command_results);
					command_sorted = true;
				}

				print_recent_searches(command_results, ss);
				break;
			}
			case 'p': {
				print_excerpt_list(excerpt_list, ss);
				break;
			}
			// miscellaneous
			case 'q': {
				take_input = false;
				break;
			}
			default: {
				print_input_error(error_ss);
				break;
			}
		}
	}

	if (command_results) {
		delete command_results; command_results = nullptr;
	}

	return;
}

// searching commands
void timestamp_search(TimestampTable &time_table, LogVec* &command_results, string &input, ostringstream &ss, ostringstream &error_ss) {

	if (command_results) {
		delete command_results; command_results = nullptr;
	}

	string start, end;

	int time_begin = 2;
	for (int i = 2; i <= int(input.length()); ++i) {
		if (i == int(input.length())) {
			end = input.substr(time_begin, i - time_begin);
		}
		else if (input.at(i) == '|') {
			start = input.substr(time_begin, i - time_begin);

			time_begin = i + 1;
		}
	}

	if ((int(start.length()) != 14) || (int(end.length()) != 14)) {
		print_input_error(error_ss);
	}

	command_results = time_table.get_time_logs(start, end);

	int num_found = 0;

	if (command_results) {
		num_found = int(command_results->size());
	}

	ss << num_found << "\n";

	return;
}

void category_search(CategoryTable &cat_table, LogVec* &command_results, string &input, ostringstream &ss) {

	if (command_results) {
		delete command_results; command_results = nullptr;
	}

	string category = input.substr(2);
	command_results = cat_table.get_cat_logs(category);

	int num_found = 0;
	
	if (command_results) {
		num_found = int(command_results->size());
	}
	
	ss << num_found << "\n";

	return;
}

void keyword_search(KeywordTable &key_table, LogVec* &command_results, string &input, ostringstream &ss) {

	if (command_results) {
		delete command_results; command_results = nullptr;
	}

	string keywords = input.substr(2);
	command_results = key_table.get_word_logs(keywords);

	int num_found = 0;
	
	if (command_results) {
		num_found = int(command_results->size());
	}
	
	ss << num_found << "\n";

	return;
}

// excerpt list editing commands
void insert_log_entry(EntryIDTable &entry_table, LogVec &excerpt_list, string &input) {

	int entry_id = stoi(input.substr(2));
	excerpt_list.push_back(entry_table.get_entry_log(entry_id));

	return;
}

void insert_search_results(LogVec &excerpt_list, LogVec* &command_results) {

	if (command_results) {
		excerpt_list.insert(excerpt_list.end(), command_results->begin(), command_results->end());
	}

	return;
}

void delete_log_entry(LogVec &excerpt_list, string &input, ostringstream &error_ss) {

	int excerpt_id = stoi(input.substr(2));

	if (excerpt_id < int(excerpt_list.size())) {
		excerpt_list.erase(excerpt_list.begin() + excerpt_id);
	}
	else {
		print_input_error(error_ss);
	}

	return;
}

void move_to_beginning(LogVec &excerpt_list, string &input, ostringstream &error_ss) {

	int excerpt_id = stoi(input.substr(2));

	if (excerpt_id < int(excerpt_list.size())) {
		Log* move = excerpt_list.at(excerpt_id);
		excerpt_list.erase(excerpt_list.begin() + excerpt_id);
		excerpt_list.insert(excerpt_list.begin(), move);
	}
	else {
		print_input_error(error_ss);
	}

	return;
}

void move_to_end(LogVec &excerpt_list, string &input, ostringstream &error_ss) {

	int excerpt_id = stoi(input.substr(2));

	if (excerpt_id < int(excerpt_list.size())) {
		Log* move = excerpt_list.at(excerpt_id);
		excerpt_list.erase(excerpt_list.begin() + excerpt_id);
		excerpt_list.push_back(move);
	}
	else {
		print_input_error(error_ss);
	}

	return;
}

void sort_excerpt_list(LogVec &excerpt_list) {

	sort(excerpt_list.begin(), excerpt_list.end(), MinLogComparator());

	return;
}

void sort_command_list(LogVec* &command_list) {

	if (command_list) {
		sort(command_list->begin(), command_list->end(), MinLogComparator());
	}
	
	return;
}

void clear_excerpt_list(LogVec &excerpt_list) {

	excerpt_list = vector <Log*> ();

	return;
}

// output commands
void print_recent_searches(LogVec* &command_results, ostringstream &ss) {

	if (command_results) {
		for (int i = 0; i < int(command_results->size()); ++i) {
			Log entry = *command_results->at(i);
			
			ss << entry.get_entry_id() << "|" << *entry.get_time_stamp() << "|" << *entry.get_category() << "|" << *entry.get_message() << "\n";
			
		}
	}

	return;
}

void print_excerpt_list(LogVec &excerpt_list, ostringstream &ss) {

	Log* entry;
	for (int i = 0; i < int(excerpt_list.size()); ++i) {
		entry = excerpt_list.at(i);
		ss << i << "|" << entry->get_entry_id() << "|" << *entry->get_time_stamp() << "|" << *entry->get_category() << "|" << *entry->get_message() << "\n";
	}

	return;
}

// Misc
Log* create_log(string &str) {

	string time = str.substr(0, 14);
	string cat;
	string mess;

	size_t time_end = str.find('|');
	size_t cat_end = str.find('|', time_end + 1);

	cat = str.substr(time_end + 1, cat_end - time_end - 1);
	mess = str.substr(cat_end + 1);

	return new Log(time, cat, mess);
}

void print_input_signal(ostringstream &ss) {

	ss << "%";

	return;
}

void print_input_error(ostringstream &error_ss) {

	error_ss << "Error: Invalid command";

	return;
}
