//
// Created by henry on 13/10/2015.
//

#include "Matrix.h"

using namespace std;


/*
 * Desmeush mnhmhs gia ton pinaka
 */
template <typename T>
void Matrix<T> :: allocate_Table(int plh8osGrammes , int plh8osSthles ) {

	table = new T * [plh8osGrammes];

    for ( int i = 0 ; i < plh8osGrammes ; i ++)
        table[i] = new T[plh8osSthles];
	
	grammes = plh8osGrammes;
	sthles = plh8osSthles;
	
}

template <typename T>
void Matrix<T> :: print_Table()
{
	for (int i = 0; i < grammes; ++i) {
		for (int j = 0; j < sthles; ++j) {
			cout << table[i][j] << ' ';
		}
		cout << endl;
	}
	
}

/*
 * topo8etei sth 8esh i,j tou pinaka to item
 */
template <typename T>
void Matrix<T> :: insert( T item ,int  i ,int j ) {

	this->table[i][j] = item;			//eisagwgh stoixeiou item ston pinaka table sthn grammh i kai sthlh j

}

template <typename T>
Matrix<T>::~Matrix() {

}
/*
* xrhsimopoieitai mono otan h krymmenh metavlhth einai to x
*/
template <typename T>
void Matrix<T>::reverse() {

	//desmeyoume xwro gia ton kai nourgio pinaka
    T ** newTable = new T*[sthles];
	for (int k = 0; k < sthles; ++k) {
        newTable[k] = new T[grammes];
	}
	//[i][j]=[j][i]---->anastrefoume ton pinaka
	for (int i = 0; i < grammes ; ++i) {
		for (int j = 0; j < sthles; ++j) {
			newTable[j][i] = table[i][j];
		}
	}

    T ** p = table;
	table = newTable;
	delete[] p;

	//oi grammes ginontai sthles kai oi sthles grammes
	int temp;
	temp = grammes;
	grammes = sthles;
	sthles = temp;
}
//pairnoume ton megisto vathmo tou poluonumou
template <typename T>
int Matrix<T>::get_vathmos() {

	if ( grammes == sthles)
		return grammes;

	int firstI = 0,firstJ= 0,secondI= 0,secondJ= 0;

	for (int i = grammes-1; i >= 0; --i) {
		for (int j = sthles-1; j >= 0; --j) {

			if( table[i][j] != 0){
				firstI = i;
				firstJ = j;
				break;
			}
		}
		if ( firstI != -1 )
			break;
	}

	for (int j = sthles-1; j >= 0; --j) {
		for (int i = grammes-1; i >= 0; --i) {
			if( table[i][j] != 0){
				secondI = i;
				secondJ = j;
				break;
			}
		}
		if ( firstJ != -1 )
			break;
	}

	firstI;
	firstJ;
	secondI;
	secondJ;

	if( (firstI + firstJ) > (secondI+secondJ) )
		return firstI + firstJ;
	else
		return secondI+secondJ;

}
