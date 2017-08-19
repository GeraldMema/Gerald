#ifndef _GENERAL_PROBLEM_H_
#define _GENERAL_PROBLEM_H_

#include <iostream>
#include <Eigen/LU>
#include "Eigen/Dense"
#include "Eigen/Eigenvalues"
#include "lapacke.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using Eigen::MatrixXd;

class GeneralProblem {
	double **L0;
	double **L1;
	int grammes;
	double *convertedL0;
	double *convertedL1;

	int L0L1grammes;

	MatrixXd lambda;
	MatrixXd V;

	int makeCaseGeneralProblem1(double *M0, double *M1);   //genikeymeno provlhma gia d=1

	int makeCaseGeneralProblemD(int vathmosKrymenhsMetavlhths, double **listOfMd);   //genikeymeno provlhma gia d>1

	int generateFirstRowOfL0();     //ftiaxnw thn prwth grammh tou l0

	int generateFirstRowOfL1();     //ftiaxnw thn prwth grammh tou l1

	int generateRestL0L1();     //kanw shift ts epomenes grammes

	int generateLastBlockOfL0(int vathmosKrymenhsMetavlhthts, double **list);   //ftiaxnw thn teleytaia grammh tou l0

	int generateLastBlockOfL1(int vathmosKrymenhsMetavlhthts, double **list);    //ftiaxnw thn teleytaia grammh tou l1

	int allocateL0L1(int grammes1, int sthles);  //desmeyw xwro gia ta lo l1

	int convertL0L1();  //convert se 1-D

	int calcEigenvectorsAndEigenValues();

	int calcX( MatrixXd & lambda, MatrixXd & V );   //ta metatrepw sthn katallhlh morfh

	bool GEP(MatrixXd & A,MatrixXd & B,MatrixXd & v,MatrixXd & lamda);   //brisko idiotimes-idiovianismata

public:

	~GeneralProblem();
	GeneralProblem();

	int solveWithGeneralProblem(int vathmosKrymenhsMetavlhthts, double **listOfMd, int grammes);

	MatrixXd getLambda();

    MatrixXd getV();
    int print_table(double **table);
};

#endif //FUNCTION_GENERAL_PROBLEM_H
