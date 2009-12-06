#include "graphscenejm.h"

#include <QtGui>
#include <iostream>

GraphSceneJM::GraphSceneJM(QWidget * parent)
  : QGraphicsScene(parent)
{
  std::cout<<"_!"<<std::endl;
}


void GraphSceneJM::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    std::cout<<"yo! "<<mouseEvent->scenePos().x()<<" "<<mouseEvent->scenePos().y()<<std::endl;

}
