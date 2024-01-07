/********************************************************************************
** Form generated from reading UI file 'graphwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHWINDOW_H
#define UI_GRAPHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GraphWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QGraphicsView *graphViewer;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *MustFollowers;
    QPushButton *Mutual;
    QPushButton *MostConnections;
    QPushButton *Suggestion;
    QPushButton *Visualize;
    QPushButton *PostSearch;
    QTextEdit *ResultGraphs;

    void setupUi(QMainWindow *GraphWindow)
    {
        if (GraphWindow->objectName().isEmpty())
            GraphWindow->setObjectName("GraphWindow");
        GraphWindow->resize(800, 600);
        GraphWindow->setMinimumSize(QSize(800, 600));
        GraphWindow->setMaximumSize(QSize(1000, 800));
        centralwidget = new QWidget(GraphWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName("gridLayout_3");
        graphViewer = new QGraphicsView(centralwidget);
        graphViewer->setObjectName("graphViewer");
        graphViewer->setMinimumSize(QSize(0, 400));

        gridLayout_3->addWidget(graphViewer, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        MustFollowers = new QPushButton(centralwidget);
        MustFollowers->setObjectName("MustFollowers");
        MustFollowers->setMinimumSize(QSize(160, 40));

        gridLayout->addWidget(MustFollowers, 0, 1, 1, 1);

        Mutual = new QPushButton(centralwidget);
        Mutual->setObjectName("Mutual");
        Mutual->setMinimumSize(QSize(160, 40));

        gridLayout->addWidget(Mutual, 1, 1, 1, 1);

        MostConnections = new QPushButton(centralwidget);
        MostConnections->setObjectName("MostConnections");
        MostConnections->setMinimumSize(QSize(160, 40));

        gridLayout->addWidget(MostConnections, 1, 0, 1, 1);

        Suggestion = new QPushButton(centralwidget);
        Suggestion->setObjectName("Suggestion");
        Suggestion->setMinimumSize(QSize(160, 40));

        gridLayout->addWidget(Suggestion, 3, 0, 1, 1);

        Visualize = new QPushButton(centralwidget);
        Visualize->setObjectName("Visualize");
        Visualize->setMinimumSize(QSize(160, 40));

        gridLayout->addWidget(Visualize, 0, 0, 1, 1);

        PostSearch = new QPushButton(centralwidget);
        PostSearch->setObjectName("PostSearch");
        PostSearch->setMinimumSize(QSize(160, 40));

        gridLayout->addWidget(PostSearch, 3, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        ResultGraphs = new QTextEdit(centralwidget);
        ResultGraphs->setObjectName("ResultGraphs");
        ResultGraphs->setMaximumSize(QSize(300, 16777215));
        ResultGraphs->setReadOnly(true);

        gridLayout_2->addWidget(ResultGraphs, 0, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 1, 0, 1, 1);

        GraphWindow->setCentralWidget(centralwidget);

        retranslateUi(GraphWindow);

        QMetaObject::connectSlotsByName(GraphWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GraphWindow)
    {
        GraphWindow->setWindowTitle(QCoreApplication::translate("GraphWindow", "Graph Representation", nullptr));
        MustFollowers->setText(QCoreApplication::translate("GraphWindow", "Users With Most Followers", nullptr));
        Mutual->setText(QCoreApplication::translate("GraphWindow", "Mutual Followers Between Two Users", nullptr));
        MostConnections->setText(QCoreApplication::translate("GraphWindow", "Users With Most Connections", nullptr));
        Suggestion->setText(QCoreApplication::translate("GraphWindow", "User Suggestion", nullptr));
        Visualize->setText(QCoreApplication::translate("GraphWindow", "Visualize", nullptr));
        PostSearch->setText(QCoreApplication::translate("GraphWindow", "Post Search", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GraphWindow: public Ui_GraphWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHWINDOW_H
