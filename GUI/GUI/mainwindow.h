#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Network_Analysis.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "xmlParser.h"
#include "graphwindow.h"




QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_InputFile_clicked();

    void on_minify_clicked();

    void on_CorrectFile_clicked();

    void on_updatechanges_clicked();

    void on_Prettify_clicked();

    void on_toJson_clicked();

    void on_Verify_clicked();

    void on_Compress_clicked();

    void on_Decompress_clicked();

    void on_Undo_clicked();

    void on_Redo_clicked();


    void on_Savefile_clicked();

    void on_Graphs_released();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
