#include <iostream>
#include <fstream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iomanip>

using namespace std;
/*
F(x) la dividimos en dos siendo la PrimeraMitad:

				G((dof+1)/2)
F(x)=-------------------------------------
			(dof*Pi)^(1/2) * G(dof/2)

*/
//.i
class PrimeraMitad
{
private:
	long double resultado;
public:
	PrimeraMitad(long double dof, long double dofSum1E2) {
		long double gammaArriba = Gamma(dofSum1E2);
		//cout << "Gamma arriba: " << gammaArriba << endl;
		long double gammaAbajo = Gamma(dof / 2);
		//cout << "Gamma abajo: " << gammaAbajo << endl;
		resultado = gammaArriba / ((pow(dof * PI, .5)) * gammaAbajo);
	}

	//.i
	/*
	Funcion que regresa el valor gamma dependiendo de la iteracion
	Gamma esta definido como:
	G(x) = (x-1) * G(x-1) cuando
	G(1) = 1
	G(1/2) = sqrt(Pi)
	*/
	long double Gamma(long double x) {
		if (x == 1) return 1;
		if (x < 1) return sqrt(PI);
		return (x - 1) * Gamma(x - 1);
	}

	long double getResultado() {
		return resultado;
	}
};

//.i
class SegundaMitad
{
private:
	long double resultado;
public:
	SegundaMitad() {
		resultado = 0;
	}

	void recalcular(long double xi, long double dof, long double dofSum1E2) {
		long double temp = (xi * xi) / dof;
		temp++;
		resultado = pow(temp, -1 * ((dof + 1) / 2));
	}

	long double getResultado() {
		return resultado;
	}
};

//Autor: Natalia Gonzalez 
//A01382007
//12 Abril 2020
//Cuarentena dia: 30
//

class Simpson
{
private:
	long double resultado;
public:
	Simpson() {
		resultado = 0;
	}
	//.i
	void calcular(long double x, long double dof, long double numSeg) {
		resultado = 0;
		long double w = x / numSeg;
		int i = 0;
		long double xi = 0;
		long double funcionEnX;
		long double temp;
		PrimeraMitad primera(dof, (dof + 1) / 2); //es la misma para todas las iteraciones
		SegundaMitad segunda; //solo para inicializar la variable


		//F(0)
		segunda.recalcular(0, dof, (dof + 1) / 2);
		resultado = resultado + primera.getResultado() * segunda.getResultado() * w / 3;


		while (i < numSeg) {
			//cout << "xi: " << xi;
			if (xi == 0) {
			}
			else if (i % 2 == 0) {
				//iteracion xi par
				segunda.recalcular(xi, dof, (dof + 1) / 2);
				funcionEnX = primera.getResultado() * segunda.getResultado();
				temp = funcionEnX * 2 * w / 3;
				resultado = resultado + temp;
			}
			else {
				//iteracion xi impar
				segunda.recalcular(xi, dof, (dof + 1) / 2);
				funcionEnX = primera.getResultado() * segunda.getResultado();
				temp = funcionEnX * 4 * w / 3;
				resultado = resultado + temp;
			}
			xi += w;
			i++;
		}
		//F(numSeg)
		segunda.recalcular(xi, dof, (dof + 1) / 2);
		resultado = resultado + primera.getResultado() * segunda.getResultado() * w / 3;


	}

	long double getResultado() {
		return resultado;
	}
};

int main()
{
    //datos que se introducen por el usuario
    //x es hasta que valor se calculara la integral
    //dof son los grados de libertad
    long double xi, dof, p, di, error; //.m
    int dofFake;
    bool vaDer, vaIzq;

    //El numero de segmentos siempre debe ser par
    //Se inicializa con 100 pues algo menor no es muy exacto
    long double numSeg = 100; //.m
    
    cin >> p; //.m
    cin >> dof;
    

    //validar que dof sea mayor que 0
    if (dof <= 0) {
        cout << "Datos invalidos\n";
        cout << "dof debe ser mayor que cero\n";
        return 0;
    }

    //validar que X sea mayor que 0
    if (p < 0 || p > .5 ) { //.m
        cout << "Datos invalidos\n";
        cout << "p esta fuera de rango\n";
        return 0;
    }

    //validar que dof sea un entero
    double intpart, fract;
    fract = modf(dof, &intpart);
    if (fract > 0) {
        cout << "Datos invalidos\n";
        cout << "dof debe ser numero entero\n";
        return 0;
    }

    xi = 1;
    di = xi / 2;
    vaDer = true;
    vaIzq = true;

    //Se necesitan dos calculaos para obtener el error
    Simpson pi; //.m
    Simpson ps; //.m
    pi.calcular(xi, dof, numSeg); //.m
    //.d=2
    error = 1;

    //Se acepta un error maximo de .0001
    while (error > .0000001) {
        //.d=2
        
        pi.calcular(xi, dof, numSeg);
        //Mover a la derecha
        if (pi.getResultado() < p) {
            if (vaDer) {
                xi = xi + di;
                vaIzq = false;
            }
                
            //Cambio de direccion
            else {
                vaIzq = false;
                vaDer = true;
                di = di / 2;
                xi = xi - di;
            }
        }
        //Mover a la izquierda
        else {
            if (vaIzq) {
                xi = xi - di;
                vaDer = false;
            }
                
            //Cambio de direccion
            else {
                vaIzq = true;
                vaDer = false;
                di = di / 2;
                xi = xi - di;
            }
        }

        ps.calcular(xi, dof, numSeg); //.m
        error = abs(ps.getResultado() - pi.getResultado()); //.m
       // cout << error << endl;

    }

    dofFake = dof;
    cout << fixed << setprecision(5);
    cout << "p = " << p << endl; //.m
    cout << "dof = " << dofFake << endl;
    cout << "x = " << xi << endl; //.m
}