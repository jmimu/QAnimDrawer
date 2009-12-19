#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define TIMER_TIME 20

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
    void save_pos();
    void goto_pos();//begin animation
    void timer_timeout();

private:
    QPushButton *m_shotbutton;
    QPushButton *m_saveposbutton;
    QPushButton *m_newposbutton;
    QPushButton *m_delposbutton;
    QPushButton *m_gotoposbutton;
    GraphSceneJM *scene;
    GraphViewJM *graph_view;
    QComboBox *m_pos_list;
    QComboBox *m_destpos_list;//destination pos

    QTimer *timer;///to update anim
    bool run_animation;
};

#endif // MAINWINDOW_H
