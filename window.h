#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "graphscenejm.h"
#include "graphviewjm.h"
#include "skeleton.h"

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

private:
    QPushButton *m_shotbutton;
    GraphSceneJM *scene;
    GraphViewJM *graph_view;
    Skeleton skel;

};

#endif // MAINWINDOW_H
