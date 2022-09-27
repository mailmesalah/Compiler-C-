#include "CodeGeneration.h"

int registers = -1;
int CodeGeneration::block = 0;

CodeGeneration::CodeGeneration(TreeNode * programNode, string fileName)
{
	this->programNode = programNode;
	new Instruction("", "B" + ++block, "", "");
	for (TreeNode* n : getChildAt(0,programNode)->children) {
		splitString = split(':', n->data)[1].substr(1, split(':', n->data)[1].length() - 1);
		new Instruction("loadI", "0", "", "r_" + splitString);
		registerList.push_back("r_" + splitString);
	}
	statementNode(getChildAt(1,programNode));

	new Instruction("exit", "", "", "");
	new Instruction(fileName);
}

void CodeGeneration::statementNode(TreeNode * statement)
{
	for (TreeNode* n : statement->children) {
		if (strcmp(n->data.c_str(), ":=") == 0) {
			assignmentStatement(n);
			break;
		}
		else if (strcmp(n->data.c_str(), "while") == 0) {
			new Instruction("jumpl", "", "", "B" + ++block);
			new Instruction("", "B" + block++, "", "");
			whileStatement(n);
		}
		else if (strcmp(n->data.c_str(), "if") == 0) {
			ifStatement(n);
		}
		else if (strcmp(n->data.c_str(), "writeint") == 0) {
			writeInt(n);
		}
	}
}

void CodeGeneration::assignmentStatement(TreeNode * assignmentNode)
{
	regex e1("^[1-9][0-9]*");
	regex e2("^[0]");
	bool matche1 = std::regex_match(split(':', getChildAt(1, assignmentNode)->data)[0], e1);
	bool matche2 = std::regex_match(split(':', getChildAt(1, assignmentNode)->data)[0], e2);
	
	if (getChildAt(1,assignmentNode)->data.find("readint")==0) {
		readint(getChildAt(1, assignmentNode));
	}
	else if (getChildAt(1, assignmentNode)->data.find("+") == 0 || getChildAt(1, assignmentNode)->data.find("-") == 0 || getChildAt(1, assignmentNode)->data.find("*") == 0 || getChildAt(1, assignmentNode)->data.find("div") == 0 || getChildAt(1, assignmentNode)->data.find("mod") == 0) {
		new Instruction("i2i", binary(getChildAt(1, assignmentNode)), "", "r_" + split(':', getChildAt(1, assignmentNode)->data)[0]);
	}
	else if (matche1 || matche2) {
		new Instruction("loadI", split(':', getChildAt(1, assignmentNode)->data)[0], "", "r_" + ++registers);
		new Instruction("i2i", "r_" + registers, "", "r_" + split(':', getChildAt(0, assignmentNode)->data)[0]);
	}
}

void CodeGeneration::readint(TreeNode * readNode)
{
	new Instruction("readint", "", "", "r_" + split(':', getChildAt(0, readNode->parent)->data)[0]);
}

string CodeGeneration::binary(TreeNode * binaryNode)
{
	registers++;
	regex e1("^[1-9][0-9]*");
	//regex e2("^[0]");
	bool matche1 = std::regex_match(split(':', getChildAt(0, binaryNode)->data)[0], e1);
	bool matche2 = std::regex_match(split(':', getChildAt(1, binaryNode)->data)[0], e1);
	if (matche1) {
		new Instruction("loadI", split(':', getChildAt(0, binaryNode)->data)[0], "", "r_" + registers);
	}
	else if (matche2) {
		new Instruction("loadI", split(':', getChildAt(1, binaryNode)->data)[0], "", "r_" + registers);
	}

	if (binaryNode->data.find("+")==0) {
		if (matche1) {
			new Instruction("add", "r_" + registers++, "r_" + split(':', getChildAt(1, binaryNode)->data)[0], "r_" + registers);
		}
		else if (matche2) {
			new Instruction("add", "r_" + split(':', getChildAt(0, binaryNode)->data)[0], "r_" + registers++, "r_" + registers);
		}
		else {
			new Instruction("add", "r_" + split(':', getChildAt(0, binaryNode)->data)[0], "r_" + split(':', getChildAt(1, binaryNode)->data)[0], "r_" + registers);
		}
	}
	else if (binaryNode->data.find("-") == 0) {
		if (matche1) {
			new Instruction("sub", "r_" + registers++, "r_" + split(':', getChildAt(1, binaryNode)->data)[0], "r_" + registers);
		}
		else if (matche2) {
			new Instruction("sub", "r_" + split(':', getChildAt(0, binaryNode)->data)[0], "r_" + registers++, "r_" + registers);
		}
		else {
			new Instruction("sub", "r_" + split(':', getChildAt(0, binaryNode)->data)[0], "r_" + split(':', getChildAt(1, binaryNode)->data)[0], "r_" + registers);
		}
	}
	else if (binaryNode->data.find("*") == 0) {
		if (matche1) {
			new Instruction("mul", "r_" + registers++, "r_" + split(':', getChildAt(1, binaryNode)->data)[0], "r_" + registers);
		}
		else if (matche2) {
			new Instruction("mul", "r_" + split(':', getChildAt(0, binaryNode)->data)[0], "r_" + registers++, "r_" + registers);
		}
		else {
			new Instruction("mul", "r_" + split(':', getChildAt(0, binaryNode)->data)[0], "r_" + split(':', getChildAt(1, binaryNode)->data)[0], "r_" + registers);
		}
	}
	return "r_" + registers;
}

