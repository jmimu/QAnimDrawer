#ifndef SKEL_EDGE_POS_H
#define SKEL_EDGE_POS_H

/**
  Skel_Edge_Pos : position of an edge of the skel graph
  in an animation
  - len
  - angle
  - img
  **/
#include <QPixmap>

class Skel_Edge_Pos
{
public:
  Skel_Edge_Pos(QString name,double length,double orientation);
  bool add_image(QString filename,bool flipY=false);
  bool got_image(){return m_got_image;}
  QPixmap * image(){if (m_got_image) return &m_image; else return NULL;}
  double orientation(){return m_orientation;}
  double length(){return m_length;}
  int flipY_img(){return m_flipY_img;}
  QString get_name(){return m_name;}
  QString get_image_filename(){return m_image_filename;}

  void set_orientation(double orient){m_orientation=orient;}
  void set_length(double len){m_length=len;}
protected:
  double m_orientation;
  double m_length;
  bool m_got_image;
  QPixmap m_image;
  int m_flipY_img;
  QString m_name;
  QString m_image_filename;

};

#endif // SKEL_EDGE_H
