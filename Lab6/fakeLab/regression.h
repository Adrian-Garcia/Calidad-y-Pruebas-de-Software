#include <iostream>
#include <cmath>

using namespace std;

//.b=20
class Regression{

    private:
        double b0;
        double b1;
    public:
        //.i
        Regression(){

        }

        //.i
        Regression(Data data){
            getRegression(data);
        }

        //.i
        void getRegression(Data data){
            b1 = (data.getSumXY() - data.getN() * data.getAvgX() * data.getAvgY()) / (data.getSquareSumX() - data.getN() * data.getAvgX() * data.getAvgX());
            b0 = data.getAvgY() - b1 * data.getAvgX();
        }

        //.i
        double predict(double value){
            return b0 + b1 * value;
        }

        //.i
        double getb0(){
            return b0;
        }

        //.i 
        double getb1(){
            return b1;
        }
};