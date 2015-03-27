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

typedef unordered_multimap <string, Log*> CatTable;

class CategoryTable {
private:
	CatTable c_table;

public:
	CategoryTable();

	void  insert_cat_log(Log* log);

	LogQueue get_cat_logs(string &cat);
};

CategoryTable::CategoryTable() {}

void CategoryTable:: insert_cat_log(Log* log) {

	string s = *log->get_category();

	for (int i = 0; i < int(s.length()); ++i) {
		s.at(i) = tolower(s.at(i));
	}

	c_table.insert(CatTable::value_type(s, log));

	return;
}

LogQueue CategoryTable::get_cat_logs(string &cat) {

	cerr << "\n_________________________________________________" << endl;
	cerr << "Category search\n";
	LogQueue logs = LogQueue();

	for (int i = 0; i < int(cat.length()); ++i) {
		cat.at(i) = tolower(cat.at(i));
	}

	pair <CatTable::iterator, CatTable::iterator> cats = c_table.equal_range(cat);

	for (CatTable::iterator it = cats.first; it != cats.second; ++it) {
		cerr << "\t" << *it->second->get_lower_case_string() << endl;

		logs.push(it->second);
	}

	return logs;
}

#endif
