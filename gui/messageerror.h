#ifndef MESSAGEERROR_H
#define MESSAGEERROR_H

#include <QDialog>

namespace Ui {
class messageerror;
}

class messageerror : public QDialog
{
    Q_OBJECT

public:
    explicit messageerror(QWidget *parent = 0);
    ~messageerror();

public slots:
    void on_toexit_clicked();

    void on_tosettings_clicked();

public:
    Ui::messageerror *ui;
};

#endif // MESSAGEERROR_H
