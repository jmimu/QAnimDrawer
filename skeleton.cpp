#include "skeleton.h"

#include <iostream>

Skeleton::Skeleton()
  : origin(0,0)
{
  make_object();
}

void Skeleton::make_object()
{
  Skel_Edge *head=new Skel_Edge(&origin,30,-90);
  //head->add_image("head.png");
  Skel_Edge *l_arm1=new Skel_Edge(&origin,30,-180);
  Skel_Edge *l_arm2=new Skel_Edge(l_arm1,40,-150);
  Skel_Edge *r_arm1=new Skel_Edge(&origin,30,0);
  Skel_Edge *r_arm2=new Skel_Edge(r_arm1,40,-30);

  Skel_Edge *body=new Skel_Edge(&origin,50,90);
  Skel_Edge *l_leg1=new Skel_Edge(body,40,45);
  l_leg1->add_image("leg2.png");
  Skel_Edge *l_leg2=new Skel_Edge(l_leg1,50,90);
  //l_leg2->add_image("l_foot.png");
  Skel_Edge *r_leg1=new Skel_Edge(body,40,60);
  //r_leg1->add_image("leg.png");
  Skel_Edge *r_leg2=new Skel_Edge(r_leg1,50,90);
  //r_leg2->add_image("r_foot.png");

}


void Skeleton::draw(QGraphicsScene *scene)
{
  origin.draw_recursive(scene);
}
