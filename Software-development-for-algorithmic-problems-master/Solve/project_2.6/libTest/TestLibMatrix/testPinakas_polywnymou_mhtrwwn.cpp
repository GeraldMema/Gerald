//
// Created by henry on 12/11/2015.
//

#include "testPinakas_polywnymou_mhtrwwn.h"
#include "cppunit/config/SourcePrefix.h"
#include <iostream>

template <typename T>
void testPinakas_polywnymou_mhtrwwn<T>::testPublicFunctions() {

    this->allocate_Table(3,3);

    int count = 1;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            this->table[i][j] = new double;
            this->table[i][j][0] = count;
            count++;
        }

    }

    // elegxw an douleuei h synarthsh converteToDouble kai make1D
    this->convertToDouble();

    this->make1D();

    double * OneDConvertedMd = this->getOneDconverdedMd();

    double ** converdedMd = this->getConvertedMd();

    count = 1;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            CPPUNIT_ASSERT_EQUAL( (double) count , converdedMd[i][j] );
            CPPUNIT_ASSERT_EQUAL( converdedMd[j][i] , OneDConvertedMd[i*this->grammes+j] );
            count ++;
        }
    }
    //------------------------------------------------

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            delete this->table[i][j];
        }

    }


}

