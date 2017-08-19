#-------------------------------------------------
#
# Project created by QtCreator 2016-01-03T15:47:44
#
#-------------------------------------------------

QT       -= gui

TARGET = Solve
TEMPLATE = lib
CONFIG += staticlib

LIBS += -llapacke

SOURCES += solve.cpp \
    project_2.6/Handler.cpp \
    project_2.6/libCurves/Interpolation.cpp \
    project_2.6/libMatrix/Matrix.cpp \
    project_2.6/libMatrix/Pinakas_polywnymou_mhtrwwn.cpp \
    project_2.6/libMatrix/Pinakas_syntelestwn.cpp \
    project_2.6/libMatrix/Polywnymo_mhtrwwn.cpp \
    project_2.6/libMatrix/Sylvester.cpp \
    project_2.6/libSolver/Companion.cpp \
    project_2.6/libSolver/GeneralProblem.cpp \
    project_2.6/libSolver/Kappa.cpp \
    project_2.6/libSolver/Zed.cpp

HEADERS += solve.h \
    project_2.6/Handler.h \
    project_2.6/libCurves/Interpolation.h \
    project_2.6/libMatrix/Matrix.h \
    project_2.6/libMatrix/Pinakas_polywnymou_mhtrwwn.h \
    project_2.6/libMatrix/Pinakas_syntelestwn.hpp \
    project_2.6/libMatrix/Polywnymo_mhtrwwn.h \
    project_2.6/libMatrix/Sylvester.h \
    project_2.6/libSolver/Companion.h \
    project_2.6/libSolver/GeneralProblem.h \
    project_2.6/libSolver/Kappa.h \
    project_2.6/libSolver/Zed.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
