#include "Pinakas_syntelestwn.hpp"

using namespace std;

using Eigen::MatrixXd;

template <typename T>
Pinakas_syntelestwn<T>::Pinakas_syntelestwn(){

    this->table = NULL;

}

template <typename T>
Pinakas_syntelestwn<T>::~Pinakas_syntelestwn(){

    if( this->table != NULL ) {
        for (int i = 0; i < this->grammes; ++i) {
            delete[] this->table[i];
        }
        delete[] this->table;
    }

}

template <typename T>
int Pinakas_syntelestwn<T>::print_to_string(string & line)
{
    line = "";
    line.clear();
    for( int i = 0; i < this->grammes ; i++ )
    {
        for ( int  j = 0; j < this->sthles ; j++ )
        {
            line.append(this->table[i][j]);
            line.append(" ") ;
        }
        line.append("\n");
    }

    return 0;

}

template <typename T>
int Pinakas_syntelestwn<T>::calcWithXAndY(double x, double y){

    double sum=0;

    for (int i = 0; i < this->grammes; ++i) {

        for (int j = 0; j < this->sthles; ++j) {
            sum += this->table[i][j] * pow( y , j) * pow( x , i);
        }

    }

    if( sum <= 1e-5 && sum >= -1e-5 ) { // ean h timh einai konta sto 0
        return 0;
    }

    return 1;

}

/*
 * Antikatastash tou y sto pinaka kai apo8hkeush tou apotelesmatos ston pinaka f
 * ston opoio ka8e grammh antiprosopuei th dynamh tou x kai ka8e stoixeio to syntelesth tou x
 */
template < typename T >
int Pinakas_syntelestwn<T>::replaceHiddenVariable( Matrix<double> & f , double y ){

    double sum = 0 ;

    if( y == 0 || y == -0 )
    {
        for (int i = 0; i < this->grammes; ++i) {

            f.insert(this->table[i][0] ,i,0);
        }

        return 0;

    }

    for (int i = 0; i < this->grammes; ++i) {

        sum = 0; //arxikopoihse to sum ka8e grammhs

        for (int j = 0; j < this->sthles; ++j) { //  gia ka8e sthlh pou einai h dynamh tou x


            sum += this->table[i][j] * pow(y,j); // o syntelesth tou x^i einai to a8roisma twn x^i*y^j

        }


        f.insert(sum ,i,0); // vale to apotelesma sto pinaka syntelestwn me 1 agnwsto

    }

    // diairw me megistofa8mio oro opws stis diafianies kanei me to bt

    for (int i = 0; i < this->grammes; ++i) {

        double * a = f.get_element(i,0);
        double * b = f.get_element(this->grammes-1,0);

        f.insert( *a / *b ,i,0);
    }

    return 0;

}

template <typename T>
void Pinakas_syntelestwn<T>::print_Table(){

    for( int i = 0; i < this->grammes ; i++ )
    {
        for ( int  j = 0; j < this->sthles ; j++ )
            cout << this->table[i][j] << " " ;
        cout << endl;
    }

}

/*
 * dhmiourgei mia pyksh anaparastash pinaka vathmosPolywnymou*vathmosPolywnymou
 * me tyxaious syntelestes
 * kai thn apo8hkeuei ston pinaka tou m
 */
template < typename T>
void Pinakas_syntelestwn<T>::create_Polywnymo( int vathmosPolywnymou ) {

    this->allocate_Table( vathmosPolywnymou+1 , vathmosPolywnymou+1 );

    int x , y;
    int c; // pairnei times apo -MAXFACTOR/2 mexri (MAXFACTOR-1) / 2

    for ( x = 0 ; x <= vathmosPolywnymou  ; x ++)
    {
        for ( y = 0 ; y <= vathmosPolywnymou ; y ++)
        {

            c = rand() % MAXFACTOR;

            // sta8eros oros den mporei na exei syntelesth 0
            if ( (x == 0 && y == 0)  )
            {

                while ( c == 0 )
                    c = rand() % MAXFACTOR;

            }

            if ( x + y > vathmosPolywnymou ) // ean eimai panw apo to miso tou pinaka vale mhden
            {
                this->insert(0,x,y);
                continue;
            }

            c = c - MAXFACTOR/2; // ry8mish proshmou

            this->insert(c,x,y);

        }

    }
}




template <typename T>
int Pinakas_syntelestwn<T>::findMultiplicity(MatrixXd & lambda , int i){

    int multiplicity = 1;

    if( abs( lambda(i,2) ) == 0 )
        return -1;

    for (int j = 0 ; j < lambda.rows(); ++j) {

        if (j != i)
            if ( ( lambda(i, 0) - lambda(j, 0) )  < 1e-7 && ( lambda(i, 0) - lambda(j, 0) )  > -1e-7) {

                multiplicity++;

            }
    }

    return multiplicity;

}

