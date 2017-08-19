//
// Created by henry on 21/10/2015.
//

#include "Handler.h"

using namespace std;

using Eigen::MatrixXd;
using Eigen::EigenSolver;
using Eigen::Map;

Handler::Handler()
{

    result = NULL;

    solutions = NULL;
    solutions_i = 0;

    solutionsWIthGeneralized = NULL;
    solutionsWIthGeneralized_i = 0;

    line = "";
    line.clear();

}

Handler::~Handler() {

    int Grammes = sylvester.get_resultGrammes();

    if ( result != NULL) {
        for (int i = 0; i < Grammes; ++i) {
            delete[] result[i];
        }
//    delete[] result;
    }

    if ( solutions != NULL) {
        for (int i = 0; i < solutionsRows; ++i) {
            delete[] solutions[i];
        }
//    delete[] result;
    }

    if ( solutionsWIthGeneralized != NULL) {
        for (int i = 0; i < solutionsWIthGeneralizedRows; ++i) {
            delete[] solutionsWIthGeneralized[i];
        }
//    delete[] solutionsWIthGeneralized;
    }

}

Pinakas_polywnymou_mhtrwwn<double*> Handler::get_Md()
{

    Pinakas_polywnymou_mhtrwwn<double*> * temp;

    temp = Polywnymo_Mhtrwwn.getMd(Polywnymo_Mhtrwwn.get_grammes()-1);

    return *temp;
}

template <typename T>
int Handler::allocate_2D_table(T *** table , int rows , int cols)
{

    table[0] = new T*[rows];

    for (int i = 0; i < rows; ++i) {

        table[0][i] = new T[cols];

    }

    return 0;

}


/*
 * Xeirizetai thn eisodo me points apo th visualization.cpp
 */
int Handler::handle_Points(double ** points, double **points2 , int pointsCounter , int points2Counter,int newd1,int newd2){

    // auta gia to prwto synolo shmeiwn

    int error;

    error = interpolationMatrix.generate_M(points,pointsCounter,newd1);

    if( error != 0 )
    {
        line.append("\n");
        line.append(interpolationMatrix.get_line());

        return 5;
    }

    int acceptableKappa = interpolationMatrix.calc_rank();

    if( acceptableKappa == 0 ){ //periptwsh kappa == rank-1

        interpolationMatrix.calc_Kernel(); // ypologizw to kernel
        interpolationMatrix.WriteToFile(); // grafw th synarthsh pou parhx8ei sto arxeio generated_functions

    }
    else if( acceptableKappa == 1 ) { // periptwsh kappa == rank
        cout << " kappa == rank , Problem is infisible\nExiting...\n";
        line.append(" kappa == rank , Problem is infisible\nExiting...\n");
        return 3;
    }
    else{ // periptwsh rank < k-1
        cout << " rank < k-1 , The solution is numerically unstable\nExiting...\n";
        line.append(" rank < k-1 , The solution is numerically unstable\nExiting...\n");
        return 4;
    }

    //---------------------------------

    // auta gia to deutero synolo shmeiwn


    error = interpolationMatrix.generate_M(points2,points2Counter,newd2);

    if( error != 0 )
    {
        line.append("\n");
        line.append(interpolationMatrix.get_line());

        return 5;
    }

    acceptableKappa = interpolationMatrix.calc_rank();

    if( acceptableKappa == 0 ){

        interpolationMatrix.calc_Kernel();
        interpolationMatrix.WriteToFile();

    }
    else if( acceptableKappa == 1 ) {
        cout << " kappa == rank , Problem is infisible\nExiting...\n";
        line.append(" kappa == rank , Problem is infisible\nExiting...\n");
        return 3;
    }
    else{
        cout << " rank < k-1 , The solution is numerically unstable\nExiting...\n";
        line.append(" rank < k-1 , The solution is numerically unstable\nExiting...\n");
        return 4;
    }

    //-----------------------------------

    read( (char*) "generated_functions.txt");

    generate_Sylvester();

	generate_Polywnymo_Mhtrwwn(); // synarthsh pou paragei ta polywnyma mhtrwwn

    error = solve();    //synarthsh epilhshs mh grammikwn eksiswsewn

    if( error != 0 )
        return error;

    return 0;

}

/*
 * Ypologizei tis rizes otan h krymenh metavlhth exei multiplicity > 1
 */
