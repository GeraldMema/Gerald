//
// Created by henry on 11/11/2015.
//

#ifndef FUNCTION_TABLE_COMPANION_H
#define FUNCTION_TABLE_COMPANION_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <Eigen/LU>
#include "Eigen/Dense"
#include "Eigen/Eigenvalues"
#include "../libMatrix/Matrix.h"

using Eigen::EigenSolver;
using Eigen::MatrixXd;

class Companion {

    double ** C;
    int Cgrammes;

    double * convertedC;

    int grammes;

    MatrixXd lambda;
    MatrixXd V;

    int makeCaseInvertable1( double * M0 , double * M1 );   //periptwsh pou to d=1

    int makeCaseInvertableD(int vathmosKrymenhsMetavlhths, double ** listOfMd); //periptwsh pou to d>1

    int generateFirstRowOfCompanion();//ftiaxnoume thn 1h grammh tou Companion

    int generateRestCompanion();//kanoume shift tis ypoloipes

    int generateLastBlockOfCompanion(int vathmosKrymenhsMetavlhthts, double ** list);//ftiaxnoume thn teleytaia grammh tou companion

    int allocateC(int grammes,int sthles );//desmeyoume xwro gia to C

    int calcX( EigenSolver<MatrixXd> & es );//pernoume ta swsta lambda kai V

    int generateFirstRowOfMultiplicityCompanion();

    int shift();

    int generateLastRowOfMultiplicityCompanion( Matrix<double> & f );

public:

    int solveWithInvert(int vathmosKrymenhsMetavlhthts , double ** listOfMd, int grammes);

    MatrixXd getLambda();

    MatrixXd getV();

    int generateMultiplicityCompanion(Matrix<double> & f);

    int calcEigenvectorsAndEigenValues();//mas dinei idiotimes-idiodianismata

    int convertC();//convert se 1-D

    int print();
};


#endif //FUNCTION_TABLE_COMPANION_H

