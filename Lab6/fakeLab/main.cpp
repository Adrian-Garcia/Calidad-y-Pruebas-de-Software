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

void output(int n, double xk, double r, double r2, double b0, double b1, double yk, double sig, double ran, double ls, double li){

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

    int n = data.getN();
    double xk = data.getXk();
    double r = correlation.getr();
    double r2 = correlation.getr2();
    double b0 = regression.getb0();
    double b1 = regression.getb1();
    double yk = regression.predict(xk);
    double sig = significance.significance(r, n, r2, s, t);
    double ran = interval.calculate_range(data.getX(), data.getY(), data.getAvgX(), n, regression, t, s, xk);
    double ls = interval.upi(yk);
    double li = interval.lpi(yk);
    output(n, xk, r, r2, b0, b1, yk, sig, ran, ls, li);
    return 0;
}