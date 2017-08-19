//
// Created by henry on 18/10/2015.
//

#ifndef FUNCTION_TABLE_PINAKAS_POLYWNYMOU_MHTRWWN_H
#define FUNCTION_TABLE_PINAKAS_POLYWNYMOU_MHTRWWN_H

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "Polywnymo_mhtrwwn.h"
#include "Matrix.h"

template <typename T>
class Pinakas_polywnymou_mhtrwwn : public Matrix<T> {

    double ** converdedMd;

    double * OneDconverdedMd;

    int copyValuesToMd();

public:

    ~Pinakas_polywnymou_mhtrwwn();
    Pinakas_polywnymou_mhtrwwn();

    void print_Table();

    void generate_Mhtrwo(Matrix<double > & m1, Matrix<double> & m2, int column);		//ftiaxnoume kapoio Ai

    int convertToDouble();

    int make1D();

    double * getOneDconverdedMd() { return OneDconverdedMd; }

    double** getConvertedMd() { return converdedMd; }

    void insert( int i, int j, T value ) { this->table[i][j] = value; }

    T get_element(int i, int j) { return this->table[i][j]; };

    int print_to_string(std::string &line);



};


#endif //FUNCTION_TABLE_PINAKAS_POLYWNYMOU_MHTRWWN_H
