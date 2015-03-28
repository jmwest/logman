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
#include <queue>
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

	string lower_case_string;

	string message;

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

	string* get_lower_case_string() { return &lower_case_string; }

	string* get_message() { return &message; }
};

int Log::count = 0;

Log::Log(string &timestamp_in, string &category_in, string &message_in)
:entry_id(count++), timestamp(timestamp_in), category(category_in), message(message_in) {

	lower_case_string = category_in + ' ' + message_in;

	for (int i = 0; i < int(lower_case_string.length()); ++i) {
		lower_case_string.at(i) = tolower(lower_case_string.at(i));
	}

	month = stoi(timestamp_in.substr(0,2));
	day = stoi(timestamp_in.substr(3,2));
	hour = stoi(timestamp_in.substr(6,2));
	minute = stoi(timestamp_in.substr(9,2));
	second = stoi(timestamp_in.substr(12,2));
}

// Other comparator and type definitions

class MaxLogComparator {
public:
	bool operator() (Log* const &one, Log* const &two) {
		if (one->get_month() > two->get_month()) {
			return true;
		}
		else if (one->get_month() == two->get_month()) {
			if (one->get_day() > two->get_day()) {
				return true;
			}
			else if (one->get_day() == two->get_day()) {
				if (one->get_hour() > two->get_hour()) {
					return true;
				}
				else if (one->get_hour() == two->get_hour()) {
					if (one->get_minute() > two->get_minute()) {
						return true;
					}
					else if (one->get_minute() == two->get_minute()) {
						if (one->get_second() > two->get_second()) {
							return true;
						}

						else if (one->get_second() == two->get_second()) {
							if (*one->get_category() > *two->get_category()) {
								return true;
							}
							else if (*one->get_category() == *two->get_category()) {
								if (one->get_entry_id() > two->get_entry_id()) {
									return true;
								}
							}
						}
					}
				}
			}
		}
		
		return false;
	}
};

class MinLogComparator {
public:
	bool operator() (Log* const &one, Log* const &two) {
		if (one->get_month() < two->get_month()) {
			return true;
		}
		else if (one->get_month() == two->get_month()) {
			if (one->get_day() < two->get_day()) {
				return true;
			}
			else if (one->get_day() == two->get_day()) {
				if (one->get_hour() < two->get_hour()) {
					return true;
				}
				else if (one->get_hour() == two->get_hour()) {
					if (one->get_minute() < two->get_minute()) {
						return true;
					}
					else if (one->get_minute() == two->get_minute()) {
						if (one->get_second() < two->get_second()) {
							return true;
						}
						
						else if (one->get_second() == two->get_second()) {
							if (*one->get_category() < *two->get_category()) {
								return true;
							}
							else if (*one->get_category() == *two->get_category()) {
								if (one->get_entry_id() < two->get_entry_id()) {
									return true;
								}
							}
						}
					}
				}
			}
		}
		
		return false;
	}
};

//class LogComparator {
//private:
//	bool max;
//
//public:
//	LogComparator()
//	: max(true) {}
//
//	LogComparator(bool max_in)
//	: max(max_in) {}
//
//	bool operator() (Log* &one, Log* &two) {
//		if (one->get_month() > two->get_month()) {
//			return max;
//		}
//		else if (one->get_month() == two->get_month()) {
//			if (one->get_day() > two->get_day()) {
//				return max;
//			}
//			else if (one->get_day() == two->get_day()) {
//				if (one->get_hour() > two->get_hour()) {
//					return max;
//				}
//				else if (one->get_hour() == two->get_hour()) {
//					if (one->get_minute() > two->get_minute()) {
//						return max;
//					}
//					else if (one->get_minute() == two->get_minute()) {
//						if (one->get_second() > two->get_second()) {
//							return max;
//						}
//						
//						else if (one->get_category() > two->get_category()) {
//							return max;
//						}
//						else if (one->get_category() == two->get_category()) {
//							if (one->get_entry_id() < two->get_entry_id()) {
//								return max;
//							}
//						}
//					}
//				}
//			}
//		}
//
//		return !max;
//	}
//};

typedef vector <Log> LogVec;

#endif
