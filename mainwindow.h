#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chat.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QMainWindow>
#include <QSettings>
#include <QMouseEvent>

class QNetworkReply;
class QNetworkAccessManager;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    //кнопки в sign up
    void connectionButton();
    void closeButton();
    void hideButton();
    void showButton();
    void connectAnswer();
    void connectServer(){
        QString url = "https://8757-95-105-74-45.ngrok-free.app/api/v1/sign_up/";
        QByteArray postData;
        postData.append("username="+ui->logLine->text().toUtf8());
        postData.append("&");
        postData.append("password="+ui->passwordLine->text().toUtf8());
        curlRequest->sendPostRequest(url, postData);


    }
    //кнопки в chat
    void sendMessage(){
        QString url = "https://8757-95-105-74-45.ngrok-free.app/api/v1/new_msg/";
        Chat dateJson;
        QByteArray postData = dateJson.Chat::messdate(
            ui->logLine->text().toStdString(),
            ui->contactLabel->text().toStdString(),
            ui->sendLine->text().toStdString()
            ).c_str();
        curlRequest->sendPostRequest(url, postData);
        emit connectDone();
    }

protected:
    void mousePressEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton && (ui->toolWidget->underMouse()==1 || ui->toolWidgetM->underMouse()==1)) {
            oldPos = event->pos();
        }
    }

    void mouseMoveEvent(QMouseEvent *event) {
        QPoint delta = event->pos() - oldPos;
        if(ui->toolWidget->underMouse()==1 || ui->toolWidgetM->underMouse()==1){
            move(pos() + delta);
        }
    }
signals:
    void connectReady();
    void clicked_();
    void connectDone();

private:
    Ui::MainWindow *ui;
    QPoint oldPos;
    Chat* curlRequest = new Chat;
};



#endif // MAINWINDOW_H
