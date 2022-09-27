#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <regex>

using namespace std;

namespace lexer {
	class Scanner {
	public:

		std::list<string> analyse(string inputFile) {
			std::list<string> tokens;
			string line;
			// open a file in read mode.
			ifstream inFile(inputFile.c_str());
			if (inFile.is_open())
			{
				string currentLine;
				int flag = 0;
				while (getline(inFile, line))
				{
					if (!line.empty()) {
						line = trim(line);//Trims the line
						std::replace(line.begin(), line.end(), '\t', ' ');//all tabs are converted to space
						regex e("\\s{2,}");
						line = std::regex_replace(line, e, " ");

						if (line.find("%") != std::string::npos) {
							currentLine = line.substr(0, line.find_first_of('%'));
							if (currentLine.empty()) {
								continue;
							}
						}
						else {
							currentLine = line;
						}

						char *str = const_cast<char *>(currentLine.c_str());
						char *tok;
						tok = strtok(str, " ");

						while (tok != NULL) {
							string sToken;

							if (strcmp(tok, "(") == 0) {
								sToken.append("LP(");
								sToken.append(tok);
								sToken.append(")");
								tokens.push_back(sToken);
								//cout << "LP(" << tok << ")";							
							}
							else if (strcmp(tok, ")") == 0) {
								sToken.append("RP(");
								sToken.append(tok);
								sToken.append(")");
								tokens.push_back(sToken);
								//cout << "RP(" << tok << ")";
							}
							else if (strcmp(tok, ":=") == 0) {
								sToken.append("ASGN(");
								sToken.append(tok);
								sToken.append(")");
								tokens.push_back(sToken);
								//cout << "ASGN(" << tok << ")";
							}
							else if (strcmp(tok, ";") == 0) {
								sToken.append("SC(");
								sToken.append(tok);
								sToken.append(")");
								tokens.push_back(sToken);
								//cout << "SC(" << tok << ")";
							}
							else if (strcmp(tok, "*") == 0 || strcmp(tok, "mod") == 0 || strcmp(tok, "div") == 0) {
								sToken.append("MULTIPLICATIVE(");
								sToken.append(tok);
								sToken.append(")");
								tokens.push_back(sToken);
								//cout << "MULTIPLICATIVE(" << tok << ")";
							}
							else if (strcmp(tok, "+") == 0 || strcmp(tok, "-") == 0) {
								sToken.append("ADDITIVE(");
								sToken.append(tok);
								sToken.append(")");
								tokens.push_back(sToken);
								//cout << "ADDITIVE(" << tok << ")";
							}
							else if (strcmp(tok, "=") == 0 || strcmp(tok, "!=") == 0 || strcmp(tok, "<") == 0 || strcmp(tok, ">") == 0 || strcmp(tok, "<=") == 0 || strcmp(tok, ">=") == 0) {
								sToken.append("COMPARE(");
								sToken.append(tok);
								sToken.append(")");
								tokens.push_back(sToken);
								//cout << "COMPARE(" << tok << ")";
							}
							else if (strcmp(tok, "if") == 0) {
								sToken.append("IF");
								tokens.push_back(sToken);
								//cout << "IF";
							}
							else if (strcmp(tok, "then") == 0) {
								sToken.append("THEN");
								tokens.push_back(sToken);
								//cout << "THEN";
							}
							else if (strcmp(tok, "else") == 0) {
								sToken.append("ELSE");
								tokens.push_back(sToken);
								//cout << "ELSE";
							}
							else if (strcmp(tok, "begin") == 0) {
								sToken.append("BEGIN");
								tokens.push_back(sToken);
								//cout << "BEGIN";
							}
							else if (strcmp(tok, "end") == 0) {
								sToken.append("END");
								tokens.push_back(sToken);
								//cout << "END";
							}
							else if (strcmp(tok, "while") == 0) {
								sToken.append("WHILE");
								tokens.push_back(sToken);
								//cout << "WHILE";
							}
							else if (strcmp(tok, "do") == 0) {
								sToken.append("DO");
								tokens.push_back(sToken);
								//cout << "DO";
							}
							else if (strcmp(tok, "program") == 0) {
								sToken.append("RPOGRAM");
								tokens.push_back(sToken);
								//cout << "PROGRAM";
							}
							else if (strcmp(tok, "var") == 0) {
								sToken.append("VAR");
								tokens.push_back(sToken);
								//cout << "VAR";
							}
							else if (strcmp(tok, "as") == 0) {
								sToken.append("AS");
								tokens.push_back(sToken);
								//cout << "AS";
							}
							else if (strcmp(tok, "int") == 0) {
								sToken.append("INT");
								tokens.push_back(sToken);
								//cout << "INT";
							}
							else if (strcmp(tok, "bool") == 0) {
								sToken.append("BOOL");
								tokens.push_back(sToken);
								//cout << "BOOL";
							}
							else if (strcmp(tok, "writeint") == 0) {
								sToken.append("WRITEINT");
								tokens.push_back(sToken);
								//cout << "WRITEINT";
							}
							else if (strcmp(tok, "readint") == 0) {
								sToken.append("READINT");
								tokens.push_back(sToken);
								//cout << "READINT";
							}
							else if (strcmp(tok, "false") == 0 || strcmp(tok, "true") == 0) {
								sToken.append("boollit(");
								sToken.append(tok);
								sToken.append(")");
								tokens.push_back(sToken);
								//cout << "boollit(" << tok << ")";
							}
							else {
								regex e1("^[1-9][0-9]*");
								regex e2("^[0]");
								regex e3("^[A-Z][A-Z0-9]*");
								bool matche1 = std::regex_match(tok, e1);
								bool matche2 = std::regex_match(tok, e2);
								bool matche3 = std::regex_match(tok, e3);
								if (matche1 || matche2) {
									sToken.append("num(");
									sToken.append(tok);
									sToken.append(")");
									tokens.push_back(sToken);
									//cout << "num(" << tok << ")";
								}
								else if (matche3) {
									sToken.append("iden(");
									sToken.append(tok);
									sToken.append(")");
									tokens.push_back(sToken);
									//cout << "iden(" << tok << ")";
								}
								else {
									cout << "Lexical error : " << tok;
									flag = 1;
								}
							}


							if (flag == 1) {
								break;
							}

							tok = strtok(NULL, " ");
						}
					}
				}
				inFile.close();

				// open a file in write mode.
				ofstream outFile;

				string outputFile = inputFile.substr(0, inputFile.find_last_of('.'));
				outputFile.append(".tok");
				outFile.open(outputFile);
				for (std::list<string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {
					outFile << *it << endl;
				}

				outFile.close();
			}
			else {
				cout << "File Couldnt be Opened."<<endl;
			}



			return tokens;
		}

		// trim from start (in place)
		static inline void ltrim(std::string &s) {
			s.erase(s.begin(), std::find_if(s.begin(), s.end(),
				std::not1(std::ptr_fun<int, int>(std::isspace))));
		}

		// trim from end (in place)
		static inline void rtrim(std::string &s) {
			s.erase(std::find_if(s.rbegin(), s.rend(),
				std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		}

		// trim from both ends (in place)
		static inline std::string trim(std::string &s) {
			ltrim(s);
			rtrim(s);
			return s;
		}

	};
}

using namespace lexer;
int main(int argc, char *argv[]) {
	try {
		Scanner lexer;
		std::list<string> tokens = lexer.analyse(argv[1]);
		cout << "Scanning is Completed" << endl;
	}
	catch (exception e) {
		cout << e.what();
	}
	return 0;
}