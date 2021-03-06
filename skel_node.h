#ifndef SKEL_NODE_H
#define SKEL_NODE_H

/**
  Skel_Node : an node of the skel graph
  **/

#include <QGraphicsScene>
#include <list>

class Skel_Edge;

class Skel_Node
{
public:
  Skel_Node(double x,double y,Skel_Edge *edge);
  void set_x(double x){m_x=x;}
  void set_y(double y){m_y=y;}
  double x(){return m_x;}
  double y(){return m_y;}
  void add_edge_from(Skel_Edge *edge){m_from_of.push_back(edge);}
  std::list<Skel_Edge *> * from_of(){return &m_from_of;}
  void draw_recursive(QGraphicsScene *scene, bool draw_lines=true);

  Skel_Edge * to_of(){return m_to_of;}
  void get_nodes_recursive(std::list <Skel_Node *> * nodes_list);

protected:
  double m_x,m_y;
  double m_previous_x,m_previous_y;
  std::list<Skel_Edge *> m_from_of;
  Skel_Edge * m_to_of;
};

#endif // SKEL_NODE_H
