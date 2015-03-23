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
	string time2 = "02:19:00:04:99";
	string time3 = "02:19:00:05:00";
	string cat = "STL Error";
	string mess = "Vector index out-of-bounds";

	string* time_ptr = &time;
	string* time2_ptr = &time2;
	string* time3_ptr = &time3;
	string* cat_ptr = &cat;
	string* mess_ptr = &mess;

	Log first = Log(time_ptr, cat_ptr, mess_ptr);
	Log second = Log(time_ptr, cat_ptr, mess_ptr);
	Log third = Log(time2_ptr, cat_ptr, mess_ptr);
	Log forth = Log(time3_ptr, cat_ptr, mess_ptr);

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

///////// double tests //////
//	double tim = (first.get_month()*100000000) + (first.get_day()*1000000) + (first.get_hour()*10000) + (first.get_minute()*100) + first.get_second();
//	double tim2 = (second.get_month()*100000000) + (second.get_day()*1000000) + (second.get_hour()*10000) + (second.get_minute()*100) + second.get_second();
//
//	cout << fixed;
//	cout << "time: " << tim << endl;
//	cout << "day: " << int(tim/1000000) << endl;
//
//	if (tim == tim2) {
//		cout << "same" << endl;
//	}
///////// end double tests //////

///////// TimestampTable tests //////
	TimestampTable time_table;

	time_table.insert_log(&first);
	time_table.insert_log(&second);
	time_table.insert_log(&third);
	time_table.insert_log(&forth);

	LogQueue* lst1 = time_table.get_logs(time_ptr, time3_ptr);

	assert(!strcmp(lst1->top()->get_time_stamp()->c_str(), time.c_str()));
	lst1->pop();
	lst1->pop();
	assert(!strcmp(lst1->top()->get_time_stamp()->c_str(), time2.c_str()));
///////// end Timestamp Table tests //////

	return 0;
}
