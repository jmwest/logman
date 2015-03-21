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

#include <string>

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

	string message;

public:
	Log(string* &timestamp_in, string* &category_in, string* &message_in);

	
};

Log::Log(string* &timestamp_in, string* &category_in, string* &message_in)
:timestamp(*timestamp_in), category(*category_in), message(*message_in) {
	
}

#endif
