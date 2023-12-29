#include "graphwindow.h"
#include "ui_graphwindow.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDir>
#include <QPixmap>
#include <string>

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


// void GraphWindow::on_pushButton_6_clicked()
// {
//     bool ok;
//     QString userInput = QInputDialog::getText(this, "Get Input 1", "Please Enter Input 1", QLineEdit::Normal, "", &ok);


//     if (ok && !userInput.isEmpty()) {
//         ui->ResultGraphs->setPlainText(userInput);
//     }
// }





void GraphWindow::on_Show_clicked()
{
    std::string path =Network_Analysis::visualize_graph();
    ui->ResultGraphs->setText(QString::fromStdString(path));
    if (!path.empty()) {
        QGraphicsScene *scene = new QGraphicsScene(this);

        std::filesystem::path currentPath = std::filesystem::current_path();
        path =(currentPath/"graph.dot.png").string();
        QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QString::fromStdString(path));


        scene->addItem(pixmapItem);


        ui->graphViewer->setScene(scene);
    }
}

