#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <iomanip>

using namespace std;

struct lineXY {
	long double x;
	long double y;
};

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

		long double calculateSumX() {

			this->sumX = 0;

			for (int i=0; i<xy.size(); i++) 
				this->sumX += xy[i].x;

			return this->sumX;
		}

		long double calculateSumXY() {

			if (this->sumXY != -1)
				return this->sumXY;

			this->sumXY = 0;

			for (int i=0; i<xy.size(); i++) 
				this->sumXY += xy[i].x * xy[i].y;

			return this->sumXY;
		}

		long double calculateSumY() {

			if (this->sumY != -1)
				return this->sumY;

			this->sumY = 0;

			for (int i=0; i<xy.size(); i++) 
				this->sumY += xy[i].y;

			return this->sumY;
		}

		long double calculatepow2SumX() {

			if (this->pow2SumX)
				return this->pow2SumX;

			this->pow2SumX = 0;

			for (int i=0; i<xy.size(); i++) 
				this->pow2SumX += xy[i].x * xy[i].x;

			return this->pow2SumX;
		}

		long double calculatepow2SumY() {

			if (this->pow2SumY)
				return this->pow2SumY;

			for (int i=0; i<xy.size(); i++) 
				this->pow2SumY += xy[i].y * xy[i].y;

			return this->pow2SumY;
		}

		// Correlation
		long double rCalculate() {

			long double sumx = calculateSumX();
			long double sumY = calculateSumY();

			this->r = ((xy.size() * calculateSumXY()) - (sumX * sumY) / 
					sqrt(xy.size() * calculatepow2SumX() - sumX * sumX) * 
							(xy.size() * calculatepow2SumY() - sumY * sumY));

			return r;
		}
		
		// Correlation
		long double r2Calculate() {

			if (r == -1)
				rCalculate();

			this->r2 = r * r;

			return this->r2;
		}

		// Regression
		long double b0Calculate() {

			if (b1 == -1)
				b1Calculate();

			this->b0 = yProm - b1 * xProm;

			return this->b0;
		}

		// Regression
		long double b1Calculate() {

			if (xProm == -1) 
				get_xProm();

			if (yProm == -1)
				get_yProm();

			this->b1 = (calculateSumXY() - (xy.size() * xProm * yProm)) /
					 			 (calculatepow2SumX() - (xy.size() * xProm * yProm));

			return this->b1;
		}

		long double ykCalculate() {

			if (b1 == -1)
				b1Calculate();

			if (b0 == -1)
				b0Calculate();

			this->yk = b0 + b1 * xk;

			return this->yk;
		}

	public:

		DataSet() {
			xk = -1;
			r = -1;
			r2 = -1;
			b0 = -1;
			b1 = -1; 
			yk = -1;
			xProm = -1;
			yProm = -1;
			sumX = -1;
			sumY = -1;
			sumXY = -1;
			pow2SumX = -1;
			pow2SumY = -1;
		}

		void set_xk(string xk) {
			this->xk = 1.0 * stoi(xk);
		}

		void xyPushBack(string xy) {

			long double coma = xy.find(',');
			long double x, y;

			lineXY currLine;

			currLine.x = stoi(xy.substr(0, coma));
			currLine.y = stoi(xy.substr(coma+1, xy.length()-1));

			this->xy.push_back(currLine);
		}

		long double get_xk() {
			return xk;
		}

		long double get_r() {

			if (r == -1)
				r = rCalculate();

			return r;
		}

		long double get_r2() {

			if (r2 == -1)
				r2 = r2Calculate();

			return r2;
		}

		long double get_b0() {

			if (b0 == -1)
				b0 = b0Calculate();

			return b0;
		}

		long double get_b1() {

			if (b1 == -1)
				b1 = b1Calculate();

			return b1;
		}

		long double get_yk() {
			
			if (yk == -1)
				yk = ykCalculate();
			
			return yk;
		}

		long double get_xProm() {
			
			if (xProm == -1) {
				
				this->sumX = 0;
		
				for (int i=0; i<xy.size(); i++)
					this->sumX += xy[i].x;
		
				xProm = this->sumX / xy.size();
			}

			return xProm;
		}

		long double get_yProm() {
			

			if (yProm == -1) {
				
				this->sumY = 0;
				
				for (int i=0; i<xy.size(); i++)
					this->sumY += xy[i].y;
				
				yProm = this->sumY / xy.size();
			}

			return xProm;
		}

		long double getN() {
			return xy.size();
		}
};

class InputFile {

private:
	
	DataSet dataSet;

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
			cout << "Archivo no encontrado" << endl;
			return;
		}

		getline(fFile, sLineContent);

		dataSet.set_xk(sLineContent);

		while(getline(fFile, sLineContent))
			dataSet.xyPushBack(sLineContent);

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

int main() {

	InputFile program;

	program.run();

	return 0;
}