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
#include <QMessageBox>

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
    ui->stackedWidget->setCurrentWidget(ui->signUp);
    setWindowFlags(Qt::FramelessWindowHint);

    QFile style;
    style.setFileName("D:/QT/mmm/css/signStyle.css");
    style.open(QFile::ReadOnly);
    QString css = style.readAll();
    qApp->setStyleSheet(css);

    //установил на пароли хуйню с точками так полезно
    ui->passwordLine->setEchoMode(QLineEdit::Password);
    ui->verPasswordLine->setEchoMode(QLineEdit::Password);

    //все коннкеторы связнные с окном регистрации
    connect(this, SIGNAL(connectReady()),this, SLOT(connectServer()));

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openChat() {
    ui->stackedWidget->setCurrentWidget(ui->mainChat);
}

void MainWindow::connectServer() {
    QByteArray regdata;
    regdata.append("username="+ui->logLine->text().toUtf8());
    regdata.append("&");
    regdata.append("password="+ui->passwordLine->text().toUtf8());

    //создание объекта менеджера для работы с пост запросами
    conManager = new QNetworkAccessManager(this);

    QUrl url("https://bb96-95-105-74-45.ngrok-free.app/api/v1/");
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader( QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded" );

    //settings.setValue("endpoint_url"," ");

    conManager->post(request,regdata);
    connect(conManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(connectAnswer(QNetworkReply*)));
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
        openChat();
        qDebug()<<debug[0];
    }
    openChat();
}

void MainWindow::on_conButton_clicked() {
    //проверка паролей на сходство и юзернейма
    QString userName = " ", password = " ", vPassword = " ";//переменная юзернейма совершенно не нужна тк не используется в проверке, проверка будет на сервере
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
