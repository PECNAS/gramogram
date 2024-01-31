#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QNetworkAccessManager>
#include <QMainWindow>
#include <QSettings>


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

    void openChat();

signals:
    void connectReady();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager* conManager;
    QSettings settings;
};



#endif // MAINWINDOW_H
