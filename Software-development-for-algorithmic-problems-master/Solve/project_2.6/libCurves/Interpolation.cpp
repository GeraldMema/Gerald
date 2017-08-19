//
// Created by henry on 21/12/2015.
//

#include "Interpolation.h"

using Eigen::MatrixXd;
using Eigen::JacobiSVD;
using Eigen::Map;
using Eigen::MatrixXf;

using std::cout;
using std::endl;
using std::abs;

Interpolation::~Interpolation() {

    if( M != NULL )
    {
        for (int i = 0; i < MGrammes; ++i) {
            delete[] M[i];
        }
        delete[] M;
    }
    if( convertedTo1dM != NULL ) {
        delete[] convertedTo1dM;
    }

    if( kernelOfInts != NULL ) {
        delete[] kernelOfInts;
    }

    myfile.close();

}

Interpolation::Interpolation() {

    // ftiaxnw ena keno arxeio gia na grapsw tis synarthseis pou 8a dhmiourghsw kai apo to opoio 8a diavasei o handler
    myfile.open ("generated_functions.txt", std::ofstream::trunc );
    myfile.close();
    //----------------------------------------------------------------------------------------------------------------

    //ftiaxnw kai adiazw ena arxeio sto opoio topo8etw tis synarthseis se morfh anagwnrisimh apo thn gnuplot
    fileForGnu.open("ploting_form.txt" , std::ofstream::trunc );
    fileForGnu.close();
    //------------------------------------------------------------------------------------------------------

    isSecondEquation = 0; // flag pou me voh8aei na grafw sth swsth 8esh se ka8e arxeio

    convertedTo1dM = NULL; // pinakas pou exei 1D eigen morfh anaparastash tou M

    kernelOfInts = NULL; // pinakas pou krataei tis times tou kernel se morfh int gia na ta grapsw meta sto arxeio

    M = NULL; // Pinakas pou exei times opws anaferetai stis diafanies

    line = "";  // metavlhth pou me voh8aei na diaxeirizomai ta output pou exw ston interpolation
    line.clear();

}

/*
 * Desemeuh tou pinaka M
 */
int Interpolation::init_M(int rows, int cols){

    MGrammes = rows; // krataw tis grammes
    MSthles = cols;  // krataw tis sthles

    M = new double*[rows];

    for (int i = 0; i < rows; ++i) {
        M[i] = new double[cols];
    }

    return 0;
}


/*
 * Dhmiourgei ton pinaka M , opws autos anaferetai stis diafanies. O opoios
 * xrhsimopoieitai gia na ypologistoun oi syntelestes tou polywnymou
 *
 * Eisodos:
 *  1: ta shmeia pou edwse o xrhsths
 *  2: to plh8os twn grammwn tou pinaka twn shmeiwn
 *  3: plh8os sthlwn tou pinaka twn shmeiwn
 *  4: to d tou polywnymou pou 8elw na dhmiourghsw
 *
 * returns:
 *  0: an ola phgan kala
 *  1: an to plh8os twn shmeiwn pou dw8hkan einai poly liga gia to antistoixo d
 *  2: an to plh8os twn shmeiwn pou dw8hka einai polla gia to d tou polywnymou
 *  3: an to o pinakas twn shmeiwn einai NULL
 *
 */
