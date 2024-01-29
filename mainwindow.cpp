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
#include <QMessageBox>
#include <QUrlQuery>

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
QString sockets[] = {
    "Connection to the server...",
    "Connection started",
    "Cpnnection continuing",
    "Connection done"
};

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow),conManager(new QNetworkAccessManager(this)) {
    //установка исходного виджета !!!ТУТ НУЖНА СЕССИЯ ЧТОБЫ ПОНИМАТЬ ЧТО ВКЛЮЧАТЬ!!!
    ui->setupUi(this);//добавить трекинг за верхней областью окна, дабы можно было двигать
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

    //все коннкеторы связнные с окном регистрации
    connect(ui->conButton, SIGNAL(clicked()),SLOT(on_conButton_clicked()));//бесполезный коннектор тк есть функция баттон клик, но убрать
    connect(ui->conButton, SIGNAL(connectReady()),SLOT(connectServer()));
    connect(conManager,SIGNAL(finished()), SLOT(connectAnswer(QNetworkReply*)));

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::connectServer() {
    //создание объекта менеджера для работы с пост запросами
    conManager = new QNetworkAccessManager(this);

    QUrl url; //НАДО ДОБАВИТЬ АДРЕС!!!!!!!!!!!!!!!!!!!!!!!!!
    QNetworkRequest request(url);// можно сделать более читабельным ссылка на stackOverflow в тг вечером почитать
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QByteArray regdata;
    regdata.append("username="+ui->logLine->text().toUtf8());
    regdata.append("password="+ui->passwordLine->text().toUtf8());

    conManager->post(request,regdata);
    qDebug()<<sockets[1];
    emit finished(); //иммитируем сигнал финиш ответа дабы понять работает или нет
}

void MainWindow::connectAnswer(QNetworkReply *reply) {
    qDebug()<<sockets[2];
    QByteArray answer = reply->readAll();
    QMessageBox::information(this,"Ответ от сервера:",QString::fromUtf8(answer),QMessageBox::Ok);
    reply->close();
    qDebug()<<sockets[3];
}



void MainWindow::on_conButton_clicked() {
    //проверка паролей на сходство и юзернейма
    QString usName = " ", password = " ", vPassword = " ";//переменная юзернейма совершенно не нужна тк не используется в проверке, проверка будет на сервере
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
            emit connectReady();
        }
    }

    //ui->stackedWidget->setCurrentWidget(ui->mainChat);
}

void MainWindow::on_closeButton_clicked() {
    this->close();
    qDebug()<<debug[0];
}


void MainWindow::on_hideButton_clicked() {
    this->showMinimized();
    qDebug()<<debug[1];
}

void MainWindow::on_showButton_clicked() {
    if(this->isFullScreen()) {
        this->showNormal();
        qDebug()<<debug[3];
    } else {
        this->showFullScreen();
        qDebug()<<debug[2];
    }
}
