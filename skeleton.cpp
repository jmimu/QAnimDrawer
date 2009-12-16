#include "skeleton.h"

#include <iostream>

#include <QFile>
#include <QTextStream>

Skeleton::Skeleton()
  : m_origin(0,0,NULL),m_nodes_list()
{
 
}

void Skeleton::update_nodes_list()
{
  m_nodes_list.clear();
  m_origin.get_nodes_recursive(&m_nodes_list);
  std::cout<<m_nodes_list.size()<<" nodes found"<<std::endl;
}

void Skeleton::draw(QGraphicsScene *scene)
{
  m_origin.draw_recursive(scene);
}

bool Skeleton::set_to_position(QString name)
{
  std::list<Skel_Edge*>::iterator it;
  for( it = m_origin.from_of()->begin(); it != m_origin.from_of()->end(); ++it ) {
    (*it)->set_to_position(name);
  }

  return true;
}

bool Skeleton::save_position(QString name)
{
  std::list<Skel_Edge*>::iterator it;
  for( it = m_origin.from_of()->begin(); it != m_origin.from_of()->end(); ++it ) {
    (*it)->save_position(name);
  }
  return true;
}


bool Skeleton::load()
{
  std::cout<<"Begin load..."<<std::endl;
  m_positions_list.clear();

  QDomDocument doc( "JMskel" );
  QFile file( "test.xml" );
  if( !file.open( QIODevice::ReadOnly ) ){
    std::cout<<"Unable to open xml file"<<std::endl;
    return false;
  }
  if( !doc.setContent( &file ) )
    {
      file.close();
      std::cout<<"Unable to read xml"<<std::endl;
      return false;
    }
  file.close();

  QDomElement root = doc.documentElement();
  if( root.tagName() != "QAnimDrawer" ) {
    std::cout<<"Wrong root element"<<std::endl;
    return false;
  }



  QDomNode n = root.firstChild();
  while( !n.isNull() ) {
    QDomElement e = n.toElement();
    if( !e.isNull() ) {
      if( e.tagName() == "skeleton" ) {
	std::cout<<"Found a new skeleton..."<<std::endl;
	QDomNode n_origin = e.firstChild();
	if (n_origin.isNull()) {
	  std::cout<<"no origin !"<<std::endl;
	  n = n.nextSibling();continue;
	}
	QDomElement e_origin = n_origin.toElement();
	if( e_origin.tagName() != "origin" ) {
	  std::cout<<"skeleton child is not origin !"<<std::endl;
	  n = n.nextSibling();continue;
	}
	
	m_origin.set_x(e_origin.attribute( "x", "" ).toFloat());
	m_origin.set_y(e_origin.attribute( "y", "" ).toFloat());

	std::cout<<"origin:\t"<<m_origin.x()<<"\t"<<m_origin.y()<<std::endl;

	QDomNode n_origin_sons = e_origin.firstChild();
	xml_read_edges_recursive(n_origin_sons);

      }
    }
    n = n.nextSibling();
  }


  std::cout<<"Correct load end."<<std::endl;
  update_nodes_list();
  set_to_position("ini");
  return true;
}


bool Skeleton::save()
{
  std::cout<<"Write file"<<std::endl;

  QDomDocument doc( "JMskel" );
  QDomElement root = doc.createElement( "QAnimDrawer" );
  doc.appendChild( root );

  /*  Contact c;
  c.name = "Kal";
  c.eMail = "kal@goteborg.se";
  c.phone = "+46(0)31 123 4567";
  root.appendChild( ContactToNode( doc, c ) );*/

  QDomElement e_version = doc.createElement("version");
  root.appendChild(e_version);
  QDomText versionText = doc.createTextNode("0.01");
  e_version.appendChild(versionText);

  std::list<Skel_Edge*>::iterator it;
  for( it = m_origin.from_of()->begin(); it != m_origin.from_of()->end(); ++it ) {
    (*it)->exportXML(doc,root);
  }

  QFile file( "test0.xml" );
  if( !file.open( QIODevice::WriteOnly ) )
    return false;

  QTextStream ts( &file );
  ts << doc.toString();

  file.close();

  return true;
}


bool Skeleton::xml_read_edges_recursive(QDomNode n_sons,Skel_Edge *current_edge)
{
  std::cout<<"enter xml_read_edges_recursive"<<std::endl;

  if (n_sons.isNull()) {
    std::cout<<"Element has no child !"<<std::endl;
    return false;
  }
  QDomElement e_sons = n_sons.toElement();
  if( e_sons.tagName() != "sons" ) {
    std::cout<<"Element had to be \"sons\" !"<<std::endl;
    return false;
  }
	
  QDomNode n_edge = e_sons.firstChild();
  while (!n_edge.isNull() ) {
    QDomElement e_edge = n_edge.toElement();
    if( e_edge.tagName() != "edge" ) {
      std::cout<<"Not an edge !"<<std::endl;
      n_edge = n_edge.nextSibling();continue;
    }
    //new edge
    Skel_Edge *edge_tmp;

    if (current_edge == NULL) edge_tmp=new Skel_Edge(&m_origin);
    else edge_tmp=new Skel_Edge(current_edge);

    std::cout<<"edge:\t"<<e_edge.attribute( "len", "" ).toFloat()<<"\t"<<e_edge.attribute( "ang", "" ).toFloat()<<std::endl;

    //for each child : if positions or sons
    QDomNode n_edge_descendent = e_edge.firstChild();
    while (!n_edge_descendent.isNull() ) {
      QDomElement e_edge_descendent = n_edge_descendent.toElement();
      if( e_edge_descendent.tagName() == "positions" )
	xml_read_edges_pos(n_edge_descendent,edge_tmp);
      if( e_edge_descendent.tagName() == "sons" )
	xml_read_edges_recursive(n_edge_descendent,edge_tmp);

      n_edge_descendent= n_edge_descendent.nextSibling();
    }


    n_edge = n_edge.nextSibling();
  }
  return true;
}


bool Skeleton::xml_read_edges_pos(QDomNode n_positions,Skel_Edge *current_edge)
{
 std::cout<<"enter xml_read_edges_pos"<<std::endl;

  if (n_positions.isNull()) {
    std::cout<<"Element has no positions !"<<std::endl;
    return false;
  }
  QDomElement e_positions = n_positions.toElement();
  if( e_positions.tagName() != "positions" ) {
    std::cout<<"Element had to be \"positions\" !"<<std::endl;
    return false;
  }
	
  QDomNode n_pos = e_positions.firstChild();
  while (!n_pos.isNull() ) {
    QDomElement e_pos = n_pos.toElement();
    if( e_pos.tagName() != "pos" ) {
      std::cout<<"Not an pos !"<<std::endl;
      n_pos = n_pos.nextSibling();continue;
    }
    //new pos
    std::cout<<"Pos name: "<<e_pos.attribute( "name", "" ).toStdString()<<std::endl;
    QString pos_name=e_pos.attribute( "name", "" );
    Skel_Edge_Pos *pos = new Skel_Edge_Pos(e_pos.attribute( "name", "" ),e_pos.attribute( "len", "" ).toFloat(),e_pos.attribute( "ang", "" ).toFloat());
    bool symmetric=( e_pos.attribute( "sym", "" ) == "true" );
    pos->add_image(e_pos.attribute( "img", "" ), symmetric);

    current_edge->add_position(pos_name,pos);

    //xcurrent_edge->set_to_position("ini");//for debug

    m_positions_list.insert(pos_name);


    n_pos = n_pos.nextSibling();
  }

  return true;
}
