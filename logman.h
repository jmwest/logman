//
//  logman.h
//  EECS 281 Project 3
//
//  Created by John West on 3/17/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#ifndef __EECS_281_Project_3__logman__
#define __EECS_281_Project_3__logman__

#include <stdio.h>

#include <fstream>
#include <string>

#include "Log.h"
#include "TimestampTable.h"
#include "CategoryTable.h"
#include "KeywordTable.h"

using namespace std;

// REQUIRES:
// MODIFIES: filestream
// EFFECTS: uses argc and argv that are passed into the program
void parse_command_line_input(int & argc, char *argv[], ifstream &file_stream);

// REQUIRES:
// MODIFIES:
// EFFECTS:
void input_master_log_file(ifstream &file_stream, TimestampTable* &time_table, CategoryTable* &cat_table, KeywordTable* &key_table);

Log* create_log(string* &str);

#endif /* defined(__EECS_281_Project_3__logman__) */
