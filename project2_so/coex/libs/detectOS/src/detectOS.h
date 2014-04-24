#include "../../../src/coex/coex.h"

#include <QString>

extern "C"
{
	QString getLibName();
	coex::typeOS detectOS(const QString&);
}