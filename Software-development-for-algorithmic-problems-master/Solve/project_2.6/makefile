all: equations generate

Zed.o:	libSolver/Zed.cpp
	g++ -c libSolver/Zed.cpp libSolver/Zed.h -g3

Kappa.o: libSolver/Kappa.cpp
	g++ -c libSolver/Kappa.cpp libSolver/Kappa.h -g3

GeneralProblem.o: libSolver/GeneralProblem.cpp
	g++ -c libSolver/GeneralProblem.cpp libSolver/GeneralProblem.h -llapacke -g3

Companion.o: libSolver/Companion.cpp
	g++ -c libSolver/Companion.cpp libSolver/Companion.h -g3

Matrix.o: libMatrix/Matrix.cpp
	g++ -c libMatrix/Matrix.cpp libMatrix/Matrix.h

generate: generate_functions.cpp
	g++ -o generate generate_functions.cpp -g3

Pinakas_syntelestwn.o: libMatrix/Pinakas_syntelestwn.cpp
	g++ -c libMatrix/Pinakas_syntelestwn.cpp libMatrix/Pinakas_syntelestwn.hpp -g3

Polywnymo_mhtrwwn.o: libMatrix/Polywnymo_mhtrwwn.cpp
	g++ -c libMatrix/Polywnymo_mhtrwwn.cpp libMatrix/Polywnymo_mhtrwwn.h -g3

Pinakas_polywnymou_mhtrwwn.o: libMatrix/Pinakas_polywnymou_mhtrwwn.cpp
	g++ -c libMatrix/Pinakas_polywnymou_mhtrwwn.cpp libMatrix/Pinakas_polywnymou_mhtrwwn.h -g3

Sylvester.o: libMatrix/Sylvester.cpp
	g++ -c libMatrix/Sylvester.cpp libMatrix/Sylvester.h

Handler.o: Handler.cpp
	g++ -c Handler.cpp Handler.h -llapack -lblas -g3

Interpolation.o: libCurves/Interpolation.cpp libCurves/Interpolation.h
	g++ -c libCurves/Interpolation.cpp libCurves/Interpolation.h -g3

equations: main.cpp Matrix.o Polywnymo_mhtrwwn.o\
 Pinakas_syntelestwn.o Sylvester.o Pinakas_polywnymou_mhtrwwn.o Handler.o Kappa.o\
 Companion.o GeneralProblem.o Zed.o Interpolation.o
	g++ -o equations GeneralProblem.o Companion.o Kappa.o Matrix.o Handler.o Polywnymo_mhtrwwn.o Pinakas_syntelestwn.o\
 Sylvester.o Pinakas_polywnymou_mhtrwwn.o Zed.o Interpolation.o main.cpp -llapacke   -g3

clean:
	rm -f *.o *.gch equations generate libCurves/*.gch libMatrix/*.gch generated_functions.txt libSolver/*.gch
