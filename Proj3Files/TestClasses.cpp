//
//  TestClasses.cpp
//  EECS 281 Project 3
//
//  Created by John West on 3/26/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#include <stdio.h>

#include "Log.h"
#include "CategoryTable.h"
#include "KeywordTable.h"
#include "EntryIDTable.h"
#include "TimestampTable.h"

using namespace std;

int main() {

	KeywordTable k_table;

	string time = "00:10:20:99:12";
	string cat = "time";
	string message = "the time for the time is time";

	Log log = Log(time, cat, message);

	k_table.insert_word_log(&log);

	cout << "k_table size: " << k_table.size() << endl;

	return 0;
}
