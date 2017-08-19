//
// Created by henry on 18/10/2015.

#include "Sylvester.h"

using namespace std;

using Eigen::PartialPivLU;
using Eigen::MatrixXd;
using Eigen::Map;


template < typename T >
Sylvester<T>::Sylvester(){

    calculatedSylvester = NULL;
    convertedCalculatedSylvester = NULL;
}

template < typename T >
Sylvester<T>::~Sylvester(){

    for (int i = 0; i < this->grammes; ++i) {

        delete[] this->table[i];

        if( calculatedSylvester != NULL )
            delete[] calculatedSylvester[i];
    }

    if( calculatedSylvester != NULL )
        delete[] calculatedSylvester;

    if( convertedCalculatedSylvester != NULL )
        delete[] convertedCalculatedSylvester;

//    delete[] this->table;
}

template < typename T >
int Sylvester<T>::calcArrayOfSylvester(int y0,int i , int j) {

    double sum=0;

    if( this->table[i][j] == NULL ) // To NULL antiprosopeuei to 0
        return 0; // gyrnaei to a8roisma tou pinaka tou sylvester

    if ( i < m2grammes - 1 ) { // gia ta stoixeia tou m1

        for (int k = 0; k < m1sthles; ++k) { // gia ka8e sthlh tou m1

            sum += this->table[i][j][k] * pow(y0,k); // to sum einai to stoixeio sth 8esh [j][k] tou m1 * y^k

        }
    }
    else { // gia ta stoixeia tou m2

        for (int k = 0; k < m2sthles; ++k) {

            sum += this->table[i][j][k] * pow(y0,k);

        }
    }

    return sum;

}
/*
 * Paragwgh tou pinaka calculatedSylvester pou einai o Sylvester ypologismenos se mia timh y0
 */
template < typename T >
int Sylvester<T>::calcSylvesterForRandomValue(int y0) {

    calculatedSylvester = new double * [this->grammes];

    for (int i = 0; i < this->grammes; ++i) {
        calculatedSylvester[i] = new double[this->sthles];
    }

    for (int i = 0; i < this->grammes; ++i) {
        for (int j = 0; j < this->sthles; ++j) {
           calculatedSylvester[i][j] = calcArrayOfSylvester(y0,i,j);
        }
    }

    return 0;

}

/*
 * Paragei to pinaka convertedCalculatedSylvester , pou einai o calculatedSylvester se morfh COL_MAJOR 1D thn
 * opoia anagnwrizei h eigen
 */
template < typename T >
int Sylvester<T>::make1D() {

    convertedCalculatedSylvester = new double[this->grammes*this->sthles];

    for (int i = 0; i < this->grammes; ++i) {
        for (int j = 0; j < this->sthles; ++j) {
            convertedCalculatedSylvester[i*this->grammes+j] = calculatedSylvester[j][i];
        }
    }

    return 0;

}

/*
 *ypologismos orizousas
 * 0 : o sylvester DEN einai tautotika 0
 * 1 : o sylvester einai tautotika 0
 */
template < typename T >
int Sylvester<T>::calcDet() {

    int y0GiaTaOpoiaDetMhdenizetai[3] = { -1,-1,-1 }; // pinakas pou krataei tis times gia tis opoies mhdenizetai o sylvester

    srand (time(NULL)); // arxikopoiw gia na paragw tyxaies times

    for (int i = 0; i < 3; ++i) {

        int y0 = rand() % 40; // pernw mia timh apo 0 mexri 40

        y0 -= 20; // kai thn kanw sto pedio -20 mexri 20

        for (int j = 0; j < 3; ++j) {
            if ( y0 == y0GiaTaOpoiaDetMhdenizetai[j] ) // ean exw ksanatsekarei auto to y apla tou allazw timh, giati den exei nohma na to ksanatsekarw
                y0++;
        }

        calcSylvesterForRandomValue(y0); // ypologizw ton sylvester gia th tyxai timh tou y

        make1D(); // ton kanw 1D gia na mporw na ftiaksw to map ths eigen pou exei etoimh synarthsh ypologismou ths det

        Map<MatrixXd> sylv(convertedCalculatedSylvester, this->grammes, this->sthles);

        if( sylv.determinant() != 0 ) // vrhka orizousa <> 0 opote o sylvester den einai tautotika 0 kai epistrefw
            return 0;
        else //diaforetika krataw to ypologismeno y kai paw sthn epomenh epanalhpsh
            y0GiaTaOpoiaDetMhdenizetai[i] = y0;

    }

    return 1 ; // h orizousa vghke kai tis 3 fores mhden
}


/*
    Sto kommati ayto tha prepei kanonika na prokypsei enas pinakas megethous (sylvester_grammes,1) alla
    o sxediasmos exei ginei ws enas pinakas (sylvester_grammes,maxSthles) me tis maxSthles na antiprosopeyoun
    thn dynamh ths krymenhs metavlhths kai oi grammes tou pinaka ena athroisma apo dianysmata polyonymwn sthn
    krymmenh metavlhth
 */
