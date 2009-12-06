#ifndef SKEL_EDGE_H
#define SKEL_EDGE_H

/**
  Skel_Edge : an edge of the skel graph
  TODO : add a picture
  **/

#include "skel_node.h"
#include <list>


class Skel_Edge
{
public:
  Skel_Edge(Skel_Node *root,double length=1.0,double orientation=0.0); //orientation in degrees
  Skel_Edge(Skel_Edge *previous,double length=1.0,double orientation=0.0); //orientation in degrees
  Skel_Node * from(){return m_from;}
  Skel_Node * to(){return m_to;}
  Skel_Edge * previous(){return m_previous;}
  std::list<Skel_Edge *> * next(){return &m_next;}
  bool add_image(QString filename,bool flipY=false);
  bool got_image(){return m_got_image;}
  QPixmap * image(){if (m_got_image) return &m_image; else return NULL;}
  double orientation(){return m_orientation;}
  double length(){return m_length;}
  int flipY_img(){return m_flipY_img;}
protected:
  double m_orientation;
  double m_length;
  double m_max_length;
  double m_min_length;
  Skel_Node *m_from;
  Skel_Node *m_to;
  Skel_Edge *m_previous;
  std::list <Skel_Edge *> m_next;
  bool m_got_image;
  QPixmap m_image;
  int m_flipY_img;

  void calc_to();
};

#endif // SKEL_EDGE_H
