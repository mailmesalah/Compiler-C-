#include "Instruction.h"



std::vector<std::vector<string>> instructionSet;


Instruction::Instruction(string val1, string val2, string val3, string val4)
{
	vector<string> instrs;
	instrs.push_back(val1);
	instrs.push_back(val2);
	instrs.push_back(val3);
	instrs.push_back(val4);
	instructionSet.push_back(instrs);
}

Instruction::Instruction(string fileName)
{
	cout << "Instructions start" << endl;
	for (size_t i = 0; i < instructionSet.size(); i++)
	{
		cout << instructionSet[i].at(0) << instructionSet[i].at(1) << instructionSet[i].at(2) << instructionSet[i].at(3) << endl;
	}
	cout << "Instructions end" << endl;

	new CfgGeneration(instructionSet, fileName);
	new AsmGenerator(instructionSet, fileName);
}