template < typename T >
int ** Sylvester <T> :: multiply(Matrix<double> & v){

    int sylv_grammes = this->get_grammes();						//grammes sylvester
    int maxSthles;
    if(m1sthles>m2sthles)
        maxSthles=m1sthles;
    else
        maxSthles=m2sthles;										//maxsthles=sthles tou S*v

    resultGrammes = sylv_grammes;
    resultSthles = maxSthles;

    int ** Sv = new int*[sylv_grammes];
    for (int i = 0; i < sylv_grammes; ++i)						//desmeyoume xwro gia to Sv
    {
        Sv[i]=new int[maxSthles];
        for (int j = 0; j < maxSthles; ++j)
        {
            Sv[i][j]=0;											//arxikopoihsh me 0
        }
    }
    for ( int x = 0; x < m2grammes-1; ++x)
    {
        for ( int m = 0; m < m1sthles; ++m)
        {
            for (int j = 0; j < sylv_grammes; ++j)
            {
                if(this->table[x][j]!=NULL)
                {
                    Sv[x][m]+=this->table[x][j][m] * v.get_int_element(j,0);		//pollaplasiasmos pinakawn
                }                               
            }
        
        }
    }
    for (int i = m2grammes-1; i <sylv_grammes ; ++i)
    {
        for (int n = 0; n < m2sthles; ++n)
        {
            for (int j = 0; j < sylv_grammes; ++j)
            {
                if(this->table[i][j]!=NULL)
                {
                    Sv[i][n]+=this->table[i][j][n] * v.get_int_element(j,0);       //pollaplasiasmos pinakawn
                }                               
            }          
        }
    }
    return Sv;											//enas pinakas [sylv_grammes][maxSthles]
}


template < typename T >
void Sylvester <T> :: make_Sylvester( Matrix<double> &m1, Matrix<double> & m2 ) {

    m1grammes = m1.get_grammes();
    m2grammes = m2.get_grammes();
    m1sthles = m1.get_sthles();
    m2sthles = m2.get_sthles();

    /*
     * 1o orisma = pyknh anaparastash ths ekshswshs pou 8elw na apo8hkeusw
     * 2o orisma= grammh sthn opoia ksekina na topo8etountai oi syntelestes ths ktymenh metavlhts
     * 3o orisma = grammes tou m1
     */
    fill_first_row_of_sylvester(m1, 0, m1grammes );

    shift_rest_first_half(); // gemisei mexri th grammh d1-1

    //------------- 2h eksiswsh ------------------

    fill_first_row_of_sylvester(m2, m2grammes-1 , m2grammes ); // grafw sth grammh d1 mexri th sthlh d1+1->gia akeraious

    shift_rest_second_half();

    //------------------------------------

}

/*
	 * 1o orisma = pyknh anaparastash ths ekshswshs pou 8elw na apo8hkeusw
	 * 2o orisma= grammh sthn opoia ksekina na topo8etountai oi eksiswseis me th ktymenh metavlhts
	 * 3o orisma = grammes tou m1
*/
template <typename T>
void Sylvester<T>::fill_first_row_of_sylvester(Matrix<double> &m1, int first_row_pos, int dimension) {

    /*
     * to dimension0 mou leei oti diavazw mexri th grammh dimensio0 tou pinaka syntelestwn m1
     * kai apo8hkeuw mexri th sthlh dimesnison0 -1  tou sylvester
    */

    int j = 0;
    for (j = 0; j < dimension ; j++ )
    {
        this->table[first_row_pos][j] = m1.get_table_row(dimension-j-1);
    }
    for (int i = dimension ; i < this->sthles; ++i) {
        this->table[first_row_pos][i] = NULL;
    }

}

/*
*shift silvester
*/
template <typename T>
void Sylvester<T>::shift_rest_first_half() {

    for( int i  = 1 ; i < m2grammes-1  ; i++  ) {

        this->table[i][0] = NULL;										//prwth sthlh ths i grammh deixnei se NULL

        int j=1;
        while(j < this->sthles)
        {
            this->table[i][j]=this->table[i-1][j-1];					//shift kata mia thesi deksia
            j++;
        }
    }

}

template <typename T>
void Sylvester<T>::shift_rest_second_half() {

    for( int i  = m2grammes ; i < this->grammes  ; i++  ) {

        this->table[i][0] = NULL;									//prwth sthlh ths i grammh deixnei se NULL

        int j=1;
        while( j < this->sthles)
        {
            this->table[i][j]=this->table[i-1][j-1];				//shift kata mia thesi deksia
            j++;
        }
    }

}

template <typename T>
void Sylvester<T>::print_Table(){

    cout << "Sylvester needs a variable in order to print\n";

}

//Ektypwsh pinaka sylvester
template <typename T>
void Sylvester<T>::print_Table(char variable ) {

    for( int i = 0 ; i < this->grammes ; i++ )
    {
        for ( int j  = 0  ; j < this->sthles ; j ++)
        {
            if ( this->table[i][j] == NULL)
                cout << "0 ";
            else
            {
                cout << "( " << this->table[i][j][0] << " ";
                if( i < m2grammes-1 )
                {
                    for (int k = 1; k < m1sthles; ++k)
                    {
                        if( this->table[i][j][k] == 0) {
                            continue;
                        }

                        if (this->table[i][j][k] > 0)
                            cout << "+ " << this->table[i][j][k] << variable<< "^" << k << " ";
                        else
                            cout << this->table[i][j][k] <<variable << "^" << k << " ";

                    }
                }
                else
                {
                    for (int k = 1; k < m2sthles; ++k)
                    {
                        if( this->table[i][j][k] == 0) {
                            continue;
                        }

                        if (this->table[i][j][k] > 0 )
                            cout << "+" << this->table[i][j][k] << variable <<"^" << k << " ";
                        else
                            cout << this->table[i][j][k] << variable << "^" << k << " ";

                    }
                }

                cout << ") ";
            }
        }
        cout << endl;
    }
}

/*+++++++++++++++++++++++++++*/
template <typename T>
void Sylvester<T>::print_Table_bonus(int ** Sv){
	
	int maxSthles;
	
	cout << "[Sylvester * v] =="<< '\n';
	if(m1sthles>m2sthles)
		maxSthles=m1sthles;
	else
		maxSthles=m2sthles;

	for (int i = 0; i < this->grammes; ++i)
	{
		for (int j = 0; j < maxSthles; ++j)
		{
			cout << Sv[i][j]<< " ";
		}
		cout << '\n';
	}

}
