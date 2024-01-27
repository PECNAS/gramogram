#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWidget>
#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//безрамочный режим тупо лучше свои сделать кнопки

    //css стиль можно установить вообще на всё в файле так тупо легче
    QFile style;
    style.setFileName("D:/QT/mmm//css/style.css");
    style.open(QFile::ReadOnly);
    QString css = style.readAll();
    qApp->setStyleSheet(css);

    ui->passwordLine->setEchoMode(QLineEdit::Password);
    ui->verPasswordLine->setEchoMode(QLineEdit::Password);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_conButton_clicked() {

    QString usName = " ", password = " ", vPassword = " ";
    usName=ui->logLine->text();
    password=ui->passwordLine->text();
    vPassword=ui->verPasswordLine->text();

    for(int i=0;i<password.length();++i){
        if(password.length()>vPassword.length() || password.length()<vPassword.length() ){
            ui->conLabel->setText("Password must match");
        }
        else if(password.at(i)!=vPassword.at(i)){
            ui->conLabel->setText("Password must match");
        }
        else{
            ui->conLabel->setText("KaiF");
        }
    }

    //ui->stackedWidget->setCurrentWidget(ui->mainChat);
}


void MainWindow::on_closeButton_clicked() {
    qDebug()<<"Window closed!";
    this->close();
    this->~MainWindow();
    delete ui;
}


void MainWindow::on_hideButton_clicked(){
    setWindowState(windowState() & ~Qt::WindowActive | Qt::WindowMinimized);
}


void MainWindow::on_showButton_clicked(){
    if(this->isFullScreen()){
        this->showNormal();
    } else {
        this->showFullScreen();
    }
}


