#include "mainfenetre.h"
#include "ui_mainfenetre.h"

MainFenetre::MainFenetre(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainFenetre)
{
    ui->setupUi(this);
}

MainFenetre::~MainFenetre()
{
    delete ui;
}
