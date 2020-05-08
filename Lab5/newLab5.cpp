// Autor: Adrián García 
// A01351166
// 22 Abril 2020
#include <iostream>
#include <math.h>
#include <string>
#include <iomanip>

#define _USE_MATH_DEFINES
#define e .0000001

using namespace std;

/*
Este programa, se encarga de realizar la intregral por el metodo
SimpsonDistribution. Para esto, utiliza 3 clases las cuales están conformadas
por
	
	Distribución T:   Usa la función gamma para obtener un resultado
	Gettet:           Calcula el primer trozo de la ecuación
	SimpsonDistribution:          Une ambas funciones y encuentra el resultado
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
			return sqrt(M_PI);
		
		else
			return (x-1) * gammaFunction(x-1);
	}
	
	//.i
	// Usando la función gamma, obtiene primer resultado
	distributionT(long double dof, long double dof2) {  
		result = gammaFunction(dof2) / ((pow(dof*M_PI,0.5))*gammaFunction(dof/2));
	}

	//.i
	// Getter de la clase
	long double getResult() {
		return result;
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

class SimpsonDistribution {

private:
	long double finalResult;

public:
	
	SimpsonDistribution() {
		finalResult = 0;
	}

	//.i
	// Una las clases distributionT y Getter para calcular el resultado
	void calculate(long double x, long double dof, long double num_seg) {
	
		finalResult = 0;
		
		long double w = x / num_seg;
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

			else if (i % 2 == 0) {
			
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
	long double getresult() {
		return finalResult;
	}
};


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