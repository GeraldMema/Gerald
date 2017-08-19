//
// Created by henry on 21/10/2015.
//

#ifndef FUNCTION_TABLE_HANDLER_H
#define FUNCTION_TABLE_HANDLER_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <ctype.h>
#include "libMatrix/Matrix.h"
#include "libMatrix/Matrix.cpp"
#include "libMatrix/Pinakas_syntelestwn.hpp"
#include "libMatrix/Pinakas_syntelestwn.cpp"
#include "libMatrix/Polywnymo_mhtrwwn.h"
#include "libMatrix/Polywnymo_mhtrwwn.cpp"
#include "libMatrix/Pinakas_polywnymou_mhtrwwn.h"
#include "libMatrix/Pinakas_polywnymou_mhtrwwn.cpp"
#include "libMatrix/Sylvester.h"
#include "libMatrix/Sylvester.cpp"
#include "libSolver/Kappa.h"
#include "libSolver/Companion.h"
#include "libSolver/GeneralProblem.h"
#include "libSolver/Zed.h"
#include "libCurves/Interpolation.h"

#define BUFFSIZE 1000

using Eigen::MatrixXd;

class Handler {

    int dimensionAi;                //megethos Md

    int d0;                        //max vathmos polywnhmou m1 
    int d1;                         //max vathmos polywnhmou m2 

    int B;                          //BOUND

    char hidden_variable;           //krymmenh metavlhth
    int ** result;                 //S*v (bonus)

    Pinakas_syntelestwn<double> m1;  //Polywnymo m1
    Pinakas_syntelestwn<double> m2;  //Polywnymo m2
    Pinakas_syntelestwn<double> v;   //dianysma v
    Sylvester <double*> sylvester;   //pinakas sulvester

    double ** solutions;
    int solutionsRows;
    int solutions_i;

    double ** solutionsWIthGeneralized;
    int solutionsWIthGeneralizedRows;
    int solutionsWIthGeneralized_i;

    int allaksaMetavlhth;

    int ypologizwKaiTis2Lyseis;

    string line;

    Polywnymo_mhtrwwn< Pinakas_polywnymou_mhtrwwn<double*> *> Polywnymo_Mhtrwwn;

    Kappa k;                                                                 // variable of condition number

    Companion c;                                                             //variable of Companion

    GeneralProblem gp;                                                       //variable of Generalized Problem

    Zed z;

    Pinakas_syntelestwn<double> oldM1;  //Polywnymo m1
    Pinakas_syntelestwn<double> oldM2;  //Polywnymo m2

    Interpolation interpolationMatrix;
    double str_to_double(char * num);

    int generate_rest_solution( MatrixXd &lambda ,MatrixXd &V , int allaksaMetavlhth  );

    template <typename T>
    int allocate_2D_table(T *** table, int rows, int cols);


protected:

    char Read_synarthsh_from_file(char *filename );                         //anagnwsh apo arxeio

    void place_function_in_Matrix(char * buffer , Matrix<double> &);           //parser gia ton pinaka Matrix<int>

  /*+++++++++++++++++++++++++++++++*/
    char find_hidden_variable( Matrix<double> & m1 , Matrix<double> & m2);        //vriskoume thn krymmenh metavlhth


    void consola();                                                         //kaloume thn place_function_in_Matrix(char * buffer , Matrix<int> &);

    void generate();                                                        //paragoyme ta 2 polyonyma

    int calc_roots_with_imagine(int * y,int * x);                           //ypologizei ts rizes me fantastikous arithmous

public:

    Handler();
    ~Handler();

    void handle_input(int argc, char * argv[]);                             //epiloges ekkinhshs programmatos

    void generate_Sylvester();                                              //ftiaxnoume Silvester

    void generate_Polywnymo_Mhtrwwn();                                      //ftiaxnoyme ta Ai (polyonuma mhtrwwn)

    /*++++++++++++++++++++++++++++++++*/
    void print();                                                           //ektypwsh epiloges xrhsth

    /*+++++++++++++++++++++++*/
    void generate_Bonus();                                                  //to bonus kommati

    int solve();                                                            //epilysh eyreshs tomhs 2 polyonymwn

    int handle_Points(double ** points , double ** points2, int pointsCounter, int points2Counter,int newd1,int newd2);
    
    double ** get_solutions() { return solutions; }
    int get_solutions_i() { return solutions_i; }

    double ** get_solutionsWIthGeneralized() { return solutionsWIthGeneralized; }
    int get_solutionsWIthGeneralized_i() { return solutionsWIthGeneralized_i; }

    void read( char * filename );                                           //kaloume thn Read_synarthsh_from_file(char *filename );

    int get_allaksaMetavlhth() { return allaksaMetavlhth; }

    Pinakas_polywnymou_mhtrwwn<double*> get_Md();

    string get_line(){ return line; }

private:
    int copy_m1_and_m2();
    int find_better_kappa(int *isAntistrepsimos, int *allaksaMetavlhth, int kappa);
    int calc_x_with_multiplicity(int i, Eigen::MatrixXd &lambda);
    int check_if_I_have_seen_y(int i, Eigen::MatrixXd lambda);
    int check_sum(int res1, int res2, MatrixXd lambda, MatrixXd V, int i);
    int is_int(char *str);
    int check_if_syntelesths_einai_1(char *buffer, double *syntelestes, int k, int pos, int proshmo);
    double diavasma_syntelesth(char *buffer, int *j);
    int check_sum(int res1, int res2, double x, double y);
    int clean_white_spaces(string &line);
};


#endif //FUNCTION_TABLE_HANDLER_H
