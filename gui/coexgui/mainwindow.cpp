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
    //connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    //connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_2_clicked()));
    //connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_3_clicked()));

    model = new QStringListModel(this);
    QDir myDir("../sources/plugins/");
    QStringList allFiles = myDir.entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
    model->setStringList(allFiles);

    ui->listView->setModel(model);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
   inputdir = QFileDialog::getExistingDirectory(this,
                               QString::fromUtf8("Открыть папку"),
                               QDir::currentPath(),
                               QFileDialog::ShowDirsOnly
                               | QFileDialog::DontResolveSymlinks);
    //ui->label->setText(inputdir);
}

void MainWindow::on_pushButton_2_clicked()
{
    outputdir = QFileDialog::getExistingDirectory(this,
                               QString::fromUtf8("Открыть папку"),
                               QDir::currentPath(),
                               QFileDialog::ShowDirsOnly
                               | QFileDialog::DontResolveSymlinks);
    //ui->label_2->setText(outputdir);
}

void MainWindow::on_pushButton_3_clicked()
{
    if ((inputdir.length() && outputdir.length()) != 0)
    {
        QProcess *proc= new QProcess();
        ui->textBrowser->clear();
        proc->setProcessChannelMode(QProcess::MergedChannels); // Устанавливаем, что вывод (и ошибки и прочее) будет валиться в один канал
        connect (proc, SIGNAL(readyReadStandardOutput()), this, SLOT(rightMessage())) ; // ловим когда процесс что то выдал
        connect (proc, SIGNAL(readyReadStandardError()), this, SLOT(wrongMessage())) ; // ловим когда процесс выдал ошибку
        connect (proc, SIGNAL(finished(int)), this, SLOT(onFinished(int))) ; //ловим когда процесс закончил работу
        QString command;
        QStringList args;
        command="./coex";
        args<<"-i"<<inputdir<<"-o"<<outputdir;

        proc->start(command,args);

    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowIcon(QIcon(QPixmap("../gui/coexgui/icon.png")));
        msgBox.setWindowTitle("coex");
        QSpacerItem* horizontalSpacer = new QSpacerItem(300, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        msgBox.setText( QString::fromUtf8("Пожалуйста выберите папки"));
        QGridLayout* layout = (QGridLayout*)msgBox.layout();
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
        msgBox.exec();

    }
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
    msgBox.setWindowIcon(QIcon(QPixmap("../gui/coexgui/icon.png")));
    QSpacerItem* horizontalSpacer = new QSpacerItem(300, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setText(QString::fromUtf8("Выполнено"));
    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msgBox.exec();
    //emit exit();
}
