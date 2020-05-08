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
	void calculate(long double x, long double dof, int num_seg) { //.m
			
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

		while (i<num_seg) { //.m

			if (currX == 0) { //.m

				i++;//.m
				currX += w;//.m
				continue;//.m
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