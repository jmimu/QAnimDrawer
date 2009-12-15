#include "skel_edge.h"

#include <math.h>
#include <iostream>
#define PI 3.14159


Skel_Edge::Skel_Edge(Skel_Node *root,double length,double orientation)
  : m_orientation(orientation),m_orientation_reference(orientation),m_length(length),m_max_length(length),m_min_length(length),m_from(root),m_to(NULL),m_previous(NULL),m_next(),m_got_image(false),m_image(NULL)
{
  m_to=new Skel_Node(0,0,this);
  calc_to();
  m_from->add_edge_from(this);
}

Skel_Edge::Skel_Edge(Skel_Edge *previous,double length,double orientation)
  : m_orientation(orientation),m_orientation_reference(orientation),m_length(length),m_max_length(length),m_min_length(length),m_from(previous->to()),m_to(NULL),m_previous(previous),m_next(),m_got_image(false),m_image(NULL)
{
  m_to=new Skel_Node(0,0,this);
  calc_to();
  m_from->add_edge_from(this);
  m_previous->m_next.push_back(this);
}

/**
   Calc coord of m_to point
 */
void Skel_Edge::calc_to()
{
  m_to->set_x(m_from->x()+m_length*cos(m_orientation*PI/180.));
  m_to->set_y(m_from->y()+m_length*sin(m_orientation*PI/180.));

  std::list<Skel_Edge*>::iterator it;
  for( it = m_next.begin(); it != m_next.end(); ++it ) {
    (*it)->set_orientation_delta(m_orientation-m_orientation_reference);
  }  

}

//recursive because all descendent may be affected
void Skel_Edge::set_orientation_reference()
{
  m_orientation_reference=m_orientation;
  std::list<Skel_Edge*>::iterator it;
  for( it = m_next.begin(); it != m_next.end(); ++it ) {
    (*it)->set_orientation_reference();
  }  
}

//recursive
bool Skel_Edge::set_to_position(QString name)
{
  std::map<QString,Skel_Edge_Pos*>::iterator iter = m_pos_list.find(name);
  if (iter == m_pos_list.end()) {
    //create the pos
    //get the first position
    Skel_Edge_Pos *first_pos = m_pos_list.begin()->second;
    Skel_Edge_Pos *pos = new Skel_Edge_Pos(name,first_pos->length(),first_pos->orientation());
    if (first_pos->got_image()) {
      pos->add_image(first_pos->get_image_filename(),first_pos->flipY_img()!=1);
    }
    iter =( m_pos_list.insert(std::make_pair(name,pos)) ).first;
  }
  m_orientation= iter->second->orientation();
  m_length= iter->second->length();
  m_image= iter->second->image();
  m_flipY_img= iter->second->flipY_img();
  m_got_image= iter->second->got_image();
  std::cout<<"set to position: "<<name.toStdString()<<" o"<<m_orientation<<" l"<<m_length<<std::endl;
  
  calc_to();
  set_length_reference();
  set_orientation_reference();
  
  std::list<Skel_Edge*>::iterator it;
  for( it = m_next.begin(); it != m_next.end(); ++it ) {
    (*it)->set_to_position(name);
  }  
  
  return true;
}
