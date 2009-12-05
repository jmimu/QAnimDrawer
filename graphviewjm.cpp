#include "graphviewjm.h"

#include <QtGui>
#include <iostream>

GraphViewJM::GraphViewJM(QWidget * parent)
	: QGraphicsView(parent)
{
	
}


void GraphViewJM::ask_shot()
{
    QPainter *pngPainter = new QPainter();
    QImage *image = new QImage(QSize(this->width(),this->height() ), QImage::Format_ARGB32);
    // Resolution of the image is 600 dpi by default
    //image->setDotsPerMeterX(600*254);
    //image->setDotsPerMeterY(600*254);
    pngPainter->begin(image);
    render(pngPainter);
    pngPainter->end();
    image->save("img.png",0,-1);
    delete pngPainter;
    delete image;
}
