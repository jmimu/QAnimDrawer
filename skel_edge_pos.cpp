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
  //std::cout<<"Add image: "<<filename.toStdString()<<std::endl;
  m_got_image=false;
  m_got_image=m_image.load(filename, 0, Qt::AutoColor);
  if (m_got_image) m_image_filename=filename;
  if (flipY) m_flipY_img=-1;
  else m_flipY_img=1; 

  return m_got_image;
}

void Skel_Edge_Pos::exportXML( QDomDocument &d,QDomElement &e)
{
  //std::cout<<"Skel_Edge_Pos::exportXML "<<m_name.toStdString()<<std::endl;
  QDomElement e_pos = d.createElement( "pos" );
  e.appendChild(e_pos);
  e_pos.setAttribute( "name", m_name );
  e_pos.setAttribute( "len", m_length );
  e_pos.setAttribute( "ang", m_orientation );
  e_pos.setAttribute( "img", m_image_filename );
  QString sym="true";
  if (m_flipY_img==1) sym="false";
  e_pos.setAttribute( "sym", sym );
} 
