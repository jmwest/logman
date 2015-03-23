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
	string cat2 = "STP Error";
	string mess = "Vector index out-of-bounds";

	string* time_ptr = &time;
	string* time2_ptr = &time2;
	string* time3_ptr = &time3;
	string* cat_ptr = &cat;
	string* cat2_ptr = &cat2;
	string* mess_ptr = &mess;

	Log first = Log(time_ptr, cat_ptr, mess_ptr);
	Log second = Log(time_ptr, cat2_ptr, mess_ptr);
	Log third = Log(time2_ptr, cat_ptr, mess_ptr);
	Log forth = Log(time3_ptr, cat2_ptr, mess_ptr);

	assert(first.get_entry_id() == 0);
	assert(!strcmp(first.get_time_stamp()->c_str(), time.c_str()));
	assert(!strcmp(first.get_category()->c_str(), cat.c_str()));
	assert(!strcmp(first.get_message()->c_str(), mess.c_str()));

	assert(first.get_month() == 1);
	assert(first.get_day() == 4);
	assert(first.get_hour() == 21);
	assert(first.get_minute() == 45);
	assert(first.get_second() == 97);

	assert(second.get_entry_id() == 1);
	assert(third.get_entry_id() == 2);
	assert(forth.get_entry_id() == 3);
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
///////// end TimestampTable tests //////
	delete lst1; lst1 = nullptr;

///////// CategoryTable tests //////
	CategoryTable cat_table;

	cat_table.insert_log(&first);
	cat_table.insert_log(&second);
	cat_table.insert_log(&third);
	cat_table.insert_log(&forth);

	LogQueue* lst2 = cat_table.get_logs(cat2_ptr);

	assert(!strcmp(lst2->top()->get_category()->c_str(), cat2.c_str()));
	assert(!strcmp(lst2->top()->get_time_stamp()->c_str(), time.c_str()));
	lst2->pop();

	assert(!strcmp(lst2->top()->get_category()->c_str(), cat2.c_str()));
	assert(!strcmp(lst2->top()->get_time_stamp()->c_str(), time3.c_str()));
	lst2->pop();

	assert(lst2->empty());

	lst2 = cat_table.get_logs(cat_ptr);

	assert(!strcmp(lst2->top()->get_category()->c_str(), cat.c_str()));
	assert(!strcmp(lst2->top()->get_time_stamp()->c_str(), time.c_str()));
	lst2->pop();

	assert(!strcmp(lst2->top()->get_category()->c_str(), cat.c_str()));
	assert(!strcmp(lst2->top()->get_time_stamp()->c_str(), time2.c_str()));
	lst2->pop();
	
	assert(lst2->empty());
///////// end CategoryTable tests //////

	return 0;
}