int Handler::calc_x_with_multiplicity(int i , MatrixXd & lambda)
{

    Matrix<double> f1; // einai oi eksiswsh 1 me agnwsto ws pros x mono , antika8istwntas to y
    Matrix<double> f2;

    f1.allocate_Table(m1.get_grammes(),1); // desmeush xwou twn pinakwn
    f2.allocate_Table(m2.get_grammes(),1);

    m1.replaceHiddenVariable( f1 , lambda(i,0) ); // antika8istw to y me th timh pou exei pollaplothta sto m1
    m2.replaceHiddenVariable( f2 , lambda(i,0) ); // kai apo8hkeuw to apotelesma sto pinaka f

    Companion f1Companion , f2Companion; // exw ena companion gia ka8e synarthsh

    f1Companion.generateMultiplicityCompanion(f1); // ftiaxnw ton companion me 1 agnwsto
    f2Companion.generateMultiplicityCompanion(f2);

    f1Companion.convertC(); // metatroph tou companion se morfh anagnwrisimh apo thn eigen
    f2Companion.convertC();

    f1Companion.calcEigenvectorsAndEigenValues(); // ypologizw tis times tou x gia multiple y
    f2Companion.calcEigenvectorsAndEigenValues();

    MatrixXd newLambdaF1 = f1Companion.getLambda(); // pairnw ta lambda
    MatrixXd newLambdaF2 = f2Companion.getLambda();

    double common_x[ max( newLambdaF1.rows(),newLambdaF2.rows() )]; // pinakas pou krataei ta x pou exw koina
    int common_x_pos = 0; // krataei th teleutaia 8esh tou pinaka

    //euresh koinwn x sta f1,f2
    for (int j = 0; j < newLambdaF1.rows(); ++j) {

        if( newLambdaF1(j,1) != 0 ) // ean to fantastiko meros einai != 0 synaixise
            continue;

        // elegxw ean exw ksanadei auto to stoixeio
        int isInCommonX = 0 ;
        for (int m = 0; m < common_x_pos; ++m) {

            if( newLambdaF1(j,0) == common_x[m] ) {
                isInCommonX = 1;
                break;
            }

        }

        if( isInCommonX == 1 )
            continue;
        //------------------------------------------

        for (int l = 0; l < newLambdaF2.rows(); ++l) {

            // ean einai peripou idia kai ean den exei fantastiko meros to newLambdaF2(l)
            if( abs( newLambdaF1(j,0) - newLambdaF2(l,0) ) < 1e-5 && newLambdaF2(l,1) == 0 ) {

                common_x[common_x_pos] = newLambdaF1(j, 0);
                ++common_x_pos;

                int result1 = oldM1.calcWithXAndY( (double)newLambdaF1(j,0) , (double)lambda(i,0) );
                int result2 = oldM2.calcWithXAndY( (double)newLambdaF2(l,0) , (double)lambda(i,0) );

                check_sum(result1,result2,(double)newLambdaF1(j,0),(double)lambda(i,0));

            }

        }

    }

    return 0;
}

/*
 * Elegxei ean exw ksanatsekarei auto to y gia na mhn paw na ypologizw polles fores thn idia lysh
 */
int Handler::check_if_I_have_seen_y(int i, MatrixXd lambda)
{
    int exw_dei_auto_to_y = 0;

    for (int n = 0; n < i; ++n) {

        if ( abs ( lambda(n, 0) - lambda(i, 0) ) < 1e-5 ) {

            exw_dei_auto_to_y = 1;
            break;
        }
    }

    return exw_dei_auto_to_y;

}

/*
 * Elegxei an oi 2 synarthseis mhdenzontai sto x kai to y kai an nai tote krataei ta apotelesemata
 */
int Handler::check_sum(int res1 , int res2 , double x , double y)
{
    if( res1 + res2 == 0 ) { // an to apotelesma einai konta sto mhden ta res1 kai res2 pernoun timh 0
        if( hidden_variable == 'y' )
        {
            cout << " y = " << y << " , x = " << x << endl;

            if( allaksaMetavlhth )
            {
                solutionsWIthGeneralized[solutionsWIthGeneralized_i][0] = x; // krataw to x
                solutionsWIthGeneralized[solutionsWIthGeneralized_i][1] = y; // krataw to y
                ++solutionsWIthGeneralized_i;
            }
            else
            {
                solutions[solutions_i][0] = x; // krataw to x
                solutions[solutions_i][1] = y; // krataw to y
                ++solutions_i;
            }
        }

    }

    return 0;

}


/*
 * Elegxei ean ta polywnyma exoyn mhdenistei kai an nai apo8hkeuei ta x kai y sto pinaka solutions.
 * Se periptwsh pou ypologizw tis lyseis kai me tous 2 tropous apo8hkeuontai oi lyseis ths mias me8odou
 * sto pinaka solutionsWIthGeneralized.
 */
int Handler::check_sum( int res1 , int res2 , MatrixXd lambda , MatrixXd V , int i)
{

    if( res1 + res2 == 0 ) { // an to apotelesma einai konta sto mhden ta res1 kai res2 pernoun timh 0
        if( hidden_variable == 'y' )
        {
            cout << " y = " << lambda(i,0) << " , x = " << V(V.rows()-2,i) << endl;

            if( ypologizwKaiTis2Lyseis == 1 )
            {
                solutionsWIthGeneralized[solutionsWIthGeneralized_i][0] = (double)V(V.rows()-2,i); // krataw to x
                solutionsWIthGeneralized[solutionsWIthGeneralized_i][1] = (double)lambda(i,0); // krataw to y
                ++solutionsWIthGeneralized_i;
            }
            else
            {
                solutions[solutions_i][0] = (double)V(V.rows()-2,i); // krataw to x
                solutions[solutions_i][1] = (double)lambda(i,0); // krataw to y
                ++solutions_i;
            }
        }
        else
        {

            cout << " x = " << lambda(i,0) << " , y = " << V(V.rows()-2,i) << endl;

            if( ypologizwKaiTis2Lyseis == 1 )
            {
                solutionsWIthGeneralized[solutionsWIthGeneralized_i][1] = (double)V(V.rows()-2,i); // krataw to y
                solutionsWIthGeneralized[solutionsWIthGeneralized_i][0] = (double)lambda(i,0); // krataw to x
                ++solutionsWIthGeneralized_i;
            }
            else
            {
                solutions[solutions_i][1] = (double)V(V.rows()-2,i); // krataw to y
                solutions[solutions_i][0] = (double)lambda(i,0); // krataw to x
                ++solutions_i;
            }

        }

    }

    return 0;

}