int Interpolation::generate_M( double ** givenPoints , int rows , int d ){

    if( givenPoints == NULL )
        return 3;

    kappa = ( ( (d+2)*(d+1) ) / 2 ) - 1; //katallhlos ypologismos tou kappa analoga me to dw8en d

    if( rows < kappa ) // epeidh to plh8os twn grammwn tou points antiproswpeuounto plh8os twn shmeiwn
    {

        cout << " rows = " << rows << " kappa = " << kappa  << endl;

        line.append(" You gave less points than you should\n");
        return 1;
    }
    if( rows > kappa)
    {
        line.append(" You gave more points than you should\n");
        return 2;
    }

    init_M( kappa , kappa+1 ); // desmeuse xwro gia ton pinaka M

    for (int i = 0; i < kappa; ++i) // gia ka8e shmeio
    {

        int x_power = 0; // metavlhth pou krataei th dynamh to x
        int y_power = 0; // metavlhth pou krataei th dynamh tou y
        int orio = 0; // metavlhth pou voh8aei sth topo8ethsh twn katallhlwn timwn sto M

        for (int j = 0; j < kappa+1; ++j) {

            M[i][j] = pow(givenPoints[i][0],x_power) * pow( givenPoints[i][1],y_power ); // M[i][j] = x^a*y^b

            if( y_power < orio ) {

                --x_power;
                ++y_power;


            }
            else{

                ++orio;
                x_power = orio;
                y_power = 0;

            } //  end if (x_power + y_power < d )

        } // end for (int j = 0; j < k+1; ++j)

    } // end for (int i = 0; i < k; ++i)

    convertTo1D();//metatroph se 1D

    return 0;

}

/*
 * Ektypwnei ton pinaka M
 */
int Interpolation :: print(){

    cout << "\n M = \n";
    for (int i = 0; i < MGrammes; ++i) {
        for (int j = 0; j < MSthles; ++j) {
            cout << M[i][j] << " " ;
        }
        cout << endl;
    }

    return 0;

}

/*
 * Metatrepei se 1D to 2D pinaka M pou einai o pinakas M stis diafanies curves.pdf tou ma8hmatos
 * H 1D morfh einai tetoia wste na mporw na th dwsw sthn eigen kai auth na ypologisei to kernel
 */
int Interpolation::convertTo1D(){

    convertedTo1dM = new double[MGrammes * (MSthles)];

    for (int i = 0; i < MGrammes; ++i) {
        for (int j = 0; j < MSthles; ++j) {
            if( j < MGrammes ) {
                convertedTo1dM[i * MGrammes + j] = M[j][i];
            }
            else {
                for (int k = 0; k < MGrammes; ++k) {
                    convertedTo1dM[ MGrammes * MGrammes + k] = M[k][MSthles-1];
                }
                break;
            }
        }
    }

    return 0;

}

/*
 * Synarthsh pou ypologizei to rank opws anaferetai sth 8ewria
 * returns:
 *  1: kappa == rank
 *  2: kappa > rank
 *  0: kappa-1 == rank
 */
int Interpolation::calc_rank(){

    Map< MatrixXd > m(convertedTo1dM,MGrammes,MSthles);

    JacobiSVD< MatrixXd > svd(m , Eigen::ComputeFullU );

    JacobiSVD< MatrixXd > :: SingularValuesType singular;

    singular = svd.singularValues(); // krataw ta singular values

    int rank = 0;

    for (int i = 0; i < singular.rows(); ++i) {

        if( singular(i) > 1e-7 )
            rank++;

    }

    if( kappa+1 == rank ) // to kappa einai hdh -1
        return 1;
    else if ( rank < kappa )
        return 2;
    else // rank == kappa - 1
        return 0;
}

/*
 * Ypologizei ton kernel tou pinaka M, o opoios kernel einai oi syntelestes
 * tou polywnymou gia ta shmeia pou do8hkan
 */
int Interpolation :: calc_Kernel(){

    Map< MatrixXd > m(convertedTo1dM,MGrammes,MSthles);

    kernel = m.fullPivLu().kernel();

    return 0;

}

/*
 * Synarthsh pou metatrepei tous double se int opws eipame sth 8ewria
 */
int Interpolation::DoubleToInt(){

    double max = kernel.maxCoeff();

    double min = kernel.minCoeff();

    if( abs(max) < abs(min) )
        max = abs(min);
    else
        max = abs(max);

    double p = 8 - log10(max);

    int power = pow(10,p); // ypologizw to 10^p

    kernelOfInts = new int[kernel.rows()];

    for (int i = 0; i < kernel.rows(); ++i) {
        kernelOfInts[i] = (int)(kernel(i)*power); // pollaplasiazontai oloi oi oroi me 10^p
    }

    return 0;

}

