#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QGraphicsScene>
#include "graphviewjm.h"

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

private:
    QPushButton *m_shotbutton;
	QGraphicsScene *scene;
	GraphViewJM *graph_view;

};

#endif // MAINWINDOW_H
