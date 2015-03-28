//
//  TimestampTable.h
//  EECS 281 Project 3
//
//  Created by John West on 3/21/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#ifndef EECS_281_Project_3_TimestampTable_h
#define EECS_281_Project_3_TimestampTable_h

#include "Log.h"

typedef map <string, LogVec*> TimeTable;

class TimestampTable {
private:
	static const int day_prime = 7;
	static const int second_prime = 971;

	TimeTable t_table;

	int time_hash(Log* log);
	int time_hash(int day, int sec);

	bool time_in_range(string &time, string &range_start, string &range_end);

public:
	TimestampTable();

	void  insert_time_log(Log* log);

	LogVec* get_time_logs(string &time1, string &time2);
};

TimestampTable::TimestampTable() {}

void TimestampTable:: insert_time_log(Log* log) {

	int key = time_hash(log);

	t_table.find(key);

	t_table.insert(TimeTable::value_type(key, log));

	return;
}

LogVec* TimestampTable::get_time_logs(string &time1, string &time2) {

//	cerr << "\n_________________________________________________" << endl;
//	cerr << "Timestamp search\n";
	LogQueue logs = LogQueue();

	int start_day = (stoi(time1.substr(0,2))*100) + stoi(time1.substr(3,2));
	int start_second = (stoi(time1.substr(6,2))*10000) + (stoi(time1.substr(9,2))*100) + stoi(time1.substr(12,2));

	int end_day = (stoi(time2.substr(0,2))*100) + stoi(time2.substr(3,2));
	int end_second = (stoi(time2.substr(6,2))*10000) + (stoi(time2.substr(9,2))*100) + stoi(time2.substr(12,2));

	while ((start_day <= end_day)) {
		if ((start_day == end_day) && (start_second >= end_second)) {
			break;
		}

		pair <TimeTable::iterator, TimeTable::iterator> stamps = t_table.equal_range(time_hash(start_day, start_second));

		for (TimeTable::iterator it = stamps.first; it != stamps.second; ++it) {

			string current_time = *it->second->get_time_stamp();
			if (time_in_range(current_time, time1, time2)) {
//				cerr << "\t" << *it->second->get_lower_case_string() << endl;

				logs.push(it->second);
			}
		}

		start_second += second_prime;

		if (start_second/1000000) {
			start_second = start_second % 1000000;
			start_day += day_prime;
		}
	}

	return logs;
}

int TimestampTable::time_hash(Log* log) {
	int key_p1 = ((log->get_month()*100) + log->get_day())/day_prime;
	int key_p2 = ((log->get_hour()*10000) + (log->get_minute()*100) + log->get_second())/second_prime;

	return key_p1*1000 + key_p2;
}

int TimestampTable::time_hash(int day, int sec) {
	return (day / day_prime)*1000 + sec/second_prime;
}

bool TimestampTable::time_in_range(string &time, string &range_start, string &range_end) {

	return (((time) >= (range_start)) && ((time) < (range_end)));
}


#endif
