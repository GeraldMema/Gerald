//
// Created by henry on 11/11/2015.
//

#include "Companion.h"

using Eigen::EigenSolver;
using Eigen::Map;

using std::cout;
using std::endl;

int Companion::print(){

    cout << " Companion : \n";
    for (int i = 0; i < Cgrammes; ++i) {
        for (int j = 0; j < Cgrammes; ++j) {
            cout << C[i][j] << ' ';
        }
        cout << endl;
    }

    return 0;

}

int Companion::generateMultiplicityCompanion( Matrix<double> &f ){

    allocateC( f.get_grammes() - 1 , f.get_grammes() - 1 ); // to mege8os tou pinaka einai t-1

    generateFirstRowOfMultiplicityCompanion();

    shift();

    generateLastRowOfMultiplicityCompanion(f);

    return 0;

}

int Companion::generateLastRowOfMultiplicityCompanion( Matrix<double> & f ){

    for (int i = 0; i < Cgrammes; ++i) {

        double * a = f.get_element(i,0);

        C[Cgrammes-1][i] = *a *(-1);
    }

    return 0;

}

int Companion::shift(){

    for (int i = 1; i < Cgrammes-1 ; ++i) {
        C[i][0] = 0;
        for (int j = 1; j < Cgrammes; ++j) {
            C[i][j] = C[i-1][j-1];
        }
    }
    return 0;

}

int Companion:: generateFirstRowOfMultiplicityCompanion(){

    for (int i = 0; i < Cgrammes; ++i) {
        C[0][i] = 0;
    }

    C[0][1] = 1;

    return 0;

}


/*
 * Gyrnaei to pinaka pou dhmhourgeite sth klass kai exei tis times tou y
 */
Eigen::MatrixXd Companion::getLambda() {
    return lambda;
}

/*
 * Gyrnaei to pinaka pou dhmhourgeite sth klass kai exei tis times ta idiodianysmata
 */
Eigen::MatrixXd Companion::getV() {
    return V;
}

/*
 * Metatrepei ton 2D table se 1D
 */
int Companion::convertC(){

    convertedC = new double[Cgrammes*Cgrammes];

    for (int i = 0; i < Cgrammes ; ++i) {
        for (int j = 0; j < Cgrammes; ++j) {
            convertedC[i*Cgrammes+j] = C[j][i];
        }
    }

    return 0;

}

/*
 * Apofasizei me krhthrio ton vathmosKrymenhsMetavlhthts pws na xthsei ton companion
 * To listOfMd einai ousiastika enas pinakas pou exei mesa deiktes se pinakes M[i] pou exoun morfh 1D gia na
 * mporesw na tous doulepsw stis synarthseis ths eigen kai exoun tis times twn M[i] column_major
 * To rows to xreiazomai parakatw kai apla to krataw
 */
int Companion::solveWithInvert(int vathmosKrymenhsMetavlhthts , double ** listOfMd , int rows ){

    grammes = rows;

    if( vathmosKrymenhsMetavlhthts == 1 ) // ean eimai sth periptwsh d == 1
        return makeCaseInvertable1(listOfMd[0],listOfMd[1]);
    else{ // d >=2
        return makeCaseInvertableD(vathmosKrymenhsMetavlhthts,listOfMd );
    }

    return 0;
}

/*
 *desmeyw xwro gia to C
 */
int Companion::allocateC(int grammes1 , int sthles){

    Cgrammes = grammes1;

    C = new double*[grammes1];

    for (int i = 0; i < sthles; ++i) {
        C[i] = new double[sthles];
    }

    if( C == NULL )
        return 1;

    return 0;

}
/*
 * h prwth grammh tou C
 */
int Companion::generateFirstRowOfCompanion(){

    for (int i = 0; i < Cgrammes; ++i)  //gia ka8e sthlh
        C[0][i] = 0;

    C[0][grammes] = 1;

    return 0;

}
/*
 * Me vash thn 1h grammh kanw ts ypoloipes shift mia thesi deksia
 */
int Companion::generateRestCompanion(){

    for (int i = 1; i < Cgrammes-grammes ; ++i) {
        C[i][0] = 0;
        for (int j = 1; j < Cgrammes; ++j) {
            C[i][j] = C[i-1][j-1];
        }
    }
    return 0;

}

/*
 * Ftiaxnei tis teleutaies m grammes tou Companion gia d > 1 opws dinetai sth 8ewria.
 */
