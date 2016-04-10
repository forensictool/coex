#ifndef MESSAGEDONE_H
#define MESSAGEDONE_H

#include <QDialog>

namespace Ui {
class messagedone;
}

class messagedone : public QDialog
{
    Q_OBJECT

public:
    explicit messagedone(QWidget *parent = 0);
    ~messagedone();

private slots:
    void on_donebutton_clicked();

private:
    Ui::messagedone *ui;
};

#endif // MESSAGEDONE_H
