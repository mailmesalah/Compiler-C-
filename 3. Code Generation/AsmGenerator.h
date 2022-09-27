#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <regex>
#include <map>
#include "TreeNode.h"

using namespace std;

class AsmGenerator {
private :
	map<string, int> stack ;
	int stackPointer = 4;
	vector<string> flds;
public : 
	AsmGenerator(vector<vector<string>> instructionSet, string fileName);
	int stackCheck(string registers);
	vector<string>& split(char delim, string str);
};

