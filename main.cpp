#include <QtGui/QApplication>
#include <iostream>
#include "window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (argc<2) {
      std::cout<<"Usage: ./qanimdrawer skel.xml"<<std::endl;
      return 0;
    }else{
      Window w(argv[1]);
      w.show();
      return a.exec();
    }
}
