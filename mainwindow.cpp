#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sendmessage.h"

#include <QWidget>
#include <QFile>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QSettings>
#include <QPoint>
#include <QMouseEvent>

QString error[] = {
    "Username and/or password is not correct. Please try again.",
    "Cannot connect to server. Please try again later.",
    "Please enter username and password.",
    "Username already taken. Please try again.",
    "Passwords do not match. Please try again.",
    "Please confirm password.",
    "Username cannot contain spaces. Please try again.",
    "Error occured. Please restart the program."
};
QString debug[] = {
    "Main chat has been opened",
    "Connection to the server...",
    "Connection started",
    "Connection done",

};
QString sockets[] = {
    "Connection has been successfully established",
    "This username is already taken, try again",
    "You are already signed up, log in"
};

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow),conManager(new QNetworkAccessManager(this)) {

    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    ui->stackedWidget->setCurrentWidget(ui->signUp);

    QFile style;
    style.setFileName("D:/QT/mmm/css/style.css");
    style.open(QFile::ReadOnly);
    QString css = style.readAll();
    qApp->setStyleSheet(css);

    connect(this, SIGNAL(connectReady()),this, SLOT(connectServer()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::sendMessage(){ //ЗАКОНЧИТЬ ВОТ ТУТ БОЛЕЕ ПРАВИЛЬНЫЕ ПЕРЕМЕННЫЕ И ТД
    SendMessage date;
    QNetworkRequest messageRequest;
    json date1;
    date1 = date.reqdate();
    QByteArray regdata;
    regdata.append(date1.is_array());
    manager = new QNetworkAccessManager(this);
    manager->post(messageRequest,regdata);

}

void MainWindow::connectServer() {
    QByteArray regdata;
    regdata.append("username="+ui->logLine->text().toUtf8());
    regdata.append("&");
    regdata.append("password="+ui->passwordLine->text().toUtf8());

    //создание объекта менеджера для работы с пост запросами
    conManager = new QNetworkAccessManager(this);

    QUrl url("https://ec8d-95-105-74-45.ngrok-free.app/api/v1/sign_up/");
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader( QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded" );

    //settings.setValue("endpoint_url"," ");
    connect(conManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(connectAnswer(QNetworkReply*)));
    conManager->post(request,regdata);
}

void MainWindow::connectAnswer(QNetworkReply *reply) {
    QByteArray answer = reply->readAll();
    qDebug()<<answer;
    reply->close();
    if(answer == sockets[1]){
        ui->conLabel->setText(sockets[1]);
    }
    else if (answer == sockets[2]){
        ui->conLabel->setText(sockets[2]);
    }
    else if (answer == sockets[0]){
        ui->stackedWidget->setCurrentWidget(ui->mainChat);
        qDebug()<<debug[0];
    }
    ui->stackedWidget->setCurrentWidget(ui->mainChat);
}

void MainWindow::on_conButton_clicked() {
    QString userName = " ", password = " ", vPassword = " ";
    userName=ui->logLine->text();
    password=ui->passwordLine->text();
    vPassword=ui->verPasswordLine->text();
    if(userName.isEmpty() || password.isEmpty()){
        ui->conLabel->setText(error[2]);
    }
    else if(vPassword.isEmpty()){
        ui->conLabel->setText(error[5]);
    }
    else{
        if(password.length() != vPassword.length()){
            ui->conLabel->setText(error[4]);
        }
        else{
            if(password != vPassword){
                ui->conLabel->setText(error[4]);
            }
            else{
                emit connectReady();
            }
        }
    }
}

void MainWindow::on_closeButton_clicked() {
    this->close();
}


void MainWindow::on_hideButton_clicked() {
    this->showMinimized();
}

void MainWindow::on_showButton_clicked() {
    if(this->isFullScreen()) {
        this->showNormal();
    }
    else {
        this->showFullScreen();
    }
}


