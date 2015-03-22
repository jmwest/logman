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

#include <string>

using namespace std;

class Log {
private:
	static int count;
	const int entry_id;

	string timestamp;
	int month;
	int day;
	int hour;
	int minute;
	int second;

	string category;

	string message;

public:
	Log(string* &timestamp_in, string* &category_in, string* &message_in);

	int get_entry_id() { return entry_id; }
	
	string* get_time_stamp() { return &timestamp; }
	int get_month() { return month; }
	int get_day() { return day; }
	int get_hour() { return hour; }
	int get_minute() { return minute; }
	int get_second() { return second; }

	string* get_category() { return &category; }

	string* get_message() { return &message; }
};

int Log::count = 0;

Log::Log(string* &timestamp_in, string* &category_in, string* &message_in)
:entry_id(++count), timestamp(*timestamp_in), category(*category_in), message(*message_in) {

	month = stoi(timestamp_in->substr(0,2));
	day = stoi(timestamp_in->substr(3,2));
	hour = stoi(timestamp_in->substr(6,2));
	minute = stoi(timestamp_in->substr(9,2));
	second = stoi(timestamp_in->substr(12,2));
}



#endif
