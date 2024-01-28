#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWidget>
#include <QFile>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QSettings>
#include <QByteArray>

QString error[] = {
    "Username and/or password is not correct. Please try again.",
    "Cannot connect to server. Please try again later.",
    "Please enter username and password.",
    "Username already taken. Please try again.",
    "Passwords do not match. Please try again.",
    "Please confirm password.",
    "Username cannot contain spaces. Please try again.",
    "User already logged in.",
    "Error occured. Please restart the program."
};
QString debug[] = {
    "Window closed",
    "Window hidden",
    "Window max",
    "Window normal"
};
QString sockets[]{
    "Connection to the server..."
};

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow),manager(new QNetworkAccessManager(this)) {
    //установка исходного виджета !!!ТУТ НУЖНА СЕССИЯ ЧТОБЫ ПОНИМАТЬ ЧТО ВКЛЮЧАТЬ!!!
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->signUp);

    //безрамочный режим тупо лучше свои сделать кнопки
    setWindowFlags(Qt::FramelessWindowHint);

    //css стиль можно установить вообще на всё в файле так тупо легче
    QFile style;
    style.setFileName("D:/QT/mmm/css/style.css");
    style.open(QFile::ReadOnly);
    QString css = style.readAll();
    qApp->setStyleSheet(css);

    //установил на пароли хуйню с точками так полезно
    ui->passwordLine->setEchoMode(QLineEdit::Password);
    ui->verPasswordLine->setEchoMode(QLineEdit::Password);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_conButton_clicked() {
    //проверка паролей на сходство и юзернейма
    QString usName = " ", password = " ", vPassword = " ";
    usName=ui->logLine->text();
    password=ui->passwordLine->text();
    vPassword=ui->verPasswordLine->text();
    for(int i=0;i<password.length();++i){
        if(password.length()>vPassword.length() || password.length()<vPassword.length()){
            ui->conLabel->setText(error[4]);
        }
        else if(password.at(i)!=vPassword.at(i)){
            ui->conLabel->setText(error[4]);
        }
        else{
            ui->conLabel->setText(sockets[0]);

            //создание объекта менеджера для работы с пост запросами
            manager = new QNetworkAccessManager(this);
            QUrl url(); //НАДО ДОБАВИТЬ АДРЕС!!!!!!!!!!!!!!!!!!!!!!!!!
            QNetworkRequest request;
            QByteArray regdata;
            regdata.append("username="+ui->logLine->text().toUtf8());
            regdata.append("password="+ui->passwordLine->text().toUtf8());

            manager->post(request,regdata);
        }
    }

    //ui->stackedWidget->setCurrentWidget(ui->mainChat);
}


void MainWindow::on_closeButton_clicked() {
    this->close();
    qDebug()<<debug[0];
}


void MainWindow::on_hideButton_clicked(){
    this->showMinimized();
    qDebug()<<debug[1];
}

void MainWindow::on_showButton_clicked(){
    if(this->isFullScreen()){
        this->showNormal();
        qDebug()<<debug[3];
    } else {
        this->showFullScreen();
        qDebug()<<debug[2];
    }
}
