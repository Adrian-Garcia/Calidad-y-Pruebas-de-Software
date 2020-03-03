#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stack>

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
		this->itemLines++;
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
		this->type = '0';
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

		string key;
		int position;
		int multiplier = 1;
		int res = 0;
		stack<char> number;

		key = (type == 'd') ?
			"//.d=" : "//.b=";

		position = line.find(key) + 5;
		int i=position;
		
		while (isdigit(line[i])) {
			number.push(line[i]);
			i++;
		}

		while (!number.empty()) {
			res += (number.top() - 48) * multiplier;
			multiplier *= 10;
			number.pop();
		}

		return res;
	}

	bool haveNoBrackets(string line) {

		for (int i=0; i<line.size(); i++) {
			if (line[i] != '{' && line[i] != '}' && line[i] != ';') {
				return true;
			}
		}

		return false;
	}

	string fix(string fileName) {

		int pos = fileName.find('.');

		if (pos != -1)
			return fileName.substr(0, pos);
		
		return fileName;
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
		int deletedLinesNum;
		int baseLinesNum;
		int totalLines = 0;

		string sLineContent;
		string FileName;

		// Pedimos nombre del archivo
		// .m
		cin >> FileName;

		while (FileName != "" || FileName != "0") {

			fFile.open(FileName.c_str());

			// Si el archivo no existe o esta vacio, la funcion termina
			if (fFile.fail() || fileEmpty(fFile)) {
				break;
				getline(cin, FileName);	
				// .M
				continue;
			}
			
			currentFile.setName(FileName);

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
					if (sLineContent.find("//.d=") != -1) {
						deletedLinesNum = getNum(sLineContent, 'd');
						currentFile.setDeletedLines(currentFile.getDeletedLines() + deletedLinesNum);
					}

					// Busca lineas base
					if (sLineContent.find("//.b=") != -1) {
						baseLinesNum = getNum(sLineContent, 'b');
						currentFile.setBaseLines(currentFile.getBaseLines() + baseLinesNum);
					}

					if (sLineContent.find("//.m") != -1) {
						currentFile.addOneModifiedLine();
					}

					// .d=4

					// Busca bloques de comentarios
					if (sLineContent.find("/*") != -1) {
						inComment = true;
						continue;
					}

					if (sLineContent == "") {
						continue;
					}

					if (sLineContent.find("//") != -1) {
						
						bool flag = false;

						if (sLineContent.find("//.b="))
							flag = true;

						if (sLineContent.find("//.d="))
							flag = true;

						if (sLineContent.find("//.i"))
							flag = true;

						if (sLineContent.find("//.m"))
							flag = true;

						if (!flag)
							continue;
					}

					// Verify if there is a character on the string
					if (sLineContent.size() > 0 && haveNoBrackets(sLineContent)) {
						currentFile.addOneCodeLine();
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

			lineCounters.push_back(currentFile);
			currentFile.clear();

			// Cerramos programa
			fFile.close();

			cin >> FileName;
		}

		// Imprimimos resultados
		cout << "PARTES BASE:" << endl;
		for (int i=0; i<lineCounters.size(); i++) {
			
			if (lineCounters[i].getType() == 'B') {

				//  A = T - B + D
				lineCounters[i].setAddedLines(lineCounters[i].getCodeLines() - lineCounters[i].getBaseLines() + lineCounters[i].getDeletedLines());

				cout << "\t" << fix(lineCounters[i].getName());
				cout << ": T=" << lineCounters[i].getCodeLines(); 
				cout << ", I=" << lineCounters[i].getItemLines(); 
				cout << ", B=" << lineCounters[i].getBaseLines();
				cout << ", D=" << lineCounters[i].getDeletedLines();
				cout << ", M=" << lineCounters[i].getModifiedLines(); 
				cout << ", A=" << lineCounters[i].getAddedLines() << endl;

				totalLines+=lineCounters[i].getCodeLines();
			} 
		} 	cout << "--------------------------------------------" << endl;
		
		cout << "PARTES NUEVAS:" << endl;
		for (int i=0; i<lineCounters.size(); i++) {

			if (lineCounters[i].getType() == 'N') {
				cout << "\t" << fix(lineCounters[i].getName());
				cout << ": T=" << lineCounters[i].getCodeLines(); 
				cout << ", I=" << lineCounters[i].getItemLines() << endl;
	
				totalLines+=lineCounters[i].getCodeLines();
			}
		} 	cout << "--------------------------------------------" << endl;
		
		cout << "PARTES REUSADAS:" << endl;
		for (int i=0; i<lineCounters.size(); i++) {

			if(lineCounters[i].getType() == 'R') {
				cout << "\t" << fix(lineCounters[i].getName());
				cout << ": T=" << lineCounters[i].getCodeLines();
				cout << ", I=" << lineCounters[i].getItemLines();
				cout << ", B=" << lineCounters[i].getBaseLines() << endl;
				
				totalLines+=lineCounters[i].getCodeLines();
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