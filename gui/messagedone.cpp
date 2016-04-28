#include "messagedone.h"
#include "ui_messagedone.h"
#include "settings.h"
#include <QDesktopServices>

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

void messagedone::on_pushButton_clicked()
{
    QSettings settings;
    QString outText = settings.value("outputdir:", "").toString();
    QDesktopServices::openUrl(QUrl(outText, QUrl::TolerantMode));
}
