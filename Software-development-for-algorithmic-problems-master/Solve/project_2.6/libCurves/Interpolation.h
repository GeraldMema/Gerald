//
// Created by henry on 21/12/2015.
//

#ifndef PROJECT_2_0_INTERPOLATION_H
#define PROJECT_2_0_INTERPOLATION_H


#include <iostream>
#include <fstream>
#include <cmath>
#include "Eigen/Dense"
#include "Eigen/Core"
#include "Eigen/SVD"

class Interpolation {

    double ** M;
    int MGrammes;
    int MSthles;

    int init_M(int grammes, int sthles);

    int kappa;

    double * convertedTo1dM;

    int * kernelOfInts;

    int convertTo1D();

    std::ofstream myfile;

    std::ofstream fileForGnu;
    int isSecondEquation;

    Eigen::MatrixXd kernel;

    bool is_empty(std::ofstream& pFile);

    std::string line;

public:

    ~Interpolation();
    Interpolation();

    int generate_M(double ** givenPoints , int grammes , int d  );//Ftiaxnoume to polywnymo paremvolhs

    int print();//ektypwnoume to polywnymo paremvolhs

    double getElement(int i , int j ) { return M[i][j]; };//pairnoume ta stoixeia tou

    int calc_rank();//ypologismos rank gia to polywnymo paremvolhs

    int calc_Kernel();//briskoume ton pyrhna tou pinaka o opoios mas dinei tous syntelestes tou poluwnymou

    int DoubleToInt();//metatroph pragmatikwn syntelestes

    int WriteToFile();//grafw se ena arxeio to teliko poluwnymo pou ypologisa

    std::string get_line() { return line; }

};


#endif //PROJECT_2_0_INTERPOLATION_H
