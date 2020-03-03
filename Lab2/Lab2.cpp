#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stack>

using namespace std;

// .b=14
// .i
class Counter {

private:
	char type;
	string name;
	unsigned long long int codeLines;
	unsigned long long int itemLines;			// .m
	unsigned long long int baseLines;			// .m
	unsigned long long int deletedLines;	
	unsigned long long int modifiedLines;	
	unsigned long long int addedLines;		

public:

	Counter() {
		type = '0';
		name = "";
		codeLines = 0;
		itemLines = 0;	//.m
		baseLines = 0;	//.m
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

	void addOneItemLine() {			//.m
		this->itemLines++;				//.m
	}

	void addOneModifiedLine() {	//.m
		this->modifiedLines++;		//.m
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

	void setCounter(Counter oldCounter) {

		this->type = oldCounter.type;
		this->name = oldCounter.name;
		this->codeLines = oldCounter.codeLines;
		this->itemLines = oldCounter.itemLines;
		this->baseLines = oldCounter.baseLines;
		this->deletedLines = oldCounter.deletedLines;
		this->modifiedLines = oldCounter.modifiedLines;
		this->addedLines = oldCounter.addedLines;
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

// .b=36
// .i
class InputFile {

private:

	vector<Counter> lineCounters; //.m

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

		if (line.find("//") < 2)
			return false;

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

	bool validateM(string line) {

		bool quotes = false;

		for (int i=0; i<line.size(); i++) {
			
			if (!quotes && line[i] == '"') {
				quotes = true;
				continue;
			}

			if (line[i] == '/') {
				if (i < line.size()-4) {
					if (quotes && line[i+1] == '/' && 
							line[i+2] == '.' && line[i+3] == 'm')
						return false;
				}
			}

			if (quotes && line[i] == '"') {
				quotes = false;
				continue;
			}
		}

		return true;
	}

public:

	ifstream fFile;

	InputFile() {}

	// Funcion principal que lee el archivo y cuenta lineas
	void scanFile() {

		// .m
		Counter currentFile;

		bool inComment = false;
		bool newFile = false;
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
				// .M
				continue;
			}
			
			for (int i=0; i<lineCounters.size(); i++) {
				if (lineCounters[i].getName() == fix(FileName)) {
					currentFile.setCounter(lineCounters[i]);
					newFile = true;
				}
			}

			if (!newFile) {
				currentFile.setName(fix(FileName));
			}

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

					// Hay un comentario
					if (sLineContent.find("//") != -1) {

						// Busca items
						if (sLineContent.find("//.i") != -1) {
							currentFile.addOneItemLine();
							continue;
						}

						// Busca lineas borradas 
						if (sLineContent.find("//.d=") != -1) {
							deletedLinesNum = getNum(sLineContent, 'd');
							currentFile.setDeletedLines(currentFile.getDeletedLines() + deletedLinesNum);
							continue;
						}

						// Busca lineas base
						if (sLineContent.find("//.b=") != -1) {
							baseLinesNum = getNum(sLineContent, 'b');
							currentFile.setBaseLines(currentFile.getBaseLines() + baseLinesNum);
							continue;
						}

						if (sLineContent.find("//.m") != -1) {
							
							if (validateM(sLineContent)) {
								currentFile.addOneModifiedLine();
							}
						}

						if (sLineContent.size() > 2 && haveNoBrackets(sLineContent)) {
							currentFile.addOneCodeLine();
							continue;
						}
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

					// Verify if there is a character on the string
					if (sLineContent.size() > 0 && haveNoBrackets(sLineContent)) {
						currentFile.addOneCodeLine();
					}
				}
			}

			// .d = 7

			// New file
			if (!currentFile.getDeletedLines() && !currentFile.getModifiedLines() && currentFile.getBaseLines() > 0)
				currentFile.setType('R');

			else if (currentFile.getBaseLines()>0 && 
				 (currentFile.getDeletedLines()>0 || currentFile.getModifiedLines()>0))
				currentFile.setType('B');

			else
				currentFile.setType('N');	

			if (!newFile) {
				lineCounters.push_back(currentFile);
			}

			else {
				for (int i=0; i<lineCounters.size(); i++) {
					if (lineCounters[i].getName() == currentFile.getName()){
						lineCounters[i].setCounter(currentFile);
					}
				}
			}

			currentFile.clear();
			newFile = false;

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

//.b=4
//.i
int main() {

	cout << "Colocar nombres de archivos y dar 0 para terminar" << endl << endl;
	InputFile input;
	input.scanFile();

	return 0;
}