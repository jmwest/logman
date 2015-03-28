//
//  KeywordTable.h
//  EECS 281 Project 3
//
//  Created by John West on 3/21/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#ifndef EECS_281_Project_3_KeywordTable_h
#define EECS_281_Project_3_KeywordTable_h

#include "Log.h"

typedef unordered_map <string, LogVec> WordTable;

class KeywordTable {
private:
	WordTable k_table;

public:
	KeywordTable();

	int size() { return int(k_table.size()); }

	void  insert_word_log(Log* log);

	LogVec* get_word_logs(string &words);
};

KeywordTable::KeywordTable() {}

void KeywordTable:: insert_word_log(Log* log) {

	unordered_map <string, string> word_map;

	string* message = log->get_lower_case_string();

	int word_start = 0;
	for (int i = 0; i <= int(message->length()); ++i) {

		if ((i == int(message->length())) || !isalnum(int(message->at(i)))) {

			if (word_start != i) {
				string word = message->substr(word_start, i - word_start);
				word_map.insert(unordered_map <string, string>::value_type(word, word));
			}

			word_start = i + 1;
		}
	}

	for (unordered_map <string, string>:: iterator it = word_map.begin();
		 it != word_map.end(); ++it) {
		k_table[it->second].push_back(log);
	}

	return;
}

LogVec* KeywordTable::get_word_logs(string &words) {

	LogVec* logs = new LogVec();

	vector <string> individual_words;

	for (int i = 0; i < int(words.size()); ++i) {
		words.at(i) = std::tolower(words.at(i));
	}

	int word_start = 0;
	for (int i = 0; i <= int(words.length()); ++i) {

		if ((i == int(words.length())) || !isalnum(int(words.at(i)))) {

			if (word_start != i) {
				individual_words.push_back(words.substr(word_start, i - word_start));
			}

			word_start = i + 1;
		}
	}

	for (int i = 0; i < int(individual_words.size()); ++i) {

		LogVec* current = &k_table[individual_words.at(i)];

		if (current->empty()) {
			delete logs; logs = nullptr;

			break;
		}
		else if (logs->empty())	{
			logs->insert(logs->begin(), current->begin(), current->end());
		}
		else {
			LogVec::iterator del = set_intersection(logs->begin(), logs->end(), current->begin(), current->end(), logs->begin());

			if ((del != --logs->end()) && ((del != logs->end()) || (del == logs->begin()))) {
				logs->erase(del, logs->end());
			}

			if (del == logs->begin()) {
				delete logs; logs = nullptr;
				break;
			}
		}
	}

	return logs;
}

#endif
