//
// Created by henry on 25/11/2015.
//

#ifndef LIBTEST_TESTGENERALPROBLEM_H
#define LIBTEST_TESTGENERALPROBLEM_H

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestCase.h"
#include "../../libSolver/GeneralProblem.h"

using namespace CPPUNIT_NS;

class TestGeneralProblem : public TestFixture {

    CPPUNIT_TEST_SUITE( TestGeneralProblem );

    CPPUNIT_TEST( testSolveWithGeneralProblem );

    CPPUNIT_TEST_SUITE_END();

public:

    void testSolveWithGeneralProblem();

};


#endif //LIBTEST_TESTGENERALPROBLEM_H
