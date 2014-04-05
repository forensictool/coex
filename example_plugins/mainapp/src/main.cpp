#include <QString>
#include <QObject>
#include <QFile>
#include <QDir>
#include <QPluginLoader>
#include <QApplication>
#include <iostream>

#include "../../interfaces/myinterface.h"

int main(int argv, char *args[])
{
     QApplication app(argv, args);
   
	// QDir pluginsDir = QDir("./");
	// QString filename = QDir::currentPath() + "/libtestPlugin.so";
	QString filename = "testPlugin.so";
	QFile file(filename);
	std::cout << "[" << filename.toStdString() << "]\n";
	
	if (!file.exists())
		std::cout << "file not found\n";
	
	QPluginLoader loader( filename );
	if ( !loader.load() )
	{
	  qWarning( "This is not Qt plugin or plugin not match out Qt Libraries" );
	  return -1;
	}
	
	MyInterface * i = qobject_cast<MyInterface*>( loader.instance() );
	if ( !i )
	{
	  qWarning( "This is not plugin for interface MyInterface" );
	  return -2;
	}
	QString text = i->doSomething( 123 ); // text = "123"
	std::cout << text.toStdString();
	return 0;
}



