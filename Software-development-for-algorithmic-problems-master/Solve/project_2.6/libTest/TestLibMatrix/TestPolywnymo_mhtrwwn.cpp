//
// Created by henry on 26/11/2015.
//

#include "TestPolywnymo_mhtrwwn.h"
#include "cppunit/config/SourcePrefix.h"
#include <iostream>

using std::cout;
using std::endl;

template <typename T>
void TestPolywnymo_mhtrwwn<T>::testMakeArrayWithDoubleArrays( ) {

    T * ppm_1 =  new T ;
    T * ppm_2 = new T ;

    ppm_1->allocate_Table(3,3);
    ppm_2->allocate_Table(3,3);

    double a[3][3];
    double b[3][3];

    int count = 1;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            a[i][j] = count;
            b[i][j] = count;
            ppm_1->insert(i,j , &a[i][j]);
            ppm_2->insert(i,j , &b[i][j]);
            count++;
        }
    }

    Polywnymo_mhtrwwn< T * > pm;

    pm.allocate_Table(1,2);

    pm.insert( ppm_1 , 0 , 0);
    pm.insert( ppm_2 , 0 , 1);

    double ** list = pm.makeArrayWithDoubleArrays();

    CPPUNIT_ASSERT_EQUAL( (double) 1 , list[0][0] );
    CPPUNIT_ASSERT_EQUAL( (double) 4 , list[0][1] );
    CPPUNIT_ASSERT_EQUAL( (double) 7 , list[0][2] );
    CPPUNIT_ASSERT_EQUAL( (double) 2 , list[0][3] );
    CPPUNIT_ASSERT_EQUAL( (double) 5 , list[0][4] );
    CPPUNIT_ASSERT_EQUAL( (double) 8 , list[0][5] );
    CPPUNIT_ASSERT_EQUAL( (double) 3 , list[0][6] );
    CPPUNIT_ASSERT_EQUAL( (double) 6 , list[0][7] );
    CPPUNIT_ASSERT_EQUAL( (double) 9 , list[0][8] );

    CPPUNIT_ASSERT_EQUAL( (double) 1 , list[1][0] );
    CPPUNIT_ASSERT_EQUAL( (double) 4 , list[1][1] );
    CPPUNIT_ASSERT_EQUAL( (double) 7 , list[1][2] );
    CPPUNIT_ASSERT_EQUAL( (double) 2 , list[1][3] );
    CPPUNIT_ASSERT_EQUAL( (double) 5 , list[1][4] );
    CPPUNIT_ASSERT_EQUAL( (double) 8 , list[1][5] );
    CPPUNIT_ASSERT_EQUAL( (double) 3 , list[1][6] );
    CPPUNIT_ASSERT_EQUAL( (double) 6 , list[1][7] );
    CPPUNIT_ASSERT_EQUAL( (double) 9 , list[1][8] );

}