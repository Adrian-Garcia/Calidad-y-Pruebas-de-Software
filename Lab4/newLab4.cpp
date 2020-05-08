// Autor: Adrián García 
// A01382007
// 15 Abril 2020

#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#define PI 3.14159265358979323846264
#define e 0.0000001

using namespace std;

/*
Este programa, se encarga de realizar la intregral por el metodo
Simpson. Para esto, utiliza 3 clases las cuales están conformadas
por
	
	Distribución T:		Usa la función gamma para obtener un resultado
	Gettet: 					Calcula el primer trozo de la ecuación
	Simpson: 					Une ambas funciones y encuentra el resultado
*/

class distributionT {

private:

	long double result;

public:

	//.i
	// Función gamma
	long double gammaFunction(long double x) {

		if (x == 1) 
			return 1;
		
		else if (x < 1)
			return sqrt(PI);
		
		else
			return (x-1) * gammaFunction(x-1);
	}

	//.i
	// Usando la función gamma, obtiene primer resultado
	distributionT(long double dof, long double dof2) {	
		result = gammaFunction(dof2) / ((pow(dof*PI,0.5))*gammaFunction(dof/2));
	}
	
	//.i
	// Getter de la clase
	long double getResult() { //.m
		return result; 		//.m
	}
};

// Se encarga de hacer el primer trozo de la simpson
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

//.b=4
class SimpsonDistribution {

private:
	long double finalResult;

public:

	SimpsonDistribution() {
		finalResult = 0;
	}

	//.i
	// Una las clases distributionT y Getter para calcular el resultado
	void calculate(long double x, long double dof, int num_seg) {
			
		long double w = x/num_seg;
		long double currX = 0; 
		
		long double Fx;
		long double tmp;
		
		int i=0; 
		
		// Objetos para realizar el cálculo
		distributionT distT(dof, (dof+1)/2);
		Getter getterObj;	

		// Obtenemos resultados principales
		getterObj.calculate(0, dof, (dof + 1) / 2);
		finalResult += distT.getResult() * getterObj.getResult() * w/3;

		while (i<num_seg) {

			if (currX == 0) {

				i++;
				currX += w;
				continue;
			}
			
			else if (i % 2 == 0){

				getterObj.calculate(currX, dof, (dof + 1) / 2);
				Fx = distT.getResult() * getterObj.getResult();
				
				tmp = Fx * 2 * w/3;
				finalResult += tmp;
			}
			
			else {

				getterObj.calculate(currX, dof, (dof + 1) / 2);
				Fx = distT.getResult() * getterObj.getResult();
				
				tmp = Fx * 4 * w/3;
				finalResult += tmp;
			}

			i++;
			currX += w;
		}

		getterObj.calculate(currX, dof, (dof + 1) / 2);
		
		finalResult += distT.getResult() * getterObj.getResult() * w/3;
	}

	//.i
	long double getResult() {
		return finalResult;
	}
};

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
		cout << "dof debe ser entero" << endl;
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