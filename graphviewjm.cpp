#include "graphviewjm.h"

#include <QtGui>
#include <iostream>

GraphViewJM::GraphViewJM(QGraphicsScene * scene, QWidget * parent)
  : QGraphicsView(scene,parent)
{
  setSceneRect(-128,-128,256,256);
}


void GraphViewJM::ask_shot(QString filename)
{
    QPainter *pngPainter = new QPainter();
    QImage *image = new QImage(QSize(this->width(),this->height() ), QImage::Format_ARGB32);
    // Resolution of the image is 600 dpi by default
    //image->setDotsPerMeterX(600*254);
    //image->setDotsPerMeterY(600*254);
    pngPainter->begin(image);
    render(pngPainter);
    pngPainter->end();
    image->save(filename,0,-1);
    delete pngPainter;
    delete image;
}

