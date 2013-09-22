#include "coex.h"

namespace coex {

	QString typeOStoString(const coex::typeOS &os)
	{
		
		if(os == coex::ceUnknown)
			return "Unknown";
		else if(os == coex::ceLinux)
			return "Linux";
		else if(os == coex::ceWindows95)
			return "Windows 95";
		else if(os == coex::ceWindows98)
			return "Windows 98";
		else if(os == coex::ceWindowsXP)
			return "Windows XP";
		else if(os == coex::ceWindowsVista)
			return "Windows Vista";
		else if(os == coex::ceWindows7)
			return "Windows 7";
		else if(os == coex::ceWindows8)
			return "Windows 8";
		else 
			return QString((int)os);
	};
};
