#include <iostream>
#include <fstream>
#include <string>
#include <vector>
// #include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

// .i
class Counter {

private:
	char type;
	string name;
	unsigned long long int codeLines;			// T
	unsigned long long int itemLines;			// I
	unsigned long long int baseLines;			// B
	unsigned long long int deletedLines;		// D
	unsigned long long int modifiedLines;		// M
	unsigned long long int addedLines;			// A

public:

	Counter() {
		type = '0';
		name = "";
		codeLines = 0;
		itemLines = 0;
		baseLines = 0;
		deletedLines = 0;
		modifiedLines = 0;
		addedLines = 0;
	}

	void setType(char type) {
		this->type = type;
	}

	void setName(string name) {
		this->name = name;
	}

	void addOneCodeLine() {
		this->codeLines++;
	}

	void addOneItemLine() {
		this->commentLines++;
	}

	void addOneModifiedLine() {
		this->modifiedLines++;
	}

	void setBaseLines(unsigned long long int baseLines) {
		this->baseLines = baseLines;
	}

	void setDeletedLines(unsigned long long int deletedLines) {
		this->deletedLines = deletedLines;
	}

	void setAddedLines(unsigned long long int addedLines) {
		this->addedLines = addedLines;
	}

	char getType() {
		return type;
	}

	string getName() {
		return name;
	}

	unsigned long long int getCodeLines() {
		return codeLines;
	}

	unsigned long long int getItemLines() {
		return itemLines;
	}

	unsigned long long int getBaseLines() {
		return baseLines;
	}

	unsigned long long int getDeletedLines() {
		return deletedLines;
	}

	unsigned long long int getModifiedLines() {
		return modifiedLines;
	}

	unsigned long long int getAddedLines() {
		return addedLines;
	}

	void clear() {
		this->type = '';
		this->name = "";
		this->codeLines = 0;
		this->itemLines = 0;
		this->baseLines = 0;
		this->deletedLines = 0;
		this->modifiedLines = 0;
		this->addedLines = 0;
	}
};

// .i
class InputFile {

private:

	vector<Counter> lineCounters;

	// Elimina los espacios de un string
	string removeSpaces(string str) { 

		string result = "";

		for (int i=0; i<str.size(); i++) 
			if (str[i] != ' ' && str[i] != '\t') 
				result.push_back(str[i]);

		return result;
	}

	// Verifica que el archivo no esté vacio
	bool fileEmpty(ifstream& file) {
		return file.peek() == std::ifstream::traits_type::eof();
	}

	// Obtiene el numero de base o borrado segun sea el caso
	int getNum(string line, char type) {

		string result = "";
		string key;
		int position;
		int i;
		
		key = (type == 'd') ?
			"//.d=" : "//.b=";

		position = line.find(key) + 5;
		i=position;

		while (isdigit(line[i])) {
			result.push_back(line[i]);
			i++;
		}

		return stoi(result);
	}

	bool haveNoBrackets(string line) {

		int i=0;

		while (i < line.size()) {
			if (line[i] != '{' line[i] != '}' && line[i] != ';') {
				return true;
			} i++;
		}

		return false;
	}

public:

	ifstream fFile;

	InputFile() {}

