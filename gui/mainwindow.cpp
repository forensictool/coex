#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
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
    settings *set = new settings(this);
    connect(set, SIGNAL(changeOutputValue(QString)), this, SLOT(setOutDir(QString)));
    connect(set, SIGNAL(changeInputValue(QString)), this, SLOT(setInputDir(QString)));
    set -> show();

}

void MainWindow::on_actionStart_triggered()
{
    qDebug() << input_dir << output_dir;
    if ((input_dir.length() && output_dir.length()) != 0)
        {
                QStringList args;
                ui->coextext->clear();
                proc.setProcessChannelMode(QProcess::MergedChannels);
                connect (&proc, SIGNAL(readyReadStandardOutput()), this, SLOT(rightMessage())) ;
                connect (&proc, SIGNAL(readyReadStandardError()), this, SLOT(wrongMessage())) ;
                connect (&proc, SIGNAL(finished(int)), this, SLOT(onFinished(int))) ;
                args<<"-i"<<input_dir<<"-o"<<output_dir;
                proc.start("./coex.sh",args);

        }
        else
        {
        qDebug() << "ololo";
            messageerror *error = new messageerror(this);
            error -> show();
        }
}

void MainWindow::rightMessage()
{
    QString output(QString::fromLocal8Bit(static_cast<QProcess *>(sender())->readAllStandardOutput()));
    ui->coextext->append(output);
}

void MainWindow::wrongMessage()
{
    QString output(static_cast<QProcess *>(sender())->readAllStandardOutput ());
    ui->coextext->setTextColor(Qt::red);
    ui->coextext->append(output);

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