/*
 * Elegxei gia lyseis sta lambda kai V
 */
int Handler::generate_rest_solution(MatrixXd &lambda ,MatrixXd &V , int allaksaMetavlhth )
{

    //desmeuw mnhmh gia to pinaka pou krataei ta x kai y ths lyshs
    solutionsRows = lambda.rows();
    allocate_2D_table<double>(&solutions,solutionsRows,2);
    //------------------------------------------------------------

    //ean allaksa metavlhth 8elw na mpei edw th 2h fora pou 8a klei8ei h generate_rest_solution
    if( allaksaMetavlhth && ypologizwKaiTis2Lyseis == 0 )
    {
        for (int i = 0; i < lambda.rows(); ++i) {
            lambda(i,0) = (z.getT1() * lambda(i,0) + z.getT2() )/( z.getT3() * lambda(i,0) + z.getT4() );
        }
    }

    // paw na elegxw an kapoia apo tis idiotimes einai lush
    for (int i = 0; i < lambda.rows(); ++i) {  //oso exw idiotimes

        int res1 ,res2; // metavlhtes pou kratane to apotelesma apo to ypologismo twn synarthsewn gia sygkekrimena x kai y

        res1 = oldM1.calcWith(lambda,V,i); // ypologizw th timh mias synarthshs sto zeugos x,y

        int exw_dei_auto_to_y; // flag gia na tsekarw ean exw ypologisei auth th lysh

        if( res1 == 1 ) // ean exw multiplicity tsekare mhn einai 1h fora pou to vlepw
            exw_dei_auto_to_y = check_if_I_have_seen_y(i,lambda);

        //res == 1 shmainei oti exw multiplicity, opote elegxw an exw tsekarei auth th timh gia th krymenh metavlhth
        if( res1 == 1 && exw_dei_auto_to_y == 0 )
        {
            calc_x_with_multiplicity(i,lambda); // ypologizw ta x kai y pou einai lyseis
        }

        if( res1 == 1 ) // exw pollaplothta ara exw dei ena einai riza kai 8elw na paw sto epomeno y
            continue;

        // alliws den exw pollaplothta kai paw na vrw th timh ths 2hs synarthshs gia tis times tou x kai tou y
        res2 = oldM2.calcWith(lambda,V,i);

        check_sum(res1,res2,lambda,V,i); // elegxw an ta polywnyma mhdenisthkan kai an nai apo8hkeuw tis times twn x kai y

    }

    if( allaksaMetavlhth ) // an allaksw metavlhth tote 8elw na mpei thn epomenh fora sthn if( allaksaMetavlhth && ypologizwKaiTis2Lyseis == 0 )
        ypologizwKaiTis2Lyseis = 0;

    return 0;
}
/*
 * krataw antigrafa gia ta arxika m1 kai m2
 */
int Handler::copy_m1_and_m2()
{
    oldM1.allocate_Table(m1.get_grammes() , m1.get_sthles() );
    oldM2.allocate_Table(m2.get_grammes() , m2.get_sthles() );

    for (int j = 0; j < m1.get_grammes(); ++j) {
        for (int l = 0; l < m1.get_sthles(); ++l) {
            oldM1.insert(m1.get_table_pos(j,l),j,l);
        }
    }

    for (int j = 0; j < m2.get_grammes(); ++j) {
        for (int l = 0; l < m2.get_sthles(); ++l) {
            oldM2.insert(m2.get_table_pos(j,l),j,l);
        }
    }

    return 0;
}

int Handler::find_better_kappa( int * isAntistrepsimos , int * allaksaMetavlhth ,int kappa )
{

    if( *isAntistrepsimos == 1 ) { // ean den einai antistrepsimos

        for (int i = 0; i < 3; ++i) { // dokimase allagh metavlhths

            int error = z.change_hidden_variable(
                    Polywnymo_Mhtrwwn.get_table_pos(0, Polywnymo_Mhtrwwn.get_sthles() - 1) , B );

            if( error != 2 ) // ean den einai nan
            {

                *isAntistrepsimos = error; // dhaldh 0 h' 1

                double newKappa = z.getKappa();

                if ( newKappa < kappa ) {
                    cout << " Vrhkame kaligetKappatero k opote stamatame kai efarmozoume thn allagh metavlhths" << endl;
                    line.append(" Vrhkame kaligetKappatero k opote stamatame kai efarmozoume thn allagh metavlhths\n");
                    *allaksaMetavlhth = 1;
                    break;
                }

            }

        }

    }

    return 0;

}


/*
 * Epilyei to provlhma akolou8ontas th 8ewria
 */
