#ifndef GRAPHVIEWJM_H
#define GRAPHSCENEJM_H

#include <QGraphicsScene>


class GraphSceneJM: public QGraphicsScene
{
Q_OBJECT
    
 public:
  GraphSceneJM(QWidget * parent = 0);
 protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);	
		
};

#endif
