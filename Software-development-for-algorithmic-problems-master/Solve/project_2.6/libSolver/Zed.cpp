//
// Created by henry on 2/12/2015.
//

#include "Zed.h"
#include "../libMatrix/Pinakas_polywnymou_mhtrwwn.cpp"
#include <iostream>

using std:: endl;
using std:: cout;


Zed::Zed() {

    OneDconverdedMd = NULL;

}

Zed::~Zed() {

    if( OneDconverdedMd != NULL )
        delete[] OneDconverdedMd;

}

int Zed::calc_z(double * tempa,double * tempb,double * Ti,int power){

    int flag=1;
    for (int k = 0; k < power; ++k)						//epanalamvanw oses fores einai ipsomeno sthn dynamh
    {
        flag=0;

        for (int q = 0; q < M1sthles; ++q)
        {
            tempa[q]=0;
        }
        for (int q = 0; q <k+2; ++q)					//pollaplasiazw to kathe stoixeio tou enos
        {
            for (int w = 0; w < 2; ++w)					//me kathe stoixeio tou allou
            {
                if(w+q+k==0){							//arxikopoiw mono sthn arxh
                    tempb[0] = Ti[0];
                    tempb[1] = Ti[1];
                }
                tempa[q+w] += (tempb[q] * Ti[w]);		//pollaplasiasmos
            }
        }
        for (int q = 0; q < M1sthles; ++q)
        {
            tempb[q]=tempa[q];							//krataw to apotelesma pou vrhka
        }
    }
    if(power == 0)										//otan den exw dinamh eis sthn prwth
    {
        flag=0;
        tempa[0] = Ti[0];
        tempa[1] = Ti[1];
    }
    return flag;
}

int Zed::change_PinakaSyntelestwn(Pinakas_syntelestwn<double> *ps) {

    M1sthles = ps->get_sthles();

    double temp1[M1sthles],temp2[M1sthles],final[M1sthles];
    double temp3[M1sthles],temp4[M1sthles];

    double T1[2],T2[2];
    T1[0]=t4; T1[1]=t3; T2[0]=t2; T2[1]=t1;						//dino times t4+t3   kai t2+t1
    double sum[M1sthles][M1sthles];
    double flag1,flag2;


    for (int j = 0; j < M1sthles; ++j)
    {
        temp1[j]=0; temp2[j]=0; temp3[j]=0; temp4[j]=0; final[j]=0;	//midenizw tous voithitikous pinakes
    }

    for (int i = 0; i < M1sthles; ++i)						//gia kathe grammh
    {
        for (int z = 0; z < M1sthles; ++z)					//mhdenizw ta sum
            sum[i][z]=0;

        for (int j = 0;  j< M1sthles; ++j)					//gia kathe sthlh
        {

            flag1=calc_z(temp1,temp3,T1,M1sthles-j-2);		//vres tis taytothtes me syntelestes t4,t3
            flag2=calc_z(temp2,temp4,T2,j-1);				//vres tis taytothtes me syntelestes t4,t3

            if( flag1 ){									//to t3z + t4 einai ipsomeno sthn mhdenikh
                for (int m = 0; m < M1sthles; ++m)
                    final[m]=temp2[m];
            }

            if ( flag2 ){									//to t1z + t2 einai ipsomeno sthn mhdenikh
                for (int m = 0; m < M1sthles; ++m)
                    final[m]=temp1[m];
            }

            if( flag1 != 0 && flag2 != 0 ){					//alliws kane pollaplasiasmo 2 orwn
                for (int q = 0; q < M1sthles; ++q)
                {
                    for (int w = 0; w < M1sthles; ++w)		//efarmozontas
                    {
                        if(q+w<M1sthles)					//epimeristikh idiothta
                            final[q+w]+=temp1[q]*temp2[w];
                    }
                }
            }

            for (int k = 0; k < M1sthles; ++k){
                final[k] =final[k] * ps->get_element(i,j) ;	//pollaplasiazw me ton syntelesth pou antistoixouse sto y
                sum[i][k]+=final[k];								//kai to athroisma to kratame gia to teliko apotelesma
            }

            for (int h = 0; h < M1sthles; ++h)
            {
                temp1[h]=0; temp3[h]=0; temp4[h]=0; temp2[h]=0; final[h]=0;  //ksanamhdenizw tous voithitikous pinakes
            }
        }
        for (int z = 0; z < M1sthles; ++z)
        {
            ps->insert( sum[i][z] , i , z );						//pairnw to teliko apotelesma
        }
    }

    return 0;

}

/*
 * Allagh metavlthths ston Md ( ppm )
 */

