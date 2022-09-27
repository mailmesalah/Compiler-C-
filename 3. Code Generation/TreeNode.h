#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <regex>

using namespace std;

class TreeNode {

private:

	std::list<TreeNode*> elementsIndex;

	void registerChildForSearch(TreeNode* node);

public:
	std::list<TreeNode*> children;
	string data;
	TreeNode* parent=NULL;	

	TreeNode();
	TreeNode(const string pdata);

	TreeNode* addChild(string child);

	bool isRoot();
	bool isLeaf();

	int getLevel();

	TreeNode* findTreeNode(const string cmp);

};