	// Funcion principal que lee el archivo y cuenta lineas
	void scanFile() {

		// .m
		Counter currentFile;

		bool inComment = false;
		int position;
		int deletedLines;
		int totalLines = 0;

		string sLineContent;
		string sFileName;

		// Pedimos nombre del archivo
		// .m
		getline(cin, fFileName);	

		while (fFileName != "") { 

			fFile.open(sFileName.c_str());

			// Si el archivo no existe o esta vacio, la funcion termina
			if (fFile.fail() || fileEmpty(fFile)) {
				
				getline(cin, fFileName);	
				// .M
				continue;
			}

			currentFile.setName(fFileName)

			// Recorremos el archivo
			while (!fFile.eof()) {

				getline(fFile, sLineContent);
				sLineContent = removeSpaces(sLineContent);

				// Si estamos en comentarios
				if (inComment) {

					if (sLineContent.find("*/") != -1) {
						inComment = false;
						// .d=1
						continue;
					}
					// .d=1
				}

				// Si no estamos en comentarios
				else if (!inComment) {

					// Busca items
					if (sLineContent.find("//.i") != -1) {
						currentFile.addOneItemLine();
					}

					// Busca lineas borradas 
					else if (sLineContent.find("//.d=") != -1) {
						deletedLinesNum = getNum(sLineContent, 'd');
						currentFile.setDeletedLines(currentFile.getDeletedLines() + deletedLinesNum);
					}

					// Busca lineas base
					else if (sLineContent.find("//.b=") != -1) {
						baseLinesNum = getNum(sLineContent, 'b');
						currentFile.setBaseLines(currenFile.getBaseLines() + baseLinesNum);
					}

					else if (sLineContent.find("//.m")) {
						currentFile.addOneModifiedLine();
					}

					// .d=4

					// Busca bloques de comentarios
					else if (sLineContent.find("/*") != -1) {
						currentFile.addOneCommentLine();
						inComment = true;
					}

					// Verify if there is a character on the string
					else if (sLineContent.size() > 0 && haveNoBrackets(sLineContent)) {
						currentFile.addOneCodeLine();
					} 

					// Add blank space
					else {
						continue;
					}
				}
			}

			// .d = 7

			// New file
			if (!currentFile.getDeletedLines() && !currentFile.getModifiedLines())
				currentFile.setType('N');

			else if (currentFile.getBaseLines()>0 && 
				 (currentFile.getDeletedLines()>0 || currentFile.getModifiedLines()>0))
				currentFile.setType('B');

			else
				currentFile.setType('R');	

			//  A = T - B + D
			currentFile.setAddedLines(currentFile.getCodeLines() - 
																currentFile.getBaseLines() + 
																currentFile.getDeletedLines());

			lineCounters.push_back(currentFile);
			currentFile.clear();

			// Cerramos programa
			fFile.close();
		}

		// Imprimimos resultados
		cout << "PARTES BASE:" << endl;
		for (int i=0; i<lineCounters.size(); i++) {
			
			if (lineCounters[i].getType() == 'B') {
				cout << "\t" << lineCounters[i].getName();
				cout << ": T=" << lineCounters[i].getCodeLines(); 
				cout << ", I=" << lineCounters[i].getItemLines(); 
				cout << ", B=" << lineCounters[i].getBaseLines();
				cout << ", D=" << lineCounters[i].getDeletedLines();
				cout << ", M=" << lineCounters[i].getModifiedLines(); 
				cout << ", A=" << lineCounters[i].getAddedLines() << endl;

				totalLines+=getCodeLines();
			} 
		} 	cout << "--------------------------------------------" << endl;
		
		cout << "PARTES NUEVAS:" << endl;
		for (int i=0; i<lineCounters.size(); i++) {

			if (lineCounters[i].getType() == 'N') {
				cout << "\t" << lineCounters[i].getName();
				cout << ": T=" << lineCounters[i].getCodeLines(); 
				cout << ", I=" << lineCounters[i].getItemLines() << endl;
				totalLines+=getCodeLines(); 
			}
		} 	cout << "--------------------------------------------" << endl;
		
		cout << "PARTES REUSADAS:" << endl;
		for (int i=0; i<lineCounters.size(); i++) {

			if(lineCounters[i].getType() == 'R') {
				cout << "\t" << lineCounters[i].getName();
				cout << ": T=" << lineCounters[i].getCodeLines();
				cout << ", I=" << lineCounters[i].getItemLines();
				cout << ", B=" << lineCounters[i].getBaseLines() << endl;
				totalLines+=getCodeLines();
			}
		}		cout << "--------------------------------------------" << endl;
		
		cout << "Total de LDC=" << totalLines;
	}	
};

int main() {

	InputFile input;
	input.scanFile();

	return 0;
}