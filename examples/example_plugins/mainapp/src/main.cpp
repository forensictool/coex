#include <QString>
#include <QObject>
#include <QFile>
#include <QDir>
#include <QPluginLoader>
#include <QLibrary>
#include <iostream>

#include "../../interfaces/myinterface.h"

int main(int argv, char *args[])
{
	if (argv < 2) {
		std::cout << " I want name of library\n";
		return -1;
	}
	
	QString filename = QString("%1").arg(args[1]);
    
    std::cout << "Filename = [" << filename.toStdString() << "]\n";
    if (QLibrary::isLibrary(filename)) {
		std::cout << " is not Library\n";
		return -2;
	} else {
		std::cout << " is Library\n";
	}
	
    
    QLibrary lib(filename, "1.0.0");
    if (lib.load()) {
		std::cout << "lib is loaded\n";
	} else {
		std::cout << "lib is NOT loaded\n" << lib.errorString().toStdString() << "\n";
		return -3;
	}
    
    typedef QString (*Fct1) (const QString&);
    typedef QString (*Fct2) (const QString&);
    
    Fct1 fct1 = (Fct1)(lib.resolve("oddUpper"));
    if (fct1) {
        std::cout << fct1("hello !!!! ").toStdString() << "\n";
    } else {
		std::cout << "nicht\n";
	}
	
    Fct2 fct2 = (Fct2)(lib.resolve("oddUpper2"));
    if (fct2) {
        std::cout << fct2("hello !!!! ").toStdString() << "\n";
    } else {
		std::cout << "nicht\n";
	}
		
    
	
	/*
     QApplication app(argv, args);
	
	// QDir pluginsDir = QDir("./");
	QString filename = QDir::currentPath() + "/libtestPlugin.so";
	// QString filename = "testPlugin.so";
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
	* */
	return 0;
}



