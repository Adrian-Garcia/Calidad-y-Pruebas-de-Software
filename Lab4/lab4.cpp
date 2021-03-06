// Autor: Adrián García
// A01351166
// 15 Abril 2020
//
#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

# define PI 3.14159265358979323846

//.b=20
class SimpsonRule {

private:

	double x;
	int dof;
	double E;
	double p;

	//.i
	double distributionT(double val) {
		
		if (val == 1) 
			return 1;

		if (val == 0.5) 
			return sqrt(PI) * 0.5;

		else
			return val*distributionT(val-1);
	}

public:

	//.i	
	SimpsonRule() {
		x = 0.0;
		dof = 0;
		E = 0.0001;
		p = 0.0;
	}

	//.i
	double getX() { //.m
		return x; //.m
	}

	int getDof() { //.m
		return dof; //.m
	}

	double getP() { //.m
		return p; //.m
	}

	void print() {

		cout << fixed << setprecision(5);
		cout << "x   = " << x << endl;
		cout << "dof = " << dof << endl;
		cout << "p   = " << p << endl;
	}

	void setX(double x) { //.m
		this->x = x; //.m
	}

	void setDof(int dof) { //.m
		this->dof = dof; //.m
	}

	/*
		Formulas
			first = pow(1+((pow (W*2, 2)/dof)), -1* ((dof+1)/2))
			distributionT(((double)(dof+1)/2)-1)
	*/
	void calculate() {
	
		int num_seg = 10;
		double W = x/num_seg;
		double total = 0;
		double t1, t2;
		int multiplier = 1;


		t1 = distributionT(((double)(dof+1)/2)-1);
		t2 = distributionT(((double)(dof)/2)-1); 

		double valueDistributionT = t1/(pow(dof*PI,0.5) * t2);

		total += (W/3) * multiplier * valueDistributionT * pow(1+((pow (W*0, 2)/dof)), -1* ((dof+1)/2));

		for (int i=1; i<=num_seg; i++) {

			multiplier = (i%2) ? 4 : 2;
			multiplier = (i==num_seg) ? 1 : multiplier;

			total += (W/3) * multiplier * valueDistributionT * pow(1+((pow (W*i, 2)/dof)), -1* ((dof+1)/2));
		}

		p = total;
	}
};

//.b=3
class Getter {

private:
	SimpsonRule simpsonRule;

public:

	//.i
	Getter(){}
	
	//.i
	void getData() {

		double x;
		double dof;

		cin >> x;
		cin >> dof;

		simpsonRule.setX(x);
		simpsonRule.setDof(dof);
	}

	//.i
	void run() {
		getData();
		simpsonRule.calculate();
		simpsonRule.print();
	}
};

//.b=4
int main() {

	Getter program; //.m
	program.run();

	return 0;
}