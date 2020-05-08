//.b=9
//.i
int main() {

	long double x, dof;
	int num_seg = 10;
	long double err;
	double intVal;

	// Pedimos valores para x y dof
	cin >> x;		//.m
	cin >> dof; //.m

	// Validamos que los valores ingresados sean correctos
	if (dof <= 0) {	//.m
		cout << "dof debe ser mayor que uno";
		return 0;
	} if (modf(dof, &intVal)) { //.m
		cout << "Dof debe ser entero" << endl;
		return 0;
	}

	SimpsonDistribution FirstOp;
	SimpsonDistribution SecondOp;

	FirstOp.calculate(x, dof, num_seg); //.m
	SecondOp.calculate(x, dof, 2*num_seg); //.m

	err = abs(FirstOp.getResult() - FirstOp.getResult());

	// Corregimos
	while (err > e) {
	
		num_seg *= 10;
	
		FirstOp.calculate(x, dof, num_seg);
		SecondOp.calculate(x, dof, num_seg + 10);
	
		err = abs(FirstOp.getResult() - FirstOp.getResult());
	}

	// Desplegamos valores finales
	cout << fixed << setprecision(5);
	cout << "x   = " << x << endl;
	cout << "dof = " << (int)dof << endl;
	cout << "p   = " << FirstOp.getResult() << endl;
}