int Handler::solve(){

    B = 7; // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Mhn to ksexaseis <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    //Elegxw an h orizousa mhdenizetai gia tyxaia y
//    if( sylvester.calcDet() == 1 ) {

//        cout << " Sylvester = " << endl;
//        sylvester.print_Table('y');

//        cout << "H orizoysa tou Sylvester mhdenizete gia ka8e " << hidden_variable << endl;
//        return 1;
//    }
    //---------------------------------------------

    int vathmosKrymmenhsMetavlhths;

    if( m1.get_sthles() > m2.get_sthles() )
        vathmosKrymmenhsMetavlhths = m1.get_sthles() - 1;
    else
        vathmosKrymmenhsMetavlhths = m2.get_sthles() - 1;

    // to list einai enas pinakas pou exei deiktes se 1D anaparastash twn Md
    double ** list = Polywnymo_Mhtrwwn.makeArrayWithDoubleArrays();

    // Ypologizw ean einai antistrepsimos o pinakas. 0 -> einai antistrepsimos , 1->den einai
    int isAntistrepsimos = z.CalcKappa( Polywnymo_Mhtrwwn.getMd( Polywnymo_Mhtrwwn.get_sthles() - 1 ),  B );

    double kappa = z.getKappa();

    allaksaMetavlhth = 0; // flag pou moy deixnei an allakse h metavlhth

    ypologizwKaiTis2Lyseis = 0; // flag pou deixnei an exw ypologisei 2 lyseis se periptwsh pou allakse h metavlhth

    copy_m1_and_m2(); // krataei tous pinakes m1 kai m2 prin ginei h allagh twn timwn tous se periptwsh pou vrw kalytero kappa

    find_better_kappa( &isAntistrepsimos , &allaksaMetavlhth , kappa );

    if( allaksaMetavlhth ) { // ean vrhka kalytero kappa

        //ypologizw tis lyseis me to generalized
        cout << " Roots mh antistrepsimoy : \n";

        // lynw to genikeumeno provlhma
        gp.solveWithGeneralProblem(vathmosKrymmenhsMetavlhths , list, Polywnymo_Mhtrwwn.get_table_pos(0, 0)->get_grammes() );

        //Pernw ta lambda kai V pou exoun parax8ei apo th lysh
        MatrixXd lambda = gp.getLambda();
        MatrixXd V = gp.getV();

        // krataw kai tis 2 lyseis auth th fora , kai gi'auto deusmeuw mnhmh gia ena 2o pinaka me tis lyseis
        solutionsWIthGeneralizedRows = lambda.rows();
        allocate_2D_table<double>(&solutionsWIthGeneralized,solutionsWIthGeneralizedRows,2);
        //--------------------------------------------------------------------------------------------------

        ypologizwKaiTis2Lyseis = 1;

        generate_rest_solution(lambda,V,0); // twra pou allaksaMetavlhth paw kai grafw ta apotelesmata sto solutionsWithGeneralized

        z.change_PinakaSyntelestwn(&m1);
        z.change_PinakaSyntelestwn(&m2);

        list = Polywnymo_Mhtrwwn.makeArrayWithDoubleArrays();

    }

    if( isAntistrepsimos == 1 ) {  // ola phgan kala alla den einai antistrepsimos o pinakas

        cout << " Roots mh antistrepsimoy : \n";

        // lynw to genikeumeno provlhma
        gp.solveWithGeneralProblem(vathmosKrymmenhsMetavlhths , list, Polywnymo_Mhtrwwn.get_table_pos(0, 0)->get_grammes() );

        //Pernw ta lambda kai V pou exoun parax8ei apo th lysh
        MatrixXd lambda = gp.getLambda();
        MatrixXd V = gp.getV();

        generate_rest_solution(lambda,V,allaksaMetavlhth);
    }

    else if ( isAntistrepsimos == 0 ) {    // antistrefete kanonika

        cout << " Roots antistrepsimou : \n";

        // lynw to standard provlhma
        c.solveWithInvert(vathmosKrymmenhsMetavlhths, list, Polywnymo_Mhtrwwn.get_table_pos(0, 0)->get_grammes());

        // Pernw ta lambda kai v pou exoun ypologistei
        MatrixXd lambda = c.getLambda();
        MatrixXd V = c.getV();

        generate_rest_solution(lambda,V,allaksaMetavlhth);

    }
    else {
        cout << " kati phge strava ston ypologismo tou k \n";
        return 2;
    }

    return 0;
}

/*
 * Synarthsh gia xeirismo kai elegxo ths eisodou apo to xrhsth
 */
