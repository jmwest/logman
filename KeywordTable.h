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

typedef unordered_multimap <string, Log*> WordTable;

class KeywordTable {
private:
	WordTable k_table;

public:
	KeywordTable();

	int size() { return int(k_table.size()); }

	void  insert_word_log(Log* log);

	LogQueue get_word_logs(string &words);
};

KeywordTable::KeywordTable() {}

void KeywordTable:: insert_word_log(Log* log) {

	//USE A MAP!
	unordered_map <string, string> word_map;

	// append the category and message together for keyword
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
		k_table.insert(WordTable::value_type(it->second, log));
	}

	return;
}

LogQueue KeywordTable::get_word_logs(string &words) {

	cerr << "_________________________________________________" << endl;
	cerr << "Keyword search";
	LogQueue logs = LogQueue();

	vector <string> individual_words;

	vector <Log*> search_intersection, current;

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

		pair <WordTable::iterator, WordTable::iterator> keys = k_table.equal_range(individual_words.at(i));

		if (keys.first == keys.second) {
			search_intersection = vector <Log*>();
			break;
		}

		cerr << endl << individual_words.at(i) << ":\n";

		if (search_intersection.empty()) {
			for (WordTable::iterator it = keys.first; it != keys.second; ++it) {
				search_intersection.push_back(it->second);
				cerr << "\t" << *it->second->get_lower_case_string() << ";\n";
			}
		}
		else {
			for (WordTable::iterator it = keys.first; it != keys.second; ++it) {
				current.push_back(it->second);
				cerr << "\t" << *it->second->get_lower_case_string() << ";\n";
			}

//			vector <Log*> temp;

			vector <Log*>::iterator del = set_intersection(search_intersection.begin(), search_intersection.end(), current.begin(), current.end(), search_intersection.begin());

			search_intersection.erase(del, search_intersection.end());
//			search_intersection = temp;
		}
		
	}

	cerr << endl << "results:\n";
	for (int i = 0; i < int(search_intersection.size()); ++i) {
		logs.push(search_intersection.at(i));
		cerr << "\t" << *search_intersection.at(i)->get_lower_case_string() << endl;
	}

	return logs;
}

#endif