void CodeGeneration::whileStatement(TreeNode * whileStatementNode)
{
	new Instruction("mul", "r_" + split(':', getChildAt(0, getChildAt(0, whileStatementNode))->data)[0], "r_" + split(':', getChildAt(1, getChildAt(0, whileStatementNode))->data)[0], "r_" + ++registers);
	
	if (strcmp(split(':', getChildAt(0, whileStatementNode)->data)[0].c_str(), "<=") == 0) {
		new Instruction("sle", "r_" + registers, "r_" + split(':', getChildAt(2, getChildAt(0, whileStatementNode))->data)[0], "r_" + ++registers);		
	}

	else if (strcmp(split(':', getChildAt(0, whileStatementNode)->data)[0].c_str(), "=") == 0) {
		new Instruction("sge", "r_" + registers, "r_" + split(':', getChildAt(2, getChildAt(0, whileStatementNode))->data)[0], "r_" + ++registers);
	}
	else if (strcmp(split(':', getChildAt(0, whileStatementNode)->data)[0].c_str(), "==") == 0) {
		new Instruction("seq", "r_" + registers, "r_" + split(':', getChildAt(2, getChildAt(0, whileStatementNode))->data)[0], "r_" + ++registers);
	}
	else if (strcmp(split(':', getChildAt(0, whileStatementNode)->data)[0].c_str(), ">") == 0) {
		new Instruction("sgt", "r_" + registers, "r_" + split(':', getChildAt(2, getChildAt(0, whileStatementNode))->data)[0], "r_" + ++registers);
	}
	else if (strcmp(split(':', getChildAt(0, whileStatementNode)->data)[0].c_str(), "<") == 0) {
		new Instruction("slt", "r_" + registers, "r_" + split(':', getChildAt(2, getChildAt(0, whileStatementNode))->data)[0], "r_" + ++registers);
	}
	else if (strcmp(split(':', getChildAt(0, whileStatementNode)->data)[0].c_str(), "!=") == 0) {
		new Instruction("sne", "r_" + registers, "r_" + split(':', getChildAt(2, getChildAt(0, whileStatementNode))->data)[0], "r_" + ++registers);
	}

	string str4 = "B" + block ;
	str4 += ",B";
	str4 += ++block;
	new Instruction("cbr", "r_" + registers, "",str4);
	new Instruction("", "B" + (block - 1), "", "");
	statementNode(getChildAt(1, whileStatementNode));
	new Instruction("jumpl", "", "", "B" + (block - 2));
	new Instruction("", "B" + block, "", "");
}

void CodeGeneration::ifStatement(TreeNode * ifStatementNode)
{
}

void CodeGeneration::writeInt(TreeNode * writeintStatement)
{
	if (getChildAt(0,writeintStatement)->data.find("+")==0 || getChildAt(0, writeintStatement)->data.find("*") == 0) {
		binary(getChildAt(0, writeintStatement));
		new Instruction("writeint", "", "", "r_" + registers);
	}
	else {
		new Instruction("writeint", "", "", "r_" + split(':', getChildAt(0, writeintStatement)->data)[0]);
	}
}

vector<string>& CodeGeneration::split(char delim, string str) {
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

TreeNode* CodeGeneration::getChildAt(int index, TreeNode* node) {
	int i = 0;
	for (std::list<TreeNode*>::iterator it = node->children.begin(); it != node->children.end(); ++it) {

		if (i == index) {
			return *it;
		}

		++i;
	}
	return NULL;
}

/*int main(int argc, char *argv[]) {
try {

}
catch (exception e) {
}

return 0;
}*/
