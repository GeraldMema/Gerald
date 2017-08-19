//
// Created by henry on 25/11/2015.
//

#ifndef LIBTEST_TESTCOMPANION_H
#define LIBTEST_TESTCOMPANION_H

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestCase.h"
#include "../../libSolver/Companion.h"

using namespace CPPUNIT_NS;

class TestCompanion : public TestFixture {

    CPPUNIT_TEST_SUITE( TestCompanion );

    CPPUNIT_TEST( testsolveWithInvert );

    CPPUNIT_TEST_SUITE_END();

public:

    void testsolveWithInvert();

};


#endif //LIBTEST_TESTCOMPANION_H
