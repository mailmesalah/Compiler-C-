#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <regex>
#include "TreeNode.h"
#include "Instruction.h"

using namespace std;

class CodeGeneration {
	TreeNode* programNode;
	string splitString;	
	list<string> registerList;	
	vector<string> flds;
public :
	static int block;
	CodeGeneration(TreeNode* programNode, string fileName);
	void statementNode(TreeNode* statement);
	void assignmentStatement(TreeNode* assignmentNode);

	void readint(TreeNode* readNode);

	string binary(TreeNode* binaryNode);
	void whileStatement(TreeNode* whileStatementNode);

	void ifStatement(TreeNode* ifStatementNode);
	void writeInt(TreeNode* writeintStatement);

	TreeNode* getChildAt(int index, TreeNode* node);
	vector<string>& split(char delim, string str);
};

