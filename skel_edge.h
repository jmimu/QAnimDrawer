#ifndef SKEL_EDGE_H
#define SKEL_EDGE_H

/**
  Skel_Edge : an edge of the skel graph
  TODO : add a picture
  **/
#include "skel_edge_pos.h"
#include "skel_node.h"
#include <list>
#include <map>
#include <QtXml/QDomDocument>

class Skel_Edge
{
public:
  Skel_Edge(Skel_Node *root,QString name,float z,double length=1.0,double orientation=0.0); //orientation in degrees
  Skel_Edge(Skel_Edge *previous,QString name,float z,double length=1.0,double orientation=0.0); //orientation in degrees
  void calc_to();
  Skel_Node * from(){return m_from;}
  Skel_Node * to(){return m_to;}
  Skel_Edge * previous(){return m_previous;}
  std::list<Skel_Edge *> * next(){return &m_next;}
  bool got_image(){return m_got_image;}
  QPixmap * image(){if (m_got_image) return m_image; else return NULL;}
  double orientation(){return m_orientation;}
  void set_orientation_delta(double delta_orient){m_orientation=m_orientation_reference+delta_orient;calc_to();}
  void set_length_delta(double delta_len){m_length=m_length_reference+delta_len;calc_to();}
  void set_orientation_reference();
  void set_length_reference(){m_length_reference=m_length;}
  double length(){return m_length;}
  int flipY_img(){return m_flipY_img;}
  bool set_to_position(QString name);
  bool set_origin_dest_pos(QString originname,QString destinationname);
  bool save_position(QString name);
  bool del_position(QString name);
  void add_position(QString pos_name,Skel_Edge_Pos* pos){m_pos_list.insert(std::make_pair(pos_name,pos));}
  void exportXML( QDomDocument &d,QDomElement &e);
  void update_anim(double dt);
  float get_z(){return m_z;}
protected:
  //current data
  QString m_edgename;
  float m_z;
  double m_orientation;
  double m_orientation_reference;
  double m_length;
  double m_length_reference;
  double m_max_length;
  double m_min_length;
  Skel_Node *m_from;
  Skel_Node *m_to;
  Skel_Edge *m_previous;
  std::list <Skel_Edge *> m_next;
  bool m_got_image;
  QPixmap *m_image;
  int m_flipY_img;

  std::map <QString,Skel_Edge_Pos*> m_pos_list;
  //for animation
  Skel_Edge_Pos* m_origin_pos;
  Skel_Edge_Pos* m_dest_pos;
};

#endif // SKEL_EDGE_H
