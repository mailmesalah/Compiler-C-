#include "TypeCheck.h"

std::list<TreeNode*> curChildren;

TreeNode* TypeCheck::checkType(TreeNode* node) {
	//check children nodes
	for (std::list<TreeNode*>::iterator it = node->children.begin(); it != node->children.end(); ++it) {
		TreeNode *pchildren = (*it);
		if (pchildren->data.find("+")==0|| pchildren->data.find("*") == 0|| pchildren->data.find("-") == 0 || pchildren->data.find("div") == 0 || pchildren->data.find("mod") == 0 || pchildren->data.find(":=") == 0 ) {
			if (getChildAt(0, pchildren)->data.find(":") != string::npos && getChildAt(1, pchildren)->data.find(":") != string::npos) {
				string val1 = split(':', getChildAt(0, pchildren)->data)[1];
				string val2 = split(':', getChildAt(1, pchildren)->data)[1];
				if (strcmp(val1.c_str(), val2.c_str()) == 0) {
					pchildren->data = "red" + pchildren->data;
				}
			}
		}
		curChildren.push_back(pchildren);
	}
	this->checkChildType();

	return node;
}

void TypeCheck::checkChildType() {
	std::list<TreeNode*> nextChildren;
	for (std::list<TreeNode*>::iterator it = curChildren.begin(); it != curChildren.end(); ++it) {
		TreeNode *pchildren = (*it);
				
		//adding children for next level iteration
		for (std::list<TreeNode*>::iterator itsub = pchildren->children.begin(); itsub != pchildren->children.end(); ++itsub) {
			nextChildren.push_back((*itsub));
		}
	}

	curChildren = nextChildren;
	if (curChildren.size() > 0) {
		this->checkChildType();
	}
	else {
		return;
	}
}

TreeNode* TypeCheck::getChildAt(int index, TreeNode* node) {
	int i = 0;
	for (std::list<TreeNode*>::iterator it = node->children.begin(); it != node->children.end(); ++it) {

		if (i == index) {
			return *it;
		}

		++i;
	}
	return NULL;
}

vector<string>& TypeCheck::split(char delim, string str) {
	if (!flds.empty()) flds.clear();  // empty vector if necessary
	string work = str;
	string buf = "";
	int i = 0;
	while (i < work.length()) {
		if (work[i] != delim)
			buf += work[i];
		else if (buf.length() > 0) {
			flds.push_back(buf);
			buf = "";
		}
		i++;
	}
	if (!buf.empty())
		flds.push_back(buf);
	return flds;
}


/*int main(int argc, char *argv[]) {
	try {

	}
	catch (exception e) {
	}

	return 0;
}*/