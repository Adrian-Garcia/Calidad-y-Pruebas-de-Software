#include <iostream>

using namespace std;

class SimpsonRule {

private:

	double x;
	int dof;
	double E;
	double p;

public:
	
	SimpsonRule() {
		x = 0.0;
		dof = 0;
		E = 0.0001;
		p = 0.0;
	}

	~SimpsonRule() {
		delete x, dof, E, p;
	}

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
		cout << "x 		=" << x << endl;
		cout << "dof 	=" << dof << endl;
		cout << "p 		=" << p << endl;
	}

	void setX(double x) { //.m
		this->x = x; //.m
	}

	void setDof(int dof) { //.m
		this->dof = dof; //.m
	}

	void calculate() {

		for (int i=0; i<10; i++) { //.m
			
		}
	}
};

class Getter {

private:
	SimpsonRule simpsonRule;

public:

	Getter();
	
	~Getter() {
		~simpsonRule();
	}

	void getData() {

		double x;
		double dof;

		cin >> x;
		cin >> dof;

		simpsonRule.setX(x);
		simpsonRule.setDof(dof);
	}

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