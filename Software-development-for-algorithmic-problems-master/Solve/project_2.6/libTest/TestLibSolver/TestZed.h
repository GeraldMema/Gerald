//
// Created by henry on 3/12/2015.
//

#ifndef FUNCTION_TABLE_TESTZED_H
#define FUNCTION_TABLE_TESTZED_H

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestCase.h"
#include "../../libSolver/Zed.h"

using namespace CPPUNIT_NS;

class TestZed : public TestFixture {

CPPUNIT_TEST_SUITE( TestZed );

        CPPUNIT_TEST( testCalcKappa );

    CPPUNIT_TEST_SUITE_END();

public:

    void testCalcKappa();

};


#endif //FUNCTION_TABLE_TESTZED_H
