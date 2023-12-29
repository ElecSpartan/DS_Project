#include "graphwindow.h"
#include "ui_graphwindow.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDir>

GraphWindow::GraphWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GraphWindow)
{
    ui->setupUi(this);
}

GraphWindow::~GraphWindow()
{
    delete ui;
}

void GraphWindow::on_pushButton_2_clicked()
{
    // Create a QGraphicsScene
    QGraphicsScene *scene = new QGraphicsScene(this);

    // Create a QGraphicsPixmapItem and set its pixmap
    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QPixmap(QDir::homePath() + "/Downloads/R.jpg"));

    // Add the pixmap item to the scene
    scene->addItem(pixmapItem);

    // Set the scene for the QGraphicsView
    ui->graphViewer->setScene(scene);
}