void Handler::handle_input(int argc, char *argv[]) {

    srand ( (unsigned int) time(NULL) ); // arxhkopoihsh tou rand , to xreiazomai sth generate

    if( argc == 10  || argc == 9 ){

        if ( strcmp("-i",argv[2] ) == 0  && strcmp("-read",argv[1]) == 0 ) {
            read(argv[3]);
            d0 = atoi(argv[5]);
            d1 = atoi(argv[7]);
            if( argc == 10 )
                B = atoi(argv[9]);
            else
                B = 7;
        }
        else {
            cout << "-------Wrong input!-------\nDid you mean : equations -read -i <file_path> -d1 d1 -d2 <d2> -solve 'B'?\n";
            cout << " Press Y/N : ";
            char answer;
            cin >> answer;
            if (answer == 'Y' || answer == 'y') {
                cout << " Insert <file_path>";
                cin >> argv[3];
                cout << " Insert -d1";
                cin >> argv[5];
                cout << " Insert -d2";
                cin >> argv[7];
                read(argv[3]);
                d0 = atoi(argv[5]);
                d1 = atoi(argv[7]);
            }
            else
                exit(3);
        }

    }
    else if( argc == 8 || argc == 7 ){

        if(strcmp("-generate",argv[1]) == 0 && strcmp("-solve" , argv[6]) == 0 ) {
            d0 = atoi(argv[3]);
            d1 = atoi(argv[5]);
            if( argc == 7)
                B = 7;
            else
                B = atoi( argv[7] );

            generate();
        }
        else {

            cout << "-------Wrong input!-------\n"
                    "Did you mean : equations -generate -d1 X -d2 Y -solve B? where X , Y , B are ints\n";
            cout << " Press Y/N : ";
            char answer;
            cin >> answer;
            if (answer == 'Y' || answer == 'y') {
                char D1[10];
                cout << "Insert d1: ";
                cin >> D1;
                d0 = atoi(D1);
                cout << "Insert d2 : ";
                cin >> D1;
                d1 = atoi(D1);
                cout << " Would you like to give B? Press Y for yes N for no";
                cin >> answer;
                if( answer == 'Y') {
                    cin >> D1;
                    B = atoi(D1);
                }
                else
                    B = 7;


                generate();
            }
            else
                exit(1);
        }

    }
    else{
        cout << "---Error input!---\n";
        cout<<" Expected one of these :\n"
                      "equations -generate -d1 X -d2 Y -solve ,  where X and Y are ints\n"
                      "equations -generate -d1 X -d2 Y -solve B , where X , Y and B are ints\n"
                      "equations -read -i <file_path> -d1 X -d2 Y –solve Β , where X , Y and B are ints \n";
        exit(1);
    }

}


/*
 * Synarthsh pou xeirizetai tis ektypwseis twn pinakwn analoga me tis epiloges tou user
 */
void Handler :: print(){

    cout << endl << "[Printing Md , which means : ]" << endl;

    line.append("\n");
    line.append(z.get_line());

    line.append("\n");
    line.append("[Printing Md , which means : ]\n");

    Polywnymo_Mhtrwwn.getMd( Polywnymo_Mhtrwwn.get_sthles() - 1 )->print_to_string(line);

    line.append("\n");

    Polywnymo_Mhtrwwn.print_Table( Polywnymo_Mhtrwwn.get_sthles() - 1 );

    return;
}

void Handler :: generate_Polywnymo_Mhtrwwn(){

    Polywnymo_Mhtrwwn.generate(m1 , m2);                    //ftiakse tous pinakes Ai
}

void Handler :: generate_Sylvester(){

    sylvester.allocate_Table(d0 + d1 , d0 + d1 );           
    sylvester.make_Sylvester(m1 ,m2);              //ftiakse ton pinaka sylvester

}

void Handler :: generate_Bonus()
{
    v.allocate_Table(d0+d1,1);                              //to dianysma v exei megethos [grammes_sylvester][1]
    
    for (int i = 0; i < d0+d1; ++i) {
        v.insert(i+1,i,0);
    }
    result = sylvester.multiply(v);                         //result=S*v

}

/*
 * Paragei tyxaia syntelestes gia ta 2 polywnyma
*/
 void Handler :: generate() {

    hidden_variable = 'y';
    m1.create_Polywnymo(d0); // paragei to pinaka syntelestwn m1
    m2.create_Polywnymo(d1); // paragei to pinaka syntelestwn m2

}

// diavasma apo consola
void Handler :: consola() {

    char function[2000];

    cout << " Enter 1st function : ";

    cin >> function;

    place_function_in_Matrix(function, m1);                 //parsing  to polyonumo 1

    cout << " Enter 2nd function : ";

    cin >> function;

    place_function_in_Matrix(function, m2);                 //parsing to polyonumo 2

    hidden_variable = find_hidden_variable(m1,m2);          //poia metavlhth tha krypsoume apo ta 2 poluonyma

    if( hidden_variable == 'x') {                           //an apofasistei na kryftei h metavlhth x
        m1.reverse();                                       //antistrefoume to m1
        m2.reverse();                                       //kai to m2
        d0 = m1.get_maxYpower();                            //max sthles gia to polyonumo m1
        d1 = m2.get_maxYpower();                            //max sthles gia to polyonumo m2
    }
    else{ // hidden == 'y'
        d0 = m1.get_maxXpower();                            //max sthles gia to polyonumo m1
        d1 = m2.get_maxXpower();                            //max sthles gia to polyonumo m2
    }

}


/*
 * Diavase tis synarthsei apo arxeio filename kai vrhskei th krymmenh metavlhth
 */
void Handler :: read( char * filename) {

    hidden_variable = Read_synarthsh_from_file( filename );

    if (hidden_variable == 'x') {                           //an apofasistei na kryftei h metavlhth x
        m1.reverse();                                       //antistrefoume to m1
        m2.reverse();                                       //kai to m2
        d0 = m1.get_maxYpower();                            //max sthles gia to polyonumo m1
        d1 = m2.get_maxYpower();                            //max sthles gia to polyonumo m2
    }
    else {
        d0 = m1.get_maxXpower();                            //max sthles gia to polyonumo m1
        d1 = m2.get_maxXpower();                            //max sthles gia to polyonumo m2
    }
}

