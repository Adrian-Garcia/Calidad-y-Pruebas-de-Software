// .b=7
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <ctype.h>
#include <iomanip>
#include <sstream>
#include <math.h>

using namespace std;

//.i
struct lineXY {
	long double x;
	long double y;
};

//.i
class DataSet {

	private:
		
		vector<lineXY> xy;
		
		long double xk;
		long double r;
		long double r2;
		long double b0;
		long double b1;
		long double yk;	

		long double xProm;
		long double yProm;

		long double sumX;
		long double sumY;

		long double sumXY;

		long double pow2SumX;
		long double pow2SumY;

		int n=0;

		void calculate() {

			for (int i=0; i<xy.size(); i++) {

				sumX += xy[i].x;
				sumY += xy[i].y;

				pow2SumX += xy[i].x * xy[i].x;
				pow2SumY += xy[i].y * xy[i].y;

				sumXY += xy[i].x * xy[i].y;

				n++;
			}

			xProm = sumX / n;
			yProm = sumY / n;

    	
			b1 = (sumXY - (n * xProm * yProm)) / 
					 (pow2SumX - (n * xProm * xProm));

			b0 = yProm - b1 * xProm;
			
			r = ((n * sumXY) - (sumX * sumY)) /
					sqrt((n * pow2SumX - sumX * sumX) *
					(n * pow2SumY - sumY * sumY));

			r2 = r * r;

			yk = b0 + b1 * xk;		 
		}

	public:

		DataSet() {
			
			xk = 0;
			r = 0;
			r2 = 0;
			b0 = 0;
			b1 = 0; 
			yk = 0;
			xProm = 0;
			yProm = 0;
			sumX = 0;
			sumY = 0;
			sumXY = 0;
			pow2SumX = 0;
			pow2SumY = 0;
		}

		void set_xk(string xk) {
			this->xk = stod(xk);
		}

		void xyPushBack(string xy) {

			long double coma = xy.find(',');
			long double x, y;

			lineXY currLine;

			currLine.x = stod(xy.substr(0, coma));
			currLine.y = stod(xy.substr(coma+1, xy.length()-1));

			this->xy.push_back(currLine);
		}

		long double get_xk() {
			return xk;
		}

		long double get_r() {
			return r;
		}

		long double get_r2() {
			return r2;
		}

		long double get_b0() {
			return b0;
		}

		long double get_b1() {
			return b1;
		}

		long double get_yk() {
			return yk;
		}

		long double get_xProm() {
			return xProm;
		}

		long double get_yProm() {
			return xProm;
		}

		long double getN() {
			return xy.size();
		}

		void calculateData() {
			calculate();
		}
};

//.i
class InputFile {

private:
	
	DataSet dataSet;

// .b=9
public:

	InputFile() {}

	ifstream fFile;	

	void run() {

		string sLineContent;
		string FileName;		

		cin >> FileName;

		fFile.open(FileName.c_str());

		// Si el archivo no existe o esta vacio, la funcion termina
		if (fFile.fail()) {			
			cout << "Archivo no encontrado" << endl; //.m
			return;
		}

		getline(fFile, sLineContent);
		stringstream ss(sLineContent);

		dataSet.set_xk(sLineContent);

		while(getline(fFile, sLineContent))
			dataSet.xyPushBack(sLineContent); //.m

		dataSet.calculateData();

		cout << "N  = " << dataSet.getN() << endl;
		cout << "xk = " << dataSet.get_xk() << endl;
		cout << fixed;
		cout << setprecision(5) << "r  = " << dataSet.get_r() << endl;
		cout << setprecision(5) << "r2 = " << dataSet.get_r2() << endl;
		cout << setprecision(5) << "b0 = " << dataSet.get_b0() << endl;
		cout << setprecision(5) << "b1 = " << dataSet.get_b1() << endl;
		cout << setprecision(5) << "yk = " << dataSet.get_yk() << endl;

		fFile.close();
	}
};

//.b=2
int main() {

	InputFile program;

	program.run(); //.m

	return 0;
}