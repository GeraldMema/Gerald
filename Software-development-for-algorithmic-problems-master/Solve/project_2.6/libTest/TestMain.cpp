//
// Created by henry on 23/10/2015.
//

#include "TestLibSolver/TestKappa.h"
#include "../libSolver/Kappa.cpp"

#include "TestLibSolver/TestCompanion.h"
#include "../libSolver/Companion.cpp"

#include "TestLibSolver/TestGeneralProblem.h"
#include "../libSolver/GeneralProblem.cpp"
#include "lapacke.h"

#include "TestLibSolver/TestZed.h"
#include "../libSolver/Zed.cpp"

#include "TestLibMatrix/testPinakas_polywnymou_mhtrwwn.h"
#include "TestLibMatrix/testPinakas_polywnymou_mhtrwwn.cpp"

#include "TestLibMatrix/TestPinakas_syntelestwn.h"

#include "TestLibMatrix/TestPolywnymo_mhtrwwn.h"
#include "TestLibMatrix/TestPolywnymo_mhtrwwn.cpp"

#include "TestLibCurves/TestInterpolation.h"
#include "../libCurves/Interpolation.cpp"

#include <iostream>
#include <stdexcept>
#include <cppunit/ui/text/TestRunner.h>

using namespace std;

using namespace CPPUNIT_NS;

int main(){

    CppUnit::TextUi::TestRunner runner;
   runner.addTest( TestKappa::suite() );
   runner.addTest( TestCompanion::suite() );
   runner.addTest( TestGeneralProblem::suite() );
   runner.addTest( testPinakas_polywnymou_mhtrwwn<double*>::suite() );
    runner.addTest( TestPinakas_syntelestwn::suite() );
   runner.addTest( TestPolywnymo_mhtrwwn< Pinakas_polywnymou_mhtrwwn<double*>  >::suite() );
   runner.addTest( TestZed::suite() );
    runner.addTest( TestInterpolation::suite() );

    runner.run();

    return 0;

}
