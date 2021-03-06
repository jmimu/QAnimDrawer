#ifndef SKELETON_H
#define SKELETON_H

/**
  Skeleton : skel graph of a sprite
  **/


#include "skel_edge.h"
#include "skel_node.h"
#include "skel_edge_pos.h"
#include <QGraphicsScene>
#include <QtXml/QDomDocument>
#include <list>
#include <set>

/**
   Skeleton is a tree
*/

class Skeleton
{
public:
    Skeleton();
    
    bool load(QString filename);
    bool save(QString filename);
    void draw(QGraphicsScene *scene, bool draw_lines=true);
    void update_nodes_list();
    std::list <Skel_Node *> * get_nodes_list(){return &m_nodes_list;}
    bool set_to_position(QString name);
    bool save_position(QString name);
    bool del_position(QString name);
    std::set <QString> * get_positions_list(){return &m_positions_list;}

    bool set_origin_dest_pos(QString originposname,QString destposname);
    void update_anim(double dt,double total_time);
protected:
    Skel_Node m_origin;
    std::list <Skel_Node *> m_nodes_list;
    std::set <QString> m_positions_list;

    bool xml_read_edges_recursive(QDomNode n_sons,Skel_Edge *current_edge=NULL);
    bool xml_read_edges_pos(QDomNode n_sons,Skel_Edge *current_edge);

};

#endif // SKELETON_H
