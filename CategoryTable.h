//
//  CategoryTable.h
//  EECS 281 Project 3
//
//  Created by John West on 3/21/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#ifndef EECS_281_Project_3_CategoryTable_h
#define EECS_281_Project_3_CategoryTable_h

#include "Log.h"

typedef unordered_multimap <int, Log*> CatTable;

class CategoryTable {
private:
	static const int cat_prime = 97;

	CatTable table;

public:
	
};

#endif
