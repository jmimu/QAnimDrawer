#include "skel_edge.h"

#include <math.h>
#include <iostream>
#define PI 3.14159


Skel_Edge::Skel_Edge(Skel_Node *root,QString name,float z,double length,double orientation)
  : m_edgename(name),m_z(z),m_orientation(orientation),m_orientation_reference(orientation),m_length(length),m_max_length(length),m_min_length(length),m_from(root),m_to(NULL),m_previous(NULL),m_next(),m_got_image(false),m_image(NULL),m_origin_pos(NULL),m_dest_pos(NULL)
{
  m_to=new Skel_Node(0,0,this);
  calc_to();
  m_from->add_edge_from(this);
}

Skel_Edge::Skel_Edge(Skel_Edge *previous,QString name,float z,double length,double orientation)
  : m_edgename(name),m_z(z),m_orientation(orientation),m_orientation_reference(orientation),m_length(length),m_max_length(length),m_min_length(length),m_from(previous->to()),m_to(NULL),m_previous(previous),m_next(),m_got_image(false),m_image(NULL),m_origin_pos(NULL),m_dest_pos(NULL)
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
  //std::cout<<"set to position: "<<name.toStdString()<<" o"<<m_orientation<<" l"<<m_length<<std::endl;
  
  calc_to();
  set_length_reference();
  set_orientation_reference();
  
  std::list<Skel_Edge*>::iterator it;
  for( it = m_next.begin(); it != m_next.end(); ++it ) {
    (*it)->set_to_position(name);
  }  
  
  return true;
}

//recursive
bool Skel_Edge::save_position(QString name)
{
  std::map<QString,Skel_Edge_Pos*>::iterator iter = m_pos_list.find(name);
  if (iter == m_pos_list.end()) {
    return false;
  }
  iter->second->set_orientation(m_orientation);
  iter->second->set_length(m_length);
  
  std::list<Skel_Edge*>::iterator it;
  for( it = m_next.begin(); it != m_next.end(); ++it ) {
    (*it)->save_position(name);
  }  
  
  return true;
}

//recursive
bool Skel_Edge::del_position(QString name)
{
  std::map<QString,Skel_Edge_Pos*>::iterator iter = m_pos_list.find(name);
  if (iter == m_pos_list.end()) {
    return false;
  }
  m_pos_list.erase(iter);
  
  std::list<Skel_Edge*>::iterator it;
  for( it = m_next.begin(); it != m_next.end(); ++it ) {
    (*it)->del_position(name);
  }  
  
  return true;
}

void Skel_Edge::exportXML( QDomDocument &d,QDomElement &e)
{
  QDomElement e_edge = d.createElement( "edge" );
  e.appendChild(e_edge);

  e_edge.setAttribute( "name",m_edgename  );
  e_edge.setAttribute( "z",m_z  );


  QDomElement e_positions = d.createElement( "positions" );
  e_edge.appendChild(e_positions);
    
  std::map<QString,Skel_Edge_Pos*>::iterator pos_iter;
  for( pos_iter = m_pos_list.begin(); pos_iter != m_pos_list.end(); ++pos_iter ) {
    pos_iter->second->exportXML(d,e_positions);
  }
  
  QDomElement e_sons = d.createElement( "sons" );
  e_edge.appendChild(e_sons);

  std::list<Skel_Edge*>::iterator it;
  for( it = m_next.begin(); it != m_next.end(); ++it ) {
    (*it)->exportXML(d,e_sons);
  }
  
}
 
//recursive
bool Skel_Edge::set_origin_dest_pos(QString originname,QString destinationname)
{
  std::map<QString,Skel_Edge_Pos*>::iterator iter = m_pos_list.find(destinationname);
  if (iter == m_pos_list.end()) {
    return false;
  }
  m_dest_pos=iter->second;
  iter = m_pos_list.find(originname);
  if (iter == m_pos_list.end()) {
    return false;
  }
  m_origin_pos=iter->second;
  
  set_to_position(originname);

  std::list<Skel_Edge*>::iterator it;
  for( it = m_next.begin(); it != m_next.end(); ++it ) {
    (*it)->set_origin_dest_pos(originname,destinationname);
  }  
  
  return true;
}

//recursive
//time = 1 for the whole animation
void Skel_Edge::update_anim(double dt)
{
  double ang_speed=m_dest_pos->orientation()-m_origin_pos->orientation();
  
  m_orientation+=ang_speed*dt;
  m_orientation_reference=m_orientation;
  calc_to();

  std::list<Skel_Edge*>::iterator it;
  for( it = m_next.begin(); it != m_next.end(); ++it ) {
    (*it)->update_anim(dt);
  }  
  
}
