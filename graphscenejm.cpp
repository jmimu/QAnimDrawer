#include "graphscenejm.h"

#include <QtGui>
#include <iostream>
#include <math.h>

GraphSceneJM::GraphSceneJM(QString filename,QWidget * parent)
  : QGraphicsScene(parent),skel(),node_selection(NULL),x_begin_right_click(0),y_begin_right_click(0)
{
  //std::cout<<"_!"<<std::endl;
  skel.load(filename);
  setBackgroundBrush(Qt::white);

}

void GraphSceneJM::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
  if (mouseEvent->buttons() != Qt::RightButton)
    return;

  if (node_selection == NULL)
    return;

  if (node_selection->to_of() == NULL){
    node_selection->set_x(mouseEvent->scenePos().x()-x_begin_right_click);  
    node_selection->set_y(mouseEvent->scenePos().y()-y_begin_right_click);
    std::list<Skel_Edge*>::iterator it;
    for( it =  node_selection->from_of()->begin(); it !=  node_selection->from_of()->end(); ++it )
      (*it)->calc_to();
  }else{
    node_selection->to_of()->set_orientation_delta(mouseEvent->scenePos().x()-x_begin_right_click);
    //node_selection->to_of()->set_length_delta(mouseEvent->scenePos().y()-y_begin_right_click);
  }

  draw_skel();
}


void GraphSceneJM::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
  if (mouseEvent->button() != Qt::LeftButton){
    x_begin_right_click=mouseEvent->scenePos().x();
    y_begin_right_click=mouseEvent->scenePos().y();
  }else{
    if ((node_selection != NULL)&& (node_selection->to_of() != NULL) ) {
      node_selection->to_of()->set_orientation_reference(); 
      node_selection->to_of()->set_length_reference(); 
    }
    int x_mouse=mouseEvent->scenePos().x();
    int y_mouse=mouseEvent->scenePos().y();
    //std::cout<<"yo! "<<mouseEvent->scenePos().x()<<" "<<mouseEvent->scenePos().y()<<std::endl;
  

    //try to find which node was clicked
    Skel_Node* closest_node=NULL;
    double min_dist=10000.;
    double dist=10000.;
    std::list<Skel_Node*>::iterator it;
    for( it = skel.get_nodes_list()->begin(); it !=skel.get_nodes_list()->end(); ++it ) {
      dist=sqrt(((*it)->x()-x_mouse)*((*it)->x()-x_mouse)+((*it)->y()-y_mouse)*((*it)->y()-y_mouse));
      //std::cout<<"Compare with: "<<(*it)->x()<<" "<<(*it)->y()<<" : "<<dist<<"   min "<<min_dist<<std::endl;
      if (dist<min_dist){
	min_dist=dist;
	closest_node=(*it);
      }
    }
    
    if (min_dist<10){
      //one was clicked
      node_selection=closest_node;
      //std::cout<<"Selection !"<<std::endl;
    }
  }
  draw_skel();
}

void GraphSceneJM::draw_skel()
{
  clear ();
  skel.draw(this);
  if (node_selection != NULL){
    //std::cout<<"sel: "<<node_selection->x()<<" "<<node_selection->y()<<std::endl;
    QPen pen(Qt::green, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QGraphicsEllipseItem * circle = addEllipse(node_selection->x()-10,node_selection->y()-10 , 20, 20, pen);
    circle->setZValue(100000);//to be above everything

  }
}
