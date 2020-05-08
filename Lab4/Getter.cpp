
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