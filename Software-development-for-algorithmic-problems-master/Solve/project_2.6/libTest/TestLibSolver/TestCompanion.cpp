//
// Created by henry on 25/11/2015.
//

#include "cppunit/config/SourcePrefix.h"
#include "TestCompanion.h"

void TestCompanion::testsolveWithInvert() {

    Companion c;

    double data1[] = {1,0,1,1,1,2,0,1,1};
    double data0[] = {0,0,0,-3,0,4,0,-3,5};
    double data2[] = {1,0,0,0,1,0,0,0,1};

    double ** list = new double*[3] ;

    list[0] = data0;
    list[1] = data1;
    list[2] = data2;

    // dexetai vathmo krymenhs metavlhths , lista me deiktes se monodiastatous pinakes double , rows
    int result = c.solveWithInvert( 1 , list , 3 ); // testarw gia vathmo krymenhs metavlhths == 1
    CPPUNIT_ASSERT( result == 0 );

    result = c.solveWithInvert( 2 , list , 3 ); // testarw gia vathmo krymenhs metavlhths > 1
    CPPUNIT_ASSERT( result == 0 );

    delete[] list;

}
