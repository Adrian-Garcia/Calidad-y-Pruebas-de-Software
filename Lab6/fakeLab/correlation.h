// Adrian Garcia Lopez
// A01351166
//
// correlation.h

#include <iostream>
#include <math.h>

//.b=19
class Correlation {
	
	private:
		double r;
		double r2;

	public:
		//.i
		Correlation(){
			r = 0;
			r2 = 0;
		}
		
		//.i
		Correlation(Data data){
			correlate(data);
		}

		//.i
		void correlate(Data data){
			r = (data.getN() * data.getSumXY() - data.getSumX() * data.getSumY()) / sqrt((data.getN() * data.getSquareSumX() - data.getSumX() * data.getSumX()) * (data.getN() * data.getSquareSumY() - data.getSumY() * data.getSumY()));
			r2 = r * r;
		}

		//.i
		double getr(){
			return r;
		}

		//.i
		double getr2(){
			return r2;
		}
};