//
//  Log.h
//  EECS 281 Project 3
//
//  Created by John West on 3/17/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#ifndef EECS_281_Project_3_Log_h
#define EECS_281_Project_3_Log_h

#include <stdio.h>

#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <map>

#include <iostream>

using namespace std;

class Log {
private:
	static int count;
	const int entry_id;

	string timestamp;

	string category;

	string lower_case_string;

	string message;

public:
	Log(string &timestamp_in, string &category_in, string &message_in);

	int get_entry_id() { return entry_id; }
	
	string* get_time_stamp() { return &timestamp; }

	string* get_category() { return &category; }

	string* get_lower_case_string() { return &lower_case_string; }

	string* get_message() { return &message; }
};

int Log::count = 0;

Log::Log(string &timestamp_in, string &category_in, string &message_in)
:entry_id(count++), timestamp(timestamp_in), category(category_in), message(message_in) {

	lower_case_string = category_in + ' ' + message_in;

	for (int i = 0; i < int(lower_case_string.length()); ++i) {
		lower_case_string.at(i) = tolower(lower_case_string.at(i));
	}
}

// Other comparator and type definitions

class MinLogComparator {
public:
	bool operator() (Log* const &one, Log* const &two) {
		if (*one->get_time_stamp() < *two->get_time_stamp()) {
			return true;
		}
		else if (*one->get_time_stamp() == *two->get_time_stamp()) {
			if (*one->get_category() < *two->get_category()) {
				return true;
			}
			else if (*one->get_category() == *two->get_category()) {
				if (one->get_entry_id() < two->get_entry_id()) {
					return true;
				}
			}
		}

		return false;
	}
};

typedef vector <Log*> LogVec;

#endif
