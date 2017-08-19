//
// Created by henry on 26/11/2015.
//

#ifndef LIBTEST_TESTPOLYWNYMO_MHTRWWN_H
#define LIBTEST_TESTPOLYWNYMO_MHTRWWN_H

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestCase.h"
#include "../../libMatrix/Polywnymo_mhtrwwn.h"
#include "../../libMatrix/Polywnymo_mhtrwwn.cpp"

using namespace CPPUNIT_NS;

template <typename T>
class TestPolywnymo_mhtrwwn : public  TestFixture {

    CPPUNIT_TEST_SUITE( TestPolywnymo_mhtrwwn );

        CPPUNIT_TEST( testMakeArrayWithDoubleArrays );

    CPPUNIT_TEST_SUITE_END();

public:

    void testMakeArrayWithDoubleArrays();

};


#endif //LIBTEST_TESTPOLYWNYMO_MHTRWWN_H
