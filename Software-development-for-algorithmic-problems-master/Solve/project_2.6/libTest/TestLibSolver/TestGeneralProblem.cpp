//
// Created by henry on 25/11/2015.
//

#include "TestGeneralProblem.h"
#include "cppunit/config/SourcePrefix.h"


void TestGeneralProblem::testSolveWithGeneralProblem() {

    GeneralProblem g;

    double data0[] = {-1,0,-1,1,-1,1,0,1,1};
    double data1[] = {1,0,1,1,1,2,0,1,1};
    double data2[] = {1,0,0,0,1,0,0,0,1};

    double ** list = new double*[3] ;

    list[0] = data0;
    list[1] = data1;
    list[2] = data2;

    // dexetai vathmo krymenhs metavlhths , lista me deiktes se monodiastatous pinakes double , rows
    int result = g.solveWithGeneralProblem( 1 , list , 3 ); // testarw gia vathmo krymenhs metavlhths == 1
    CPPUNIT_ASSERT( result == 0 );

    result = g.solveWithGeneralProblem( 2 , list , 3 ); // testarw gia vathmo krymenhs metavlhths > 1
    CPPUNIT_ASSERT( result == 0 );

    delete[] list;

}