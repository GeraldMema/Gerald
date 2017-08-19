//
// Created by henry on 3/12/2015.
//

#include "TestZed.h"
#include "cppunit/config/SourcePrefix.h"

void TestZed::testCalcKappa() {

    double data[] = {2,1,0,0,2,1,1,0,-1};

    Zed z;

    Pinakas_polywnymou_mhtrwwn<double*> ppm;

    ppm.allocate_Table(3,3);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            ppm.insert(i,j,&data[i*3+j]);
        }
    }

    z.setB(7);

    int result = z.CalcKappa(&ppm,7);

    CPPUNIT_ASSERT_EQUAL(0, result ); // perimenw oti o pinakas einai antistrepsimos

    data[0] = 1;
    data[1] = 1;
    data[2] = 0;
    data[3] = 0;
    data[4] = 1;
    data[5] = 1;
    data[6] = 1;
    data[7] = 2;
    data[8] = 1;

    result = z.CalcKappa(&ppm,1e-7);

    CPPUNIT_ASSERT_EQUAL(1,result); // perimenw oti o pinakas na mhn einai einai antistrepsimos

}