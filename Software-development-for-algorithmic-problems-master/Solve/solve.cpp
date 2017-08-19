#include "solve.h"

Solve::Solve()
{

}

int Solve::solve_with_points(double ** points , double ** points2 , int pointsCounter, int points2Counter, int d1,int d2){

    handler.handle_Points(points,points2 , pointsCounter , points2Counter ,d1 ,d2);

    return 0;

}
