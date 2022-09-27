#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <regex>
#include "TreeNode.h"
#include "DotGeneration.h"
#include "TypeCheck.h"

using namespace std;

//class TreeNode;

class Parser {
public:
	

	//Tree Declarations
	TreeNode* declarationNode;
	TreeNode* programNode;
	TreeNode* beginNode;
	TreeNode* statementSequenceNode;
	TreeNode* endNode;
	TreeNode* varNode;
	TreeNode* idenNode;
	TreeNode* asNode;
	TreeNode* scNode;
	TreeNode* typeNode;
	TreeNode* intNode;
	TreeNode* boolNode;
	TreeNode* statementNode;
	TreeNode* assignmentNode;
	TreeNode* ifStatementNode;
	TreeNode* whileStatementNode;
	TreeNode* writeintNode;
	TreeNode* asgnNode;
	TreeNode* assignmentModifiedNode;
	TreeNode* expressionNode;
	TreeNode* readInt;
	TreeNode* ifNode;
	TreeNode* thenNode;
	TreeNode* elseClauseNode;
	TreeNode* elseNode;
	TreeNode* whileNode;
	TreeNode* doNode;
	TreeNode* compareNode;
	TreeNode* compNode;
	TreeNode* simpleExpressionNode;
	TreeNode* writeNode;
	TreeNode* termNode;
	TreeNode* addNode;
	TreeNode* additiveNode;
	TreeNode* rpNode;
	TreeNode* lpNode;
	TreeNode* boollitNode;
	TreeNode* numNode;
	TreeNode* multiNode;
	TreeNode* factorNode;
	TreeNode* multiplicativeNode;
	TreeNode* emptyNode;
	TreeNode* whileStatementSequenceNode;
	TreeNode* ifStatementSequenceNode;
	
	
	//Tree Declarations Ends
	Parser(std::list<string> tokens, string fileName);

	string getTockenAt(int index);

	void parseTokens();

	void match(string token);

	// <program>::=PROGRAM <declarations> BEGIN <statementSequence> END
	void program();

	//<declarations>::=VAR ident AS <type> SC <declarations>|E
	void declarations();
		
	//<type>::=INT||BOOL
	void type();	
	
	//<statementSequence>::=<statement> SC <statementSequence> | E
	void statementSequence();
	
	//<statement>::=<assignment>||<ifStatement>||<whileStatement>||<writeInt>
	void statement();
	
	//<assignment>::=ident ASGN <assignmentModified>
	void assignment();
	
	//<assignmentModified>::=<expression>|READINT
	void assignmentModified();
	
	//<ifStatement>::=IF<expression> THEN <statementSequence> <elseClause> END
	void ifStatement();
	
	//<elseClause>::=ELSE<statementSequence>|E
	void elseClause();

	//<whileStatement>::=WHILE<expression> DO <statementSequence> END
	void whileStatement();

	//<writeint>::=WRITEINT<expression>
	void writeInt();

	//<expression>::=<simpleExpression><comp>
	static int com;
	void expression();

	//<comp>::=COMPARE<expression>|E
	void comp();

	//<simpleExpression>::=<term><add>
	void simpleExpression();

	//<add>::==ADDITIVE<simpleExpression>|E
	void add();

	//<term>::=<factor><multi>
	void term();

	//<multi>::=MULTIPLICATIVE<term>|E
	void multi();

	//<factor>::=ident|num|boollit|LP<expression>RP
	void factor();
};