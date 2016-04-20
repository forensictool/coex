#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QString>
#include "mainwindow.h"

namespace Ui {
class settings;
}

class settings : public QDialog
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = 0);
    ~settings();

public slots:
    void on_input_clicked();

    void on_output_clicked();

public:
    Ui::settings *ui;
    QString inputdir;
    QString outputdir;
signals:
    void changeInputValue(QString var);
    void changeOutputValue(QString var);
private slots:
    void on_save_clicked();
};

#endif // SETTINGS_H
