//
//  TimestampTable.h
//  EECS 281 Project 3
//
//  Created by John West on 3/21/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#ifndef EECS_281_Project_3_TimestampTable_h
#define EECS_281_Project_3_TimestampTable_h

#include <vector>
#include <list>

#include "Log.h"

class TimestampTable {
private:
	vector < vector < vector < vector < vector < list <Log*> > > > > > table;

public:
	TimestampTable();

	void insert_log(Log* log);

	list <Log*>* get_logs(string* &time1, string* &time2);
};

TimestampTable::TimestampTable() {
	vector<list<Log*> > s = vector<list<Log*> >(100);
	cerr << "s" << endl;
	vector< vector<list<Log*> > > m = vector<vector<list<Log*> > >(100, s);
	cerr << "m" << endl;
	vector<vector<vector<list<Log*> > > > h = vector<vector<vector<list<Log*> > > >(100, m);
	cerr << "h" << endl;
	vector<vector<vector<vector<list<Log*> > > > > d = vector<vector<vector<vector<list<Log*> > > > >(100, h);
	cerr << "d" << endl;

	table = vector<vector<vector<vector<vector<list<Log*> > > > > > (100, d);
	cerr << "m" << endl;

}

void TimestampTable::insert_log(Log* log) {
	table.at(log->get_month()).at(log->get_day()).at(log->get_hour()).at(log->get_minute()).at(log->get_second()).push_front(log);

	return;
}

list <Log*>* TimestampTable::get_logs(string* &time1, string* &time2) {
	list <Log*>* logs = new list <Log*> ();

	int start_day = (stoi(time1->substr(0,2))*100) + stoi(time1->substr(3,2));
	int start_second = (stoi(time1->substr(6,2))*10000) + (stoi(time1->substr(9,2))*100) + stoi(time1->substr(12,2));

	int end_day = (stoi(time2->substr(0,2))*100) + stoi(time2->substr(3,2));
	int end_second = (stoi(time2->substr(6,2))*10000) + (stoi(time2->substr(9,2))*100) + stoi(time2->substr(12,2));

	int i = start_day;
	int j = start_second;
	while ((i != end_day) || (j != end_second)) {
		cerr << "i: " << i << " j: " << j << endl;

		list <Log*> lst = table.at(i/100).at(i%100).at(j/10000).at((j/100)%100).at(j%100);
		logs->insert(logs->end(), lst.begin(), lst.end());

		++j;

		if (j == 10000) {
			++i;
			j = 0;
		}
	}

	return logs;
}

#endif
