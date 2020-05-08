// Martin Rodrigo Ruiz Mares
// A00821630
// Simpson.h se encarga de calcular el valor de 
// p, x y de imprimir los resultados al usuario
using namespace std;
#include <iomanip>

//.b=29
class Simpson{
private:
    double e = 0.0000001;
    double d = 0.5;
    /*
        p calcula los segmentos y los va sumando, regresa el area
        de la distribucion

        x: valor maximo a calcular
        dof: dof
        t: objeto de la clase T donde se llamara la funcion f
        num_seg: numero de segmentos en los que se divide x
    */
    //.i
    double p(double x, int dof, T t, int num_seg){
        double w = x/num_seg;
        double p = t.f(0, dof);
        for(int i = 1; i < num_seg-1; i+=2){
            p += 4 * t.f(i*w, dof);
        }
        for(int i = 2; i < num_seg-2; i+=2){
            p += 2* t.f(i*w, dof);
        }
        p+= t.f(x,dof);
        p = p * w / 3;
        return p;
    }

public:
    /*
        result regresa el valor optimo para 

        x: valor a calcular
        dof: dof
        t: objeto de T
    */
    //.i
    double result(double x, int dof, T t){ //.m
        int num_seg = 10;
        double p1 = p(x,dof,t,num_seg);
        num_seg = 20;
        double p2 = p(x,dof,t,num_seg);
        while(abs(p2-p1) > e){
            p1 = p2;
            num_seg *= 2;
            p2 = p(x,dof,t,num_seg);
        }
        return p2; //.m
    }

    // Se enarga de imprimir los resultados a la consola
    //.i
    void print(double x, int dof, double p){
        cout << fixed << setprecision(5);
        cout << "p = " << p << "\n";
        cout << "dof = " << dof << "\n";
        cout << "x = " << x << "\n";
    }

    /*
        Se encarga de buscar el valor de x en base a los valores dados

        p: valor del cual se busca x
        dof: dof
        t: Objeto de la clase T
    */
    //.i
    double x(double P, int dof, T t){
        double x = 1.0;
        double p0 = result(x, dof, t);
        bool bigger = false;
        if(p0 < P) bigger = true;
        if(bigger) d*= -1;
        while(abs(p0 - P) > e){
            if(p0 > P){
                if(!bigger){
                    d /= -2;
                    bigger = true;
                }
            } else {
                if(bigger){
                    d /= -2;
                    bigger = false;
                }
            }
            x += d;
            p0 = result(x, dof, t);
        }
        //print(x, dof, P);
        return x;
    }
};
