#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void on_conButton_clicked();

    void on_closeButton_clicked();

    void on_hideButton_clicked();

    void on_showButton_clicked();

    void connectServer();

    void connectAnswer(QNetworkReply* reply);

    void sendMessage();

protected:
    void mousePressEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton && ui->toolWidget->underMouse()==1) {
            oldPos = event->pos();
        }
    }
    void mouseDoublePressEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton && ui->toolWidget->underMouse()==1) {
            if(this->isFullScreen()) {
                this->showNormal();
            }
            else {
                this->showFullScreen();
            }
        }
    }

    void mouseMoveEvent(QMouseEvent *event) {
        QPoint delta = event->pos() - oldPos;
        if(ui->toolWidget->underMouse()==1){
            move(pos() + delta);
        }
    }


signals:
    void connectReady();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager* conManager;
    QNetworkAccessManager* manager;
    QPoint oldPos;
};



#endif // MAINWINDOW_H
