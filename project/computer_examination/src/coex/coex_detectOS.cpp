#include "coex.h"

#include <QFile>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QIODevice>
#include <QList>
#include <iostream>

namespace coex {

  struct fileos
  {
     fileos(coex::typeOS os, QString version, QString filePath, QString hash) :
      filePath(filePath), hash(hash), version(version), os(os) 
     {
     };
     QString filePath;
     QString hash;
     QString version;
     coex::typeOS os;

     QString toString() {
       return "filePath: " + filePath + "; hash: " + hash + "; version: " + version + "; os: " + typeOStoString(os) + ";";
     };
  };


	coex::typeOS detectOS(QString inputFolder)
	{
		QList<fileos> listfiles;
		QList<fileos> checkfiles;

		// Windows XP
		listfiles << fileos( coex::ceWindowsXP, "5.1.2600.5512", "/WINDOWS/system32/kernel32.dll", "d612ee36f95da6d1179f7567b2b77d77");
		listfiles << fileos( coex::ceWindowsXP, "5.1.2600.5512", "/WINDOWS/system32/kernel32.dll", "800937D2446728367B713F5AC0B9BAC0"); // ??
		listfiles << fileos( coex::ceWindowsXP, "5.1.2600.5781", "/WINDOWS/system32/kernel32.dll", "E1E261C6D29F87FAFCC88F94952ED8D5");
		listfiles << fileos( coex::ceWindowsXP, "5.1.2600.6293", "/WINDOWS/system32/kernel32.dll", "9CB5C708CFBD8B007BE2C8A44A3DDE25");
		listfiles << fileos( coex::ceWindowsXP, "5.1.2600.6293", "/WINDOWS/system32/kernel32.dll", "D056B67FCC32221681438A6240DB3E1A");
		listfiles << fileos( coex::ceWindowsXP, "5.2.3790.4480", "/WINDOWS/system32/kernel32.dll", "43301E4453581691B791855934BFF7C5");
		listfiles << fileos( coex::ceWindowsXP, "5.2.3790.4480", "/WINDOWS/system32/kernel32.dll", "B4B82A9E888B1A8964D136AD227C6428");
		listfiles << fileos( coex::ceWindowsXP, "5.2.3790.5069", "/WINDOWS/system32/kernel32.dll", "23A6C522DF754CAD344D737AA45CBD03");
		listfiles << fileos( coex::ceWindowsXP, "5.2.3790.5069", "/WINDOWS/system32/kernel32.dll", "B6D45BB7311512B268064C1A203C003E");
		listfiles << fileos( coex::ceWindowsXP, "5.2.3790.5069", "/WINDOWS/system32/kernel32.dll", "2836EF1A4A12D5149D085833AC84A006");
		
		// Windows Vista
		listfiles << fileos( coex::ceWindowsVista , "6.0.6002.18704", "/Windows/system32/kernel32.dll", "A02EB771DAE80667E3C877CF19E3F6EE");		
		listfiles << fileos( coex::ceWindowsVista , "6.0.6002.18449", "/Windows/system32/KERNEL32.dll", "2299078C1E59FE69ADDF49897D6A373A");
		listfiles << fileos( coex::ceWindowsVista , "6.0.6002.18449", "/Windows/syswow64/kernel32.dll", "7F4CAEAC24592FA9F574E1F8CD1D0604");
		listfiles << fileos( coex::ceWindowsVista , "6.0.6002.18740", "/Windows/system32/kernel32.dll", "14EED915B63F7AB64A1E367BCB6973D0");
		listfiles << fileos( coex::ceWindowsVista , "6.0.6002.18740", "/Windows/system32/kernel32.dll", "12A16A6E0883D403FA78D1D825BB9824");
		listfiles << fileos( coex::ceWindowsVista , "6.0.6002.18740", "/Windows/system32/kernel32.dll", "A8EAB98AC1E987C925EF518E6065A36C");

		// Windows 7
		listfiles << fileos( coex::ceWindows7 , "6.1.7600.16385", "/Windows/system32/kernel32.dll", "5b4b379ad10deda4eda01b8c6961b193");
		listfiles << fileos( coex::ceWindows7 , "6.1.7600.16385", "/Windows/SYSTEM32/kernel32.dll", "4605F7EE9805F7E1C98D6C959DD2949C"); // ?? HW32.Laneul.xkyw
		listfiles << fileos( coex::ceWindows7 , "6.1.7600.16385", "/Windows/SysWOW64/kernel32.dll", "606ECB76A424CC535407E7A24E2A34BC");
		listfiles << fileos( coex::ceWindows7 , "6.1.7600.16850", "/Windows/system32/kernel32.dll", "DDBD24DC04DA5FD0EDF45CF72B7C01E2");
		listfiles << fileos( coex::ceWindows7 , "6.1.7600.17206", "/Windows/system32/kernel32.dll", "43DB3433F141F01E53D1C5AA0F434098");
		listfiles << fileos( coex::ceWindows7 , "6.1.7600.17206", "/Windows/SysWOW64/kernel32.dll", "385BE92E3106491BBB542F8F1C06C606");
		listfiles << fileos( coex::ceWindows7 , "6.1.7601.17514", "/Windows/system32/kernel32.dll", "7A6326D96D53048FDEC542DF23D875A0");		
		listfiles << fileos( coex::ceWindows7 , "6.1.7601.17514", "/Windows/SysWOW64/kernel32.dll", "e80758cf485db142fca1ee03a34ead05");
		listfiles << fileos( coex::ceWindows7 , "6.1.7601.17651", "/Windows/system32/kernel32.dll", "B9B42A302325537D7B9DC52D47F33A73");
		listfiles << fileos( coex::ceWindows7 , "6.1.7601.17651", "/Windows/SysWOW64/kernel32.dll", "99C3F8E9CC59D95666EB8D8A8B4C2BEB");
		listfiles << fileos( coex::ceWindows7 , "6.1.7601.17932", "/Windows/system32/kernel32.dll", "EAF41CFBA5281834CBC383C710AC7965");
		listfiles << fileos( coex::ceWindows7 , "6.1.7601.17932", "/Windows/SysWOW64/kernel32.dll", "9B98D47916EAD4F69EF51B56B0C2323C");		
		listfiles << fileos( coex::ceWindows7 , "6.1.7601.17965", "/Windows/system32/kernel32.dll", "1DC3504CA4C57900F1557E9A3F01D272");
		listfiles << fileos( coex::ceWindows7 , "6.1.7601.17965", "/Windows/SysWOW64/kernel32.dll", "D4F3176082566CEFA633B4945802D4C4");
		listfiles << fileos( coex::ceWindows7 , "6.1.7601.18015", "/Windows/system32/kernel32.dll", "65C113214F7B05820F6D8A65B1485196");
		listfiles << fileos( coex::ceWindows7 , "6.1.7601.18015", "/Windows/system32/kernel32.dll", "AE09B85158C66E2C154C5C9B3C0027B3"); // HW32.Laneul.gqke
		listfiles << fileos( coex::ceWindows7 , "6.1.7601.18015", "/Windows/SysWOW64/kernel32.dll", "AC0B6F41882FC6ED186962D770EBF1D2");
		listfiles << fileos( coex::ceWindows7 , "6.1.7601.18229", "/Windows/system32/kernel32.dll", "D8973E71F1B35CD3F3DEA7C12D49D0F0");
		listfiles << fileos( coex::ceWindows7 , "6.1.7601.18229", "/Windows/SysWOW64/kernel32.dll", "365A5034093AD9E04F433046C4CDF6AB");
		
		// windows 8
		listfiles << fileos( coex::ceWindows8 , "6.2.9200.16384", "/Windows/System32/kernel32.dll", "3C6933B638BB812F4084CF44AE698704");
		listfiles << fileos( coex::ceWindows8 , "6.2.9200.16384", "/Windows/System32/kernel32.dll", "744B34F13E730805E63076622418CCB8");
		listfiles << fileos( coex::ceWindows8 , "6.2.9200.16384", "/Windows/SysWOW64/kernel32.dll", "1C5F50F98291B7545391BB57C406E615");		
		listfiles << fileos( coex::ceWindows8 , "6.2.9200.16627", "/Windows/System32/kernel32.dll", "e1ff9d65e6b86f7ebb531ae36c5af635");

		for(int i = 0; i < listfiles.size(); i++)
		{
			QFileInfo fi(inputFolder + listfiles[i].filePath);
			if(fi.exists())
			{
				QFile file(fi.absoluteFilePath());
				if (file.open(QIODevice::ReadOnly)) 
				{
					QByteArray fileData = file.readAll();
					QByteArray hashData = QCryptographicHash::hash(fileData, QCryptographicHash::Md5);
					QString str = hashData.toHex();
							 
					if(str.toLower() == listfiles[i].hash.toLower())
						checkfiles << listfiles[i];
				}
			}
		}

		if(checkfiles.size() == 0)
			return coex::ceUnknown;


		coex::typeOS os_result = coex::ceUnknown;
		// check on conflicts
		{
			int nCounter = 0;
			for(int x = 0; x < checkfiles.size()-1; x++)
				for(int y = x+1; y < checkfiles.size(); y++)
				{
					if(checkfiles[x].os != checkfiles[y].os)
					{
						std::cout << " conflict between: \n\t " 
						<< checkfiles[x].toString().toStdString() 
						<< "\n\t and " << checkfiles[y].toString().toStdString() << "\n";
						nCounter++;
					};
				};
			if(nCounter == 0) 
			{
				std::cout << checkfiles[0].toString().toStdString() << "\n";
				os_result = checkfiles[0].os;
			}
		};

    return os_result;
  };  
};
