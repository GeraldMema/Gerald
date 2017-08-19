//
// Created by henry on 10/11/2015.
//

#ifndef FUNCTION_TABLE_KAPPA_H
#define FUNCTION_TABLE_KAPPA_H

#include <iostream>
#include "Eigen/Dense"
#include "Eigen/Core"
#include "Eigen/SVD"

using Eigen::MatrixXd;
using Eigen::JacobiSVD;
using Eigen::Map;

class Kappa {

protected:
    double k;                                                   //deikths katastashs

    JacobiSVD< MatrixXd > :: SingularValuesType singular;       //metavlhth pou kratame tis idiazouses times

    double smax;                                                //max idiazousa timh
    double smin;                                                //min idiazousa timh

    double bound;                                                //orio k

    int calcKappa();                                             //ypologismos k

    int checkbound(double);

    std::string line;

public:

    Kappa();

    std::string get_line() { return line; }

    int generateKappa(double * data,int grammes , int B);

    double getKappa(){ return k; }

};


#endif //FUNCTION_TABLE_KAPPA_H

