#include <iostream>
#include <vector>
#include <math.h>

class Interval {
private:

    double range;

    //.i
    double standard_deviation(vector<double> &x, vector<double> &y, int n, Regression &r) {
        double sum = 0, dif;
        for(int i = 0; i < n; i++){
            dif = y[i] - r.predict(x[i]);
            sum += dif * dif;
        }
        return sqrt(1.0 / (n - 2.0) * sum);
    }

    //.i
    double calculate_root(vector<double> &x, double avgX, int n, double xk) {
        double sum = 0, dif;
        for(int i = 0; i < n; i++){
            dif = x[i] - avgX;
            sum += dif * dif;
        }
        dif = xk - avgX;
        return sqrt(1 + 1.0 / n + dif * dif / sum);
    }

public:
    //.i
    Interval() {
    }

    //.i
    double calculate_range(vector<double> x, vector<double> y, double avgX, int n, Regression &r, T &t, Simpson &s, double xk){
        range = s.x(0.35, n - 2, t) * standard_deviation(x, y, n, r) * calculate_root(x, avgX, n, xk);
        return range;
    }

    //.i
    double upi(double y) {
        return y + range;
    }

    //.i
    double lpi(double y) {
        double res = y - range;
        return res < 0 ? 0 : res;
    }
};