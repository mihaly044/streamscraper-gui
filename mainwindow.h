#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

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

private:
    void loadParserList();
    void resetState();

private:
    Ui::MainWindow *ui;
    QProcess* pProcForList;
    QProcess* pProcForDL;
};

#endif // MAINWINDOW_H