int Handler::clean_white_spaces(string & line)
{

    for (int i = 0; line[i]!='\0'; ++i) {

        if( isspace(line[i]) )
        {
            line.erase(line.begin()+i);
            --i;
        }


    }
    return 0;
}

/*
 * diavazei mia synarthsh apo to filename kai ftiaxnei pyknh anaparastash sto pinaka m
 * epishs gyrnaei ena char gia th metavlhth pou prepei na kryftei
 *
 * Exei thn paradoxh oti h synarthsh sto filename dinetai xwris kena
 */
char Handler :: Read_synarthsh_from_file(char *filename ) {

    ifstream myfile;
    myfile.open (filename);

    string line;

    cout << "Equations\n------------" << endl;

    if ( myfile.is_open() ) { // anoikse arxeio

        getline(myfile,line);

        clean_white_spaces(line);

        cout << line << endl;

        place_function_in_Matrix( (char*)line.c_str() , m1 );

        line = "";
        line.clear();

        getline(myfile,line);

        clean_white_spaces(line);

        cout << line << endl;

        place_function_in_Matrix( (char*)line.c_str() , m2 );   //epeksergasia m2 polyonumou

    }
    else {
        cerr << " Error while opening file " << filename << endl;
        exit(1);
    }

    myfile.close();

    return find_hidden_variable(m1,m2);           //vres poia apo tis 2 metavlhtes tha krypsoume

}

char Handler::find_hidden_variable( Matrix<double> & m1 , Matrix<double> & m2){

    int m1MaxXpower = m1.get_maxXpower();                                      //megistos vathmos tou x sto polhwnymo m1
    int m1MaxYpower = m1.get_maxYpower();                                       //megistos vathmos tou y sto polhwnymo m1
    int m2MaxXpower = m2.get_maxXpower();                                       //megistos vathmos tou x sto polhwnymo m2
    int m2MaxYpower = m2.get_maxYpower();                                       //megistos vathmos tou y sto polhwnymo m2

    if( ( m1MaxXpower >= m1MaxYpower) && (m2MaxXpower >= m2MaxYpower) )           //an kai sta 2 polyonyma o vathmos toy x einai
        return 'y';                                                                //megalyteros tote krypse to y
    else if ( (m1MaxXpower < m1MaxYpower) && (m2MaxXpower < m2MaxYpower) )      //an kai sta 2 polyonyma o vathmos tou y einai
        return 'x';                                                              //megalyteros tote krypse ton x
    else                                                                          //alliws
    {
       if( m1MaxXpower >= m1MaxYpower)                                           //an o maxvathmos tou x sto m1 polywnymo einai 
        {                                                                       //megaliteros apo ton maxvathmo y sto m1   tote
            if(m1MaxXpower >= m2MaxYpower)                                       //an o max x sto m1 einai megaliteros apo ton max y sto m2
                return 'y';                                                     //krypse thn metavlhth apo ton megalitero 
            else
                return  'x';                                                    //alliws krypse thn allh metavlhth
        }                           
       else
        {
            if(m1MaxYpower > m2MaxXpower)                                       //an o max y tou m1 megaliteros apo ton max y tou m2
                return 'x';                                                     //krypse thn metavlhth apo ton megalitero
            else
                return 'y';                                                      //alliws krypse thn allh metavlhth
        }
    }

}

double Handler::str_to_double(char * num)
{
    int proshmo=1;

    int pshfiaAristeraApoToCommaCounter = 0;

    while ( num[pshfiaAristeraApoToCommaCounter] != '.' && num[pshfiaAristeraApoToCommaCounter] != ' ' && num[pshfiaAristeraApoToCommaCounter] != '\n' )
        pshfiaAristeraApoToCommaCounter++;

    if( num[pshfiaAristeraApoToCommaCounter] == ' ' || num[pshfiaAristeraApoToCommaCounter] == '\n')
        return (double)atoi(num);

    double result = num[pshfiaAristeraApoToCommaCounter-1] - '0';

    if( num[0] == '-' )
    {
        for (int i = pshfiaAristeraApoToCommaCounter-2; i >= 1; --i)
        {

            result = 10*result + num[i] - '0';

        }
        proshmo = -1;
    }
    else
    {
        proshmo = 1;
        for (int i = pshfiaAristeraApoToCommaCounter-2; i >= 0; --i) {

            result = 10*result + num[i] - '0';

        }
    }

    int pos = pshfiaAristeraApoToCommaCounter+1;
    double dekadikoMeros = num[pos] -'0';
    pos++;
    long double diaireths = 10;

    while ( num[pos]!='\0' && num[pos] != '\n' ){

        dekadikoMeros = dekadikoMeros*10 + num[pos]-'0';
        diaireths *= 10;
        ++pos;

    }

    dekadikoMeros = dekadikoMeros / diaireths;

    result = result+dekadikoMeros;

    result = result*proshmo;

    return result;

}

int Handler::is_int( char * str )
{
    while ( *str )
    {
        if( !isdigit(*str) && *str != '-' && *str != '+')
            return 1;
        else
            ++str;
    }
    return 0;
}

int Handler::check_if_syntelesths_einai_1(char * buffer ,double * syntelestes , int k, int pos ,int proshmo )
{
    if( (buffer[k]=='x') || (buffer[k]=='y') ) { // ean dw sketo x h' sketo y katalavainw oti o syntelesths einai +1

        syntelestes[pos] = 1 * proshmo;

        return 0;
    }

    return 1;

}

