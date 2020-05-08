// Adrian Garcia Lopez
// A01351166
//
// significance.h

#include <stdlib.h>
#include <math.h>

class Significance {
private:
   
	//.i
	double calculate_x(double r, int n, double r2) {
		return abs(r) * sqrt(n - 2) / sqrt(1 - r2);
	}

	//.i
	double calculate_p(Simpson &s, int dof, double x, T &t) {
		return s.result(x, dof, t);
	}

public:
	
	//.i
	Significance() {
	}

	//.i
	double significance(double r, int n, double r2,  Simpson &s, T &t) {
		return 1 - 2 * calculate_p(s, n - 2, calculate_x(r, n, r2), t);
	}
};