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

private slots:
    void on_input_clicked();
    void on_output_clicked();
    void on_save_clicked();


private:
    Ui::settings *ui;
    QString inputdir;
    QString outputdir;
    //QString SettingsFile;
    void readsettings();
signals:
    void changeInputValue(QString var);
    void changeOutputValue(QString var);
};

#endif // SETTINGS_H
