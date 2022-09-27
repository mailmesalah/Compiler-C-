#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <regex>
#include "TreeNode.h"
using namespace std;


class DotGeneration {
public:

	DotGeneration(string fileName);

	void generate(TreeNode* programNode);
	void printDot(TreeNode* node);
	void printChildren();
	void printLevel();
};