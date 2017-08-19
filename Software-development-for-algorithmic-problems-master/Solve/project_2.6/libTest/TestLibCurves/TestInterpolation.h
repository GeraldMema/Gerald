//
// Created by henry on 21/12/2015.
//

#ifndef PROJECT_2_0_TESTINTERPOLATION_H
#define PROJECT_2_0_TESTINTERPOLATION_H

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestCase.h"
#include "../../libCurves/Interpolation.h"

using namespace CPPUNIT_NS;

class TestInterpolation : public TestFixture {

    CPPUNIT_TEST_SUITE( TestInterpolation );

    CPPUNIT_TEST( testGenerate_M );

    CPPUNIT_TEST_SUITE_END();

private:

    double ** points;

public:

    TestInterpolation();
    ~TestInterpolation();

    void testGenerate_M();

};


#endif //PROJECT_2_0_TESTINTERPOLATION_H
