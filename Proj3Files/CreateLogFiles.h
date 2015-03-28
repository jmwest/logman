//
//  CreateLogFiles.h
//  EECS 281 Project 3
//
//  Created by John West on 3/27/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#ifndef __EECS_281_Project_3__CreateLogFiles__
#define __EECS_281_Project_3__CreateLogFiles__

#include <stdio.h>
#include <fstream>
#include <sstream>

using namespace std;

void parse_command_line_input(int & argc, char *argv[], ofstream &log_stream, ofstream &cmnd_stream, int &log_size, int &cmnd_size);

void make_log_file(ostringstream &log_ss, int &log_size);

void make_cmnd_file(ostringstream &cmnd_ss, int &log_size, int &cmnd_size);

#endif /* defined(__EECS_281_Project_3__CreateLogFiles__) */
