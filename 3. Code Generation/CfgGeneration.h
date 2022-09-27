#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <regex>
#include "TreeNode.h"
#include "CodeGeneration.h"

using namespace std;

class CfgGeneration {

public:
	CfgGeneration(vector<vector<string>> instructionSet, string fileName);
};
