// Martin Rodrigo Ruiz Mares
// A00821630
// Calcula la distribucion de t en vase a x y dof
#include <math.h>
#define M_PI 3.14159265358979323846

//.b=10
class T{
private:
public:
    /*
        Calcula gamma
        x: valor del cual se buscara gamma
    */
    //.i
    double gamma(double x){
        if(x == 1) return 1;
        if(x < 1) return sqrt(M_PI);
        return (x - 1) * gamma(x - 1);
    }

    /*
        se calcula la distribucion
        x: valor del cual se busca la distribucion
        dof: dof
    */
    //.i
    double f(double x, double dof){
        return gamma((dof + 1) / 2) / (sqrt(dof * M_PI) * gamma(dof/2)) * pow(1 + x * x / dof, (dof +1)/-2);
    }
};