#ifndef GRAPHVIEWJM_H
#define GRAPHVIEWJM_H

#include <QGraphicsView>


class GraphViewJM: public QGraphicsView
{
Q_OBJECT
    
 public:
  GraphViewJM(QGraphicsScene * scene, QWidget * parent = 0);
 public slots:
  void ask_shot(QString filename="img.jpg");
 private:

		
};

#endif
