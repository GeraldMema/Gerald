all: main

testPinakas_polywnymou_mhtrwwn.o: TestLibMatrix/testPinakas_polywnymou_mhtrwwn.cpp
	g++ -c TestLibMatrix/testPinakas_polywnymou_mhtrwwn.cpp TestLibMatrix/testPinakas_polywnymou_mhtrwwn.h

TestZed.o: TestLibSolver/TestZed.cpp
	g++ -c TestLibSolver/TestZed.cpp TestLibSolver/TestZed.h -g3

TestPinakas_syntelestwn.o: TestLibMatrix/TestPinakas_syntelestwn.cpp
	g++ -c TestLibMatrix/TestPinakas_syntelestwn.cpp TestLibMatrix/TestPinakas_syntelestwn.h

TestPolywnymo_mhtrwwn.o: TestLibMatrix/TestPolywnymo_mhtrwwn.cpp
	g++ -c TestLibMatrix/TestPolywnymo_mhtrwwn.cpp TestLibMatrix/TestPolywnymo_mhtrwwn.h

TestKappa.o: TestLibSolver/TestKappa.cpp
	g++ -c TestLibSolver/TestKappa.cpp TestLibSolver/TestKappa.h -g3

TestCompanion.o: TestLibSolver/TestCompanion.cpp
	g++ -c TestLibSolver/TestCompanion.cpp TestLibSolver/TestCompanion.h -g3

TestGeneralProblem.o: TestLibSolver/TestGeneralProblem.cpp
	g++ -c TestLibSolver/TestGeneralProblem.cpp TestLibSolver/TestGeneralProblem.h -g3

TestInterpolation.o: TestLibCurves/TestInterpolation.cpp TestLibCurves/TestInterpolation.h
	g++ -c TestLibCurves/TestInterpolation.cpp TestLibCurves/TestInterpolation.h -g3

main: TestInterpolation.o TestMain.cpp TestZed.o TestPolywnymo_mhtrwwn.o testPinakas_polywnymou_mhtrwwn.o TestKappa.o TestCompanion.o TestGeneralProblem.o TestPinakas_syntelestwn.o
	g++ -o main TestMain.cpp TestKappa.o TestZed.o testPinakas_polywnymou_mhtrwwn.o TestCompanion.o \
TestGeneralProblem.o TestPinakas_syntelestwn.o TestPolywnymo_mhtrwwn.o TestInterpolation.o \
-g3 -lcppunit -llapacke

clean:
	rm -rf *.o TestLibSolver/*.gch TestLibMatrix/*.gch TestLibCurves/*.gch main