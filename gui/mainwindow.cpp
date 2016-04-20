#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    set = new settings(this);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionInfo_triggered()
{
    about *info = new about(this);
    info -> show();

}

void MainWindow::on_actionSettings_triggered()
{

        set -> show();
        connect(set, SIGNAL(changeOutputValue(QString)), this, SLOT(setOutDir(QString)));
        connect(set, SIGNAL(changeInputValue(QString)), this, SLOT(setInputDir(QString)));
}

void MainWindow::on_actionStart_triggered()
{
    proc= new QProcess;
    qDebug() << input_dir << output_dir;
    if ((input_dir.length() && output_dir.length()) != 0)
        {

                QStringList args;
                ui->coextext->clear();
                proc->setProcessChannelMode(QProcess::MergedChannels);
                connect (proc, SIGNAL(readyReadStandardOutput()), this, SLOT(rightMessage())) ;
                connect (proc, SIGNAL(readyReadStandardError()), this, SLOT(wrongMessage())) ;
                connect (proc, SIGNAL(finished(int)), this, SLOT(onFinished(int))) ;
                args<<"-i"<<input_dir<<"-o"<<output_dir;
                proc->start("../../bin/coex",args);

        }
        else
            {
                QMessageBox msgBox;
                msgBox.setText("Для начала работы выберите директории в настройках");
                msgBox.setWindowTitle("coex");
                QPixmap exportSuccess(":/prefix1/settings");
                msgBox.setWindowIcon(exportSuccess);
                msgBox.exec();
            }
}

void MainWindow::rightMessage()
{
    ui->coextext->append(QString(proc->readAll())); 
    qDebug()<<QString(proc->readAll());
}

void MainWindow::wrongMessage()
{

    ui->coextext->setTextColor(Qt::red);

    ui->coextext->append(QString(proc->readAll()));

}

void MainWindow::onFinished(int /*result*/)
{
    messagedone *done = new messagedone(this);
    done->show();

}



void MainWindow::setInputDir(QString in)
{
    input_dir = in;
}

void MainWindow::setOutDir(QString out)
{
    output_dir = out;
}
