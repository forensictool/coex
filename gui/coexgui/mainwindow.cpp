#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFileDialog>
#include <QLabel>
#include <QProcess>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_2_clicked()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_3_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString inputdir = QFileDialog::getExistingDirectory(this,
                               QString::fromUtf8("Открыть папку"),
                               QDir::currentPath(),
                               QFileDialog::ShowDirsOnly
                               | QFileDialog::DontResolveSymlinks);
    ui->label->setText(inputdir);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString outputdir = QFileDialog::getExistingDirectory(this,
                               QString::fromUtf8("Открыть папку"),
                               QDir::currentPath(),
                               QFileDialog::ShowDirsOnly
                               | QFileDialog::DontResolveSymlinks);
    ui->label_2->setText(outputdir);
}

void MainWindow::on_pushButton_3_clicked()
{
    QProcess *proc= new QProcess();
    ui->textBrowser->clear();
    proc->setProcessChannelMode(QProcess::MergedChannels); // Устанавливаем, что вывод (и ошибки и прочее) будет валиться в один канал
    connect (proc, SIGNAL(readyReadStandardOutput()), this, SLOT(rightMessage())) ; // ловим когда процесс что то выдал
    connect (proc, SIGNAL(readyReadStandardError()), this, SLOT(wrongMessage())) ; // ловим когда процесс выдал ошибку
    connect (proc, SIGNAL(finished(int)), this, SLOT(onFinished(int))) ; //ловим когда процесс закончил работу

    proc->start("/bin/bash", QStringList() << "-c" << "ls -l");
}

void MainWindow::rightMessage()
{
    QString output(QString::fromLocal8Bit(static_cast<QProcess *>(sender())->readAllStandardOutput()));
    ui->textBrowser->setTextColor(Qt::black);
    ui->textBrowser->append(output);
}

void MainWindow::wrongMessage()
{
    QString output(static_cast<QProcess *>(sender())->readAllStandardOutput ());
    ui->textBrowser->setTextColor(Qt::red);
    ui->textBrowser->append(output);
}

void MainWindow::onFinished(int /*result*/)
{
    QMessageBox msgBox;
    msgBox.setText("Complete");
    msgBox.exec();
}

