#include "Parser.h"

using namespace std;

//static members
std::list<string> tokens;
string fileName;
int tokCount=0;
int flag=1;
string lookAhead=" ";

int whileToken=1;
int ifToken=1;


string iden = "";
string mType;
int com = 0;

Parser::Parser(std::list<string> ptokens, string pfileName) {
	tokens = ptokens;
	fileName = pfileName;
	tokCount = 0;
	lookAhead = getTockenAt(tokCount);
}

string Parser::getTockenAt(int index) {
	int i = 0;
	for (std::list<string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {
		
		if (i==index) {
			return *it;
		}

		++i;
	}
	return " ";
}

void Parser::match(string token) {
	if (strcmp(token.c_str(),lookAhead.c_str())==0 && tokCount<tokens.size()- 1) {
		lookAhead = getTockenAt(++tokCount);
	}
	else if (strcmp(token.c_str(), lookAhead.c_str()) != 0) {
		cout<<"Parsing Error Expected: " << token << " Found: " << lookAhead<<endl;
		flag = 0;
	}
}

// <program>::=PROGRAM <declarations> BEGIN <statementSequence> END
void Parser::program() {
	if (strcmp(lookAhead.c_str(),"PROGRAM")==0) {
		const string sProgram = "program";
		programNode= new TreeNode(sProgram);
		cout << programNode->data<<endl;
		this->match("PROGRAM");
		declarationNode = programNode->addChild("decl list");
		cout << declarationNode->data<<endl;
		this->declarations();
		this->match("BEGIN");
		statementSequenceNode = programNode->addChild("stmt list");
		cout << statementSequenceNode->data<<endl;
		this->statementSequence();
		this->match("END");
	}
}

void Parser::declarations() {
	if (strcmp(lookAhead.c_str(),"VAR")==0) {
		this->match("VAR");
		
		if (lookAhead.find("iden(")!= string::npos) {
			iden = lookAhead;
			this->match(lookAhead);
		}
		this->match("AS");
		this->type();
		idenNode = declarationNode->addChild("decl:'" + iden.substr(5, iden.length() - 6) + "':" + mType);
		cout << idenNode->data<<endl;
		this->match("SC(;)");
		this->declarations();
	}
	else {
		return;
	}
}

//<type>::=INT||BOOL
void Parser::type() {
	if (strcmp(lookAhead.c_str(),"INT")==0) {
		this->match("INT");
		mType = "int";
	}
	else if (strcmp(lookAhead.c_str(),"BOOL")==0) {
		this->match("BOOL");
		mType = "bool";
	}
}

//<statementSequence>::=<statement> SC <statementSequence> | E
void Parser::statementSequence() {
	if (lookAhead.find("iden(")!=string::npos || strcmp(lookAhead.c_str(),"IF")==0 || strcmp(lookAhead.c_str(), "WHILE")==0 || strcmp(lookAhead.c_str(), "WRITEINT")==0) {
		this->statement();
		this->match("SC(;)");
		this->statementSequence();
	}
	else {
		return;
	}
}

//<statement>::=<assignment>||<ifStatement>||<whileStatement>||<writeInt>
void Parser::statement() {
	if (lookAhead.find("iden(") != string::npos) {
		ifToken = 1;
		if (whileToken == 0) {
			assignmentNode = whileStatementSequenceNode->addChild(":=");
			cout << assignmentNode->data<<endl;
		}
		else {
			assignmentNode = statementSequenceNode->addChild(":=");
			cout << assignmentNode->data<<endl;
		}
		this->assignment();
	}
	else if (strcmp(lookAhead.c_str(), "IF")==0) {
		if (whileToken == 0) {
			ifStatementNode = whileStatementSequenceNode->addChild("if");
			cout << ifStatementNode->data<<endl;
		}
		else if (ifToken == 0) {
			assignmentNode = ifStatementSequenceNode->addChild(":=");
			cout << assignmentNode->data<<endl;
		}
		else {
			ifStatementNode = statementSequenceNode->addChild("if");
			cout << ifStatementNode->data<<endl;
		}
		this->ifStatement();
	}
	else if (strcmp(lookAhead.c_str(), "WHILE")==0) {
		whileToken = 0;
		if (ifToken == 0) {
			assignmentNode = ifStatementSequenceNode->addChild(":=");
			cout << assignmentNode->data<<endl;
		}
		else {
			whileStatementNode = statementSequenceNode->addChild("while");
			cout << whileStatementNode->data<<endl;
		}
		this->whileStatement();
	}
	else if (strcmp(lookAhead.c_str(), "WRITEINT")==0) {
		if (whileToken == 0) {
			writeintNode = whileStatementSequenceNode->addChild("writeint");
			cout << writeintNode->data<<endl;
		}
		else {
			writeintNode = statementSequenceNode->addChild("writeint");
			cout << writeintNode->data<<endl;
		}
		this->writeInt();
	}
}

//<assignment>::=ident ASGN <assignmentModified>
void Parser::assignment() {
	if (lookAhead.find("iden(")!=string::npos) {
		idenNode = assignmentNode->addChild(lookAhead.substr(5, lookAhead.length() - 6) + ":int");
		cout << idenNode->data<<endl;
		this->match(lookAhead);
		this->match("ASGN(:=)");
		this->assignmentModified();
	}
}

//<assignmentModified>::=<expression>|READINT
void Parser::assignmentModified() {
	if (lookAhead.find("iden(")!=string::npos || lookAhead.find("num(") != string::npos || lookAhead.find("boollit(") != string::npos || strcmp(lookAhead.c_str(), "LP(()")==0) {
		expressionNode = assignmentNode->addChild("expression");
		cout << expressionNode->data<<endl;
		this->expression();
	}
	else if (strcmp(lookAhead.c_str(), "READINT")==0) {
		readInt = assignmentNode->addChild("readint:int");
		cout << readInt->data<<endl;
		this->match("READINT");
	}
}

//<ifStatement>::=IF<expression> THEN <statementSequence> <elseClause> END
void Parser::ifStatement() {
	if (strcmp(lookAhead.c_str(), "IF")==0) {
		this->match("IF");
		expressionNode = ifStatementNode->addChild("expression");
		cout << expressionNode->data<<endl;
		this->expression();
		this->match("THEN");
		ifStatementSequenceNode = ifStatementNode->addChild("StatementSequence");
		cout << ifStatementSequenceNode->data<<endl;
		this->statementSequence();
		elseClauseNode = ifStatementNode->addChild("elseClause");
		cout << elseClauseNode->data<<endl;
		this->elseClause();
		this->match("END");
		ifToken = 1;
	}
}

//<elseClause>::=ELSE<statementSequence>|E
void  Parser::elseClause() {
	if (strcmp(lookAhead.c_str(), "ELSE")==0) {
		elseNode = elseClauseNode->addChild("else");
		cout << elseNode->data<<endl;
		this->match("ELSE");
		statementSequenceNode = elseClauseNode->addChild("StatementSequnce");
		cout << statementSequenceNode->data<<endl;
		this->statementSequence();
	}
	else {
		return;
	}
}

//<whileStatement>::=WHILE<expression> DO <statementSequence> END
void  Parser::whileStatement() {
	if (strcmp(lookAhead.c_str(), "WHILE")==0) {
		this->match("WHILE");
		expressionNode = whileStatementNode->addChild("expression");
		cout << expressionNode->data<<endl;
		this->expression();
		this->match("DO");
		whileStatementSequenceNode = whileStatementNode->addChild("StatementSequence");
		cout << whileStatementSequenceNode->data<<endl;
		this->statementSequence();
		this->match("END");
		whileToken = 1;
	}
}

//<writeint>::=WRITEINT<expression>
void  Parser::writeInt() {
	if (strcmp(lookAhead.c_str(), "WRITEINT")==0) {
		this->match("WRITEINT");
		expressionNode = writeintNode->addChild("Expression");
		cout << expressionNode->data<<endl;
		this->expression();
	}
}

//<expression>::=<simpleExpression><comp>
void  Parser::expression() {
	if (lookAhead.find("iden(")!=string::npos || lookAhead.find("num(")!=string::npos || lookAhead.find("boollit(")!=string::npos || strcmp(lookAhead.c_str(), "LP(()")==0) {		
		this->simpleExpression();			
		this->comp();
	}
}


//<comp>::=COMPARE<expression>|E
void  Parser::comp() {
	if (lookAhead.find("COMPARE") != string::npos) {
		compareNode = expressionNode->addChild(lookAhead.substr(8, lookAhead.length() - 9) + ":bool");
		cout << compareNode->data<<endl;
		this->match(lookAhead);
		expressionNode = expressionNode->addChild("Expression");
		cout << expressionNode->data<<endl;
		this->expression();
	}
	else {
		return;
	}
}

//<simpleExpression>::=<term><add>
void  Parser::simpleExpression() {
	if (lookAhead.find("iden(")!=string::npos || lookAhead.find("num(")!=string::npos || lookAhead.find("boollit(")!=string::npos || strcmp(lookAhead.c_str(), "LP(()")==0) {		
		this->term();		
		this->add();
	}
}

//<add>::==ADDITIVE<simpleExpression>|E
void  Parser::add() {
	if (lookAhead.find("ADDITIVE(")!=string::npos) {
		additiveNode = expressionNode->addChild(lookAhead.substr(9, lookAhead.length() - 10) + ":int");
		cout << additiveNode->data<<endl;
		this->match(lookAhead);		
		this->simpleExpression();
	}
	else {
		return;
	}
}

//<term>::=<factor><multi>
void  Parser::term() {
	if (lookAhead.find("iden(")!=string::npos || lookAhead.find("num(")!=string::npos || lookAhead.find("boollit(")!=string::npos || strcmp(lookAhead.c_str(), "LP(()")==0) {		
		this->factor();		
		this->multi();
	}
}

//<multi>::=MULTIPLICATIVE<term>|E
void  Parser::multi() {
	if (lookAhead.find("MULTIPLICATIVE(")!=string::npos) {
		multiplicativeNode = expressionNode->addChild(lookAhead.substr(15, lookAhead.length() - 16) + "int");
		cout << multiplicativeNode->data<<endl;
		this->match(lookAhead);		
		this->term();
	}
	else {
		return;
	}
}

//<factor>::=ident|num|boollit|LP<expression>RP
void  Parser::factor() {
	if (lookAhead.find("iden(")!=string::npos) {
		idenNode = expressionNode->addChild(lookAhead.substr(5, lookAhead.length() - 6) + ":int");
		cout << idenNode->data<<endl;
		this->match(lookAhead);
	}
	else if (lookAhead.find("num(")!=string::npos) {
		numNode = expressionNode->addChild(lookAhead.substr(4, lookAhead.length() - 5) + ":int");
		cout << numNode->data<<endl;
		this->match(lookAhead);
	}
	else if (lookAhead.find("boollit(")!=string::npos) {
		boollitNode = expressionNode->addChild(lookAhead.substr(8, lookAhead.length() - 9) + ":bool");
		cout << boollitNode->data<<endl;
		this->match(lookAhead);
	}
	else if (strcmp(lookAhead.c_str(), "LP(()")==0) {
		lpNode = expressionNode->addChild(lookAhead.substr(3, lookAhead.length() - 4));
		cout << lpNode->data<<endl;
		this->match("LP(()");
		expressionNode = expressionNode->addChild("expression");
		cout << expressionNode->data<<endl;
		this->expression();
		rpNode = expressionNode->addChild(lookAhead.substr(3, lookAhead.length() - 4));
		cout << rpNode->data<<endl;
		this->match("RP())");
	}
}

void Parser::parseTokens() {
	this->program();
	if (strcmp(lookAhead.c_str(), "END")==0 && flag == 1) {
		cout<<"Parsing Success"<<endl;
	}
	CodeGeneration(programNode, fileName);

	TypeCheck tc;
	programNode = tc.checkType(programNode);
	
	DotGeneration dot(fileName);
	dot.generate(programNode);
}
