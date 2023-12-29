#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDir>
#include "Network_Analysis.h"
namespace Ui {
class GraphWindow;
}

class GraphWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphWindow(QWidget *parent = nullptr);
    ~GraphWindow();

private slots:


    void on_Show_clicked();

private:
    Ui::GraphWindow *ui;
};

#endif // GRAPHWINDOW_H
