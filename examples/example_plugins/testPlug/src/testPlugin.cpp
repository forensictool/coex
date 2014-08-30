
#include "testPlugin.h"

/*QString MyPlugin::doSomething( int value ) {
	return QString::number( value );
}*/

QString oddUpper(const QString& str)
{
    return str + " from lib";
}

QString oddUpper2(const QString& str)
{
    return str + " (2) from lib";
}

// Q_EXPORT_PLUGIN2( my_plugin, MyPlugin )
