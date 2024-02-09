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
#include <QScrollArea>
#include <QGroupBox>
#include <QScrollBar>
#include <QVBoxLayout>

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

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    ui->passwordLine->setEchoMode(QLineEdit::Password);
    ui->verPasswordLine->setEchoMode(QLineEdit::Password);
    ui->stackedWidget->setCurrentWidget(ui->signUp);

    QFile style;
    style.setFileName("D:/QT/gram/css/style.css");
    style.open(QFile::ReadOnly);
    QString css = style.readAll();
    qApp->setStyleSheet(css);

    int n=20;
    QScrollArea *scroll = new QScrollArea;
    scroll->setParent(ui->mainChat);
    scroll->setGeometry(0,80,200,520);

    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(QPixmap("D:/QT/mmm/css/contactFrame.png")));
    scroll->setPalette(palette);
    scroll->setStyleSheet("border: none;");

    QScrollBar scrollBar;
    scrollBar.setParent(scroll);
    scrollBar.setGeometry(185,0,15,520);

    QWidget* allChats = new QWidget;
    allChats->setParent(scroll);
    allChats->setGeometry(0,0,183,n*60);
    allChats->setPalette(palette);

    QVBoxLayout* layout = new QVBoxLayout(allChats);
    layout->setAlignment(Qt::AlignTop);
    layout->setDirection(QBoxLayout::TopToBottom);
    layout->setSpacing(0);

    for(int i=0;i<n;++i){
        QFrame* chat = new QFrame;
        chat->setParent(scroll);
        chat->setObjectName("chat"+QString::number(n));
        chat->setFixedSize(185,60);
        chat->setStyleSheet("background-color: rgba(200,0,0,0.5);");
        QLabel photo(chat);
        photo.setParent(chat);
        photo.setPixmap(QPixmap("D:/QT/gram/css/busov.png"));
        photo.setGeometry(5,5,30,50);
        layout->addWidget(chat);
    }
    layout->setContentsMargins(0,0,0,0);
    allChats->setLayout(layout);
    allChats->show();
    scroll->setWidget(allChats);

    connect(this, SIGNAL(connectReady()), this, SLOT(connectServer()));
    connect(this, SIGNAL(connectDone()), this, SLOT(connectAnswer()));
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

void MainWindow::connectAnswer() {
    Chat chat;
    QString answer = chat.backData;
    qDebug()<<answer;
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
    //ui->stackedWidget->setCurrentWidget(ui->mainChat);
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


