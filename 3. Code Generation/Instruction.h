#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <regex>
#include "TreeNode.h"
#include "CfgGeneration.h"
#include "AsmGenerator.h"

using namespace std;


class Instruction {

public:
	Instruction(string val1, string val2, string val3, string val4);
	Instruction(string fileName);
};

