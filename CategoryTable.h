//
//  CategoryTable.h
//  EECS 281 Project 3
//
//  Created by John West on 3/21/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#ifndef EECS_281_Project_3_CategoryTable_h
#define EECS_281_Project_3_CategoryTable_h

#include "Log.h"

typedef unordered_map <string, LogVec> CatTable;

class CategoryTable {
private:
	CatTable c_table;

public:
	CategoryTable();

	void insert_cat_log(Log* &log);

	LogVec* get_cat_logs(string &cat);
};

CategoryTable::CategoryTable() {}

void CategoryTable:: insert_cat_log(Log* &log) {

	c_table[*log->get_lower_cat()].push_back(log);

	return;
}

LogVec* CategoryTable::get_cat_logs(string &cat) {

	LogVec* logs = new LogVec();

	for (int i = 0; i < int(cat.length()); ++i) {
		cat.at(i) = tolower(cat.at(i));
	}

	LogVec* kitties = &c_table[cat];

	logs->insert(logs->end(), kitties->begin(), kitties->end());

	return logs;
}

#endif
