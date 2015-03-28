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

typedef map <string, LogVec> TimeTable;

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

	t_table[*log->get_time_stamp()].push_back(log);

	return;
}

LogVec* TimestampTable::get_time_logs(string &time1, string &time2) {

	LogVec* logs = new LogVec();

	TimeTable::iterator it = t_table.lower_bound(time1);
	TimeTable::iterator end = t_table.lower_bound(time2);

	while (it != end) {
		if (!it->second.empty()) {
			logs->insert(logs->end(), it->second.begin(), it->second.end());
		}

		++it;
	}

	return logs;
}

#endif
