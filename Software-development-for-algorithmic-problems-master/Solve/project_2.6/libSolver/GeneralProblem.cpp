#include "GeneralProblem.h"

using Eigen::MatrixXd;
using Eigen::Map;

using std::cout;
using std::endl;

GeneralProblem::GeneralProblem(){

    convertedL0 = NULL;
    convertedL1 = NULL;
    L0 = NULL;
    L1 = NULL;

}

GeneralProblem::~GeneralProblem(){

    if( convertedL0 != NULL )
        delete[] convertedL0;
    if( convertedL1 != NULL )
        delete[] convertedL1;

    if( L0 != NULL ) {
        for (int i = 0; i < L0L1grammes; ++i) {
            delete[] L0[i];
        }
        delete[] L0;
    }

    if( L1 != NULL ) {
        for (int i = 0; i < L0L1grammes; ++i) {
            delete[] L1[i];
        }
        delete[] L1;
    }

}

/*
 * Metatroph L0 L1 se monodiastatous pinakes
 */
int GeneralProblem::convertL0L1(){

    convertedL0 = new double[L0L1grammes*L0L1grammes];
    convertedL1 = new double[L0L1grammes*L0L1grammes];

    for (int i = 0; i < L0L1grammes ; ++i) {
        for (int j = 0; j < L0L1grammes; ++j) {
            convertedL0[i*L0L1grammes+j] = L0[j][i];
            convertedL1[i*L0L1grammes+j] = L1[j][i];
        }
    }

    return 0;

}

MatrixXd GeneralProblem::getLambda() {
    return lambda;
}

MatrixXd GeneralProblem::getV() {
    return V;
}

/*
 * an d=1 exw thn prwth periptwsh alliws paw sthn allh
 */
int GeneralProblem::solveWithGeneralProblem(int vathmosKrymenhsMetavlhthts , double ** listOfMd , int rows ){

    grammes = rows;

    if( vathmosKrymenhsMetavlhthts == 1 )
        makeCaseGeneralProblem1(listOfMd[0],listOfMd[1]);
    else{ // d >=2
        makeCaseGeneralProblemD(vathmosKrymenhsMetavlhthts,listOfMd );
    }

    return 0;
}
/*
 *desmeyw xwro gia ta L0L1
 */
int GeneralProblem::allocateL0L1(int grammes1 , int sthles){

    L0L1grammes = grammes1;

    L0 = new double*[L0L1grammes];
    L1 = new double*[L0L1grammes];

    for (int i = 0; i < sthles; ++i) {
        L0[i] = new double[sthles];
        L1[i] = new double[sthles];
    }

    if(( L0 == NULL ) || (L1 == NULL))
        return 1;

    return 0;

}
/*
 * ftiaxnw thn 1h grammh tou L0
 */
int GeneralProblem::generateFirstRowOfL0(){

    for (int i = 0; i < L0L1grammes; ++i)  //gia ka8e sthlh
        L0[0][i] = 0;

    L0[0][grammes] = -1;

    return 0;

}

/*
 * ftiaxnw thn 1h grammh tou L1
 */
int GeneralProblem::generateFirstRowOfL1(){

    for (int i = 1; i < L0L1grammes; ++i)  //gia ka8e sthlh
        L1[0][i] = 0;

    L1[0][0] = 1;

    return 0;

}

/*
 * kanw shift mia thsi deksia tis epomenes grammes
 */
int GeneralProblem::generateRestL0L1(){

    for (int i = 1; i < L0L1grammes-grammes ; ++i) {
        L0[i][0] = 0;
        L1[i][0] = 0;
        for (int j = 1; j < L0L1grammes; ++j) {
            L0[i][j] = L0[i-1][j-1];
            L1[i][j] = L1[i-1][j-1];
        }
    }
    return 0;

}
/*
 * ftiaxnw thn teleytaia grammh tou L0
 */
int GeneralProblem::generateLastBlockOfL0(int vathmosKrymenhsMetavlhthts, double ** list){

    int offset = 0;

    for (int i = 0; i < vathmosKrymenhsMetavlhthts  ; ++i) {

        Map<MatrixXd> m(list[i],grammes,grammes);

        for (int j = L0L1grammes-grammes ; j < L0L1grammes; ++j) {

            for (int k = 0; k < grammes; ++k) {

                L0[j][offset+k] = m(j-L0L1grammes+grammes,k);

            }

        }

        offset += grammes;

    }
    return 0;
}


/*
 * ftiaxnw thn teleytaia grammh tou L1
 */
