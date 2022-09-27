#include "AsmGenerator.h"

AsmGenerator::AsmGenerator(vector<vector<string>> instructionSet, string fileName)
{
	try {
		ofstream outputFile;
		outputFile.open(fileName + ".s");
		outputFile << "\t.data" << endl;		
		outputFile << "newline: .asciiz \"\\n\"" << endl;		
		outputFile << "\t.text" << endl;		
		outputFile << "\t.globl main" << endl;
		outputFile << "main:" << endl;		
		outputFile << "\tli $fp, 0x7ffffffc" << endl;		

		for (vector<string> n : instructionSet) {
			outputFile << "\t# " << n[0] << " " << n[1] << " " << n[2] << " " << n[3] << endl;

			if (n[1].find("B")==0) {
				outputFile << n[1] << ":" << endl;				
			}
			else if (strcmp(n[0].c_str(),"loadI")==0) {
				outputFile << "\tli $t0, " << n[1] << endl;				
				outputFile << "\tsw $t0, " << stackCheck(n[3]) << "($fp)" << endl;				
			}
			else if (strcmp(n[0].c_str(), "readint")==0) {
				outputFile << "\tli $v0, 5" << endl;				
				outputFile << "\tsyscall" << endl;				
				outputFile << "\tadd $t0, $v0, $zero" << endl;				
				outputFile << "\tsw $t0, " << stackCheck(n[3]) << "($fp)" << endl;				
			}
			else if (!n[0].empty() && !n[1].empty() && !n[2].empty() && !n[3].empty()) {
				outputFile << "\tlw $t1," << stackCheck(n[1]) << "($fp)" << endl;				
				outputFile << "\tlw $t2," << stackCheck(n[2]) << "($fp)" << endl;				
				outputFile << "\t" << n[0] << " $t0, $t1, $t2" << endl;				
				outputFile << "\tsw $t0, " << stackCheck(n[3]) << "($fp)" << endl;				
			}
			else if (strcmp(n[0].c_str(), "exit")==0) {
				outputFile << "\tli $v0, 10" << endl;				
				outputFile << "\tsyscall" << endl;				
			}
			else if (strcmp(n[0].c_str(), "writeint")==0) {
				outputFile << "\tli $v0, 1" << endl;				
				outputFile << "\tlw $t1," << stackCheck(n[3]) << "($fp)" << endl;				
				outputFile << "\tadd $a0, $t1, $zero" << endl;				
				outputFile << "\tsyscall" << endl;				
				outputFile << "\tli $v0, 4" << endl;				
				outputFile << "\tlw $a0, newline" << endl;				
				outputFile << "\tsyscall" << endl;				
			}
			else if (strcmp(n[0].c_str(), "i2i")==0) {
				outputFile << "\tlw $t1," << stackCheck(n[1]) << "($fp)" << endl;				
				outputFile << "\tadd $t0, $t1, $zero" << endl;				
				outputFile << "\tsw $t0, " << stackCheck(n[3]) << "($fp)" << endl;				
			}
			else if (strcmp(n[0].c_str(), "jumpl")==0) {
				outputFile << "\tj " << n[3] << endl;				
			}
			else if (strcmp(n[0].c_str(), "cbr")==0) {
				outputFile << "\tlw $t0," << stackCheck(n[1]) << "($fp)" << endl;				
				outputFile << "\tbne $t0, $zero " << split(',', n[3])[0] << endl;
				outputFile << "L1:" << endl;				
				outputFile << "\tj " << split(',', n[3])[1] << endl;
			}
			outputFile << endl;
		}

		outputFile.close();
	}
	catch (exception e) {
		cout << e.what();
	}
}

int AsmGenerator::stackCheck(string registers)
{
	if (stack.find(registers)!=stack.end()) {
		return stack[registers];
	}
	else {
		stackPointer -= 4;
		stack[registers]= stackPointer;
		return stackPointer;
	}
}

vector<string>& AsmGenerator::split(char delim, string str) {
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
