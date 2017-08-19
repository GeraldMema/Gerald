#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QString>
#include "visualization.h"
#include "ui_visualization.h"
#include "QPoint"

using namespace std;

Visualization::Visualization(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Visualization)
{
    ui->setupUi(this);
    widget = new QtGnuplotWidget();
    widget->installEventFilter(this);
    widget->setStatusLabelActive(true);
    instance = new QtGnuplotInstance();
    instance->setWidget(widget);

    secondwidget = new QtGnuplotWidget();
    secondwidget->installEventFilter(this);
    secondwidget->setStatusLabelActive(true);
    secondinstance = new QtGnuplotInstance();
    secondinstance->setWidget(secondwidget);

    pointsCounter = 0;
    points2Counter = 0;
    isSecondSetOfPoints = 0;
    points = NULL;
    points2 = NULL;

    // default times gia metavlhtes input
    x_range_from = -1;
    x_range_until = 1;
    y_range_from = -10;
    y_range_until = 10;
    //-----------------------------------

    have_read_file = 0;

}

Visualization::~Visualization()
{
    delete ui;
    delete instance;
    delete widget;

    delete secondinstance;
    delete secondwidget;

    if( points != NULL )
    {
        for (int i = 0; i < pointsCounter; ++i) {
            delete[] points[i];
        }
        delete[] points;
    }

    if( points2 != NULL )
    {
        for (int i = 0; i < points2Counter; ++i) {
            delete[] points2[i];
        }
        delete[] points2;
    }

}
/*
 *rythmizoume thn eisodo gia to d2 (megistovathmios vathmos 2ou poluwnymou)
 */

void Visualization::on_d2_returnPressed()
{

    QString input = ui->d2->text();

    bool ok;

    d2_int_input = input.toInt(&ok,10);

    if( ok )
    {
        ui->outputTxt->append( ui->d2->text() );
    }
    else
    {
        ui->outputTxt->append("Not acceptable d2 , please change input");
        ui->d2->clear();
    }

}

/*
 *rythmizoume thn eisodo gia to d1 (megistovathmios vathmos 1ou poluwnymou)
 */
void Visualization::on_d1_returnPressed()
{

    QString input = ui->d1->text();

    bool ok;

    d1_int_input = input.toInt(&ok,10);

    if( ok )
    {
        ui->outputTxt->append( ui->d1->text() );
    }
    else
    {
        ui->outputTxt->append("Not acceptable d1 , please change input");
        ui->d1->clear();
    }

}

/*
 * Ftiaxnoume to eyros gia ton thetiko(pano) aksona y
 */
void Visualization::on_Y_range_until_returnPressed()
{

    QString input = ui->Y_range_until->text();

    bool ok;

    y_range_until = input.toDouble(&ok);

    if( ok )
    {
        ui->outputTxt->append( ui->Y_range_until->text() );
    }
    else
    {
        ui->outputTxt->append("Not acceptable y_range_until , value set to 10");
        y_range_until = 10;
    }

}

/*
 * Ftiaxnoume to eyros gia ton arnhtiko(katw) aksona y
 */
void Visualization::on_Y_range_from_returnPressed()
{
    QString input = ui->Y_range_from->text();

    bool ok;

    y_range_from = input.toDouble(&ok);

    if( ok )
    {
        ui->outputTxt->append( ui->Y_range_from->text() );
    }
    else
    {
        ui->outputTxt->append("Not acceptable y_range_from , value set to -10");
        y_range_from = -10;
    }
}

/*
 * Ftiaxnoume to eyros gia ton thetiko(deksio) aksona x
 */
void Visualization::on_X_range_until_returnPressed()
{

    QString input = ui->X_range_until->text();

    bool ok;

    x_range_until = input.toDouble(&ok);

    if( ok )
    {
        ui->outputTxt->append( ui->X_range_until->text() );
    }
    else
    {
        ui->outputTxt->append("Not acceptable x_range_until , value set to 1");
        x_range_until = 1;
    }

}

