//
// Created by henry on 10/11/2015.
//

#include "Kappa.h"

using Eigen::MatrixXd;
using Eigen::JacobiSVD;
using Eigen::Map;

using namespace std;

Kappa::Kappa()
{

    line = "";
    line.clear();
}

/*
 * Dexete ena tetragwniko pinaka , ton kanei convert se morfh anagnwrisimh
 * apo to JacobiSVD kai ypologizei to k
 */
int Kappa::generateKappa(double * data , int grammes , int B ) {

    bound = pow(10 , B);

    Map< MatrixXd > m(data,grammes,grammes);

    JacobiSVD< MatrixXd > svd(m , Eigen::ComputeFullU );

    singular = svd.singularValues(); // krataw ta singular values

    if( calcKappa() == 0 ) // ypologizw to k = smax/smin
        return 0; // eimai standard problem
    else if ( k == 1)
        return 2; // k was nan
    else
        return 1; //  eimai generalize problem

}

/*
 * Ypologismos tou k opws anaferetai sth 8ewria
 */
int Kappa::calcKappa( ) {

    double max = singular(0); // arxikopoiw ta min kai max
    double min = singular(0);

    long rows = singular.rows(); // gia logous veltistopoihshs

    for (int i = 0; i < rows ; ++i) {

        if( max < singular(i) ) {
            max = singular(i);
            continue;
        }
        if( min > singular(i) )
            min = singular(i);

    }

    //alliws ola kala kai ypologizw to kappa
    k = max/min;

    cout << " k ~= " << k ;
    line.append(" k ~= ");
    std::ostringstream str;
    str << k;
    line.append(str.str().c_str());

    if( k > bound ) {
        cout << " > Bound: ill-conditioned Md, generalized eigenproblem \n";
        line.append(" > Bound: ill-conditioned Md, generalized eigenproblem \n");
        return 3;
    }
    else if( isnan(k) )
    {
        cout << " , which means is no better than previous\n";
        line.append(" , which means is no better than previous\n");
        return 1;
    }
    else {
        cout << " < Bound: non-singular Μd, standard eigenproblem\n";
        line.append(" < Bound: non-singular Μd, standard eigenproblem\n");
        return 0;
    }
}
