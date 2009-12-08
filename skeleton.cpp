#include "skeleton.h"

#include <iostream>
#include <QtXml/QDomDocument>
#include <QFile>


Skeleton::Skeleton()
  : m_origin(0,0,NULL),m_nodes_list()
{
  make_object();
}

void Skeleton::make_object()
{
  Skel_Edge *head=new Skel_Edge(&m_origin,30,-90);
  head->add_image("head.png");
  
  Skel_Edge *l_sholder=new Skel_Edge(&m_origin,30,-180);
  l_sholder->add_image("arm.png", true);
  Skel_Edge *r_sholder=new Skel_Edge(&m_origin,30,0);
  r_sholder->add_image("arm.png");
  
  Skel_Edge *l_arm1=new Skel_Edge(l_sholder,35,-150);
  l_arm1->add_image("arm.png", true);
  Skel_Edge *r_arm1=new Skel_Edge(r_sholder,35,-30);
  r_arm1->add_image("arm.png");
  Skel_Edge *l_forearm=new Skel_Edge(l_arm1,35,-140);
  l_forearm->add_image("forearm.png", true);
  Skel_Edge *r_forearm=new Skel_Edge(r_arm1,35,-40);
  r_forearm->add_image("forearm.png");
  
  Skel_Edge *l_hand=new Skel_Edge(l_forearm,25,-150);
  l_hand->add_image("hand.png", true);
  Skel_Edge *r_hand=new Skel_Edge(r_forearm,25,-80);
  r_hand->add_image("hand.png");
  
  Skel_Edge *body=new Skel_Edge(&m_origin,50,90);
  body->add_image("body.png");
  
  Skel_Edge *l_leg1=new Skel_Edge(body,40,120);
  l_leg1->add_image("leg.png",true);
  Skel_Edge *l_leg2=new Skel_Edge(l_leg1,50,90);
  l_leg2->add_image("leg2.png", true);
  Skel_Edge *r_leg1=new Skel_Edge(body,40,60);
  r_leg1->add_image("leg.png");
  Skel_Edge *r_leg2=new Skel_Edge(r_leg1,50,90);
  r_leg2->add_image("leg2.png");
  
  Skel_Edge *r_foot=new Skel_Edge(r_leg2,25,0);
  r_foot->add_image("foot.png");
  Skel_Edge *l_foot=new Skel_Edge(l_leg2,25,-180);
  l_foot->add_image("foot.png", true);
  
  update_nodes_list();
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

bool Skeleton::load()
{
  std::cout<<"Begin load..."<<std::endl;

  QDomDocument doc( "JM_skel" );
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
  if( root.tagName() != "skel" ) {
    std::cout<<"Wrong root element"<<std::endl;
    return false;
  }



  QDomNode n = root.firstChild();
  while( !n.isNull() ) {
    QDomElement e = n.toElement();
    if( !e.isNull() ) {
      if( e.tagName() == "contact" ) {
	QString c_name;
	QString c_phone;
	QString c_eMail;
	c_name = e.attribute( "name", "" );
	c_phone = e.attribute( "phone", "" );
	c_eMail = e.attribute( "email", "" );
	std::cout<<"Contact:\t"<<c_name.toStdString()<<"\t"<<c_phone.toStdString()<<"\t"<<c_eMail.toStdString()<<std::endl;
      }
    }
    n = n.nextSibling();
  }


  std::cout<<"Correct load end."<<std::endl;
  return true;
}
