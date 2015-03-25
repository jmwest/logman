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
#include "EntryIDTable.h"

using namespace std;

// REQUIRES:
// MODIFIES: filestream
// EFFECTS: uses argc and argv that are passed into the program
void parse_command_line_input(int & argc, char *argv[], ifstream &file_stream);

// REQUIRES:
// MODIFIES:
// EFFECTS:
void input_master_log_file(ifstream &file_stream, TimestampTable* &time_table, CategoryTable* &cat_table, KeywordTable* &key_table, EntryIDTable* &entry_table);

void take_user_input(TimestampTable* &time_table, CategoryTable* &cat_table, KeywordTable* &key_table, EntryIDTable* &entry_table);

void timestamp_search(TimestampTable* &time_table, LogQueue* &command_results, string &input);

void category_search(CategoryTable* &cat_table, LogQueue* &command_results, string &input);

void keyword_search(KeywordTable* &key_table, LogQueue* &command_results, string &input);

void insert_log_entry(EntryIDTable* &entry_table, vector <Log*> &excerpt_list, string &input);

void insert_search_results(vector <Log*> &excerpt_list, LogQueue* &command_results);

void delete_log_entry(vector <Log*> &excerpt_list, string &input);

void move_to_beginning(vector <Log*> &excerpt_list, string &input);

void move_to_end(vector <Log*> &excerpt_list, string &input);

void sort_excerpt_list(vector <Log*> &excerpt_list);

void clear_excerpt_list(vector <Log*> &excerpt_list);

void print_recent_searches(LogQueue* &command_results);

void print_excerpt_list(vector <Log*> &excerpt_list);

Log* create_log(string* &str);

#endif /* defined(__EECS_281_Project_3__logman__) */
