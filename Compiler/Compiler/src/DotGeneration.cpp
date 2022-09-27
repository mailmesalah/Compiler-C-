#include "DotGeneration.h"

using namespace std;

//static members
string mfileName;
ofstream outputFile;
int numberOfNodes = 0;
int count = 0;
int nodeCount = 2;
int level = 1;

std::list<TreeNode*> currentChildren;

DotGeneration::DotGeneration(string pfileName) {
	mfileName = pfileName;
}

void DotGeneration::generate(TreeNode* programNode) {
	

	try {
		
		outputFile.open(mfileName + ".ast.dot");				
		outputFile << "digraph tl12Ast {" << endl;
		outputFile << "ordering=out;" << endl;
		outputFile << "node [shape = box, style = filled, fillcolor=\"white\"];" << endl;
		outputFile << "n" << ++numberOfNodes << " [label=\"" << programNode->data << "\",shape=box]" << endl;
		printDot(programNode);
		
		outputFile << "}" << endl;

		outputFile.close();
	}
	catch (exception e) {
		cout<<e.what();
	}
}

void DotGeneration::printDot(TreeNode* node) {
	//Print children nodes
	for (std::list<TreeNode*>::iterator it = node->children.begin(); it != node->children.end(); ++it) {
		TreeNode *pchildren = (*it);
		outputFile << "n" << ++numberOfNodes << " [label=\"" << pchildren->data + "\",shape=box]" << endl;
		currentChildren.push_back(pchildren);
	}
	this->printChildren();

	//Printing levels and children
	numberOfNodes = 1;
	currentChildren = {};
	level = 1;
	for (std::list<TreeNode*>::iterator it = node->children.begin(); it != node->children.end(); ++it) {
		TreeNode *pchildren = (*it);		
		outputFile << "n" << level << " -> " << "n" << ++numberOfNodes << endl;
		currentChildren.push_back(pchildren);
	}
	//increment level
	++level;
	this->printLevel();
}

void DotGeneration::printChildren() {
	//print each level
	std::list<TreeNode*> nextChildren;
	for (std::list<TreeNode*>::iterator it = currentChildren.begin(); it != currentChildren.end(); ++it) {
		TreeNode *pchildren = (*it);		
		outputFile << "n" << ++numberOfNodes << " [label=\"" << pchildren->data + "\",shape=box]" << endl;

		//adding children for next level iteration
		for (std::list<TreeNode*>::iterator itsub = pchildren->children.begin(); itsub != pchildren->children.end(); ++itsub) {
			nextChildren.push_back((*itsub));
		}
	}
	
	currentChildren = nextChildren;
	if (currentChildren.size() > 0) {
		this->printChildren();
	}
	else {
		return;
	}
}

void DotGeneration::printLevel() {
	//print each level
	std::list<TreeNode*> nextChildren;
	for (std::list<TreeNode*>::iterator it = currentChildren.begin(); it != currentChildren.end(); ++it) {
		TreeNode *pchildren = (*it);
		outputFile << "n" << level << " -> " << "n" << ++numberOfNodes << endl;

		//adding children for next level iteration
		for (std::list<TreeNode*>::iterator itsub = pchildren->children.begin(); itsub != pchildren->children.end(); ++itsub) {
			nextChildren.push_back((*itsub));
		}
	}
	//increment level
	++level;
	currentChildren = nextChildren;
	if (currentChildren.size() > 0) {
		this->printLevel();
	}
	else {
		return;
	}
}
