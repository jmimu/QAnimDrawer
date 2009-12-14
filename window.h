#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include "graphscenejm.h"
#include "graphviewjm.h"

class Window : public QWidget
{
    Q_OBJECT

  public:
    Window();

    void update_pos_list();

  public slots:
    void change_pos(int index);


private:
    QPushButton *m_shotbutton;
    GraphSceneJM *scene;
    GraphViewJM *graph_view;
    QComboBox *m_pos_list;

};

#endif // MAINWINDOW_H
