#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(width(), height());
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    loadParserList();

    /* Temp workaround for killing streamscraper when
     * the gui closes.
     * Checking if pProcForDL is null or nullptr
     * will always return false. Instead, create
     * a new QProcess even if it will be never used
     */
    this->pProcForDL = new QProcess(this);
}

void MainWindow::loadParserList()
{
    this->pProcForList = new QProcess(this);
    QStringList args;
    args << "listparsers";

    connect(pProcForList, SIGNAL(readyReadStandardOutput()), this, SLOT(readStandardOutputForList()));

    pProcForList->start("bin/streamscraper", args);
}

void MainWindow::readStandardOutputForList()
{
    QByteArray processOutput;
    processOutput = pProcForList->readAllStandardOutput();

    QString strOut(processOutput);
    QStringList splitted = strOut.split(",");
    for (const auto& p : splitted)
    {
        ui->comboBox->addItem(p.simplified());
    }

    pProcForList->kill();
}

void MainWindow::readStdOutDL()
{

    QByteArray processOutput;
    processOutput = pProcForDL->readAllStandardOutput();

    QString strOut(processOutput);

    qDebug() << strOut;

    if(strOut.contains("Unhandled Exception:"))
    {
        QMessageBox::warning(this, "Error", "Something went wrong...");
        resetState();
    }

    if(strOut.contains('_'))
    {
        QStringList splitted = strOut.simplified().split("_");
        const QString jobID = splitted.at(0);
        const QString jobContent = splitted.at(1);

        if(jobID == "PROGRESS")
        {
            ui->progressBar->setValue(jobContent.toInt());
        }
        else if(jobID == "COMPLETE")
        {
            resetState();
            QMessageBox::information(this, "Download complete", "Download complete");
        }
    }
}

void MainWindow::resetState()
{
    ui->pushButtonDownload->setEnabled(true);
    ui->pushButtonBrowse->setEnabled(true);
    ui->pushButtonCancel->setEnabled(false);
}

void MainWindow::readStdErrDL()
{
    QByteArray processOutput;
    processOutput = pProcForDL->readAllStandardError();

    QString strOut(processOutput);

    qDebug() << strOut;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonBrowse_clicked()
{
    QString location = QFileDialog::getSaveFileName(this, "Save file", "./", "MP4 Movies  (*.mp4)");

#ifndef Q_OS_WIN
   location.append(".mp4"); // append file extension. Windows does it auto
#endif

    ui->txtLocation->setText(location);
}

void MainWindow::on_pushButtonDownload_clicked()
{

    QString url = ui->txtUrl->text();
    QString location = ui->txtLocation->text();

    if(url.isEmpty() || location.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Please fill out both the URL and the location fields");
        return;
    }

    // Workaround for crash on exit. See more details in ctor
    delete pProcForDL;
    pProcForDL = nullptr;

    this->pProcForDL = new QProcess(this);
    pProcForDL->setProcessChannelMode(QProcess::MergedChannels);
    pProcForDL->setProgram("bin/streamscraper");

    connect(pProcForDL, SIGNAL(readyReadStandardOutput()), this, SLOT(readStdOutDL()));
    connect(pProcForDL, SIGNAL(readyReadStandardError()), this, SLOT(readStdErrDL()));

    QStringList args;

    args << "download"
         << "-p " + ui->comboBox->currentText()
         << "-u " + ui->txtUrl->text()
         << "-o " + ui->txtLocation->text()
         << "-g ";

    pProcForDL->setArguments(args);
    pProcForDL->start();
    ui->pushButtonDownload->setEnabled(false);
    ui->pushButtonBrowse->setEnabled(false);
    ui->pushButtonCancel->setEnabled(true);
}

void MainWindow::closeEvent(QCloseEvent* pClose)
{
    Q_UNUSED(pClose);
    killDownload();
}

void MainWindow::killDownload()
{
    // kill will do nothing if the process
    // has never been running
    pProcForDL->kill();
}

void MainWindow::on_pushButtonCancel_clicked()
{
    killDownload();
    ui->progressBar->setValue(0);
    resetState();
}
