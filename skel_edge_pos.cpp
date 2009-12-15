#include "skel_edge_pos.h"

#include <math.h>
#include <iostream>
#define PI 3.14159


Skel_Edge_Pos::Skel_Edge_Pos(QString name,double length,double orientation)
  : m_orientation(orientation),m_length(length),m_got_image(false),m_image(),m_name(name),m_image_filename("")
{
  std::cout<<"make Position: "<<name.toStdString()<<" "<<orientation<<" "<<length<<std::endl;
}

bool Skel_Edge_Pos::add_image(QString filename,bool flipY)
{
  std::cout<<"Add image: "<<filename.toStdString()<<std::endl;
  m_got_image=false;
  m_got_image=m_image.load(filename, 0, Qt::AutoColor);
  if (m_got_image) m_image_filename=filename;
  if (flipY) m_flipY_img=-1;
  else m_flipY_img=1; 

  return m_got_image;
}
