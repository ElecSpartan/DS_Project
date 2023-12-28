// graphwindow.h
#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QDialog>

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GraphWindow(QWidget *parent = nullptr);
    ~GraphWindow();

private:
    Ui::GraphWindow *ui;
};

#endif // GRAPHWINDOW_H
