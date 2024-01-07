#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->Graphs, SIGNAL(clicked()), this, SLOT(on_Graphs_clicked()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_InputFile_clicked()
{
        Undo_and_redo::push_to_undo(0,ui->InputText->toPlainText().toStdString());

        QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt);;All Files (*)"));

        if (!filePath.isEmpty()) {

            QFile file(filePath);


            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {

                QTextStream in(&file);
                QString fileContent = in.readAll();


                file.close();

                ui->InputText->setPlainText(fileContent);
            } else {

                qDebug() << "Error: Could not open file";
            }
        }
}







void MainWindow::on_minify_clicked()
{
    Undo_and_redo::push_to_undo(1,ui->Result->toPlainText().toStdString());
    std::string input = ui->InputText->toPlainText().toStdString();
    std::string result = xmlParser::minify(input);
    ui->Result->setPlainText(QString::fromStdString(result));
}


void MainWindow::on_CorrectFile_clicked()
{
    Undo_and_redo::push_to_undo(1,ui->Result->toPlainText().toStdString());
    std::string input = ui->InputText->toPlainText().toStdString();
    std::string result = xmlParser::correct_xml(input);
    ui->Result->setPlainText(QString::fromStdString(result));
}


void MainWindow::on_updatechanges_clicked()
{
    Undo_and_redo::push_to_undo(0,ui->InputText->toPlainText().toStdString());
    ui->InputText->setPlainText(ui->Result->toPlainText());
}


void MainWindow::on_Prettify_clicked()
{
    Undo_and_redo::push_to_undo(1,ui->Result->toPlainText().toStdString());
    std::string input = ui->InputText->toPlainText().toStdString();
    std::string result = xmlParser::prettify(input);
    ui->Result->setPlainText(QString::fromStdString(result));
}


void MainWindow::on_toJson_clicked()
{
    Undo_and_redo::push_to_undo(1,ui->Result->toPlainText().toStdString());
    std::string input = ui->InputText->toPlainText().toStdString();
    std::string result = xmlParser::toJsonByStrings(input);
    ui->Result->setPlainText(QString::fromStdString(result));
}


void MainWindow::on_Verify_clicked()
{
    Undo_and_redo::push_to_undo(1,ui->Result->toPlainText().toStdString());
    std::string input = ui->InputText->toPlainText().toStdString();
    std::string result = xmlParser::get_errors(input);
    if(!result.empty()){
    ui->Result->setPlainText("Error: \n" + QString::fromStdString(result));
    }
    else{
        ui->Result->setPlainText(QString::fromStdString("No Errors"));
    }
}


void MainWindow::on_Compress_clicked()
{
    Undo_and_redo::push_to_undo(1,ui->Result->toPlainText().toStdString());
    std::string input = ui->InputText->toPlainText().toStdString();
    std::string result = xmlParser::compressAndWriteToFile(input);
    ui->Result->setPlainText(QString::fromStdString(result));

}


void MainWindow::on_Decompress_clicked()
{
    Undo_and_redo::push_to_undo(1,ui->Result->toPlainText().toStdString());
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt);;All Files (*)"));
    std::string path = filePath.toStdString();

    std::string resultFromDC= xmlParser::readAndDecompressFromFile(path);
    ui->Result->setPlainText(QString::fromStdString(resultFromDC));

}




void MainWindow::on_Undo_clicked()
{
    std::pair<int,std::string> undo;
    undo=Undo_and_redo::undo(ui->InputText->toPlainText().toStdString(),ui->Result->toPlainText().toStdString());
    if(undo.first==0)
        ui->InputText->setPlainText(QString::fromStdString(undo.second));
    if(undo.first==1)
        ui->Result->setPlainText(QString::fromStdString(undo.second));

}


void MainWindow::on_Redo_clicked()
{
    std::pair<int,std::string> redo;
    redo=Undo_and_redo::redo(ui->InputText->toPlainText().toStdString(),ui->Result->toPlainText().toStdString());
    if(redo.first==0)
        ui->InputText->setPlainText(QString::fromStdString(redo.second));
    if(redo.first==1)
        ui->Result->setPlainText(QString::fromStdString(redo.second));

}




void MainWindow::on_Savefile_clicked()
{

    QString filePath = QFileDialog::getSaveFileName(this, "Save File", "", "Text Files (*.txt);;All Files (*)");

    if (!filePath.isEmpty()) {

        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {

            QString textToSave = ui->Result->toPlainText();


            QTextStream stream(&file);
            stream << textToSave;

            file.close();
        }
    }

}






void MainWindow::on_Graphs_released()
{
    Network_Analysis::UsingParse(ui->InputText->toPlainText().toStdString());
    GraphWindow *newWindow = new GraphWindow(this);
    newWindow->show();
}

