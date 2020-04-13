#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <iomanip>

using namespace std;

class Renglon
{
private: 
    long double x;
    long double y;
    long double xCuadr;
    long double yCuadr;
    long double xy;

public: 
    Renglon(long double x, long double y);
    long double getX();
    void setX(long int x);
    long double getY();
    void setY(long int y);
    long double getXCuadr();
    long double getYCuadr();
    long double getXY();
};
//i
//Constructor con parametros
Renglon::Renglon(long double x, long double y) {
    this->x = x;
    this->y = y;
    xCuadr = x * x;
    yCuadr = y * y;
    xy = x * y;
};
//Gets y Sets
long double Renglon::getX() {
    return x;
}
void Renglon::setX(long int x) {
    this->x = x;
};

long double Renglon::getY() {
    return y;
};
void Renglon::setY(long int y) {
    this->y = y;
};
//Gets de variables no modificables por el usuario
long double Renglon::getXCuadr() {
    return xCuadr;
}
long double Renglon::getYCuadr() {
    return yCuadr;
};
long double Renglon::getXY() {
    return xy;
}

class Formato
{
public:
    Formato(int n, long double xk, long double r, long double bCero, long double bUno, long double yk) {
        cout << "N: " << n << endl;
        cout << "xk = " << xk << endl;
        cout << fixed;
        cout << setprecision(5) << "r = " << r << endl;
        cout << setprecision(5) << "r2 = " << r * r << endl;
        cout << setprecision(5) << "b0 = " << bCero << endl;
        cout << setprecision(5) << "b1 = " << bUno << endl;
        cout << setprecision(5) << "yk = " << yk << endl;
    }
};


using namespace std;
//i
bool fileEmpty(ifstream& file) {
    return file.peek() == std::ifstream::traits_type::eof();
}
//i
int main()
{
    //Archivo
    string nomArch, line; 
    ifstream archEnt;

    //Variables de sumatorias y promedios
    long double sumXY, sumX, sumY, sumXCuadr, sumYCuadr;
    long double yAverage, xAverage, xCuadrAverage;

    sumX = 0;
    sumY = 0;
    sumXCuadr = 0;
    sumXY = 0;
    sumYCuadr = 0;
    yAverage = 0;
    xAverage = 0;
    xCuadrAverage = 0;

    //Datos
    long double x, y;
    long double xk, yk, r;

    //Cantidad de pares en el archivo
    int n = 0;

    //Variables a calcular
    long double bCero, bUno;

    //Vector
    vector <Renglon> renglones;

    //Pedir archivo
    cout << "Nombre del archivo: ";
    cin >> nomArch;

    //Abrir archivo
    archEnt.open(nomArch);

    // Si el archivo no existe o esta vacio, la funcion termina
    if (archEnt.fail() || fileEmpty(archEnt)) {
        cout << "El archivo esta vacío o no existe" << endl;
        return 0;
    }

    getline(archEnt, line);
    xk = stod(line);
   // cout << "XK: " << xk << endl;

    //leer archivo linea por linea
    while (!archEnt.eof())
    {
        getline(archEnt, line);
        // stringstream ss(line);

        //Separar x & y
        int split = line.find(',');
        x =(stod(line.substr(0, split)));
        y = (stod(line.substr(split + 1)));


        Renglon renTemp(x, y);
        n++;

        sumX += x;
        sumY += y;
        sumXCuadr += x * x;
        sumYCuadr += y * y;
        sumXY += x * y;

        cout << x << " " << y << " " 
        << sumX << " " << sumY << " "
        << sumXCuadr << " " << sumYCuadr << " "
        << sumXY << endl;
    }

    cout << endl << endl;
    
    xAverage = sumX / n;
    yAverage = sumY / n;
    xCuadrAverage = sumXCuadr / n;

    cout << xAverage << " " << yAverage << endl << endl;

    //regresion
    bUno = (sumXY-(n * xAverage * yAverage)) / (sumXCuadr - (n * xAverage * xAverage));
    bCero = yAverage - bUno * xAverage;

    //correlacion
    r = ((n * sumXY) - (sumX * sumY)) /
        sqrt((n * sumXCuadr - sumX * sumX) * (n * sumYCuadr - sumY * sumY));

    yk = bCero + bUno * xk;

    /*
    cout << "Sumatoria de X: " << sumX << endl;
    cout << "Sumatoria de Y: " << sumY << endl;
    cout << "Sumatoria de X cuadrada: " << sumXCuadr << endl;
    cout << "Sumatoria de XY: " << sumXY << endl;
    cout << "Sumatoria de Y cuadrada: " << sumYCuadr << endl;
    cout << "Promedio X: " << xAverage << endl;
    cout << "Promedio Y: " << yAverage << endl;
    cout << "Promedio x cuadraro: " << xCuadrAverage << endl;
    */

    Formato f(n, xk, r, bCero, bUno, yk);
}