/*
 * Ftiaxnoume to eyros gia ton arnhtiko(aristero) aksona y
 */
void Visualization::on_X_range_from_returnPressed()
{
    QString input = ui->X_range_from->text();

    bool ok;

    x_range_from = input.toDouble(&ok);

    if( ok )
    {
        ui->outputTxt->append( ui->X_range_from->text() );
    }
    else
    {
        ui->outputTxt->append("Not acceptable x_range_from , value set to -1");
        x_range_from = -1;
    }

}

void Visualization::on_actionExit_triggered()
{
    qApp->quit();
}

/*
 * parser gia pragmatikous syntelestes
 */
double Visualization::str_to_double(char * num)
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
    double diaireths = 10;

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


/*
 *Diavazoume kai Apothikeyoume ta shmeia sta poionts
 */
void Visualization::read_points_from_file(ifstream & myfile , double ** points , int pointsCounter)
{

    char x[50],y[50];

    int pos = 0;

    while( pos < pointsCounter )
    {
        myfile >> x;

        if( strcmp(x,"\n") == 0 )
            break;

        int x_pos = 0;

        while( x[x_pos] != '\0')
            ++x_pos;

        x[x_pos-1] = '\0'; // gia na vgalw to comma

        points[pos][0] = str_to_double(x);

        myfile >> y ;

        points[pos][1] =  str_to_double(y);

        ++pos;

    }

}

/*
 * paragei kai sxediazei to arxeio pou 8a ginei plot apo th gnuplot
 */
void Visualization::on_Plot_equations_clicked()
{

    widget->show();
    widget->resize(QSize(800,600));

    fstream gnuFile;
    fstream file;
    string line;
    ostringstream value;

    gnuFile.open("ploting_form.txt", ios_base::in | ios_base::out);
    file.open("ploting_form.txt", ios_base::out | ios_base::in);

    size_t pos_in_file = 0;

    getline(gnuFile,line);
    pos_in_file += line.length() + 1 ; // to +1 einai gia to \n
    getline(gnuFile,line);
    pos_in_file += line.length() + 1 ; // to +1 einai gia to \n

    file.seekp(pos_in_file,ios_base::beg);

    file << "set contour base \n"
            "set cntrparam levels discrete 0.0 \n"
            "unset surface \n"
            "set table 'curve.dat' \n"
            "splot f(x,y) \n"
            "replot g(x,y) \n"
            "unset table \n"
            "set yrange[";
    value.str("");
    value.clear();
    value << y_range_from;
    file << value.str();
    file << ":";
    value.str("");
    value.clear();
    value << y_range_until;
    file << value.str();
    file << "] \n"
            "set xrange[";
    value.str("");
    value.clear();
    value << x_range_from;
    file << value.str();
    file << ":";
    value.str("");
    value.clear();
    value << x_range_until;
    file << value.str();
    file << "] \n"
            "plot 'curve.dat' w l \n";

    gnuFile.close();
    file.close();

    *instance << "load \"ploting_form.txt\"\n"
                 "replot 'solutions.txt'\n";

    if( ypologisaKaiTis2Lyseis == 1 )//periptwsh pou kanw allaghmetavlhths ypologizw kai tis 2 luseis
    {
        secondwidget->show();
        secondwidget->resize(QSize(800,600));

        *secondinstance << "load \"ploting_form.txt\"\n"
                           "replot 'solutions2.txt'\n";
    }

}


/*
 * Topo8etei katallhla oria sthn emfanish twn lysewn apo th gnuplot prokeimenou na symperilamvanontai oi rizes
 */
