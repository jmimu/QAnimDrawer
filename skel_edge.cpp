#include "skel_edge.h"

#include <math.h>

Skel_Edge::Skel_Edge(Skel_Node *root,double length,double orientation)
  : m_orientation(orientation),m_length(length),m_max_length(length),m_min_length(length),m_from(root),m_to(NULL),m_previous(NULL),m_next()
{
  m_to=new Skel_Node(0,0);
  calc_to();
  m_from->add_edge_from(this);
}

Skel_Edge::Skel_Edge(Skel_Edge *previous,double length,double orientation)
  : m_orientation(orientation),m_length(length),m_max_length(length),m_min_length(length),m_from(previous->to()),m_to(NULL),m_previous(previous),m_next()
{
  m_to=new Skel_Node(0,0);
  calc_to();
  m_from->add_edge_from(this);
}

/**
   Calc coord of m_to point
 */
void Skel_Edge::calc_to()
{
  m_to->set_x(m_from->x()+m_length*cos(m_orientation));
  m_to->set_y(m_from->y()+m_length*sin(m_orientation));
}
