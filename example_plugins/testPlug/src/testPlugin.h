
#ifndef __MYPLUGIN_H__
#define __MYPLUGIN_H__

#include <QString>
#include <QObject>
#include "../../interfaces/myinterface.h"
#include <QtPlugin>

class MyPlugin : public QObject, MyInterface
{
  Q_OBJECT
  Q_INTERFACES( MyInterface )
public:
  QString doSomething( int value );
};

#endif // __MYPLUGIN_H__
