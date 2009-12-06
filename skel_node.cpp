#include "skel_node.h"

#include "skel_edge.h"
#include <QtGui>
#include <iostream>
#include <math.h>
#define PI 3.14159

Skel_Node::Skel_Node(double x,double y)
  : m_x(x),m_y(y),m_from_of()
{
}

/**
   recursive drawing function
*/
void Skel_Node::draw_recursive(QGraphicsScene *scene)
{
  QPen pen(Qt::blue, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
  std::list<Skel_Edge*>::iterator it;
  for( it = from_of()->begin(); it != from_of()->end(); ++it ) {
    if ((*it)->got_image()){
      QGraphicsItem *item;
      item = scene->addPixmap(*((*it)->image()));
      double decal=-(*it)->image()->height()/2;
      item->setPos(decal*sin(-(*it)->orientation()*PI/180.) + (*it)->from()->x()
		   , decal*cos(-(*it)->orientation()*PI/180.) + (*it)->from()->y());
      //item->setPos(-(*it)->image()->width()/2+(*it)->from()->x(),(*it)->from()->y());
      item->rotate((*it)->orientation());

      std::cout<<"pic : "<<(*it)->from()->x()<<"  "<<(*it)->from()->y()<<"  "<<(*it)->orientation()<<std::endl;

    }else{
      QLine ligne((*it)->from()->x(),(*it)->from()->y(),(*it)->to()->x(),(*it)->to()->y());
      scene->addLine(ligne, pen);
    }
    if ((*it)->to() != NULL) (*it)->to()->draw_recursive(scene);
  }
}
