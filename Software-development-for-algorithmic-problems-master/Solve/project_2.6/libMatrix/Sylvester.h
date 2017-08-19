//
// Created by henry on 18/10/2015.
//

#ifndef FUNCTION_TABLE_SYLVESTER_H
#define FUNCTION_TABLE_SYLVESTER_H

#include "Matrix.h"
#include "Eigen/Dense"
#include "Eigen/LU"
#include <time.h>
#include <math.h>

template <typename T>
class Sylvester : public Matrix<T> {

    int m1grammes;
    int m2grammes;
    int m1sthles;
    int m2sthles;

    int resultGrammes;
    int resultSthles;

    double ** calculatedSylvester;

    double * convertedCalculatedSylvester;

public:

    Sylvester();
    ~Sylvester();

    int get_resultGrammes(){ return resultGrammes;}
    int get_resultSthles(){ return resultSthles;}

    void print_Table();
    void print_Table(char variable);
    void print_Table_bonus(int ** Sv);/*++++++++++++++++++*/

    void make_Sylvester(Matrix<double> &m1, Matrix<double> &m2);					//ftiaxnoume to pinaka Sylvester

    void fill_first_row_of_sylvester(Matrix<double> &m1, int first_row_pos, int dimension0);	//anathetoume timh sthn prwth kai sthn m2grammes-1  grammh tou silvester

    void shift_rest_first_half();															//kanoume shift gia to poluonumo m1

    void shift_rest_second_half();															//kanoume shift gia to poluonumo m2

    int get_vathmos(){return this->grammes;}											

    int** multiply(Matrix<double> & v);	/*++++++++++*/													//ulopoioume to bonus kommati (Sv)

    int calcDet();

    int calcSylvesterForRandomValue(int y0);

    int calcArrayOfSylvester(int y0,int grammh , int sthlh);

    int make1D();

};


#endif //FUNCTION_TABLE_SYLVESTER_H
