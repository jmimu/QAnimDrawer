#ifndef SKELETON_H
#define SKELETON_H

/**
  Skeleton : skel graph of a sprite
  **/


#include "skel_edge.h"
#include "skel_node.h"

#include <QtGui>

/**
   Skeleton is a tree
*/

class Skeleton
{
public:
    Skeleton();
    
    void make_object();
    bool load();
    bool save();
    void draw(QGraphicsScene *scene);
protected:
    Skel_Node origin;
};

#endif // SKELETON_H
