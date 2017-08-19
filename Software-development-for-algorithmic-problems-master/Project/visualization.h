#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <QMainWindow>
#include <QtGnuplot/QtGnuplotWidget.h>
#include <QtGnuplot/QtGnuplotInstance.h>

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include "solve.h"

namespace Ui {
class Visualization;
}

class Visualization : public QMainWindow
{
    Q_OBJECT

public:
    explicit Visualization(QWidget *parent = 0);
    ~Visualization();


private:

    QtGnuplotWidget *widget; // gia xeirismo para8yrou
    QtGnuplotInstance *instance; // gia na dinw entoles sth gnuplot

    QtGnuplotWidget *secondwidget;
    QtGnuplotInstance *secondinstance;

    // metavlhtes kai synarthseis pou exoume orisei emeis
    std::ofstream myfile;

    double ** points,**points2;
    int pointsCounter;
    int points2Counter;
    int isSecondSetOfPoints;

    // metavlhtes gia to input

    double x_range_from;
    double x_range_until;

    double y_range_from;
    double y_range_until;

    int d1_int_input;
    int d2_int_input;

    int have_read_file;

    int ypologisaKaiTis2Lyseis;

    string filename;

    //++++++++++++++++++++++++

    void read_points_from_file(ifstream & myfile, double **points, int pointsCounter);

    double str_to_double(char * num);

    void generate_Solutions_filegenerate_Solutions_file(char * filename,double ** solutions ,int solutionsNumber);

    void generate_Points();

    void generate_Ploting_form();

    //-----------------------------------------------------

protected:
    bool eventFilter(QObject *obj, QEvent *event);


private slots:
    void on_actionExit_triggered();

    void on_actionOpen_triggered();

    void on_Insert_points_clicked();

    void on_Insert_2nd_points_clicked();

    void on_Solve_clicked();

    void on_Plot_equations_clicked();

    void on_X_range_from_returnPressed();

    void on_X_range_until_returnPressed();

    void on_Y_range_from_returnPressed();

    void on_Y_range_until_returnPressed();

    void on_d1_returnPressed();
    void on_d2_returnPressed();

private:
    Ui::Visualization *ui;
    int handle_read_from_file(Handler &handler);
    int handle_read_points(Handler &handler);
    int handle_generate_solutions_file(Handler &handler);
    void generate_Solutions_file(char *filename, double **solutions, int solutionsNumber);
    int reset_ranges();
};

#endif // VISUALIZATION_H
