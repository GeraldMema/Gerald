//
// Created by henry on 21/12/2015.
//

#include "TestInterpolation.h"
#include "cppunit/config/SourcePrefix.h"

TestInterpolation::TestInterpolation()
{

    this->points = new double * [5];

    for (int i = 0; i < 5; ++i) {
        this->points[i] = new double[2];
    }

    this->points[0][0] = -1;
    this->points[0][1] = 0;
    this->points[1][0] = 1;
    this->points[1][1] = 0;
    this->points[2][0] = 3;
    this->points[2][1] = -1;
    this->points[3][0] = 4;
    this->points[3][1] = -1;
    this->points[4][0] = 1;
    this->points[4][1] = -3;

}

TestInterpolation::~TestInterpolation() {

    for (int i = 0; i < 5; ++i) {
        delete[] this->points[i];
    }

    delete[] this->points;

}

void TestInterpolation::testGenerate_M() {

    Interpolation m;

    m.generate_M((double**)this->points,5,2);

    // elegxw thn timh kapoiwn 8esewn tou pinaka gia na dw ean exei ginei la8os
    CPPUNIT_ASSERT(1 == m.getElement(0,0));
    CPPUNIT_ASSERT(-1 == m.getElement(0,1));
    CPPUNIT_ASSERT(0 == m.getElement(0,2));
    CPPUNIT_ASSERT(1 == m.getElement(0,3));
    CPPUNIT_ASSERT(-0 == m.getElement(0,4));
    CPPUNIT_ASSERT(0 == m.getElement(0,5));

    CPPUNIT_ASSERT(1 == m.getElement(1,0));
    CPPUNIT_ASSERT(1 == m.getElement(1,1));
    CPPUNIT_ASSERT(0 == m.getElement(1,2));
    CPPUNIT_ASSERT(1 == m.getElement(1,3));
    CPPUNIT_ASSERT(0 == m.getElement(1,4));
    CPPUNIT_ASSERT(0 == m.getElement(1,5));

    CPPUNIT_ASSERT(1 == m.getElement(2,0));
    CPPUNIT_ASSERT(3 == m.getElement(2,1));
    CPPUNIT_ASSERT(-1 == m.getElement(2,2));
    CPPUNIT_ASSERT(9 == m.getElement(2,3));
    CPPUNIT_ASSERT(-3 == m.getElement(2,4));
    CPPUNIT_ASSERT(1 == m.getElement(2,5));

    CPPUNIT_ASSERT(1 == m.getElement(3,0));
    CPPUNIT_ASSERT(4 == m.getElement(3,1));
    CPPUNIT_ASSERT(-1 == m.getElement(3,2));
    CPPUNIT_ASSERT(16 == m.getElement(3,3));
    CPPUNIT_ASSERT(-4 == m.getElement(3,4));
    CPPUNIT_ASSERT(1 == m.getElement(3,5));

    CPPUNIT_ASSERT(1 == m.getElement(4,0));
    CPPUNIT_ASSERT(1 == m.getElement(4,1));
    CPPUNIT_ASSERT(-3 == m.getElement(4,2));
    CPPUNIT_ASSERT(1 == m.getElement(4,3));
    CPPUNIT_ASSERT(-3 == m.getElement(4,4));
    CPPUNIT_ASSERT(9 == m.getElement(4,5));

    //-------------------------------

    m.print();

    // periptwsh pou exw dwsei perissotera shmeia apo oti 8a eprepe
    int error = m.generate_M((double**)this->points,6,2);
    CPPUNIT_ASSERT( 2 == error );
    //-------------------------------------------------------------

    // periptwsh pou deinw ligotera shmeia apoti prepei
    error = m.generate_M((double**)this->points,4,2);
    CPPUNIT_ASSERT( 1 ==  error );
    //--------------------------------------------------

    //periptwsh pou gia kapoio logo do8oun points = NULL
    error = m.generate_M(NULL,4,2);
    CPPUNIT_ASSERT( 3 ==  error );
    //--------------------------------------------------


//    m.calc_rank();
//    m.calc_Kernel();
//    m.DoubleToInt();
//    m.WriteToFile();
//    m.WriteToFile();



}