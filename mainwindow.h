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

constexpr QPoint kInvalidPoint(-1, -1);
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

    void setSettings();

    void mousePressEvent(QMouseEvent* event);

    void mouseMoveEvent(QMouseEvent* event);


signals:
    void connectReady();
    void signalOpenChat();
    void signSettings();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager* conManager;
    QSettings settings;
    QPoint pos_;
};



#endif // MAINWINDOW_H
