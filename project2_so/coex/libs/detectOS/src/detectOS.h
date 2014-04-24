#include "../../../src/coex/coex.h"

#include <QString>

extern "C"
{
	QString getLibName();
	namespace coex
	{
		coex::typeOS detectOS(const QString&);
		coex::typeOS retOS();
	}
}