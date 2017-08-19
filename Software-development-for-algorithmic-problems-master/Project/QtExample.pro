QT = core gui widgets network printsupport svg

TARGET = qtgnuplotlib-example
TEMPLATE = app
LIBS += -lQtGnuplot "../Lib/build-Solve-Qt_5_2_1_qt5-Debug/libSolve.a" -llapacke

CONFIG += debug

SOURCES = qtgnuplotlib-example.cpp \
    visualization.cpp

FORMS += \
    visualization.ui

HEADERS += \
    visualization.h \
    ../Lib/Solve/solve.h

INCLUDEPATH += "$$PWD/../Lib/Solve"
