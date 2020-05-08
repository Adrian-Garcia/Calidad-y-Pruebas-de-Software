/*
    Martin Rodrigo Ruiz Mares
    25/sep/2019

    Se encarga de leer cada linea del archivo, procesar estos datos y almacenarlos en esta clase,
    tiene los getters y setters necesarios para extraer la informacion desde otras clases
*/ 
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

//.b=83
class Data{
    private:
        double xk;
        vector<double> x;
        vector<double> y;
        double N;
        double SumX;
        double SumY;
        double SquareSumX;
        double SquareSumY;
        double SumXY;
        double AvgX;
        double AvgY;

    public:
    Data(){};

    //.i
    Data(string file){
        start(file);
    }

    //.i
    void start(string filename){
        ifstream file(filename);
        if(file.is_open()){

            string line;
            getline(file, line);
            xk = stod(line);

            while(getline(file, line)){

                if(line.find(',') == string::npos){
                    throw invalid_argument("Error en el archivo");
                }
                int split = line.find(',');
                x.push_back(stod(line.substr(0,split)));
                y.push_back(stod(line.substr(split + 1)));
                N++;
            }
            file.close();

            SumX = sumV(x);
            SumY = sumV(y);
            SquareSumX = sumSquareV(x);
            SquareSumY = sumSquareV(y);
            SumXY = sumMultipliedV(x,y);
            AvgX = SumX / N;
            AvgY = SumY / N;
        }
    }

    //.i
    vector<double> getX() const{
        return x;
    }

    //.i
    vector<double> getY() const{
        return y;
    }

    //.i
    double getXk(){
        return xk;
    }

    //.i 
    double getSumX(){
        return SumX;
    }

    //.i 
    double getSumY(){
        return SumY;
    }

    //.i 
    double getSquareSumX(){
        return SquareSumX;
    }

    //.i 
    double getSquareSumY(){
        return SquareSumY;
    }

    //.i
    double getSumXY(){
        return SumXY;
    }

    //.i
    double getAvgX(){
        return AvgX;
    }

    //.i
    double getAvgY(){
        return AvgY;
    }

    //.i
    double getN(){
        return N;
    }

    // Funciones auxiliares para realizar las sumas
    //.i
    void DisplayGetX(vector<double> v){
        for(int i = 0; i < v.size(); i++){
            cout << v[i] << endl;
        }
    }

    //.i
    double sumV(vector<double> v){
        double total = 0;
        for(int i = 0; i < v.size(); i++){
            total+=v[i];
        }
        return total;
    }

    //.i
    double sumSquareV(vector<double> v){
        double total = 0;
        for(int i = 0; i < v.size(); i++){
            total+=v[i]*v[i];
        }
        return total;
    }

    //.i 
    double sumMultipliedV(vector<double> v1, vector<double> v2){
        double total = 0;
        for(int i = 0; i < v1.size(); i++){
            total+=v1[i]*v2[i];
        }
        return total;
    }
};