void Visualization::generate_Solutions_file(char * filename,double ** solutions ,int solutionsNumber)
{

    ofstream file; // anoigw to arxeio pou 8a zwgrafisei h gnuplot
    string line; // grammh/grammes pou 8a ektypw8oun sto outputTxt

    string str; // metavlhth pou xrhsimopoieitai sthn ektypwsh twn lysewn
    char num[100];

    file.open(filename, ios_base::out | ios_base::trunc);

    str = "\nFound ";
    sprintf(num,"%d",solutionsNumber);
    str.append( num );
    str.append(" solutions : \n");
    ui->outputTxt->append(str.c_str());


    // arxeikopoihse ta oria
    double min_x = solutions[0][0];
    double max_x = solutions[0][0];
    double min_y = solutions[0][1];
    double max_y = solutions[0][1];
    //----------------------

    //euresh katallhlwn oriwn gia ektypwsh kai ektypwnei tis lyseis sto para8yro
    for (int i = 0; i < solutionsNumber; ++i)
    {

        if( solutions[i][0] < min_x )
            min_x = solutions[i][0];
        if( solutions[i][0] > max_x)
            max_x = solutions[i][0];
        if( solutions[i][1] < min_y )
            min_y = solutions[i][1];
        if( solutions[i][1] > max_y )
            max_y = solutions[i][1];

        std::ostringstream x , y;

        x << solutions[i][0];
        std::string x_str = x.str();

        y << solutions[i][1];
        std::string y_str = y.str();

        file << x_str ;
        file << ", ";
        file << y_str;
        file << '\n';

        // printing solutions
        line = "x = ";
        line.append(x_str.c_str() );
        line.append(" , y = ");
        line.append(y_str.c_str());

        ui->outputTxt->append(line.c_str());
        //--------------------

    }
    //dimiourgoume to katallhlo euros gia thn apoikonish ths grafikhs parastashs
    x_range_from = min_x - 10;
    x_range_until = max_x + 10;
    y_range_from = min_y - 10;
    y_range_until = max_y + 10;

    file.close();

}

/*
 * Diavasma apo ta arxeia points.txt kai points2.txt ta shmeia twn lysewn antistoixa
 *  gia na perastoun ston Handler
 */
void Visualization::generate_Points()
{

    ifstream myfile;

    // diavasma kai apo8hkeush gia to prwto set apo points
    myfile.open( "points.txt", std::ifstream::in );

    points = new double * [pointsCounter];

    for (int i = 0; i < pointsCounter; ++i) {
        points[i] = new double[2];
    }

    read_points_from_file(myfile,points , pointsCounter);

    myfile.close();
    //----------------------------------------------------

    //diavasma kai apo8hkeush gia to deutero set apo points
    myfile.open( "points2.txt", std::ifstream::in );

    points2 = new double * [points2Counter];

    for (int i = 0; i < points2Counter; ++i) {
        points2[i] = new double[2];
    }

    read_points_from_file(myfile,points2 , points2Counter);
    myfile.close();
    //-----------------------------------------------------

}

/*
 * Xeirizetai th periptwsh pou h eisodos htan arxeio
 */
int Visualization::handle_read_from_file(Handler & handler )
{

    handler.read((char*)filename.c_str()); // kalese th synarthsh read me to onoma tou arxeiou pou do8hke

    handler.generate_Sylvester(); // parhgage ton sylvester

    handler.generate_Polywnymo_Mhtrwwn(); // parhgage to polywnymo mhtrwwn

    int error;

    error = handler.solve(); // Lyse to provlhma

    if( error == 1 )
    {
        ui->outputTxt->append( "Sylvester tautotika 0" );
        return error;
    }

    ypologisaKaiTis2Lyseis = handler.get_allaksaMetavlhth(); // elegkse an to provlhma ly8hke me generalized kai me Companion

    generate_Ploting_form(); // parhgage to arxeio pou 8a zwgrafisei h gnuplot

    handle_generate_solutions_file(handler); // kanei kapoies aparaithtes metatropes sto arxeio pou zwgrafizei h gnuplot

    return 0; // ola phgan kala epestrepse 0

}
/*
 * dimiourgeite to arxeio pou periexei ts luseis
 */
