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

	void insert_word_log(Log* &log);

	void sort_key_logs();

	LogVec* get_word_logs(string &words);
};

KeywordTable::KeywordTable() {}

void KeywordTable::insert_word_log(Log* &log) {

//	unordered_map <string, string> word_map;
	vector <string> word_map;

	string message = *log->get_lower_message();

	int word_start = 0;
	for (int i = 0; i <= int(message.length()); ++i) {

		if ((i == int(message.length())) || !isalnum(int(message.at(i)))) {

			if (word_start != i) {
				string word = message.substr(word_start, i - word_start);
//				word_map.insert(unordered_map <string, string>::value_type(word, word));
				if (find(word_map.begin(), word_map.end(), word) == word_map.end()) {
					word_map.push_back(word);
				}
			}

			word_start = i + 1;
		}
	}

//	for (unordered_map <string, string>:: iterator it = word_map.begin();
//		 it != word_map.end(); ++it) {
//		k_table[it->second].push_back(log);
//	}
	for (int j = 0; j < int(word_map.size()); ++j) {
		k_table[word_map.at(j)].push_back(log);
	}

	return;
}

void KeywordTable::sort_key_logs() {

	for (WordTable::iterator it = k_table.begin(); it != k_table.end(); ++it) {
		sort(it->second.begin(), it->second.end());
	}

	return;
}

LogVec* KeywordTable::get_word_logs(string &words) {

	LogVec* logs = new LogVec();

	map <string, string> individual_words;

	for (int i = 0; i < int(words.size()); ++i) {
		words.at(i) = std::tolower(words.at(i));
	}

	int word_start = 0;
	for (int i = 0; i <= int(words.length()); ++i) {

		if ((i == int(words.length())) || !isalnum(int(words.at(i)))) {

			if (word_start != i) {
				string key = words.substr(word_start, i - word_start);
				individual_words.insert(map <string, string>:: value_type(key, key));
			}

			word_start = i + 1;
		}
	}

	///////////////////////////////////////////////////////////////
//	cerr << "\n____________________________________________________________________________\n";
//	cerr << "Keyword Search:\n";
	///////////////////////////////////////////////////////////////

	for (map <string, string>::iterator it = individual_words.begin(); it != individual_words.end(); ++it) {

		///////////////////////////////////////////////////////////////
//		cerr << "\n" << individual_words.at(i) << endl;
		///////////////////////////////////////////////////////////////

		LogVec* current = &k_table[it->second];
//		sort(current->begin(), current->end());

		///////////////////////////////////////////////////////////////
//		for (int a = 0; a < int(current->size()); ++a) {
//			cerr << "\t" << *current->at(a)->get_lower_case_string() << endl;
//		}
		///////////////////////////////////////////////////////////////

		if (current->empty()) {
			delete logs; logs = nullptr;

			break;
		}
		else if (logs->empty())	{
			logs->insert(logs->begin(), current->begin(), current->end());
		}
		else {
			LogVec::iterator del = set_intersection(logs->begin(), logs->end(), current->begin(), current->end(), logs->begin());

			logs->erase(del, logs->end());

			if (del == logs->begin()) {
				delete logs; logs = nullptr;
				break;
			}
		}

		///////////////////////////////////////////////////////////////
//		cerr << "Intersection:" << endl;
//		if (logs) {
//			for (int b = 0; b < int(logs->size()); ++b) {
//				cerr << "\t" << *logs->at(b)->get_lower_case_string() << endl;
//			}
//		}
		///////////////////////////////////////////////////////////////

	}

	return logs;
}

#endif
