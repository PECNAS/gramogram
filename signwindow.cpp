#include "signwindow.h"
#include "ui_signwindow.h"
#include "QDebug"
signWindow::signWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::signWindow) {
    ui->setupUi(this);

}

signWindow::~signWindow()
{
    delete ui;
}


