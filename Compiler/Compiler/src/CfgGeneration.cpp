#include "CfgGeneration.h"



CfgGeneration::CfgGeneration(vector<vector<string>> instructionSet, string fileName) {
	try {
		int nodeNumber = 0;
		ofstream outputFile;
		outputFile.open(fileName + ".3A.cfg.dot");
		outputFile << "digraph graphviz {" << endl;
		outputFile << "node [shape = none];" << endl;
		outputFile << "edge [tailport = s];" << endl;
		outputFile << "entry" << endl;
		outputFile << "subgraph cluster {" << endl;
		outputFile << "color=\"/x11/white\" ";
		//System.out.println(CodeGeneration.block);
		int b = 1;
		int insnum = 0;
		int know = 0;
		vector<int> jump;
		vector<int> cbr;
		while (nodeNumber < CodeGeneration::block) {
			outputFile << "n" << nodeNumber << " [label=<<table border=\"0\">";
			for (vector<string> n : instructionSet) {
				insnum++;
				if (insnum < know) {
					continue;
				}
				//fop.write("<tr><td>"+insnum+"</td></tr>");	
				if (n[1].find("B" + (b + 1)) == 0) {
					b++;
					know = insnum;
					break;
				}
				if (n[1].find("B" + b) == 0) {
					outputFile << "<tr>";
					outputFile << "<td border=\"1\" colspan=\"3\">" << n[1] << "</td>";
					outputFile << "</tr>";
				}
				else {
					outputFile << "<tr>";
					outputFile << "<td align=\"left\">" << n[0] << "</td>";
					outputFile << "<td align=\"left\">" << n[1] << "</td>";
					outputFile << "<td align=\"left\">" << n[2] << "</td>";
					outputFile << "<td align=\"left\"> =&gt; </td>";
					outputFile << "<td align=\"left\">" << n[3] << "</td>";
					outputFile << "</tr>";
				}
				if (strcmp(n[0].c_str(), "jumpl") == 0) {
					jump.push_back(nodeNumber);
				}
				if (strcmp(n[0].c_str(), "cbr") == 0) {
					cbr.push_back(nodeNumber);
				}
			}
			outputFile << "</table>>,fillcolor=\"/x11/white\",shape=box]";
			nodeNumber++;
			insnum = 0;
		}
		outputFile << endl;
		outputFile << "}" << endl;
		outputFile << "entry -> n0" << endl;
		int count = 0;
		int j = 0;
		for (vector<string> n : instructionSet) {
			if (strcmp(n[0].c_str(), "jumpl") == 0 && count < jump.size()) {
				outputFile << "n" << jump[count] << "-> n" << (stoi(n[3].substr(1, n[3].length())) - 1) << endl;
				count++;
			}
			else if (strcmp(n[0].c_str(), "cbr") == 0 && j < cbr.size()) {
				outputFile << "n" << cbr[j] << "-> n" << (stoi(n[3].substr(1, 2)) - 1) << endl;
				outputFile << "n" << cbr[j] << "-> n" << (stoi(n[3].substr(4, 5)) - 1) << endl;
				j++;
			}
		}
		outputFile << endl;
		outputFile << "n" << (nodeNumber - 1) << "->exit" << endl;
		outputFile << "}" << endl;
		outputFile.close();
	}
	catch (exception e) {
		cout << e.what();
	}
}
/*int main(int argc, char *argv[]) {
	try {

	}
	catch (exception e) {
	}

	return 0;
}*/