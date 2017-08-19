#ifndef _PINAKAS_SYNTELESTWN_HPP_
#define _PINAKAS_SYNTELESTWN_HPP_

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "Matrix.h"
#include "Pinakas_polywnymou_mhtrwwn.h"
#include "Eigen/LU"
#include "Eigen/Dense"
#include "math.h"

using Eigen::MatrixXd;

template <typename T>
class Pinakas_syntelestwn : public Matrix<T>{

    int findMultiplicity(MatrixXd & lambda,  int pos );

    int calcWithImag(double * temp,double * variable,int power);

    int imag_roots(double * result,double * y,double * x);

    int calc_roots_with_imagine( double * y , double * x );

public:

    Pinakas_syntelestwn();
    ~Pinakas_syntelestwn();

    void print_Table();

    void create_Polywnymo( int vathmosPolywnymou );					//ftiaxnoume tyxaia polywnhma dedomenou d1 kai d2

    int calcWith(Eigen::MatrixXd lambda, Eigen::MatrixXd V , int k );

    T get_table_pos(int i , int j ) { return this->table[i][j];};

    T get_element(int i, int j){ return this->table[i][j]; }

    int replaceHiddenVariable( Matrix<double> & f1 , double valueOfHiddenVariable );

    int calcWithXAndY( double x , double y );

    int print_to_string(std::string &line);
};

#endif
