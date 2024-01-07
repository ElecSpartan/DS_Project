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


    void on_Visualize_clicked();

    void on_MustFollowers_clicked();

    void on_MostConnections_clicked();

    void on_Suggestion_clicked();

    void on_Mutual_clicked();

    void on_PostSearch_clicked();

private:
    Ui::GraphWindow *ui;
};

#endif // GRAPHWINDOW_H
