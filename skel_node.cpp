#include "skel_node.h"

#include "skel_edge.h"
#include <QtGui>
#include <iostream>
#include <math.h>
#define PI 3.14159

Skel_Node::Skel_Node(double x,double y,Skel_Edge *edge)
  : m_x(x),m_y(y),m_from_of(),m_to_of(edge)
{
}

/**
   recursive drawing function
*/
void Skel_Node::draw_recursive(QGraphicsScene *scene)
{
  QPen pen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
  std::list<Skel_Edge*>::iterator it;
  for( it = from_of()->begin(); it != from_of()->end(); ++it ) {
    if (!(*it)->got_image()){    
      QLine ligne((*it)->from()->x(),(*it)->from()->y(),(*it)->to()->x(),(*it)->to()->y());
      scene->addLine(ligne, pen);
      //std::cout<<"add a line !"<<std::endl;
    }else{
      QGraphicsItem *item;
      item = scene->addPixmap(*((*it)->image()));

      double decalY=-(*it)->image()->height()/2;
      double decalX=-(*it)->image()->height();
      double angle=(*it)->orientation()*PI/180.;
      double scaleX=(*it)->length()/((*it)->image()->width() - (*it)->image()->height()*2);
      double scaleY=(*it)->flipY_img();
      item->rotate((*it)->orientation());
      item->scale(scaleX,scaleY);
      item->moveBy(scaleY*decalY*sin(-angle)+scaleX*decalX*cos(angle) + (*it)->from()->x(),
		   scaleY*decalY*cos(-angle)+scaleX*decalX*sin(angle) + (*it)->from()->y());

      //std::cout<<"pic : "<<(*it)->from()->x()<<"  "<<(*it)->from()->y()<<"  "<<(*it)->orientation()<<std::endl;

    }
     
    if ((*it)->to() != NULL) (*it)->to()->draw_recursive(scene);
  }
}

void Skel_Node::get_nodes_recursive(std::list <Skel_Node *> * nodes_list)
{
  nodes_list->push_back(this);
  std::list<Skel_Edge*>::iterator it;
  for( it = from_of()->begin(); it != from_of()->end(); ++it ) {
    if ((*it)->to() != NULL) (*it)->to()->get_nodes_recursive(nodes_list);
  }  
}
