#include "skel_edge.h"

#include <math.h>
#define PI 3.14159


Skel_Edge::Skel_Edge(Skel_Node *root,double length,double orientation)
  : m_orientation(orientation),m_length(length),m_max_length(length),m_min_length(length),m_from(root),m_to(NULL),m_previous(NULL),m_next(),m_got_image(false),m_image()
{
  m_to=new Skel_Node(0,0,this);
  calc_to();
  m_from->add_edge_from(this);
}

Skel_Edge::Skel_Edge(Skel_Edge *previous,double length,double orientation)
  : m_orientation(orientation),m_length(length),m_max_length(length),m_min_length(length),m_from(previous->to()),m_to(NULL),m_previous(previous),m_next(),m_got_image(false),m_image()
{
  m_to=new Skel_Node(0,0,this);
  calc_to();
  m_from->add_edge_from(this);
}

/**
   Calc coord of m_to point
 */
void Skel_Edge::calc_to()
{
  m_to->set_x(m_from->x()+m_length*cos(m_orientation*PI/180.));
  m_to->set_y(m_from->y()+m_length*sin(m_orientation*PI/180.));
}

bool Skel_Edge::add_image(QString filename,bool flipY)
{
  m_got_image=false;
  m_got_image=m_image.load(filename, 0, Qt::AutoColor);

  if (flipY) m_flipY_img=-1;
  else m_flipY_img=1; 

  return m_got_image;
}
