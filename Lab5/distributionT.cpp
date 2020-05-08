//.b=15
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