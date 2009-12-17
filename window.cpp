#include <QtGui>

#include "window.h"
#include <iostream>

//! [0]
Window::Window()
{
  scene = new GraphSceneJM();
  graph_view = new GraphViewJM(scene);
  m_shotbutton = new QPushButton("Shot", this);
  m_saveposbutton = new QPushButton("Save Pos", this);
  m_newposbutton = new QPushButton("New Pos", this);
  m_delposbutton = new QPushButton("Del Pos", this);
  m_pos_list = new QComboBox(this);

  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->addWidget(graph_view,1,1,6,2);
  mainLayout->addWidget(m_shotbutton,1,3);
  mainLayout->addWidget(m_saveposbutton,2,3);
  mainLayout->addWidget(m_pos_list,3,3);
  mainLayout->addWidget(m_newposbutton,4,3);
  mainLayout->addWidget(m_delposbutton,5,3);

  setLayout(mainLayout);
  
  setWindowTitle(tr("QAnimDrawer"));
  QObject::connect(m_shotbutton, SIGNAL(clicked()), graph_view, SLOT(ask_shot()));
  QObject::connect(m_saveposbutton, SIGNAL(clicked()), this, SLOT(save_pos()));

  QObject::connect(m_pos_list, SIGNAL(currentIndexChanged(int)), this, SLOT(change_pos(int)));

  scene->draw_skel();
  
  update_pos_list();
}


void Window::update_pos_list()
{
  m_pos_list->clear();

  for( std::set<QString>::const_iterator iter =  scene->get_skel()->get_positions_list()->begin();iter !=  scene->get_skel()->get_positions_list()->end();++iter ) {
    m_pos_list->addItem(*iter);
  }

}


void Window::change_pos(int index)
{
  std::cout<<"Change to position: "<<m_pos_list->itemText(index).toStdString()<<std::endl;
  scene->get_skel()->set_to_position(m_pos_list->itemText(index));

  scene->draw_skel();
}

void Window::save_pos()
{
  std::cout<<"Save position: "<<m_pos_list->currentText().toStdString()<<std::endl;
  scene->get_skel()->save_position(m_pos_list->currentText());
  scene->get_skel()->save();
}
