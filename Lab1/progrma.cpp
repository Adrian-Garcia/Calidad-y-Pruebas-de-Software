#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Counter {

private:
	unsigned long long int codeLines;
	unsigned long long int commentLines;
	unsigned long long int blankLines;

public:

	Counter() {
		codeLines = 0;
		commentLines = 0;
		blankLines = 0;
	}

	void addOneCodeLine() {
		this->codeLines++;
	}

	void addOneCommentLine() {
		this->commentLines++;
	}

	void addOneBlankLine() {
		this->blankLines++;
	}

	unsigned long long int getCodeLines() {
		return codeLines;
	}

	unsigned long long int getCommentLines() {
		return commentLines;
	}

	unsigned long long int getBlankLines() {
		return blankLines;
	}
};

class InputFile {

private:

	Counter lineCounter;

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

		bool inComment = false;
		string sLineContent;
		string sFileName;

		// Pedimos nombre del archivo
		cin >> sFileName;
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
};

int main() {

	InputFile input;
	input.scanFile();

	return 0;
}