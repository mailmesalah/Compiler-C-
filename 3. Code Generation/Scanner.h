#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <regex>

using namespace std;

class Scanner {
public:

	std::list<string> analyse(string inputFile);

	// trim from start (in place)
	//static inline void ltrim(std::string &s);

	// trim from end (in place)
	//static inline void rtrim(std::string &s);

	// trim from both ends (in place)
	//static inline std::string trim(std::string &s);

};