int Visualization::handle_generate_solutions_file(Handler &handler)
{
    double ** solutions;
    int solutionsNumber;

    // elegxw ean ypologisa tis lyseis kai me tous 2 tropous gia na kanw kai to antistoixo visualize
    if( ypologisaKaiTis2Lyseis == 1)
    {

        solutions = handler.get_solutionsWIthGeneralized(); // pare tis lyseis
        solutionsNumber = handler.get_solutionsWIthGeneralized_i();

        generate_Solutions_file((char*)"solutions2.txt",solutions,solutionsNumber); // grapse tis lyseis se arxeio

    }

    solutions = handler.get_solutions(); // pare tis lyseis
    solutionsNumber = handler.get_solutions_i();

    generate_Solutions_file((char*)"solutions.txt",solutions,solutionsNumber); // grapse tis lyseis se arxeio

    return 0;

}

/*
 * Diaxeirizetai to daivasma kai th paragwgh arxeiwn me tis lyseis x,y
 */
int Visualization::handle_read_points( Handler & handler)
{

    generate_Points(); // diavasma twn shmeiwn apo ta arxeia

    int error = handler.handle_Points(points,points2,pointsCounter,points2Counter,d1_int_input,d2_int_input); // douleuei mono gia 5 shmeia me d = 2

    if( error != 0 )
    {
        if( error == 1 )
        {
            ui->outputTxt->append( "Sylvester tautotika 0" );
        }
        return error;
    }

    ypologisaKaiTis2Lyseis = handler.get_allaksaMetavlhth();

    handle_generate_solutions_file(handler);// paragei katallhla arxeio/arxeia me tis lyseis

    return 0;
}

void Visualization::on_Solve_clicked()
{

    int error;

    Handler handler;

    string line ;  // metavlhth pou me voh8aei na kanw ektypwseis sto outputTxT

    if( have_read_file == 1 )
    {

        error = handle_read_from_file(handler);

        if( error != 0 )
            return;

        handler.print(); // grafei to Md sto line tou handler

        line = handler.get_line();

        ui->outputTxt->append( line.c_str() );

        return;

    }

    error = handle_read_points(handler);

    if( error != 0 ) // kati den phge kala sto diavasma twn points
    {

        line = handler.get_line();

        ui->outputTxt->append( line.c_str() );

        return;

    }

    handler.print(); // grafei thn eksodo sto line tou handler

    line = handler.get_line();

    ui->outputTxt->append( line.c_str() );

}

/*
 * paragei to arxeio ploting_form diavazontas tis synarthseis apo to arxeio pou edwse o xrhsths
 */
void Visualization::generate_Ploting_form()
{
    fstream from;
    fstream to;
    string line;

    from.open (filename.c_str(), ios_base::in | ios_base::out ); // in kai out gia na mhn ginontai trunced
    to.open ("ploting_form.txt", ios_base::in | ios_base::out );

    getline(from,line);

    // antikatestise to ^ me **
    for (int i = 0; i < (int)line.length(); ++i)
    {

        if( line[i] == '^')
        {
            line.replace(i,1,"*");
            line.insert(i,"*");
        }

    }
    //---------------------------

    to << "f(x,y)= ";
    to << line;
    to << '\n';

    getline(from,line); // pare th grammh

    // antikatestise to ^ me **
    for (int i = 0; i < (int)line.length(); ++i)
    {

        if( line[i] == '^')
        {
            line.replace(i,1,"*");
            line.insert(i,"*");
        }

    }
    //---------------------------

    to << "g(x,y)= ";
    to << line;

    to << "\nset contour base \n"
                  "set cntrparam levels discrete 0.0 \n"
                  "unset surface \n"
                  "set table 'curve.dat' \n"
                  "splot f(x,y) \n"
                  "replot g(x,y) \n"
                  "unset table \n"
                  "set yrange[-30:30] \n"
                  "set xrange[-3:3] \n"
                  "plot 'curve.dat' w l \n";

    return;

}

/*
 * Diavazei arxeio pou dinetai apo to ui krataei to onoma tou kai kanei set ena flag oti egine diavasma apo arxeio
 */
