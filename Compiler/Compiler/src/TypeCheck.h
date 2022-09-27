#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <regex>
#include "TreeNode.h"

using namespace std;

class TypeCheck {
	vector<string> flds;
private : 
	void checkChildType();
	TreeNode* getChildAt(int index, TreeNode* node);
	vector<string>& split(char delim, string str);
public:
	TreeNode* checkType(TreeNode* node);
};

