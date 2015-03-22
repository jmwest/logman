//
//  TimestampTable.h
//  EECS 281 Project 3
//
//  Created by John West on 3/21/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#ifndef EECS_281_Project_3_TimestampTable_h
#define EECS_281_Project_3_TimestampTable_h

#include <unordered_map>
#include <queue>

#include "Log.h"

typedef unordered_multimap <int, Log*> TimeTable;

class TimestampTable {
private:
	static const int day_prime = 7;
	static const int second_prime = 971;

	TimeTable table;

	int hash(Log* &log);

public:
	TimestampTable();

	void insert_log(Log* log);

	priority_queue <Log*>* get_logs(string* &time1, string* &time2);
};

TimestampTable::TimestampTable() {


}

void TimestampTable::insert_log(Log* log) {

	int key = hash(log);

	table.insert(TimeTable::value_type(key, log));

	return;
}

priority_queue <Log*>* TimestampTable::get_logs(string* &time1, string* &time2) {
	priority_queue <Log*>* logs = new priority_queue <Log*> ();

	int start_day = (stoi(time1->substr(0,2))*100) + stoi(time1->substr(3,2));
	int start_second = (stoi(time1->substr(6,2))*10000) + (stoi(time1->substr(9,2))*100) + stoi(time1->substr(12,2));

	int end_day = (stoi(time2->substr(0,2))*100) + stoi(time2->substr(3,2));
	int end_second = (stoi(time2->substr(6,2))*10000) + (stoi(time2->substr(9,2))*100) + stoi(time2->substr(12,2));

	while ((start_day <= end_day)) {
		if ((start_day == end_day) && (start_second >= end_second)) {
			break;
		}

		

		start_second += second_prime;

		if (start_second/1000000) {
			start_second = start_second % 1000000;
			start_day += day_prime;
		}
	}

	return logs;
}

int TimestampTable::hash(Log* &log) {
	int key_p1 = ((log->get_month()*100) + log->get_day())/day_prime;
	int key_p2 = ((log->get_hour()*10000) + (log->get_minute()*100) + log->get_second())/second_prime;

	return key_p1*1000 + key_p2;
}

#endif
