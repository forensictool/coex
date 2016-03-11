#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFileDialog>
#include <QLabel>
#include <QProcess>
#include <QMessageBox>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QStringListModel(this);
    QDir myDir("../../sources/plugins/");
    QStringList allFiles = myDir.entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
    model->setStringList(allFiles);
    ui->listView->setModel(model);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OpenDir_clicked()
{
   inputdir = QFileDialog::getExistingDirectory(this,
                               QString::fromUtf8("Открыть папку"),
                               QDir::homePath(),
                               QFileDialog::ShowDirsOnly
                               | QFileDialog::DontResolveSymlinks);
}

void MainWindow::on_SaveDir_clicked()
{
    outputdir = QFileDialog::getExistingDirectory(this,
                               QString::fromUtf8("Открыть папку"),
                               QDir::homePath(),
                               QFileDialog::ShowDirsOnly
                               | QFileDialog::DontResolveSymlinks);
}

void MainWindow::on_RunCoex_clicked()
{
    if ((inputdir.length() && outputdir.length()) != 0)
    {
        proc= new QProcess;

        QStringList args;

        ui->textBrowser->clear();
        proc->setProcessChannelMode(QProcess::MergedChannels);

        connect (proc, SIGNAL(readyReadStandardOutput()), this, SLOT(rightMessage())) ;
        connect (proc, SIGNAL(readyReadStandardError()), this, SLOT(wrongMessage())) ;
        connect (proc, SIGNAL(finished(int)), this, SLOT(onFinished(int))) ;
        args<<"-i"<<inputdir<<"-o"<<outputdir;
        proc->start("./coex",args);

    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowIcon(QIcon(QPixmap("icon.png")));
        msgBox.setWindowTitle("coex");
        QSpacerItem* horizontalSpacer = new QSpacerItem(300, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        msgBox.setText( QString::fromUtf8("Пожалуйста выберите папки"));
        QGridLayout* layout = (QGridLayout*)msgBox.layout();
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
        msgBox.exec();

    }
}



void MainWindow::on_BuildCoex_clicked()
{
    build = new QProcess;
    build->setProcessChannelMode(QProcess::MergedChannels);
    connect (build, SIGNAL(readyReadStandardOutput()), this, SLOT(rightMessage())) ;
    connect (build, SIGNAL(readyReadStandardError()), this, SLOT(wrongMessage())) ;
    connect (build, SIGNAL(finished(int)), this, SLOT(onFinished(int))) ;
    build->start("./build.sh");
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
    msgBox.setWindowTitle("coex");
    msgBox.setWindowIcon(QIcon(QPixmap("icon.png")));
    QSpacerItem* horizontalSpacer = new QSpacerItem(300, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setText(QString::fromUtf8("Выполнено"));
    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
    //emit exit();
}
