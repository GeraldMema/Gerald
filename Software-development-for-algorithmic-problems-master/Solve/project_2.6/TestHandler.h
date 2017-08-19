//
// Created by henry on 22/10/2015.
//

#ifndef FUNCTION_TABLE_TESTHANDLER_H
#define FUNCTION_TABLE_TESTHANDLER_H

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestFixture.h"
#include "cppunit/TestCase.h"
#include "Handler.h"

using namespace CPPUNIT_NS;

class TestHandler : public TestFixture , public Handler {

    CPPUNIT_TEST_SUITE( TestHandler );

        CPPUNIT_TEST( testRead_synarthsh_from_file );

    CPPUNIT_TEST_SUITE_END();

public:

    void setUp();

    void tearDown();

    void testRead_synarthsh_from_file();

};


#endif //FUNCTION_TABLE_TESTHANDLER_H
