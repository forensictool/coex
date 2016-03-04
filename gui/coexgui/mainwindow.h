#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QtGui>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void exit();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void rightMessage();
    void wrongMessage();
    void onFinished(int);

public:
    Ui::MainWindow *ui;
    QLabel *label;
    QLabel *label_2;
    QString inputdir;
    QString outputdir;
    QStringListModel *model;
    QProcess *proc;
    QProcess *build;

};

#endif // MAINWINDOW_H