int Zed::z_is_hidden_variable( Pinakas_polywnymou_mhtrwwn<double*> * ppm ){

    Pinakas_polywnymou_mhtrwwn<double*> tempPpm;

    tempPpm.allocate_Table(M1sthles , M1sthles );  // 8a klei8ei o destructor otan teleiwsei to programma kai 8a ginei apodesmeush

    for (int i = 0; i < M1sthles; ++i) {
        for (int j = 0; j < M1sthles; ++j) {
            tempPpm.insert(i,j, ppm->get_element(i,j) );
        }
    }

    double temp1[M1sthles],temp2[M1sthles],final[M1sthles];
    double temp3[M1sthles],temp4[M1sthles];

    double T1[2],T2[2];
    T1[0]=t4; T1[1]=t3; T2[0]=t2; T2[1]=t1;						//dino times t4+t3   kai t2+t1
    double sum[M1sthles][M1sthles];
    double t3zt4,t1zt2;


    for (int j = 0; j < M1sthles; ++j)
    {
        temp1[j]=0; temp2[j]=0; temp3[j]=0; temp4[j]=0; final[j]=0;	//midenizw tous voithitikous pinakes
    }

    for (int i = 0; i < M1sthles; ++i)						//gia kathe grammh
    {
        for (int z = 0; z < M1sthles; ++z)					//mhdenizw ta sum
            sum[i][z]=0;

        for (int j = 0;  j< M1sthles; ++j)					//gia kathe sthlh
        {

            t3zt4=calc_z(temp1,temp3,T1,M1sthles-j-2);		//vres tis taytothtes me syntelestes t4,t3
            t1zt2=calc_z(temp2,temp4,T2,j-1);					//vres tis taytothtes me syntelestes t4,t3

            if(t3zt4){											//to t3z + t4 einai ipsomeno sthn mhdenikh
                for (int m = 0; m < M1sthles; ++m)
                    final[m]=temp2[m];
            }
            else if (t1zt2){									//to t1z + t2 einai ipsomeno sthn mhdenikh
                for (int m = 0; m < M1sthles; ++m)
                    final[m]=temp1[m];
            }
            else{												//alliws kane pollaplasiasmo 2 orwn
                for (int q = 0; q < M1sthles; ++q)
                {
                    for (int w = 0; w < M1sthles; ++w)		//efarmozontas
                    {
                        if(q+w<M1sthles)					//epimeristikh idiothta
                            final[q+w]+=temp1[q]*temp2[w];
                    }
                }
            }

            for (int k = 0; k < M1sthles; ++k){
                int a;
                if( tempPpm.get_element(i,j) != NULL )
                    a = *tempPpm.get_element(i,j);
                else
                    a = 0;
                final[k] =final[k] * a ;	//pollaplasiazw me ton syntelesth pou antistoixouse sto y
                sum[i][k]+=final[k];								//kai to athroisma to kratame gia to teliko apotelesma
            }

            for (int h = 0; h < M1sthles; ++h)
            {
                temp1[h]=0; temp3[h]=0; temp4[h]=0; temp2[h]=0; final[h]=0;  //ksanamhdenizw tous voithitikous pinakes
            }
        }
        for (int z = 0; z < M1sthles; ++z)
        {
            tempPpm.insert( i , z , &sum[i][z] );						//pairnw to teliko apotelesma
        }
    }

    return CalcKappa( &tempPpm , B ); // des to kappa tou kainourgioy pinaka Md

}
/*
 * Dokimazei thn allagh metavlhths sto Md
 */
int Zed::change_hidden_variable( Pinakas_polywnymou_mhtrwwn<double*> * ppm , double bound ) {

    Pinakas_polywnymou_mhtrwwn<double*> myPpm; // proswrinos pinakas gia na dokimasw thn alagh metavlhths

    M1sthles = ppm->get_sthles(); // krataw tis sthles tou m1

    myPpm.allocate_Table(M1sthles,M1sthles); // deusmeuw xwro gia to proswrino pinaka

    //antigrafw tis times tou Md sto prwsorino pinaka gia na kanw prakseis panw se autes
    for (int i = 0; i < M1sthles; ++i) {
        for (int j = 0; j < M1sthles; ++j) {
            myPpm.insert( i,j,ppm->get_element(i,j) );
        }
    }
    //----------------------------------------------------------------------------------

    B = bound;

    t1 = (rand() % MAXFACTOR) - (MAXFACTOR/2);
    t2 = (rand() % MAXFACTOR) - (MAXFACTOR/2);
    t3 = (rand() % MAXFACTOR) - (MAXFACTOR/2);
    t4 = (rand() % MAXFACTOR) - (MAXFACTOR/2);

    return z_is_hidden_variable(&myPpm);						//kai kalw thn synarthsh pou tha allaksei ton pinaka syntelestwn

}

int Zed::CalcKappa( Pinakas_polywnymou_mhtrwwn<double*> * ppm , int bound ) {

    B = bound;

    if( ppm->convertToDouble() != 0 ) // metatrepw to Md apo int se double
        return 1;

    // to kanw se morfh pou 8elei to Jacobi
    if( make1D( ppm->getConvertedMd() , ppm->get_grammes() , ppm->get_sthles() ) != 0 )
        return 2;

    //Ypologizw to k
    int result = k.generateKappa( OneDconverdedMd , ppm->get_grammes() , B );

    //den mporw na antistrepsw to pinaka na to k den mporei na ypologistei h' einai poly megalo
    if( result == 1 )
        return 1;
    else if( result == 2) // kappa is nan
        return 2;
    else//periptwsh pou o pinakas einai antistrepsimos
        return 0;

}

/*
 * Metatroph disdiastatou pinaka se monodiastato
 */
int Zed::make1D( double ** converdedMd , int grammes , int sthles){

    OneDconverdedMd = new double[grammes*sthles];

    for (int i = 0; i < grammes ; ++i) {
        for (int j = 0; j < sthles; ++j) {
            OneDconverdedMd[i*grammes+j] = converdedMd[j][i];
        }

    }

    return 0;
}
