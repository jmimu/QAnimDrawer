#include <QtGui>

#include "window.h"
#include <iostream>

//! [0]
Window::Window():run_animation(false),m_animation_number(0),anim_time(0.0)
{
  scene = new GraphSceneJM();
  graph_view = new GraphViewJM(scene);
  m_shotbutton = new QPushButton("Shot", this);
  m_saveposbutton = new QPushButton("Save Pos", this);
  m_newposbutton = new QPushButton("New Pos", this);
  m_newposname_edit = new QLineEdit(this);
  m_delposbutton = new QPushButton("Delete this position", this);
  m_gotoposbutton = new QPushButton("Goto Pos:", this);
  m_pos_list = new QComboBox(this);
  m_destpos_list = new QComboBox(this);
  m_animfile_label = new QLabel("Save as:",this);
  m_animfile_edit = new QLineEdit(this);
  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->addWidget(graph_view,1,1,10,2);
  mainLayout->addWidget(m_shotbutton,1,3,1,2);
  mainLayout->addWidget(m_saveposbutton,2,3,1,2);
  mainLayout->addWidget(m_pos_list,3,3,1,2);
  mainLayout->addWidget(m_delposbutton,4,3,1,2);

  mainLayout->addWidget(m_newposbutton,5,3,1,1);
  mainLayout->addWidget(m_newposname_edit,5,4,1,1);

  mainLayout->addWidget(m_gotoposbutton,6,3,1,1);
  mainLayout->addWidget(m_destpos_list,6,4,1,1);

  mainLayout->addWidget(m_animfile_label,7,3,1,1);
  mainLayout->addWidget(m_animfile_edit,7,4,1,1);

  setLayout(mainLayout);
  
  setWindowTitle(tr("QAnimDrawer"));
  QObject::connect(m_shotbutton, SIGNAL(clicked()), graph_view, SLOT(ask_shot("img.png")));
  QObject::connect(m_saveposbutton, SIGNAL(clicked()), this, SLOT(save_pos()));
  QObject::connect(m_delposbutton, SIGNAL(clicked()), this, SLOT(del_pos()));
  QObject::connect(m_gotoposbutton, SIGNAL(clicked()), this, SLOT(goto_pos()));
  QObject::connect(m_newposbutton, SIGNAL(clicked()), this, SLOT(new_pos()));

  QObject::connect(m_pos_list, SIGNAL(currentIndexChanged(int)), this, SLOT(change_pos(int)));

  scene->draw_skel();
  
  update_pos_list();

  timer=new QTimer(this);
  QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));

}


void Window::update_pos_list()
{
  m_pos_list->clear();
  m_destpos_list->clear();

  for( std::set<QString>::const_iterator iter =  scene->get_skel()->get_positions_list()->begin();iter !=  scene->get_skel()->get_positions_list()->end();++iter ) {
    m_pos_list->addItem(*iter);
    m_destpos_list->addItem(*iter);
  }

}

void Window::enable_all(bool enable)
{
  m_shotbutton->setEnabled(enable);
  m_saveposbutton->setEnabled(enable);
  m_newposbutton->setEnabled(enable);
  m_newposname_edit->setEnabled(enable);
  m_delposbutton->setEnabled(enable);
  m_gotoposbutton->setEnabled(enable);
  m_pos_list->setEnabled(enable);
  m_destpos_list->setEnabled(enable);
  m_animfile_label->setEnabled(enable);
  m_animfile_edit->setEnabled(enable);
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

void Window::del_pos()
{
  std::cout<<"Del position: "<<m_pos_list->currentText().toStdString()<<std::endl;
  scene->get_skel()->del_position(m_pos_list->currentText());
  scene->get_skel()->save();
  update_pos_list();
}

void Window::goto_pos()//begin animation
{
  std::cout<<"Animation to position: "<<m_destpos_list->currentText().toStdString()<<std::endl;
  scene->get_skel()->set_origin_dest_pos(m_pos_list->currentText(),m_destpos_list->currentText());
  scene->draw_skel();
  timer->start(TIMER_TIME);
  run_animation=true;
  anim_time=0.0;

  //see if needs to save it to files :
  if (m_animfile_edit->text()!=""){
    m_animation_number=1001;
    //shot
    QString filename=QString::number(m_animation_number);//how to add leading zeros ?
    filename="out/"+m_animfile_edit->text()+filename+".png";
    std::cout<<"Write to "<<filename.toStdString()<<std::endl;
    graph_view->ask_shot(filename);
  }
  enable_all(false);
}

void Window::timer_timeout()
{
  //std::cout<<"BIP"<<std::endl;
  if (run_animation){

    scene->get_skel()->update_anim(0.05);
    anim_time+=0.05;

    run_animation=anim_time<1.0;

    scene->draw_skel();
    //save img
    if (m_animation_number>0) {
      m_animation_number+=1;
      QString filename=QString::number(m_animation_number);//how to add leading zeros ?
      filename="out/"+m_animfile_edit->text()+filename+".png";
      std::cout<<"Write to "<<filename.toStdString()<<std::endl;
      graph_view->ask_shot(filename);
    }
    
    if (!run_animation) {
      run_animation=false;
      std::cout<<"Animation finished"<<std::endl;
      timer->stop();m_animation_number=0;

      //invert current pos and goto pos
      int pos1=m_pos_list->currentIndex();
      int pos2=m_destpos_list->currentIndex();
      m_pos_list->setCurrentIndex(pos2);
      m_destpos_list->setCurrentIndex(pos1);
      enable_all(true);

    } else {
      timer->start(TIMER_TIME);
      //std::cout<<"run_animation=true;"<<std::endl;
    }


  }
}


//create au new_pos
void Window::new_pos()
{
  //ask for a name
  QString posname=m_newposname_edit->text();
  std::cout<<"New position: "<<posname.toStdString()<<std::endl;
  scene->get_skel()->set_to_position(posname);
  scene->get_skel()->get_positions_list()->insert(posname);
  update_pos_list();
  scene->get_skel()->save_position(posname);
  scene->get_skel()->save();
}
