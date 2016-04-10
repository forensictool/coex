#include "messagedone.h"
#include "ui_messagedone.h"

messagedone::messagedone(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::messagedone)
{
    ui->setupUi(this);
}

messagedone::~messagedone()
{
    delete ui;
}

void messagedone::on_donebutton_clicked()
{
    close();
}
