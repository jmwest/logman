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

	void  insert_word_log(Log* log);

	LogQueue* get_word_logs(string* &words);
};

KeywordTable::KeywordTable() {}

void KeywordTable:: insert_word_log(Log* log) {

	// append the category and message together for keyword
	string message = *log->get_category();
	char c = ' ';
	message.append(&c, 1);
	message.append(log->get_message()->begin(), log->get_message()->end());

	for (int i = 0; i < int(message.size()); ++i) {
		message.at(i) = std::tolower(message.at(i));
	}

	int word_start = 0;
	for (int i = 0; i <= int(message.length()); ++i) {

		if ((i == int(message.length())) || !isalnum(int(message.at(i)))) {

			if (word_start != i) {
				string word = message.substr(word_start, i - word_start);

				k_table.insert(WordTable::value_type(word, log));
			}

			word_start = i + 1;
		}
	}

	return;
}

LogQueue* KeywordTable::get_word_logs(string* &words) {

	LogQueue* logs = new LogQueue ();

	vector <string> individual_words;

	deque <Log*> one, two;
	deque <Log*>* to_use = &one;
	deque <Log*>* current_min = &two;

	for (int i = 0; i < int(words->size()); ++i) {
		words->at(i) = std::tolower(words->at(i));
	}

	int word_start = 0;
	for (int i = 0; i <= int(words->length()); ++i) {

		if ((i == int(words->length())) || !isalnum(int(words->at(i)))) {

			if (word_start != i) {
				individual_words.push_back(words->substr(word_start, i - word_start));
			}

			word_start = i + 1;
		}
	}

	for (int i = 0; i < int(individual_words.size()); ++i) {

		pair <WordTable::iterator, WordTable::iterator> keys = k_table.equal_range(individual_words.at(i));

		for (WordTable::iterator it = keys.first; it != keys.second; ++it) {
			to_use->push_back(it->second);
		}

		if (current_min->empty()) {
			deque <Log*>* temp = current_min;
			current_min = to_use;
			to_use = temp;
		}
		else {
			if (current_min->size() > to_use->size()) {
				deque <Log*>* temp = current_min;
				current_min = to_use;
				to_use = temp;
			}

			*to_use = deque <Log*>();
		}
	}

	while (!current_min->empty()) {
		Log* log = current_min->front();

		bool add_log = true;

		for (int j = 0; j < int(individual_words.size()); ++j) {
			string word = *log->get_category();
			char c = ' ';
			word.append(&c);
			word.append(log->get_message()->begin(), log->get_message()->end());

			for (int k = 0; k < int(word.size()); ++k) {
				word.at(k) = std::tolower(word.at(k));
			}
			
			if (word.find(individual_words.at(j)) == string::npos) {
				add_log = false;

				break;
			}
		}

		if (add_log) {
			logs->push(log);
		}

		current_min->pop_front();
	}

	return logs;
}

#endif
