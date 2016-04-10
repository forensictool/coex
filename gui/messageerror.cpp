#include "messageerror.h"
#include "ui_messageerror.h"
#include "settings.h"
#include "ui_settings.h"

messageerror::messageerror(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::messageerror)
{
    ui->setupUi(this);
}

messageerror::~messageerror()
{
    delete ui;
}

void messageerror::on_toexit_clicked()
{
    close();
}

void messageerror::on_tosettings_clicked()
{
    settings *set = new settings();
    set -> show();
    close();

}
