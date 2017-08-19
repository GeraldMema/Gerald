//
// Created by henry on 4/1/2016.
//

#ifndef PROJECT_2_0_TESTSYLVESTER_H
#define PROJECT_2_0_TESTSYLVESTER_H

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestCase.h"
#include "../../libMatrix/Sylvester.h"
#include "../../libMatrix/Sylvester.cpp"

using namespace CPPUNIT_NS;

class TestSylvester : public TextFixture {

    CPPUNIT_TEST_SUITE( TestSylvester );

    CPPUNIT_TEST( testCalcSylvesterForRandomValue );

    CPPUNIT_TEST_SUITE_END();

public:

    void testCalcSylvesterForRandomValue();

};


#endif //PROJECT_2_0_TESTSYLVESTER_H
