#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

#define MAX_OROI 4
#define MAX_POWER 5
#define BUFFSIZE 1000

using namespace std;

int generate_dynamh();
char generate_metavlhth();
int generate_syntelesth();
char generate_proshmo();

int main(){

	//ftiaxnoume tyxaia polywnyma kai ta topothetoume se arxeio

    srand ( (unsigned int) time(NULL) );
    ofstream myfile;
    myfile.open ("generated_functions.txt");

    char buffer[BUFFSIZE];
    int flag = 0,flag1=0;
    int syntelesths , plh8osOrwn;

    char proshmo , metavlhth;

    

    int exwX = 0,exwY = 0;

    if (myfile.is_open()) { // anoikse arxeio

        for (int j = 0; j < 2; ++j) {

            plh8osOrwn = (rand() % MAX_OROI ) +1;			//paragwgh wrwn gia kathe polyonymo

            //paragwgh syntelesth

            syntelesths = generate_syntelesth();			//paragegh syntelesth statherou oroy

            snprintf(buffer, sizeof(buffer), "%d", syntelesths);

            myfile << buffer;
            //---------------------

            for (int i = 0; i < plh8osOrwn; ++i) {
                
                
                //eisagwgei syntelesth
                syntelesths = generate_syntelesth();

                snprintf(buffer, sizeof(buffer), "%d", syntelesths);

                if( syntelesths >= 0 )
                    myfile << '+';
                myfile << buffer;								//vale to proshmo
                //------------------

                myfile << "*";									//vale ton pol/smo

                //eisagwgh metavlhths
                metavlhth = generate_metavlhth();				//vale thn metavlhth

                myfile << metavlhth;
                //-------------------

                myfile << '^';									//meta thn dynamh

                //eisagwgh dynamhs
                syntelesths = generate_dynamh();				//vale thn dynamh

                if ( syntelesths == 0)
                    flag = 1;									//na
                else
                    if ( metavlhth == 'x' )
                        exwX = 1;
                    else
                        exwY = 1;
                
                if((i==0) && (syntelesths==0))
                {
                    while( syntelesths == 0 )
                        syntelesths = generate_dynamh();
                }
                
                snprintf(buffer, sizeof(buffer), "%d", syntelesths);

                myfile << buffer;
                //--------------------

                myfile << '*';

                //eisagwgh 2hs metavlhths
                if (metavlhth == 'x')
                    myfile << "y";
                else
                    myfile << 'x';
                //-------------------

                myfile << '^';

                //eisagwgh dynamhs
                syntelesths = generate_dynamh();
                if(( syntelesths == 0) && (flag1==0))
                    flag1=1;

                if (( flag1 == 1 ) || (flag == 1)){						//apokleioume to endexomeno na exoume mono mia metavlhth
                    while( syntelesths == 0 )							//'h na emfanistei pali statheros oros
                        syntelesths = generate_dynamh();
                    flag1=0;
                    flag=0;
                    
                }
                if(syntelesths != 0)
                    if ( metavlhth == 'x' )								
                        exwX = 1;
                    else
                        exwY = 1;

                snprintf(buffer, sizeof(buffer), "%d", syntelesths);

                myfile << buffer;
                //--------------------

                if( exwX == 0 || exwY == 0){
                    --i;
                }

            }
            myfile << '\n';

        }

    }

    myfile.close();


}

int generate_dynamh(){

    int syntelesths;

    syntelesths =  rand() % MAX_POWER;

    return syntelesths;
}

char generate_metavlhth(){

    int proshmo;
    proshmo = rand()%2;
    if(proshmo == 0)
        return 'x';
    return 'y';

}

int generate_syntelesth(){

    int syntelesths;
    syntelesths =  rand() % 100;
    syntelesths -=50;
    return syntelesths;

}

char generate_proshmo(){

    int proshmo;
    proshmo = rand()%2;
    if(proshmo == 0)
        return '-';
    return '+';

}