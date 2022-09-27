#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <regex>
#include "Scanner.h"
#include "TreeNode.h"
#include "Parser.h"


int main(int argc, char *argv[]) {
	try {
		Scanner lexer;
		std::list<string> tokens = lexer.analyse(argv[1]);
		cout << "Scanning is Completed" << endl;
		string inputFile = argv[1];
		string outputFile = inputFile.substr(0, inputFile.find_last_of('.'));
		Parser parser(tokens, outputFile);
		parser.parseTokens();
		cout << "Parsing is Completed" << endl;
		
	}
	catch (exception e) {
		cout << "Error:";
		cout << e.what();
	}

	return 0;
}
