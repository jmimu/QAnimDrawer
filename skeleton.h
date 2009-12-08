#ifndef SKELETON_H
#define SKELETON_H

/**
  Skeleton : skel graph of a sprite
  **/


#include "skel_edge.h"
#include "skel_node.h"
#include <QGraphicsScene>
#include <QtXml/QDomDocument>
#include <list>

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
    void update_nodes_list();
    std::list <Skel_Node *> * get_nodes_list(){return &m_nodes_list;}

protected:
    Skel_Node m_origin;
    std::list <Skel_Node *> m_nodes_list;

    bool xml_read_edges_recursive(QDomNode n_sons,Skel_Edge *current_edge=NULL);

};

#endif // SKELETON_H
