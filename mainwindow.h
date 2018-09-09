#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void readStandardOutputForList();
    void readStdOutDL();
    void readStdErrDL();

    void on_pushButtonBrowse_clicked();

    void on_pushButtonDownload_clicked();

    void on_pushButtonCancel_clicked();

private:
    void loadParserList();
    void resetState();
    void killDownload();

    void closeEvent (QCloseEvent *event);
private:
    Ui::MainWindow *ui;
    QProcess* pProcForList;
    QProcess* pProcForDL;
};

#endif // MAINWINDOW_H
