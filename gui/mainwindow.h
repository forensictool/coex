#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QDebug>
#include "ui_mainwindow.h"
#include "about.h"
#include "ui_about.h"
#include "settings.h"
#include "ui_settings.h"
#include "messagedone.h"
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_actionExit_triggered();

    void on_actionInfo_triggered();

    void on_actionSettings_triggered();
    void on_actionStart_triggered();
    void rightMessage();
    void wrongMessage();
    void onFinished(int);

    void setOutDir(QString out);
    void setInputDir(QString in);
public:
    Ui::MainWindow *ui;
    QProcess *proc;
    QDialog *set;

private:
    QString input_dir;
    QString output_dir;
};

#endif // MAINWINDOW_H
