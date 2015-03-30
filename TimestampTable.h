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
//typedef LogVec TimeTable;

class TimestampTable {
private:
	TimeTable t_table;

public:
	TimestampTable();

	void  insert_time_log(Log* &log);

	LogVec* get_time_logs(string &time1, string &time2);
};

//class TimeComp {
//public:
//	bool operator () (Log* const &one, Log* const &two) {
//		if (*one->get_time_stamp() < *two->get_time_stamp()) {
//			return true;
//		}
//
//		return false;
//	}
//};

TimestampTable::TimestampTable() {}

void TimestampTable:: insert_time_log(Log* &log) {

	t_table[*log->get_time_stamp()].push_back(log);

//	LogVec::iterator it = lower_bound(t_table.begin(), t_table.end(), log, TimeComp());
//
//	t_table.insert(it, log);

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

//	string s;
//
//	Log log1 = Log(time1, s, s);
//	Log log2 = Log(time2, s, s);
//	Log* log1_ptr = &log1;
//	Log* log2_ptr = &log2;
//
//	LogVec::iterator begin = lower_bound(t_table.begin(), t_table.end(), log1_ptr, TimeComp());
//	LogVec::iterator end = lower_bound(t_table.begin(), t_table.end(), log2_ptr, TimeComp());
//
//	logs->insert(logs->begin(), begin, end);

	return logs;
}

#endif
