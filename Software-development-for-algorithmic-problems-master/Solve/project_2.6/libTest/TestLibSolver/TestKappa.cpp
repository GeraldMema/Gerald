//
// Created by henry on 22/10/2015.
//

#include "cppunit/config/SourcePrefix.h"
#include "TestKappa.h"
#include <iostream>

using  std::endl;
using  std::cout;
using  Eigen::MatrixXd;

void TestKappa::testGenerateKappa() {

    Kappa k;

    double data[] = {1,0,1,1,1,2,0,1,1};
    CPPUNIT_ASSERT( k.generateKappa(data , 3 , 7) == 1 );

    double data1[] = {2,0,1,1,2,0,0,1,-1};
    CPPUNIT_ASSERT( k.generateKappa(data1 , 3 , 7) == 0 );

    double data2[] = {1,0,0,0,1,0,0,0,1};
    CPPUNIT_ASSERT( k.generateKappa(data2 , 3 , 7) == 0 );

}