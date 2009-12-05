#ifndef SKEL_NODE_H
#define SKEL_NODE_H

/**
  Skel_Node : an node of the skel graph
  **/

class Skel_Node
{
public:
    Skel_Node();
protected:
    double m_x,m_y;
    double m_weight;
};

#endif // SKEL_NODE_H
