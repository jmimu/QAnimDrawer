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
    QLine ligne((*it)->from()->x(),(*it)->from()->y(),(*it)->to()->x(),(*it)->to()->y());
    scene->addLine(ligne, pen);

    if ((*it)->got_image()){
      QGraphicsItem *item;
      item = scene->addPixmap(*((*it)->image()));


         
      /*   double decal=-(*it)->image()->height()/2;   
	   item->setPos(decal*sin(-(*it)->orientation()*PI/180.) + (*it)->from()->x()
		   , decal*cos(-(*it)->orientation()*PI/180.) + (*it)->from()->y());
           item->rotate((*it)->orientation());
	   item->scale((*it)->length()/(*it)->image()->width(),1.0);
      */

      /*double decalY=-(*it)->image()->height()/2;
      double decalX=-(*it)->image()->height();
      double angle=(*it)->orientation()*PI/180.;
      item->setPos(decalX*cos(-angle) + decalY*sin(-angle) +  (*it)->from()->x()
		   , decalX*sin(-angle) + decalY*cos(-angle) + (*it)->from()->y());
      item->rotate((*it)->orientation());
      //item->scale((*it)->length()/((*it)->image()->width() - (*it)->image()->height()*2),1.0);
      */

      double decalY=-(*it)->image()->height()/2;
      double decalX=-(*it)->image()->height();
      double angle=(*it)->orientation()*PI/180.;
      double scaleX=(*it)->length()/((*it)->image()->width() - (*it)->image()->height()*2);
      double scaleY=(*it)->flipY_img();
      item->rotate((*it)->orientation());
      item->scale(scaleX,scaleY);
      item->moveBy(scaleY*decalY*sin(-angle)+scaleX*decalX*cos(angle) + (*it)->from()->x(),
		   scaleY*decalY*cos(-angle)+scaleX*decalX*sin(angle) + (*it)->from()->y());

      std::cout<<"pic : "<<(*it)->from()->x()<<"  "<<(*it)->from()->y()<<"  "<<(*it)->orientation()<<std::endl;

    }
     
    if ((*it)->to() != NULL) (*it)->to()->draw_recursive(scene);
  }
}
