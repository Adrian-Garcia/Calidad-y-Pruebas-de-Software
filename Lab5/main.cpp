//.b=27
//.i
int main() {
	
	long double x, dof, p, di; //.m
	int num_seg = 100; //.m
	long double err = 1; //.m
	double intVal;
	
	bool right = true;
	bool left = true;
	
	// Pedimos valores para p y dof
	cin >> p; //.m
	cin >> dof;

	// Validamos que los valores ingresados sean correctos
	if (dof <= 0) {	
		cout << "dof debe ser mayor que uno";
		return 0;
	} if (modf(dof, &intVal)) { 
		cout << "dof debe ser entero" << endl;
		return 0;
	} if (p>0.5 || p<0) {
		cout << "p debe ser positivo y mayor que 0.5\n";
		return 0;
	}

	x = 1;
	di = x / 2;

	SimpsonDistribution FirstOp; //.m
	SimpsonDistribution SecondOP; //.m
	
	FirstOp.calculate(x, dof, num_seg); //.m
	//.d=2

	// Corregimos
	while (err > e) {
		
		//.d=2

		FirstOp.calculate(x, dof, num_seg);
		
		if (p > FirstOp.getresult()) {

			if (right) {
				left = false;
				x+=di;
			} else {
				left = false;
				right = true;
				di/=2;
				x-=di;
			}
		}
		
		else {
			
			if (left) {
				x -= di;
				right = false;
			} else {
				left = true;
				right = false;
				di /= 2;
				x -= di;
			}
		}

		SecondOP.calculate(x, dof, num_seg); //.m
		err = abs(SecondOP.getresult() - FirstOp.getresult()); //.m
	}

	// Desplegamos valores finales
	cout << fixed << setprecision(5);
	cout << "p   = " << p << endl; //.m
	cout << "dof = " << (int)dof << endl;
	cout << "x   = " << x << endl; //.m
}