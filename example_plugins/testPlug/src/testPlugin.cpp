
#include "testPlugin.h"

QString MyPlugin::doSomething( int value ) {
	return QString::number( value );
}

Q_EXPORT_PLUGIN2( my_plugin, MyPlugin )
