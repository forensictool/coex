#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void rightMessage();
    void wrongMessage();
    void onFinished(int);

public:
    Ui::MainWindow *ui;
    QLabel *label;
    QLabel *label_2;
    QString inputdir;
    QString outputdir;
};

#endif // MAINWINDOW_H
