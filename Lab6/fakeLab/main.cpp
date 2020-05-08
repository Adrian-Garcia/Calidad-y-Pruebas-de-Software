// Adrian Garcia Lopez
// A01351166
//
// main.cpp 
#include <iostream>
#include <iomanip>
#include "data.h"
#include "regression.h"
#include "correlation.h"
#include "T.h"
#include "simpson.h"
#include "significance.h"
#include "interval.h"

using namespace std;

void printResult(int n, double xk, double r, double r2, double b0, double b1, double yk, double sig, double ran, double ls, double li){

	cout << fixed << setprecision(5);
	cout << "  n = " << n << "\n";
	cout << " xk = " << xk << "\n";
	cout << "  r = " << r << "\n";
	cout << " r2 = " << r2 << "\n";
	cout << " b0 = " << b0 << "\n";
	cout << " b1 = " << b1 << "\n";
	cout << " yk = " << yk << "\n";
	cout << fixed << setprecision(10);
	cout << "sig = " << sig << "\n";
	cout << fixed << setprecision(5);
	cout << "ran = " << ran << "\n";
	cout << " ls = " << ls << "\n";
	cout << " li = " << li << "\n";
}

//.i
int main() {
	
	string file;
	cout << "Nombre del archivo: ";
	cin >> file;
	Data data;
	data.start(file);
	Regression regression(data);
	Correlation correlation(data);
	Simpson s;
	T t;
	Interval interval;
	Significance significance;

	int n;
	double xk;
	double r;
	double r2;
	double b0;
	double b1;
	double yk;
	double sig;
	double ran;
	double ls;
	double li;

	n = data.getN();
	xk = data.getXk();
	r = correlation.getr();
	r2 = correlation.getr2();
	b0 = regression.getb0();
	b1 = regression.getb1();
	yk = regression.predict(xk);
	sig = significance.significance(r, n, r2, s, t);
	ran = interval.calculate_range(data.getX(), data.getY(), data.getAvgX(), n, regression, t, s, xk);
	ls = interval.upi(yk);
	li = interval.lpi(yk);
	
	printResult(n, xk, r, r2, b0, b1, yk, sig, ran, ls, li);
	
	return 0;
}