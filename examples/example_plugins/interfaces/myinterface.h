
#ifndef __MYINTERFACE_H__
#define __MYINTERFACE_H__

#include <QString>

class MyInterface
{
	public:
	  virtual ~MyInterface();
	  virtual QString doSomething( int value ) = 0;
};

Q_DECLARE_INTERFACE( MyInterface, "coex.MyInterface.version-1.0")

#endif // __MYINTERFACE_H__
