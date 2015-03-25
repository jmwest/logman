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

typedef unordered_multimap <int, Log*> EntryTable;

class EntryIDTable {
private:
	EntryTable e_table;

public:
	EntryIDTable();

	void  insert_entry_log(Log* log);

	Log* get_entry_log(int entry_id);
};

EntryIDTable::EntryIDTable() {}

void EntryIDTable:: insert_entry_log(Log* log) {

	e_table.insert(EntryTable::value_type(log->get_entry_id(), log));

	return;
}

Log* EntryIDTable::get_entry_log(int entry_id) {

	return e_table.find(entry_id)->second;
}

#endif
