//
// Created by henry on 12/11/2015.
//

#ifndef LIBTEST_TESTPINAKAS_POLYWNYMOU_MHTRWWN_H
#define LIBTEST_TESTPINAKAS_POLYWNYMOU_MHTRWWN_H

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestCase.h"
#include "../../libMatrix/Pinakas_polywnymou_mhtrwwn.h"
//#include "../../libMatrix/Pinakas_polywnymou_mhtrwwn.cpp"
#include "../../libMatrix/Matrix.h"
#include "../../libMatrix/Matrix.cpp"

using namespace CPPUNIT_NS;

template <typename T>
class testPinakas_polywnymou_mhtrwwn : public TestFixture , public Pinakas_polywnymou_mhtrwwn<T> {

    CPPUNIT_TEST_SUITE( testPinakas_polywnymou_mhtrwwn );

    CPPUNIT_TEST( testPublicFunctions );

    CPPUNIT_TEST_SUITE_END();

public:

    void testPublicFunctions();


};


#endif //LIBTEST_TESTPINAKAS_POLYWNYMOU_MHTRWWN_H
