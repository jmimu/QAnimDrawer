#ifndef SKEL_EDGE_H
#define SKEL_EDGE_H

/**
  Skel_Edge : an edge of the skel graph
  TODO : add a picture
  **/

#include "skel_node.h"

class Skel_Edge
{
public:
    Skel_Edge();
protected:
    double m_orientation;
    double m_length;
    double m_max_length;
    double m_min_length;
    Skel_Node *m_from;
    Skel_Node *m_to;
};

#endif // SKEL_EDGE_H
