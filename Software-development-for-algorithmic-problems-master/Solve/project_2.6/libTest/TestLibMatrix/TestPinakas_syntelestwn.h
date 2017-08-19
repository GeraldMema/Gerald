//
// Created by henry on 26/11/2015.
//

#ifndef LIBTEST_TESTPINAKAS_SYNTELESTWN_H
#define LIBTEST_TESTPINAKAS_SYNTELESTWN_H

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestCase.h"
#include "../../libMatrix/Pinakas_syntelestwn.hpp"
#include "../../libMatrix/Pinakas_syntelestwn.cpp"
//#include "../../Handler.h"

using namespace CPPUNIT_NS;

class TestPinakas_syntelestwn : public TestFixture {

    CPPUNIT_TEST_SUITE( TestPinakas_syntelestwn );

    CPPUNIT_TEST( testcalcWith );

    CPPUNIT_TEST_SUITE_END();

public:

    void testcalcWith();

};


#endif //LIBTEST_TESTPINAKAS_SYNTELESTWN_H
