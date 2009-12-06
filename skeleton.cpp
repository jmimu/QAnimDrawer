#include "skeleton.h"

#include <iostream>

Skeleton::Skeleton()
  : origin(0,0,NULL)
{
  make_object();
}

void Skeleton::make_object()
{
  Skel_Edge *head=new Skel_Edge(&origin,30,-90);
  head->add_image("head.png");
  
  Skel_Edge *l_sholder=new Skel_Edge(&origin,30,-180);
  l_sholder->add_image("arm.png", true);
  Skel_Edge *r_sholder=new Skel_Edge(&origin,30,0);
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
  
  Skel_Edge *body=new Skel_Edge(&origin,50,90);
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
  
  
}


void Skeleton::draw(QGraphicsScene *scene)
{
  origin.draw_recursive(scene);
}
