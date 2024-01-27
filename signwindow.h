#ifndef SIGNWINDOW_H
#define SIGNWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {class signWindow;}
QT_END_NAMESPACE

class signWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit signWindow(QWidget *parent = nullptr);
    ~signWindow();

private:
    Ui::signWindow *ui;
};

#endif // SIGNWINDOW_H
