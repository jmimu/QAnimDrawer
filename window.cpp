#include <QtGui>

#include "window.h"

//! [0]
Window::Window()
{
  scene = new GraphSceneJM();
  graph_view = new GraphViewJM(scene);
  m_shotbutton = new QPushButton("Shot", this);

  QHBoxLayout *mainLayout = new QHBoxLayout;
  mainLayout->addWidget(graph_view);
  mainLayout->addWidget(m_shotbutton);

  setLayout(mainLayout);
  
  setWindowTitle(tr("QAnimDrawer"));
  QObject::connect(m_shotbutton, SIGNAL(clicked()), graph_view, SLOT(ask_shot()));

  scene->draw_skel();
}




