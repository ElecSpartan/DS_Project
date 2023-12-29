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

    QGraphicsScene *scene = new QGraphicsScene(this);

    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QPixmap(QDir::homePath() + "/Downloads/Popeye.jpg"));

    qreal scaleFactor = 0.4;
    pixmapItem->setScale(scaleFactor);
    scene->addItem(pixmapItem);

    ui->graphViewer->setScene(scene);
}