/*
 * diavazei to syntelesth sto buffer kai afhnei to j sth epomenh tou teleytaiou pshfiou 8esh
 */
double Handler::diavasma_syntelesth( char * buffer , int * j )
{
    char syntelesthsBuffer[1000];

    int z = 0; // krataw th 8esh pou ksekinaei o sta8eros oros ston buffer

    int i = *j;

    while( buffer[i] != '+' && buffer[i]!='-' && buffer[i] != ' ' && buffer[i] != 'x' && buffer[i] != 'y' && buffer[i]!= '*' ) // mexri na teleiwsei o ari8mos
    {
        syntelesthsBuffer[z] = buffer[i]; // antigrafw ta grammata
        ++i;
        z++;
    }

    *j = i;

    syntelesthsBuffer[z] = '\0'; // dhlwnw pou teleiwnei h symvoloseira pou diavasa

    if( is_int(syntelesthsBuffer) == 0 )
    {
        return strtoul((const char*)syntelesthsBuffer,NULL,10 );
    }
    else
        return str_to_double(syntelesthsBuffer);

}

/*
 * Dhmiourgei ton pinaka syntelestwn m mesw ths eksiswshs sto buffer
 */
void Handler::place_function_in_Matrix( char * buffer , Matrix<double> & m){

    char metavlhth;
    int maxXpower=0;
    int maxYpower=0;

    int xPowers[100]; // pinakas me tis dynameis tou x pou vlepw
    int yPowers[100]; // pinakas me tis dynameis tou y pou vlepw
    double syntelestes[100]; // pinakas me tous syntelestes ka8e orou

    int pos = 0;      //thesi tou kathe orou

    //mhdenizw tous pinakes
    for (int i1 = 0; i1 < 100 ; ++i1) {
        xPowers[i1] = 0;
        yPowers[i1] = 0;
    }

    int bufferSize = strlen(buffer);

    int proshmo = 1;

    int j = 0;

    if ( buffer[j] == '-') {    //diavasma proshmou
        proshmo = -1;
        j++;
    }
    else // an den exw dei proshmo arnhtiko tote exw dei proshmo 8etiko
    {
        proshmo = 1;
    }

    syntelestes[pos] = proshmo*diavasma_syntelesth(buffer , &j );

    for (int k = j; k < (int)bufferSize ; ++k) { // gia ta ypoloipa grammata tou buffer

        if ( buffer[k] == '+' ) // ean dw + h' - shmainei oti ksekinaei kainourgios oros
            proshmo = 1;
        else
            proshmo = -1;

        pos++; // to pos deixnei gia poion oro milaw
        ++k; //diavasa to + kai paw sto epomeno gramma

        // an yparxei syntelesths
        if( check_if_syntelesths_einai_1(buffer,syntelestes,k,pos,proshmo) != 0 )
        {
            syntelestes[pos] = proshmo * diavasma_syntelesth(buffer , &k);
            k++;
        }

        metavlhth = buffer[k]; //

        ++k; // to buffer deixnei sto meta th metavlhth stoixeio

        if ( buffer[k] == '*' ) { // auto symainei oti h metavlhth einai ypsomenh sthn 1

            if (metavlhth == 'x') {

                xPowers[pos] = 1;
                if (maxXpower < xPowers[pos])
                    maxXpower = xPowers[pos];                       //eisagwgh sthn katallhlh thesi

            }
            else { // periptwsh metavlhth = y

                yPowers[pos] = 1;                         // kai anti gia y^1 na dexetai kai to y
                if (maxYpower < yPowers[pos])
                    maxYpower = yPowers[pos];
            }

            ++k; // paw to deikth sth metavlhth

            metavlhth = buffer[k]; // krataw th metavlhth

            ++k; // paw to deikth sto stoixeio meta th metavlhth

            if( buffer[k] == ' ' || buffer[k] == '+' || buffer[k] == '-' || buffer[k] == '\0' ) // periptwsh pou h 2h metavlhth den eixei dynamh
            {
                if (metavlhth == 'x') {

                    xPowers[pos] = 1;
                    if (maxXpower < xPowers[pos])
                        maxXpower = xPowers[pos];                       //eisagwgh sthn katallhlh thesi

                }
                else { // periptwsh metavlhth = y

                    yPowers[pos] = 1;                         // kai anti gia y^1 na dexetai kai to y
                    if (maxYpower < yPowers[pos])
                        maxYpower = yPowers[pos];
                }

                --k; //meiwnw to k giati 8a auksh8ei apo th for
                continue; // phgaine ston epomeno oro
            }
            else // to y exei dynamh , eida ^
            {
                k++; // paw sto prwto pshfio ths dynamhs

                if (metavlhth == 'x') {

                    xPowers[pos] = diavasma_syntelesth(buffer,&k);
                    if (maxXpower < xPowers[pos])
                        maxXpower = xPowers[pos];                       //eisagwgh sthn katallhlh thesi

                }
                else { // periptwsh metavlhth = y

                    yPowers[pos] = diavasma_syntelesth(buffer,&k);       // kai anti gia y^1 na dexetai kai to y
                    if (maxYpower < yPowers[pos])
                        maxYpower = yPowers[pos];
                }

                --k; //meiwnw to k giati 8a auksh8ei apo th for
                continue; // phgaine ston epomeno oro

            }

        }
        else if( buffer[k] == ' ' || buffer[k] == '+' || buffer[k] == '-' || buffer[k] == '\0' )
        {

            if (metavlhth == 'x') {

                xPowers[pos] = 1;
                if (maxXpower < xPowers[pos])
                    maxXpower = xPowers[pos];                       //eisagwgh sthn katallhlh thesi

            }
            else { // periptwsh metavlhth = y

                yPowers[pos] = 1;                         // kai anti gia y^1 na dexetai kai to y
                if (maxYpower < yPowers[pos])
                    maxYpower = yPowers[pos];
            }

            if( metavlhth == 'x')
                yPowers[pos] = 0;
            else
                xPowers[pos] = 0;

            --k; //meiwnw to k giati 8a auksh8ei apo th for
            continue; // phgaine ston epomeno oro
        }
        else // eida ^ kai diavazw th dynamh ths metavlhths
        {
            k++; // paw sto prwto pshfio ths dynamhs

            if (metavlhth == 'x') {

                xPowers[pos] = diavasma_syntelesth(buffer,&k);
                if (maxXpower < xPowers[pos])
                    maxXpower = xPowers[pos];                       //eisagwgh sthn katallhlh thesi

            }
            else { // periptwsh metavlhth = y

                yPowers[pos] = diavasma_syntelesth(buffer,&k);       // kai anti gia y^1 na dexetai kai to y
                if (maxYpower < yPowers[pos])
                    maxYpower = yPowers[pos];
            }

            if( buffer[k] == ' ' || buffer[k] == '+' || buffer[k] == '-' || buffer[k] == '\0' ) // an dw ena apo auta tote h dynamh ths allhs metavlhths einai 0
            {

                if( metavlhth == 'x')
                    yPowers[pos] = 0;
                else
                    xPowers[pos] = 0;

                --k; //meiwnw to k giati 8a auksh8ei apo th for
                continue;

            }
            else // perimenw na dw *
            {

                k++; // deikse meta to *

                metavlhth = buffer[k]; // apo8hkeuse th metavlhth

                k++; // deikse meta thn epomenh metavlhth

                if( buffer[k] == ' ' || buffer[k] == '+' || buffer[k] == '-' || buffer[k] == '\0' ) // periptwsh pou h 2h metavlhth den eixei dynamh
                {
                    if (metavlhth == 'x') {

                        xPowers[pos] = 1;
                        if (maxXpower < xPowers[pos])
                            maxXpower = xPowers[pos];                       //eisagwgh sthn katallhlh thesi

                    }
                    else { // periptwsh metavlhth = y

                        yPowers[pos] = 1;                         // kai anti gia y^1 na dexetai kai to y
                        if (maxYpower < yPowers[pos])
                            maxYpower = yPowers[pos];
                    }

                    --k; //meiwnw to k giati 8a auksh8ei apo th for
                    continue; // phgaine ston epomeno oro
                }
                else // to y exei dynamh , eida ^
                {
                    k++; // paw sto prwto pshfio ths dynamhs

                    if (metavlhth == 'x') {

                        xPowers[pos] = diavasma_syntelesth(buffer,&k);
                        if (maxXpower < xPowers[pos])
                            maxXpower = xPowers[pos];                       //eisagwgh sthn katallhlh thesi

                    }
                    else { // periptwsh metavlhth = y

                        yPowers[pos] = diavasma_syntelesth(buffer,&k);       // kai anti gia y^1 na dexetai kai to y
                        if (maxYpower < yPowers[pos])
                            maxYpower = yPowers[pos];
                    }

                    --k; //meiwnw to k giati 8a auksh8ei apo th for
                    continue; // phgaine ston epomeno oro

                }

            }

        }

        //teleiwse o oros kai paw ston epomeno

        while( buffer[k] == ' ' && k < bufferSize ) // agnoeise ta kena
            ++k;

        if( k >= bufferSize) // telos eisodou
            break;
        else // vrhka + h' - kai ksekinaei neos oros
            --k; //meiwnw to k giati 8a auksh8ei apo th for

    }

    m.allocate_Table(maxXpower + 1, maxYpower + 1);                     //desmeyoume ton pinaka syntelestwn

    //mhdenizw to pinaka syntelestwn giati 8a gemisw mono merika kommatia tou
    for (int l = 0; l <= maxXpower ; ++l)
        for (int i = 0; i <= maxYpower; ++i)
            m.insert(0,l,i);                                        
    //------------------------------

    //topo8etshsh syntelestwn se pinaka syntlestwn
    for (int i = 0; i <= pos ; ++i) {

        m.insert(syntelestes[i],xPowers[i],yPowers[i]);
    }
    //-------------------------------------------

    m.set_maxXpower(maxXpower);
    m.set_maxYpower(maxYpower);

    if( maxXpower<1 || maxYpower<1 ) // an mia apo tis 2 metavlhtes den yparxei tote to programma den trexei
    {
        cout<< "To programma prepei na periexei akrivws dyo(2) metavlhtes" ;
        cout<<'\n';
        exit(0);
    }

}
