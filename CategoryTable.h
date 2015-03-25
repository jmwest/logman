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

typedef unordered_multimap <int, Log*> CatTable;

class CategoryTable {
private:
	static const int cat_prime = 599;
	static const int dog_prime = 97;

	CatTable c_table;

	int cat_hash(string* &str);

public:
	CategoryTable();

	void  insert_cat_log(Log* log);

	LogQueue* get_cat_logs(string* &cat);
};

CategoryTable::CategoryTable() {}

void CategoryTable:: insert_cat_log(Log* log) {

	string* s = log->get_category();
	int key = cat_hash(s);

	c_table.insert(CatTable::value_type(key, log));

	return;
}

LogQueue* CategoryTable::get_cat_logs(string* &cat) {

	LogQueue* logs = new LogQueue ();

	pair <CatTable::iterator, CatTable::iterator> cats = c_table.equal_range(cat_hash(cat));

	for (CatTable::iterator it = cats.first; it != cats.second; ++it) {
		if (!strcmp(cat->c_str(), it->second->get_category()->c_str())) {
			logs->push(it->second);
		}
	}

	return logs;
}

int CategoryTable::cat_hash(string* &str) {

	int key = 0;

	for (int i = 1; i <= int(str->length()); ++i) {
		key += (i * i * cat_prime * atoi(&str->at(i - 1))) / dog_prime;
	}

	return key;
}

#endif
