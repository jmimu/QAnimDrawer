#include "skeleton.h"

#include <iostream>

Skeleton::Skeleton()
  : origin(0,0)
{
  make_object();
}

void Skeleton::make_object()
{
  Skel_Edge *bone1=new Skel_Edge(&origin,10);
}


void Skeleton::draw(QGraphicsScene *scene)
{
  //  QRect rectangle(10, 10, 100, 50);
  //scene->addRect(rectangle);
  QPen pen(Qt::blue, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
  /*QLine ligne(50, 50, 200, 200);
  scene->addLine(ligne, pen);
  std::cout<<"Draw skel"<<std::endl;
  */
  std::list<Skel_Edge*>::iterator it;
  for( it = origin.from_of()->begin(); it != origin.from_of()->end(); ++it ) {
    QLine ligne((*it)->from()->x(),(*it)->from()->y(),(*it)->to()->x(),(*it)->to()->y());
    scene->addLine(ligne, pen);
    std::cout<<"Add on bone..."<<std::endl;
  }
}
