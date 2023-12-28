// graphwindow.cpp
#include "graphwindow.h"
#include "ui_graphs.h"

GraphWindow::GraphWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);
}

GraphWindow::~GraphWindow()
{
    delete ui;
}
