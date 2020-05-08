//.b=10
class Getter {

private:
	long double result;

public:
	
	Getter() {
		result = 0;
	}

	//.i
	// Calcula el resultado
	void calculate(long double currX, long double dof, long double dof2) {  
		result = pow((currX * currX) / dof+1, -1 * ((dof + 1) / 2));
	}

	//.i
	// Getter del resultado
	long double getResult() {
		return result;
	}
};