/*
 * Grafei tis synarthseis me tous syntelestes pou ypologisa se 2 arxeia.
 * 1 gia na mporei na diavasei h solve tou handler , to generated_functions.txt
 * kai to ploting_form.txt gia na mporei na to xeiristei h gnuplot
 */
int Interpolation::WriteToFile() {

    //ftiaxnoume tyxaia polywnyma kai ta topothetoume se arxeio

    myfile.open ("generated_functions.txt", std::ofstream::in | std::ofstream::app );
    fileForGnu.open ("ploting_form.txt", std::ofstream::in | std::ofstream::app );

    if( isSecondEquation == 0 )
        fileForGnu << "f(x,y)= ";
    else
        fileForGnu << "g(x,y)= ";

    char buffer[300];
    int syntelesths, plh8osOrwn;

    char metavlhth;

    plh8osOrwn = kappa;            //paragwgh wrwn gia kathe polyonymo

    //eisagwgh syntelesth

    // grafw se ena arxeio pou 8a diavasei h gnuplot gia na kanei to grafhma
    snprintf(buffer, sizeof(buffer), "%f", kernel(0));

    //allazw ta kommata se teleies gia na mporei na doulepsei h plot
    int pos = 0;
    while( buffer[pos] != ',' )
        ++pos;
    buffer[pos] = '.';
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    myfile << buffer;

    fileForGnu << buffer;
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    //---------------------

    int orio = 1;

    int x_power = 1, y_power = 0;

    for (int i = 0; i < plh8osOrwn; ++i) {

        //eisagwgei syntelesth
        snprintf(buffer, sizeof(buffer), "%f", kernel(i+1));

        if (kernel(i+1) >= 0)
        {
            myfile << '+';
            fileForGnu << '+';
        }

        snprintf(buffer, sizeof(buffer), "%f", kernel(i+1));

        //allazw ta kommata se teleies gia na mporei an doulepsei h plot
        int pos = 0;
        while( buffer[pos] != ',' )
            ++pos;
        buffer[pos] = '.';
        //--------------------------------------------------------------

        myfile << buffer;

        fileForGnu << buffer;
        //------------------

        myfile << "*";                                    //vale ton pol/smo
        fileForGnu << '*';

        //eisagwgh metavlhths
        metavlhth = 'x';                //vale thn metavlhth

        myfile << metavlhth;
        fileForGnu << metavlhth;
        //-------------------

        myfile << "^";                                    //meta thn dynamh
        fileForGnu << "**";

        //eisagwgh dynamhs
        syntelesths = x_power;                //vale thn dynamh

        snprintf(buffer, sizeof(buffer), "%d", syntelesths);

        myfile << buffer;
        fileForGnu << buffer;
        //--------------------

        myfile << '*';
        fileForGnu << '*';

        //eisagwgh 2hs metavlhths
        myfile << "y";
        fileForGnu << 'y';
        //-------------------

        myfile << "^";
        fileForGnu << "**";

        //eisagwgh dynamhs
        syntelesths = y_power;

        snprintf(buffer, sizeof(buffer), "%d", syntelesths);

        myfile << buffer;

        fileForGnu << buffer;

        //--------------------

        if (y_power == orio) {

            ++orio;
            x_power = orio;
            y_power = 0;

        }
        else {

            --x_power;
            ++y_power;

        }

    }

    if(isSecondEquation == 1){

        fileForGnu << "\nset contour base \n"
                      "set cntrparam levels discrete 0.0 \n"
                      "unset surface \n"
                      "set table 'curve.dat' \n"
                      "splot f(x,y) \n"
                      "replot g(x,y) \n"
                      "unset table \n"
                      "set yrange[-30:30] \n"
                      "set xrange[-3:3] \n"
                      "plot 'curve.dat' w l \n";
    }

    myfile << '\n';
    fileForGnu << '\n';

    myfile.close();
    fileForGnu.close();

    isSecondEquation = 1;

    return 0;

}
