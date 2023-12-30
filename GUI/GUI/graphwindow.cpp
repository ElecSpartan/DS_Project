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





void GraphWindow::on_Visualize_clicked()
{
    std::string path =Network_Analysis::visualize_graph();

    if (!path.empty()) {
        QGraphicsScene *scene = new QGraphicsScene(this);

        // std::filesystem::path currentPath = std::filesystem::current_path();
        // path =(currentPath/"graph.dot.png").string();
        QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QString::fromStdString(path));


        scene->addItem(pixmapItem);


        ui->graphViewer->setScene(scene);
    }
}


void GraphWindow::on_MustFollowers_clicked()
{
    std::string followers = Network_Analysis::most_followers();
    ui->ResultGraphs->setPlainText(QString::fromStdString(followers));
}


void GraphWindow::on_MostConnections_clicked()
{
    std::string connections = Network_Analysis::most_connections();
    ui->ResultGraphs->setPlainText(QString::fromStdString(connections));
}


void GraphWindow::on_Suggestion_clicked()
{
    bool ok;
        QString userInput = QInputDialog::getText(this, "Get Input", "Please Enter User ID: ", QLineEdit::Normal, "", &ok);


        if (ok && !userInput.isEmpty()) {
            std::string suggestion = Network_Analysis::user_suggestion(std::stoi(userInput.toStdString()));
            ui->ResultGraphs->setPlainText(QString::fromStdString(suggestion));
        }
}


void GraphWindow::on_Mutual_clicked()
{
    bool ok;
    QString userInput1 = QInputDialog::getText(this, "Get Input", "Please Enter User1 ID: ", QLineEdit::Normal, "", &ok);
    QString userInput2 = QInputDialog::getText(this, "Get Input", "Please Enter User2 ID: ", QLineEdit::Normal, "", &ok);

    if (ok && !userInput1.isEmpty() && !userInput2.isEmpty()) {
        std::string mutuals = Network_Analysis::mutual_followers(std::stoi(userInput1.toStdString()),std::stoi(userInput2.toStdString()));
        ui->ResultGraphs->setPlainText(QString::fromStdString(mutuals));
    }
}


void GraphWindow::on_PostSearch_clicked()
{
    bool ok;
    QString userInput = QInputDialog::getText(this, "Get Input", "Please Enter word to search about: ", QLineEdit::Normal, "", &ok);

    if (ok && !userInput.isEmpty()) {
        std::string search = Network_Analysis::post_search(userInput.toStdString());
        ui->ResultGraphs->setPlainText(QString::fromStdString(search));
    }
}