void Visualization::on_actionOpen_triggered()
{

    have_read_file = 0; // mhdenizetai to flag oti exw diavasei arxeio

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                tr("All Files (*.*)"));

    if (!fileName.isEmpty()) {

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }

        QTextStream in(&file);

        QString str = in.readAll();

        ui->equationsTxt->setText(str);

        file.close();

        filename = fileName.toStdString(); // krataw to onoma tou arxeiou pou exei dw8ei gia anoigma

        have_read_file = 1; // set read flag = 1

    }
}

/*
 * Apo8hkeush twn shmeiwn ths prwths kai ths 2hs ekshswshs to arxeio points.txt kai points2.txt antistoixa
 */
bool Visualization::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (obj == this->widget) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                ui->outputTxt->append( this->widget->getStatusLabel()->text() );

                if( isSecondSetOfPoints == 1) // ean dinw to 2o set shmeiwn
                {
                    myfile.open( "points2.txt", ios_base::app );
                    points2Counter++;

                    *instance << "load 'Points_gnu_commands.txt'\n"
                                 "plot 'points2.txt' \n";
                }
                else
                {
                    myfile.open( "points.txt", ios_base::app );
                    pointsCounter++;

                    *instance << "load 'Points_gnu_commands.txt'\n"
                                 "plot 'points.txt'\n";
                }

                myfile << this->widget->getStatusLabel()->text().toStdString() ;
                myfile << "\n";
                myfile.close();

            }
        }
    }

    return QObject::eventFilter(obj, event);
}


int Visualization::reset_ranges()
{

    on_X_range_from_returnPressed();
    on_X_range_until_returnPressed();
    on_Y_range_from_returnPressed();
    on_Y_range_until_returnPressed();

    return 0;

}

void Visualization::on_Insert_2nd_points_clicked()
{

    have_read_file = 0;

    reset_ranges();

    myfile.open("points2.txt" , ios_base::trunc );
    myfile.close();

    points2Counter = 0;

    isSecondSetOfPoints = 1;

    ofstream gnuFile;

    gnuFile.open("Points_gnu_commands.txt" , ios_base::out | ios_base::trunc );

    gnuFile << "set tics scale 0.75\n"
               "set xtics 1\n"
               "set ytics 1\n"
               "set yrange [";
    gnuFile << y_range_from ;
    gnuFile << ':';
    gnuFile << y_range_until;
    gnuFile <<"]\n";
    gnuFile <<"set xrange [";
    gnuFile << x_range_from ;
    gnuFile << ':';
    gnuFile << x_range_until;
    gnuFile <<"]\n"
              "set xlabel 'x-axis'\n"
               "set ylabel 'y-axis'\n"
               "set zeroaxis\n"
               "plot 'points2.txt'\n";
    gnuFile.close();

    widget->show();
    widget->resize(QSize(800,600));

    *instance << "load 'Points_gnu_commands.txt'\n";

}


/*
 * Paragwgh arxeiou me katallhla ranges gia thn eisodo twn shmeiwn kai anoigei to para8yro ths gnuplot
 */
void Visualization::on_Insert_points_clicked()
{

    have_read_file = 0;

    reset_ranges();

    myfile.open("points.txt" ,ios_base::out | ios_base::trunc );
    myfile.close();

    pointsCounter = 0;
    isSecondSetOfPoints = 0;

    ofstream gnuFile;

    gnuFile.open("Points_gnu_commands.txt" , ios_base::out | ios_base::trunc );

    gnuFile << "set tics scale 0.75\n"
               "set xtics 1\n"
               "set ytics 1\n"
               "set yrange [";
    gnuFile << y_range_from ;
    gnuFile << ':';
    gnuFile << y_range_until;
    gnuFile <<"]\n";
    gnuFile <<"set xrange [";
    gnuFile << x_range_from ;
    gnuFile << ':';
    gnuFile << x_range_until;
    gnuFile <<"]\n"
              "set xlabel 'x-axis'\n"
               "set ylabel 'y-axis'\n"
               "set zeroaxis\n"
               "plot 'points.txt'\n";

    gnuFile.close();

    widget->show();
    widget->resize(QSize(800,600));

    *instance << "load 'Points_gnu_commands.txt'\n";
}
