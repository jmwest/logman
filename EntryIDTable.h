//
//  EntryIDTable.h
//  EECS 281 Project 3
//
//  Created by John West on 3/24/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#ifndef EECS_281_Project_3_EntryIDTable_h
#define EECS_281_Project_3_EntryIDTable_h

#include "Log.h"
#include <iostream>

class EntryIDTable {
private:
	LogVec e_table;

public:
	EntryIDTable();
	~EntryIDTable();

	void insert_entry_log(Log* log);

	Log* get_entry_log(int entry_id);
};

EntryIDTable::EntryIDTable() {}

EntryIDTable::~EntryIDTable() {
	for (int i = int(e_table.size()) - 1; i >= 0; --i) {
		delete e_table.at(i); e_table.at(i) = nullptr;
	}
}

void EntryIDTable:: insert_entry_log(Log* log) {

	e_table.push_back(log);

	return;
}

Log* EntryIDTable::get_entry_log(int entry_id) {

	return e_table.at(entry_id);
}

#endif
