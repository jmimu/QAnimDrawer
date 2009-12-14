#ifndef GRAPHVIEWJM_H
#define GRAPHSCENEJM_H

#include <QGraphicsScene>
#include "skeleton.h"


class GraphSceneJM: public QGraphicsScene
{
  Q_OBJECT
    
  public:
    GraphSceneJM(QWidget * parent = 0);
    void draw_skel();
    Skeleton * get_skel(){return &skel;}
  
  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);	
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);	
    Skeleton skel;		
    Skel_Node *node_selection;
    int x_begin_right_click;
    int y_begin_right_click;
};

#endif
