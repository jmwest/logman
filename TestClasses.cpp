//
//  TestClasses.cpp
//  EECS 281 Project 3
//
//  Created by John West on 3/21/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#include "TestClasses.h"

#include <cassert>
#include <iostream>

#include "log.h"
#include "TimestampTable.h"
#include "CategoryTable.h"
#include "KeywordTable.h"

int main() {

///////// Log tests /////
	string time = "01:04:21:45:97";
	string cat = "STL Error";
	string mess = "Vector index out-of-bounds";

	string* time_ptr = &time;
	string* cat_ptr = &cat;
	string* mess_ptr = &mess;

	Log first = Log(time_ptr, cat_ptr, mess_ptr);
	Log second = Log(time_ptr, cat_ptr, mess_ptr);

	assert(first.get_entry_id() == 1);
	assert(!strcmp(first.get_time_stamp()->c_str(), time.c_str()));
	assert(!strcmp(first.get_category()->c_str(), cat.c_str()));
	assert(!strcmp(first.get_message()->c_str(), mess.c_str()));

	assert(first.get_month() == 1);
	assert(first.get_day() == 4);
	assert(first.get_hour() == 21);
	assert(first.get_minute() == 45);
	assert(first.get_second() == 97);

	assert(second.get_entry_id() == 2);
///////// end Log tests /////

	
	return 0;
}