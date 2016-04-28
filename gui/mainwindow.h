#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QDebug>
#include "ui_mainwindow.h"
#include "about.h"
#include "settings.h"
#include "messagedone.h"
#include <QMessageBox>
#include <QSettings>
#include <QByteArray>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();
    void on_actionInfo_triggered();
    void on_actionSettings_triggered();
    void on_actionStart_triggered();
    void rightMessage();
    void wrongMessage();
    void onFinished(int);
    void setOutDir(QString out);
    void setInputDir(QString in);
private:
    Ui::MainWindow *ui;
    QProcess *proc;
    QDialog *set;
    QString m_sSettingsFile;
    QString input_dir;
    QString output_dir;
    //QString SettingsFile;
    //QSettings pref;
    void closeEvent(QCloseEvent *event);

};

#endif // MAINWINDOW_H
