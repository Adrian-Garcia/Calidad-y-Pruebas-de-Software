#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

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

	void setBaseLines(unsigned long long int baseLines) {
		this->baseLines = baseLines;
	}

	void setDeletedLines(unsigned long long int deletedLines) {
		this->deletedLines = deletedLines;
	}

	void setModifiedLines(unsigned long long int modifiedLines) {
		this->modifiedLines = modifiedLines;
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

	bool fileEmpty(ifstream& file) {
		return file.peek() == std::ifstream::traits_type::eof();
	}

public:

	ifstream fFile;

	InputFile() {}

	// Funcion principal que lee el archivo y cuenta lineas
	void scanFile() {

		// .M
		Counter currentFile;
		bool inComment = false;
		string sLineContent;
		string sFileName;

		// Pedimos nombre del archivo
		// .M
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
						currentFile.addOneCommentLine();				
						continue;
					}

					currentFile.addOneCommentLine();
				}

				// Si no estamos en comentarios
				else if (!inComment) {

					// Busca items
					if (sLineContent.find("//.i")) {
						currentFile.addOneItemLine();
					}

					// Busca lineas borradas 
					if (sLineContent.find("//.d=")) {
						
						currentFile.
					}

					// Busca commentarios de una linea
					else if (sLineContent.find("//") != -1) {
						currentFile.addOneCommentLine();
					}

					// Busca bloques de comentarios
					else if (sLineContent.find("/*") != -1) {
						currentFile.addOneCommentLine();
						inComment = true;
					}

					// Verify if there is a character on the string
					else if (sLineContent.size() > 0) {
						currentFile.addOneCodeLine();
					} 

					// Add blank space
					else {
						lineCounter.addOneBlankLine();
					}
				}
			}

			// .d = 7

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
			} 
		} 	cout << "--------------------------------------------" << endl;
		
		cout << "PARTES NUEVAS:" << endl;
		for (int i=0; i<lineCounters.size(); i++) {

			if (lineCounters[i].getType() == 'N') {
				cout << "\t" << lineCounters[i].getName();
				cout << ": T=" << lineCounters[i].getCodeLines(); 
				cout << ", I=" << lineCounters[i].getItemLines() << endl; 
			}
		} 	cout << "--------------------------------------------" << endl;
		
		cout << "PARTES REUSADAS:" << endl;
		for (int i=0; i<lineCounters.size(); i++) {

			if(lineCounters[i].getType() == 'R') {
				cout << "\t" << lineCounters[i].getName();
				cout << ": T=" << lineCounters[i].getCodeLines();
				cout << ", I=" << lineCounters[i].getItemLines();
				cout << ", B=" << lineCounters[i].getBaseLines() << endl;
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