int GeneralProblem::generateLastBlockOfL1(int vathmosKrymenhsMetavlhthts, double ** list){

    Map<MatrixXd> m(list[vathmosKrymenhsMetavlhthts],grammes,grammes);

    for (int j = L0L1grammes-grammes ; j < L0L1grammes; ++j) {

        for (int k = 0; k < L0L1grammes- grammes; ++k)
            L1[j][k]=0;

        for (int i = L0L1grammes- grammes; i < L0L1grammes; ++i)
        	L1[j][i] = m(j-L0L1grammes+grammes,i-L0L1grammes+grammes);

    }
    return 0;
}

int GeneralProblem::calcEigenvectorsAndEigenValues() {

    Map<MatrixXd> a(convertedL0,L0L1grammes,L0L1grammes);
    Map<MatrixXd> b(convertedL1,L0L1grammes,L0L1grammes);

    MatrixXd m0(L0L1grammes,L0L1grammes);
    MatrixXd m1(L0L1grammes,L0L1grammes);

    m0 = a; m1 = (-1) * b;

    GEP(m0,m1,V,lambda);

    calcX(lambda,V);

    return 0;

}

int GeneralProblem::print_table( double ** table)
{

    for (int i = 0; i < L0L1grammes; ++i) {

        for (int j = 0; j < L0L1grammes; ++j) {

            cout << table[i][j] << " ";

        }

        cout << endl;

    }

    return 0;

}

/*
 * lynoume to problhma gia d>1
 */
int GeneralProblem::makeCaseGeneralProblemD(int vathmosKrymenhsMetavlhthts, double ** list) {

    if ( allocateL0L1(vathmosKrymenhsMetavlhthts * grammes, vathmosKrymenhsMetavlhthts * grammes) == 1 )
        return 1;

    generateFirstRowOfL0();

    generateFirstRowOfL1();

    generateRestL0L1();

    generateLastBlockOfL0(vathmosKrymenhsMetavlhthts, list);

    generateLastBlockOfL1(vathmosKrymenhsMetavlhthts, list);

    convertL0L1();

    calcEigenvectorsAndEigenValues();

    return 0;

}
/*
 metatrepoume tis idiotimes-idiodianismata sthn swsth morfh
 */
int GeneralProblem::calcX( MatrixXd & lambda , MatrixXd & V ){

    // fernw to v sth morfh pou exei 1 sto telos
    for (int k = 0; k < V.rows(); ++k)
        for (int j = 0; j < V.cols(); ++j) {

            if(  V(V.rows() - 1 , j ) != 0 )
                V(k,j) = V(k,j) / V( V.rows() - 1 , j);//diairoume to telaiytaio stoixeio tou V me to prwteleytaio

        }
    //-------------------------------------------

    for (int i = 0; i < lambda.rows() ; ++i) {

        lambda(i,0) = lambda(i,0) / lambda(i,2);//diairesh pragmatikou me paronomasth
        lambda(i,1) = lambda(i,1) / lambda(i,2);//diairesh fantastikou me paronomasth

    }

    return 0;

}

/*
 *linoume to provlhma gia d==1
 */
int GeneralProblem::makeCaseGeneralProblem1( double * M0 , double * M1 ) {

    Map<MatrixXd> a(M0,grammes,grammes);
    Map<MatrixXd> b(M1,grammes,grammes);

    MatrixXd m0(grammes,grammes);
    MatrixXd m1(grammes,grammes);

    m0 = a; m1 = (-1) * b;

    GEP(m0,m1,V,lambda);

    calcX(lambda,V);

    return 0;

}

/*
 * Mas epistrefei ta lambda kai V
 */
bool GeneralProblem:: GEP(MatrixXd & A,MatrixXd & B,MatrixXd & V,MatrixXd & lambda){

    int N = A.cols();

    if( B.cols() != N ||  A.rows() != N ||  B.rows() != N ){

        return false;

    }

    V.resize(N,N);
    lambda.resize(N,3);

    int LDA = A.outerStride();
    int LDB = B.outerStride();
    int LDV = V.outerStride();
    int INFO = 0;

    double * alphar = lambda.col(0).data();
    double * alphai = lambda.col(1).data();
    double * beta = lambda.col(2).data();

    INFO = LAPACKE_dggev(LAPACK_COL_MAJOR, 'N' , 'V' , N , A.data() , LDA , B.data() , LDB , alphar ,
                         alphai, beta , 0 ,LDV ,V.data() , LDV );

    return INFO == 0;

}


