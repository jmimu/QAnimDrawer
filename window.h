#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define TIMER_TIME 20

#define ANIM_SPEED 0.1

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include "graphscenejm.h"
#include "graphviewjm.h"

class Window : public QWidget
{
  Q_OBJECT

public:
  Window(QString filename);

  void update_pos_list();
  void enable_all(bool enable);

public slots:
  void change_pos(int index);
  void save_pos();
  void del_pos();
  void goto_pos();//begin animation
  void new_pos();
  void timer_timeout();
  void write_file();

private:
  QPushButton *m_shotbutton;
  QPushButton *m_saveposbutton;
  QPushButton *m_newposbutton;
  QLineEdit *m_newposname_edit;
  QPushButton *m_delposbutton;
  QPushButton *m_gotoposbutton;
  GraphSceneJM *scene;
  GraphViewJM *graph_view;
  QComboBox *m_pos_list;
  QComboBox *m_destpos_list;//destination pos
  QLabel *m_animfile_label;
  QLineEdit *m_animfile_edit;

  QPushButton *m_writefilebutton;

  QTimer *timer;///to update anim
  bool run_animation;
  int m_animation_number;//number of the image in animation

  float anim_time;
};

#endif // MAINWINDOW_H
