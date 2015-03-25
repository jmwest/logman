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

void print_input_signal();

void print_input_error();

using namespace std;

int main(int argc, char *argv[]) {

	ifstream file_stream;

	TimestampTable time_table;
	CategoryTable cat_table;
	KeywordTable key_table;
	EntryIDTable entry_table;

	TimestampTable* time_table_ptr = &time_table;
	CategoryTable* cat_table_ptr = &cat_table;
	KeywordTable* key_table_ptr = &key_table;
	EntryIDTable* entry_table_ptr = &entry_table;

	parse_command_line_input(argc, argv, file_stream);

	input_master_log_file(file_stream, time_table_ptr, cat_table_ptr, key_table_ptr, entry_table_ptr);

	take_user_input(time_table_ptr, cat_table_ptr, key_table_ptr, entry_table_ptr);

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

void input_master_log_file(ifstream &file_stream, TimestampTable* &time_table, CategoryTable* &cat_table, KeywordTable* &key_table, EntryIDTable* &entry_table) {

	string str_in;
	int num_logs = 0;

	while (getline(file_stream, str_in)) {

		if (int(str_in.size()) > 0) {
			Log* wood = create_log(str_in);
			++num_logs;

			time_table->insert_time_log(wood);
			cat_table->insert_cat_log(wood);
			key_table->insert_word_log(wood);
			entry_table->insert_entry_log(wood);
		}
	}

	cout << num_logs << " entries loaded\n";

	return;
}

void take_user_input(TimestampTable* &time_table, CategoryTable* &cat_table, KeywordTable* &key_table, EntryIDTable* &entry_table) {

	vector <Log*> excerpt_list;
	LogQueue command_results;

	string user_input;
	bool take_input = true;

	while (take_input) {

		print_input_signal();

		getline(cin, user_input);

		switch (user_input.at(0)) {
			// searching commands
			case 't':
				timestamp_search(time_table, command_results, user_input);
				break;

			case 'c':
				category_search(cat_table, command_results, user_input);
				break;

			case 'k':
				keyword_search(key_table, command_results, user_input);
				break;

			// excerpt list editing commands
			case 'i':
				insert_log_entry(entry_table, excerpt_list, user_input);
				break;

			case 'r':
				insert_search_results(excerpt_list, command_results);
				break;

			case 'd':
				delete_log_entry(excerpt_list, user_input);
				break;

			case 'b':
				move_to_beginning(excerpt_list, user_input);
				break;

			case 'e':
				move_to_end(excerpt_list, user_input);
				break;

			case 's':
				sort_excerpt_list(excerpt_list);
				break;

			case 'l':
				clear_excerpt_list(excerpt_list);
				break;

			// output commands
			case 'g':
				print_recent_searches(command_results);
				break;

			case 'p':
				print_excerpt_list(excerpt_list);
				break;

			// miscellaneous
			case 'q':
				take_input = false;
				break;

			default:
				print_input_error();
				break;
		}
	}

	return;
}

// searching commands
void timestamp_search(TimestampTable* &time_table, LogQueue &command_results, string &input) {

	string start, end;

	int time_begin = 2;
	for (int i = 2; i <= int(input.length()); ++i) {
		if (input.at(i) == '|') {
			start = input.substr(time_begin, i - time_begin);

			time_begin = i + 1;
		}
		else if (i == int(input.length())) {
			end = input.substr(time_begin, i - time_begin);
		}
	}

	if ((int(start.length()) != 14) || (int(end.length()) != 14)) {
		print_input_error();
	}


	command_results = time_table->get_time_logs(start, end);

	cout << command_results.size() << "\n";

	return;
}

void category_search(CategoryTable* &cat_table, LogQueue &command_results, string &input) {

	string category = input.substr(2);
	command_results = cat_table->get_cat_logs(category);

	cout << command_results.size() << "\n";

	return;
}

void keyword_search(KeywordTable* &key_table, LogQueue &command_results, string &input) {

	string keywords = input.substr(2);
	command_results = key_table->get_word_logs(keywords);

	cout << command_results.size() << "\n";

	return;
}

// excerpt list editing commands
void insert_log_entry(EntryIDTable* &entry_table, vector <Log*> &excerpt_list, string &input) {

	int entry_id = stoi(input.substr(2));
	excerpt_list.push_back(entry_table->get_entry_log(entry_id));

	return;
}

void insert_search_results(vector <Log*> &excerpt_list, LogQueue &command_results) {

	while (!command_results.empty()) {
		excerpt_list.push_back(command_results.top());
		command_results.pop();
	}

	return;
}

void delete_log_entry(vector <Log*> &excerpt_list, string &input) {

	int excerpt_id = stoi(input.substr(2));

	if (excerpt_id < int(excerpt_list.size())) {
		excerpt_list.erase(excerpt_list.begin() + excerpt_id);
	}
	else {
		print_input_error();
	}

	return;
}

void move_to_beginning(vector <Log*> &excerpt_list, string &input) {

	int excerpt_id = stoi(input.substr(2));
	
	if (excerpt_id < int(excerpt_list.size())) {
		Log* move = excerpt_list.at(excerpt_id);
		excerpt_list.erase(excerpt_list.begin() + excerpt_id);
		excerpt_list.insert(excerpt_list.begin(), move);
	}
	else {
		print_input_error();
	}

	return;
}

void move_to_end(vector <Log*> &excerpt_list, string &input) {

	int excerpt_id = stoi(input.substr(2));
	
	if (excerpt_id < int(excerpt_list.size())) {
		Log* move = excerpt_list.at(excerpt_id);
		excerpt_list.erase(excerpt_list.begin() + excerpt_id);
		excerpt_list.push_back(move);
	}
	else {
		print_input_error();
	}

	return;
}

void sort_excerpt_list(vector <Log*> &excerpt_list) {

	sort(excerpt_list.begin(), excerpt_list.end(), MinLogComparator());

	return;
}

void clear_excerpt_list(vector <Log*> &excerpt_list) {

	excerpt_list = vector <Log*> ();

	return;
}

// output commands
void print_recent_searches(LogQueue command_results) {

	ostringstream ss;
	while (!command_results.empty()) {
		Log* entry = command_results.top();
		ss << entry->get_entry_id() << "|" << *entry->get_time_stamp() << "|" << *entry->get_category() << "|" << *entry->get_message() << "\n";

		command_results.pop();
	}

	cout << ss.str();

	return;
}

void print_excerpt_list(vector <Log*> &excerpt_list) {
	
	ostringstream ss;
	Log* entry;
	for (int i = 0; i < int(excerpt_list.size()); ++i) {
		entry = excerpt_list.at(i);
		ss << i << "|" << entry->get_entry_id() << "|" << *entry->get_time_stamp() << "|" << *entry->get_category() << "|" << *entry->get_message() << "\n";
	}

	cout << ss.str();

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

void print_input_signal() {

	cout << "%";

	return;
}

void print_input_error() {

	cerr << "Error: Invalid command";

	print_input_signal();

	return;
}
