/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLabel *label_2;
    QGridLayout *gridLayout;
    QTextEdit *InputText;
    QTextEdit *Result;
    QGridLayout *gridLayout_5;
    QPushButton *Redo;
    QPushButton *Savefile;
    QPushButton *Undo;
    QGridLayout *gridLayout_4;
    QPushButton *InputFile;
    QPushButton *Verify;
    QPushButton *CorrectFile;
    QPushButton *minify;
    QPushButton *Prettify;
    QPushButton *Compress;
    QPushButton *Decompress;
    QPushButton *toJson;
    QPushButton *updatechanges;
    QPushButton *Graphs;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(1000, 800);
        MainWindow->setMinimumSize(QSize(1000, 800));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_6 = new QGridLayout(centralwidget);
        gridLayout_6->setObjectName("gridLayout_6");
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout_2->setVerticalSpacing(5);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setMinimumSize(QSize(0, 50));
        label->setMaximumSize(QSize(200, 16777215));

        gridLayout_2->addWidget(label, 0, 0, 1, 1, Qt::AlignHCenter|Qt::AlignTop);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(0, 40));
        label_2->setMaximumSize(QSize(200, 16777215));

        gridLayout_2->addWidget(label_2, 0, 1, 1, 1, Qt::AlignHCenter|Qt::AlignTop);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        gridLayout->setHorizontalSpacing(10);
        InputText = new QTextEdit(centralwidget);
        InputText->setObjectName("InputText");
        InputText->setMinimumSize(QSize(400, 520));
        InputText->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setPointSize(20);
        InputText->setFont(font);

        gridLayout->addWidget(InputText, 0, 0, 1, 1);

        Result = new QTextEdit(centralwidget);
        Result->setObjectName("Result");
        Result->setMinimumSize(QSize(400, 520));
        Result->setMaximumSize(QSize(16777215, 16777215));
        Result->setFont(font);
        Result->setAutoFillBackground(false);
        Result->setReadOnly(true);

        gridLayout->addWidget(Result, 0, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout, 1, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_3, 0, 0, 1, 1);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName("gridLayout_5");
        Redo = new QPushButton(centralwidget);
        Redo->setObjectName("Redo");
        Redo->setMinimumSize(QSize(160, 40));
        Redo->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_5->addWidget(Redo, 0, 1, 1, 1);

        Savefile = new QPushButton(centralwidget);
        Savefile->setObjectName("Savefile");
        Savefile->setMinimumSize(QSize(160, 40));
        Savefile->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_5->addWidget(Savefile, 0, 2, 1, 1);

        Undo = new QPushButton(centralwidget);
        Undo->setObjectName("Undo");
        Undo->setMinimumSize(QSize(160, 40));
        Undo->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_5->addWidget(Undo, 0, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_5, 1, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName("gridLayout_4");
        InputFile = new QPushButton(centralwidget);
        InputFile->setObjectName("InputFile");
        InputFile->setMinimumSize(QSize(160, 40));

        gridLayout_4->addWidget(InputFile, 0, 0, 1, 1);

        Verify = new QPushButton(centralwidget);
        Verify->setObjectName("Verify");
        Verify->setMinimumSize(QSize(160, 40));

        gridLayout_4->addWidget(Verify, 0, 1, 1, 1);

        CorrectFile = new QPushButton(centralwidget);
        CorrectFile->setObjectName("CorrectFile");
        CorrectFile->setMinimumSize(QSize(160, 40));

        gridLayout_4->addWidget(CorrectFile, 0, 2, 1, 1);

        minify = new QPushButton(centralwidget);
        minify->setObjectName("minify");
        minify->setMinimumSize(QSize(160, 40));

        gridLayout_4->addWidget(minify, 0, 3, 1, 1);

        Prettify = new QPushButton(centralwidget);
        Prettify->setObjectName("Prettify");
        Prettify->setMinimumSize(QSize(160, 40));
        Prettify->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_4->addWidget(Prettify, 0, 4, 1, 1);

        Compress = new QPushButton(centralwidget);
        Compress->setObjectName("Compress");
        Compress->setMinimumSize(QSize(160, 40));

        gridLayout_4->addWidget(Compress, 1, 0, 1, 1);

        Decompress = new QPushButton(centralwidget);
        Decompress->setObjectName("Decompress");
        Decompress->setMinimumSize(QSize(160, 40));

        gridLayout_4->addWidget(Decompress, 1, 1, 1, 1);

        toJson = new QPushButton(centralwidget);
        toJson->setObjectName("toJson");
        toJson->setMinimumSize(QSize(160, 40));

        gridLayout_4->addWidget(toJson, 1, 2, 1, 1);

        updatechanges = new QPushButton(centralwidget);
        updatechanges->setObjectName("updatechanges");
        updatechanges->setMinimumSize(QSize(160, 40));

        gridLayout_4->addWidget(updatechanges, 1, 3, 1, 1);

        Graphs = new QPushButton(centralwidget);
        Graphs->setObjectName("Graphs");
        Graphs->setMinimumSize(QSize(160, 40));

        gridLayout_4->addWidget(Graphs, 1, 4, 1, 1);


        gridLayout_6->addLayout(gridLayout_4, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        QWidget::setTabOrder(InputText, Result);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", " XML Parser", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:26pt;\">Input</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:26pt;\">Result</span></p></body></html>", nullptr));
        Redo->setText(QCoreApplication::translate("MainWindow", "Redo", nullptr));
        Savefile->setText(QCoreApplication::translate("MainWindow", "Save File", nullptr));
        Undo->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
        InputFile->setText(QCoreApplication::translate("MainWindow", "Input XML file", nullptr));
        Verify->setText(QCoreApplication::translate("MainWindow", "Verify", nullptr));
        CorrectFile->setText(QCoreApplication::translate("MainWindow", "Correct", nullptr));
        minify->setText(QCoreApplication::translate("MainWindow", "Minify", nullptr));
        Prettify->setText(QCoreApplication::translate("MainWindow", "Prettify", nullptr));
        Compress->setText(QCoreApplication::translate("MainWindow", "Compress", nullptr));
        Decompress->setText(QCoreApplication::translate("MainWindow", "Decompress", nullptr));
        toJson->setText(QCoreApplication::translate("MainWindow", "Convert to JSON", nullptr));
        updatechanges->setText(QCoreApplication::translate("MainWindow", "Update Input", nullptr));
        Graphs->setText(QCoreApplication::translate("MainWindow", "Graphs", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
