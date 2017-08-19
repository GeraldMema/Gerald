//
// Created by henry on 22/10/2015.
//

#ifndef FUNCTION_TABLE_TESTHANDLER_H
#define FUNCTION_TABLE_TESTHANDLER_H

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestCase.h"
#include "../../libSolver/Kappa.h"

using namespace CPPUNIT_NS;

class TestKappa : public CppUnit::TestFixture  {

    CPPUNIT_TEST_SUITE( TestKappa );

        CPPUNIT_TEST( testGenerateKappa );

    CPPUNIT_TEST_SUITE_END();

public:

    void testGenerateKappa();

};


#endif //FUNCTION_TABLE_TESTHANDLER_H