int Companion::generateLastBlockOfCompanion(int vathmosKrymenhsMetavlhthts, double ** list){

    Map<Eigen::MatrixXd> md(list[vathmosKrymenhsMetavlhthts],grammes,grammes); // Kanw to Md se typo MatrixXd giati voleuei

    Map<Eigen::MatrixXd> temp(list[0],grammes,grammes);

    md = md.inverse() * -1; // antistrofo kai epi -1

    int offset = 0; // xrhsimopoihtai gia na gemhzw block tou Companion ka8e fora

    for (int i = 0; i < vathmosKrymenhsMetavlhthts  ; ++i) { // gia ka8e ena pinaka mexri d-1

        Map<Eigen::MatrixXd> m(list[i],grammes,grammes);

        temp = md * m; // temp = auto pou 8elw na valw sto block tou Companion

        for (int j = Cgrammes-grammes ; j < Cgrammes; ++j) { // j antiprosopeuei th grammh tou teleytaiou block

            for (int k = 0; k < grammes; ++k) { // to grammes antiprosopeuei to m , m = symbolo pou xrhsimopoieitai stis diafanies

                C[j][offset+k] = temp(j-Cgrammes+grammes,k);

            }

        }

        offset += grammes;

    }

    return 0;

}

/*
 * H synarthsh pou xrhsimopoiei ton solver
 */
int Companion::calcEigenvectorsAndEigenValues() {

    Map<Eigen::MatrixXd> m(convertedC,Cgrammes,Cgrammes);

    EigenSolver<Eigen::MatrixXd> es(m);

    calcX( es );

    return 0;

}

/*
 * Ftiaxnw ton Companion opws leei h 8ewria kai
 * lynw to provlhma gia th periptwsh pou d >= 2
 */
int Companion::makeCaseInvertableD(int vathmosKrymenhsMetavlhthts, double ** list){

    if( allocateC(vathmosKrymenhsMetavlhthts*grammes,vathmosKrymenhsMetavlhthts*grammes) == 1 )
        return 1;

    generateFirstRowOfCompanion(); // ftiaxnw th prwth gramm

    generateRestCompanion(); // oi ypoloipes einai h prwth apla exwntas kanei ena shift pros ta deksia

    generateLastBlockOfCompanion(vathmosKrymenhsMetavlhthts,list); // ftiaxnw tis teleutaies m grammes tou Companion

    convertC(); // ton kanw apo 2D se 1D

    calcEigenvectorsAndEigenValues(); // ypologizw kai krataw idiotimes kai idiodianysmata

    return 0;

}

/*
 * Edw krataw apo8hkeuw tis idotime kai ta idiodianysmata
 * kai ta fernw stis katalhles morfes gia na vrw th lysh
 */
int Companion::calcX( EigenSolver<Eigen::MatrixXd> & es ){

    EigenSolver<Eigen::MatrixXd>::EigenvalueType eigenvalues = es.eigenvalues();
    EigenSolver<Eigen::MatrixXd>::EigenvectorsType eigenvectors = es.eigenvectors();

    lambda.resize(eigenvalues.rows(),3);
    V.resize(eigenvectors.rows() , eigenvectors.cols());

    // diairw ta eigevalues me to teleutaio stoixeio gia na er8w se morfh na exw 1 sto telos
    for (int k = 0; k < eigenvectors.rows(); ++k)
        for (int j = 0; j < eigenvectors.cols(); ++j) {
            if(  eigenvectors(eigenvectors.rows() - 1 , j ).real() ) // an einai mhdne den mpainei giati h syn8hkh einai pseudhs
                eigenvectors(k,j).real() = eigenvectors(k,j).real() / eigenvectors(eigenvectors.rows() - 1 , j).real();
        }
    //-----------------------------------------------------------------------------------------

    // ana8etw tis times tou lambda kai tou V
    for (int i = 0; i < eigenvalues.rows(); ++i) {
            lambda(i, 0) = eigenvalues(i).real();
            lambda(i,1) = eigenvalues(i).imag();
            for (int j = 0; j < eigenvectors.cols(); ++j) {
                V(i, j) = eigenvectors(i, j).real();
            }
    }
    //------------------------------------

    return 0;

}

/*
 * Lynw to provlhma gia d = 1
 * Ta M0 kai M1 exoun th morfh pou 8elei h eigen
 */
int Companion::makeCaseInvertable1( double * M0 , double * M1 ) {

    Map<Eigen::MatrixXd> m0(M0,grammes,grammes);
    Map<Eigen::MatrixXd> m1(M1,grammes,grammes);

    m1 = m1.inverse() * (-1); // to kanw sth morfh -M1^(-1)

    m0 = m1 * m0; //  to m0 ginetai to apotelesma

    EigenSolver<Eigen::MatrixXd> es(m0);

    return calcX( es );

}

