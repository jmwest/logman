//
//  Log.h
//  EECS 281 Project 3
//
//  Created by John West on 3/17/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#ifndef EECS_281_Project_3_Log_h
#define EECS_281_Project_3_Log_h

#include <stdio.h>

#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <map>

#include <iostream>

using namespace std;

class Log {
private:
	static int count;
	const int entry_id;

	string timestamp;
	int month;
	int day;
	int hour;
	int minute;
	int second;

	string category;

	string lower_cat;

	string message;

	string lower_message;

public:
	Log(string &timestamp_in, string &category_in, string &message_in);

	int get_entry_id() { return entry_id; }
	
	string* get_time_stamp() { return &timestamp; }
	int get_month() { return month; }
	int get_day() { return day; }
	int get_hour() { return hour; }
	int get_minute() { return minute; }
	int get_second() { return second; }

	string* get_category() { return &category; }

	string* get_lower_cat() { return &lower_cat; }

	string* get_message() { return &message; }

	string* get_lower_message() { return &lower_message; }
};

int Log::count = 0;

Log::Log(string &timestamp_in, string &category_in, string &message_in)
:entry_id(count++), timestamp(timestamp_in), category(category_in), message(message_in) {

	month = stoi(timestamp_in.substr(0,2));
	day = stoi(timestamp_in.substr(3,2));
	hour = stoi(timestamp_in.substr(6,2));
	minute = stoi(timestamp_in.substr(9,2));
	second = stoi(timestamp_in.substr(12,2));

	lower_cat = category_in;

	for (int i = 0; i < int(lower_cat.length()); ++i) {
		lower_cat.at(i) = tolower(lower_cat.at(i));
	}

	lower_message = lower_cat + " " + message_in;

	for (int i = int(lower_cat.size() + 1); i < int(lower_message.length()); ++i) {
		lower_message.at(i) = tolower(lower_message.at(i));
	}
}

// Other comparator and type definitions

class MinLogComparator {
public:
	bool operator() (Log* const &one, Log* const &two) {
		if (*one->get_time_stamp() < *two->get_time_stamp()) {
			return true;
		}
		else if (*one->get_time_stamp() == *two->get_time_stamp()) {
			if (*one->get_lower_cat() < *two->get_lower_cat()) {
				return true;
			}
			else if (*one->get_lower_cat() == *two->get_lower_cat()) {
				if (one->get_entry_id() < two->get_entry_id()) {
					return true;
				}
			}
		}

		return false;
	}
};

//class MinLogComparator {
//public:
//	bool operator() (Log* const &one, Log* const &two) {
//		if (one->get_month() < two->get_month()) {
//			return true;
//		}
//		else if (one->get_month() == two->get_month()) {
//			if (one->get_day() < two->get_day()) {
//				return true;
//			}
//			else if (one->get_day() == two->get_day()) {
//				if (one->get_hour() < two->get_hour()) {
//					return true;
//				}
//				else if (one->get_hour() == two->get_hour()) {
//					if (one->get_minute() < two->get_minute()) {
//						return true;
//					}
//					else if (one->get_minute() == two->get_minute()) {
//						if (one->get_second() < two->get_second()) {
//							return true;
//						}
//						
//						else if (one->get_second() == two->get_second()) {
//							if (*one->get_lower_cat() < *two->get_lower_cat()) {
//								return true;
//							}
//							else if (*one->get_lower_cat() == *two->get_lower_cat()) {
//								if (one->get_entry_id() < two->get_entry_id()) {
//									return true;
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//		
//		return false;
//	}
//};

typedef vector <Log*> LogVec;

#endif
