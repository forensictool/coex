#include "settings.h"
#include "ui_settings.h"
#include <QString>
#include <QFileDialog>
#include <QDir>
#include <QSettings>

settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    readsettings();
}

settings::~settings()
{
    delete ui;
}

void settings::on_input_clicked()
{
    inputdir = QFileDialog::getExistingDirectory(this,QString::fromUtf8("Открыть папку"),QDir::homePath(),QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    ui->inpulabel->setText(inputdir);

}

void settings::on_output_clicked()
{
    outputdir = QFileDialog::getExistingDirectory(this,QString::fromUtf8("Открыть папку"),QDir::homePath(),QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->outputlabel->setText(outputdir);

}

void settings::on_save_clicked()
{
    //SettingsFile = QApplication::applicationDirPath() + "/settings.ini";
    //QSettings settings(SettingsFile, QSettings::NativeFormat);
    QSettings settings;
    QString inputText = ui->inpulabel->text();
    QString outputtext = ui->outputlabel->text();
    settings.setValue("inputdir:", inputText);
    settings.setValue("outputdir:",outputtext);
    settings.setValue("firefox:",ui->firefox->isChecked());
    settings.setValue("icq:",ui->icq->isChecked());
    settings.setValue("archive:",ui->searcharchive->isChecked());
    settings.setValue("programm:",ui->searchprogramm->isChecked());
    settings.setValue("pidgin:",ui->pidgin->isChecked());
    settings.setValue("image:",ui->imageverifier->isChecked());
    settings.setValue("outlook:",ui->outlook->isChecked());
    settings.setValue("google:",ui->googlecheckBox->isChecked());

    emit changeInputValue(inputdir);
    emit changeOutputValue(outputdir);
    hide();

}

void settings::readsettings()
{
    //SettingsFile = QApplication::applicationDirPath() + "/settings.ini";
    //QSettings settings(SettingsFile, QSettings::NativeFormat);
    QSettings settings;
    QString inpText = settings.value("inputdir:", "").toString();
    QString outText = settings.value("outputdir:", "").toString();
    inputdir=inpText;
    outputdir=outText;
    ui->inpulabel->setText(inputdir);
    ui->outputlabel->setText(outputdir);

    ui->firefox->setChecked(settings.value("firefox:").toBool());
    ui->icq->setChecked(settings.value("icq:").toBool());
    ui->searcharchive->setChecked(settings.value("archive:").toBool());
    ui->searchprogramm->setChecked(settings.value("programm:").toBool());
    ui->pidgin->setChecked(settings.value("pidgin:").toBool());
    ui->imageverifier->setChecked(settings.value("image:").toBool());
    ui->outlook->setChecked(settings.value("outlook:").toBool());
    ui->googlecheckBox->setChecked(settings.value("google:").toBool());
}
