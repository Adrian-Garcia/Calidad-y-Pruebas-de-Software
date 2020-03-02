#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Counter {

private:
	unsigned long long int codeLines; 			// T
	unsigned long long int itemLines;				// I
	unsigned long long int baseLines;				// B
	unsigned long long int deletedLines; 		// D
	unsigned long long int modifiedLines;		// M
	unsigned long long int addedLines; 			// A

public:

	Counter() {
		codeLines = 0;
		itemLines = 0;
		baseLines = 0;
		deletedLines = 0;
		modifiedLines = 0;
		addedLines = 0;
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

	unsigned long long int getCodeLines() {
		return codeLines;
	}

	unsigned long long int itemLines() {
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

	clear() {
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
		Counter currentLine;
		bool inComment = false;
		string sLineContent;
		string sFileName;

		// Pedimos nombre del archivo
		// .M
		getline(cin, fFileName);	

		while (fFileName != "") { 

			fFile.open(sFileName.c_str());

			// Si el archivo no existe o esta vacio, la funcion termina
			if (fFile.fail() || fileEmpty(fFile))
				return;

			// Recorremos el archivo
			while (!fFile.eof()) {

				getline(fFile, sLineContent);
				sLineContent = removeSpaces(sLineContent);

				// Si estamos en comentarios
				if (inComment) {

					if (sLineContent.find("*/") != -1) {
						inComment = false;
						lineCounter.addOneCommentLine();				
						continue;
					}

					lineCounter.addOneCommentLine();
				}

				// Si no estamos en comentarios
				else if (!inComment) {

					// Busca commentarios de una linea
					if (sLineContent.find("//") != -1) {
						lineCounter.addOneCommentLine();
					}

					// Busca bloques de comentarios
					else if (sLineContent.find("/*") != -1) {
						lineCounter.addOneCommentLine();
						inComment = true;
					}

					// Verify if there is a character on the string
					else if (sLineContent.size() > 0) {
						lineCounter.addOneCodeLine();
					} 

					// Add blank space
					else {
						lineCounter.addOneBlankLine();
					}
				}
			}

			// Imprimimos resultados
			cout << "Nombre del archivo: " << sFileName << endl;
			cout << "--------------------------------------------" << endl;
			cout << "Cantidad de líneas en blanco: " << lineCounter.getBlankLines() << endl;
			cout << "Cantidad de líneas con comentarios: " << lineCounter.getCommentLines() << endl;
			cout << "Cantidad de líneas con código: " << lineCounter.getCodeLines() << endl;
			cout << "--------------------------------------------" << endl;
			cout << "Cantidad total de líneas: " << lineCounter.getBlankLines() + lineCounter.getCommentLines() + lineCounter.getCodeLines() << endl;

			// Cerramos programa
			fFile.close();
		}
	}
};

int main() {

	InputFile input;
	input.scanFile();

	return 0;
}