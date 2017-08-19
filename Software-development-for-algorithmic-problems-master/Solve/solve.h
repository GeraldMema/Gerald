#ifndef SOLVE_H
#define SOLVE_H

#include "project_2.6/Handler.h"

class Solve
{

    Handler handler;

public:

    Solve();

    int solve_with_points( double ** points , double ** points2 , int pointsCounter , int points2Counter , int d1,int d2);

};

#endif // SOLVE_H
