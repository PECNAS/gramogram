#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chat.h"

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
#include <QPalette>

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
    ui->passwordLine->setEchoMode(QLineEdit::Password);
    ui->verPasswordLine->setEchoMode(QLineEdit::Password);
    ui->stackedWidget->setCurrentWidget(ui->signUp);

    QFile style;
    style.setFileName("D:/QT/mmm/css/style.css");
    style.open(QFile::ReadOnly);
    QString css = style.readAll();
    qApp->setStyleSheet(css);


    connect(this, SIGNAL(connectReady()), this, SLOT(connectServer()));
    connect(ui->conButton, SIGNAL(clicked()), this, SLOT(connectionButton()));
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(closeButton()));
    connect(ui->showButton, SIGNAL(clicked()), this, SLOT(showButton()));
    connect(ui->hideButton, SIGNAL(clicked()), this, SLOT(hideButton()));
    connect(ui->closeButtonM, SIGNAL(clicked()), this, SLOT(closeButton()));
    connect(ui->showButtonM, SIGNAL(clicked()), this, SLOT(showButton()));
    connect(ui->hideButtonM, SIGNAL(clicked()), this, SLOT(hideButton()));
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::sendMessage(){
    QUrl url("https://5889-95-105-74-45.ngrok-free.app/api/v1/new_msg/");
    QNetworkRequest messageRequest;
    messageRequest.setUrl(url);
    QByteArray message;
    Chat dateJson;

    qDebug()<<dateJson.Chat::reqdate(ui->contactLabel->text().toUtf8().toStdString(), ui->logLine->text().toUtf8().toStdString(),ui->sendLine->text().toUtf8().toStdString());
    message.append(
        dateJson.Chat::reqdate(
            ui->logLine->text().toStdString(),
            ui->contactLabel->text().toStdString(),
            ui->sendLine->text().toStdString()
        )
    );
    manager = new QNetworkAccessManager(this);
    manager->post(messageRequest,message);

}

void MainWindow::connectServer() {
    QByteArray regdata;
    regdata.append("username="+ui->logLine->text().toUtf8());
    regdata.append("&");
    regdata.append("password="+ui->passwordLine->text().toUtf8());

    //создание объекта менеджера для работы с пост запросами
    conManager = new QNetworkAccessManager(this);

    QUrl url1("https://5889-95-105-74-45.ngrok-free.app/api/v1/sign_up/");
    QNetworkRequest request;
    request.setUrl(url1);
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

void MainWindow::connectionButton() {
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

void MainWindow::closeButton() {
    this->close();
}


void MainWindow::hideButton() {
    this->showMinimized();
}

void MainWindow::showButton() {
    if(this->isFullScreen()) {
        this->showNormal();
    }
    else {
        this->showFullScreen();
    }
}


