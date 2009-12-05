#ifndef SKELETON_H
#define SKELETON_H

/**
  Skeleton : skel graph of a sprite
  **/


#include "skel_edge.h"
#include "skel_node.h"

class Skeleton
{
public:
    Skeleton();
    
	void makeObject();
    bool load();
    bool save();
protected:
    Skel_Node *origin;
};

#endif // SKELETON_H
