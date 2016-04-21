#include "settings.h"
#include "ui_settings.h"
#include <QString>
#include <QFileDialog>
#include <QDir>

settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
}

settings::~settings()
{
    delete ui;
}

void settings::on_input_clicked()
{
    inputdir = QFileDialog::getExistingDirectory(this,
                                QString::fromUtf8("Открыть папку"),
                                QDir::homePath(),
                                QFileDialog::ShowDirsOnly
                                | QFileDialog::DontResolveSymlinks);
    ui->inpulabel->setText(inputdir);

}

void settings::on_output_clicked()
{
    outputdir = QFileDialog::getExistingDirectory(this,
                                QString::fromUtf8("Открыть папку"),
                                QDir::homePath(),
                                QFileDialog::ShowDirsOnly
                                | QFileDialog::DontResolveSymlinks);
    ui->outputlabel->setText(outputdir);

}

void settings::on_save_clicked()
{
    emit changeInputValue(inputdir);
    emit changeOutputValue(outputdir);
    hide();

}
