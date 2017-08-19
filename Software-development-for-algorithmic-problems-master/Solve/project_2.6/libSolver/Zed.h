//
// Created by henry on 2/12/2015.
//

#ifndef FUNCTION_TABLE_ZED_H
#define FUNCTION_TABLE_ZED_H

#include "../libMatrix/Pinakas_polywnymou_mhtrwwn.h"
//#include "../libMatrix/Pinakas_polywnymou_mhtrwwn.cpp"
#include "../libMatrix/Pinakas_syntelestwn.hpp"
#include "Kappa.h"
#include <stdlib.h>

class Zed {

    double B;

    int t1,t2,t3,t4;

    int M1sthles;

    double * OneDconverdedMd;

    Kappa k;

    int make1D(double ** converdedMd, int grammes , int sthles);

    int calc_z(double *tempa, double *tempb, double *Ti, int power);                 //ypologizei tis taytothtes  (t1z+t2)^3

    int z_is_hidden_variable(Pinakas_polywnymou_mhtrwwn<double *> *ppm );      //ypologizei ton pinaka Md me z anti gia y


public:

    Zed();
    ~Zed();

    std::string get_line() { return k.get_line(); }

    void setB(double value) { B = value; }

    int change_hidden_variable( Pinakas_polywnymou_mhtrwwn<double*> * , double B );  //dinei timh sta t1 t2 t3 t4 kai kanoume allagh metavlhths

    int change_PinakaSyntelestwn(Pinakas_syntelestwn<double> * ps);             //ypologizei tous pinakes syntelestwn me z anti gia y

    double getKappa() { return k.getKappa() ; }

    int CalcKappa( Pinakas_polywnymou_mhtrwwn<double*> * ppm , int bound );

    int getT1() { return t1; }
    int getT2() { return t2; }
    int getT3() { return t3; }
    int getT4() { return t4; }

    double * getOneDconvertedMd() { return OneDconverdedMd; };

};


#endif //FUNCTION_TABLE_ZED_H