template <typename T>
int Pinakas_syntelestwn<T>::calcWith(MatrixXd lambda, MatrixXd V , int k ) {

    long double sum = 0.0;

    int multiplicity;

    multiplicity = findMultiplicity(lambda, k); // vres to multiplicity

    if( multiplicity == -1 )
        return -1;

    if( multiplicity > 1 && lambda(k,1) == 0 ) { // an einai megalytero tou 1 ( to multiplicity )

        return 1;

    }

    //  ean to teleutaio stoixeio tou idiodianysmatos einai 0 , h' exw fantastiko meros sthn idiotimh den kanw tipota
    if( V(V.rows() - 1, k) == 0 ) {
        return 2;
    }

    // alliws ypologizw th timh ths synarthshs se auto to y kai x
    for (int i = 0; i < this->grammes; ++i) {

        for (int j = 0; j < this->sthles; ++j) {

            sum += (double)this->table[i][j] * pow( lambda(k, 0) , j ) * pow( V(V.rows() - 2, k), i );

        }

    }

    if( sum <= 1e-10 && sum >= -1e-10 ) { // ean h timh einai konta sto 0
        return 0;
    }

    return 3;

}

/******************8o erwthma********************************/
/*
 * Ypologizei thn variable ^ power
 * variable = pinakas 2 8esewn me 0-> pragmatiko kai 1-> fantastiko
 */
template <typename T>
int Pinakas_syntelestwn<T>::calcWithImag(double * temp,double * variable,int power){

    double a = variable[0]; // a  = real
    double b = variable[1]; // b = imag
    double realResultSoFar = temp[0];
    double imagResultSoFar = temp[1];

    if( power == 0 )
        return 1 ;
    else if( power==1 ){
        return 0;
    }
    else{ // power > 1

        temp[0] = ( realResultSoFar * a ) -  ( imagResultSoFar * b ); // temp[0] kratatei to realSoFar apotelesma
        temp[1] = realResultSoFar * b + imagResultSoFar * a ;

    }

    --power;

    return calcWithImag(temp,variable,power);

}

template <typename T>
int Pinakas_syntelestwn<T>::imag_roots(double * result,double * y,double * x){

    double sum[2];
    sum[0]=this->table[0][0];       //Real
    sum[1]=0;                       //Imag
    double yYpsomenoSthnJ[2], xYpsomenoSthnI[2], resultSofar[2];

    for (int i = 0; i < this->sthles; ++i)  // epeidh o pinakas einai tetragwnikos
    {
        for (int j = 0; j < this->sthles; ++j)
        {
            if( (i) || (j) ){ // ean to i h' j einai diaforo tou 0 , dhladh den eimai sto sta8ero oro table[0][0]

                xYpsomenoSthnI[0]=x[0], xYpsomenoSthnI[1]=x[1], yYpsomenoSthnJ[0]=y[0], yYpsomenoSthnJ[1]=y[1]; //mhdenizw tous pinakes

                calcWithImag(yYpsomenoSthnJ,y,j);
                calcWithImag(xYpsomenoSthnI,x,i);

                if( j == 0 ){ // ean to y einai sth mhdenikh , to result einai to x
                    resultSofar[0]=xYpsomenoSthnI[0]; // result = x^i*y^0
                    resultSofar[1]=xYpsomenoSthnI[1];
                }
                else if( i == 0 ){ // ean to x einai sth mhdenikh , to result einai to y
                    resultSofar[0]=yYpsomenoSthnJ[0]; // result = y^j*x^0
                    resultSofar[1]=yYpsomenoSthnJ[1];
                }
                else // x kai y einai ypsomena se kapoia dynamh
                {
                    resultSofar[0]= xYpsomenoSthnI[0]* yYpsomenoSthnJ[0]-(yYpsomenoSthnJ[1]* xYpsomenoSthnI[1]); // real = a^2 - b^2
                    resultSofar[1]= xYpsomenoSthnI[1]* yYpsomenoSthnJ[0]+ yYpsomenoSthnJ[1]* xYpsomenoSthnI[0]; // imag = 2ab
                }

                sum[0] += resultSofar[0] * this->table[i][j]; // realOfSum += result.real * syntelesth
                sum[1] += resultSofar[1] * this->table[i][j]; // imaginaryOfSum += result.imaginary * syntelesth

            } // end if( (i) || (j) )
        }
    }

    result[0]=sum[0];
    result[1]=sum[1];

    return 0;

}

//************************8o erwthma********************************************//
template <typename T>
int Pinakas_syntelestwn<T>::calc_roots_with_imagine( double * y,double * x){

    double res[2];

    imag_roots(res , y , x);

    if( res[0] < 1e-5 && res[0] > -1e-5 && res[1] < 1e-5 && res[1] > -1e-5 ) // exw riza
        return 0;

    return 1;
}
