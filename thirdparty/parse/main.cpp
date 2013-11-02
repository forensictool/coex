#include <QCoreApplication>
#include <iostream>
#include <QStringList>
#include <QString>
#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include <QVector>
#include <QDirIterator>


int mode_loglist = 0;
int mode_meta = 0;
int print_verbose = 0;
int print_header = 1;
QString DB_PATH;
QString LOG;

/*
typedef struct _EVENTLOGRECORD {
DWORD Length;
DWORD Reserved;
DWORD RecordNumber;
DWORD TimeGenerated;
DWORD TimeWritten;
DWORD EventID;
WORD EventType;
WORD NumStrings;
WORD EventCategory;
WORD ReservedFlags;
DWORD ClosingRecordNumber;
DWORD StringOffset;
DWORD UserSidLength;
DWORD UserSidOffset;
DWORD DataLength;
DWORD DataOffset;
//
// Then follow:
//
// TCHAR SourceName[]
// TCHAR Computername[]
// SID UserSid
// TCHAR Strings[]
// BYTE Data[]
// CHAR Pad[]
// DWORD Length;
//

}
*/

class winEventLog
{
	public:
		winEventLog(QString filename)
		{
			m_file = new QFile(filename);
			m_bOpen = m_file->open(QIODevice::ReadOnly);
		}
		
		~winEventLog()
		{
			if(m_bOpen) m_file->close();
		}
		
		struct _EVENTLOGRECORD 
		{
			quint32 MessageNumber;
			quint32 DateCreated;
			quint32 DateWritten;
			quint16 EventID;
			quint8 Unknown1;
			quint8 Unknown2;
			quint8 EventType;
			QString strEventType;
			quint16 StringCount;
			quint16 Category;
			QString strCategory;
			char SID[8];
			char Unknown3[8];
			char Unknown4[11];
			QString Message;
			QString Source;
			QString ComputerName;
			QString Message1;
			
			char Unknown5[8];
			
			QString readString(QDataStream &stream)
			{
				bool bEnd = false;
				QString res = "";
				while(!bEnd)
				{
					char data[4];
					stream.readRawData(data, 4);
					
					if(
						(data[0] == 0x00 && data[2] == 0x00)
						|| (data[2] == 0x00)
					)
						bEnd = true;
					else
					{
						if(data[0] != 0x00)
							res += QChar::fromAscii(data[0]);
						else 
							res += " ";
						
						if(data[2] != 0x00)
							res += QChar::fromAscii(data[2]);
						else 
							res += " ";
					}
				}
				return res;
			}
			
			void read(QDataStream &stream)
			{
				// 1 Message Number (4 bytes - Padded with null characters from left to right to fill in the full 4 bytes. It is in little endian byte order)
				stream >> MessageNumber;
				
				// 2 Date Created (4 bytes, little endian, decimal value in epoch)
				stream >> DateCreated;
				
				// 3 Date Written (4 bytes, little endian, decimal value in epoch)
				stream >> DateWritten;
				
				// 4 Event ID (2 bytes, little endian, decimal value)
				stream >> EventID;
				
				// 5 Unknown? (1 byte)
				stream >> Unknown1;
				
				// 6 Unknown? (1 byte)
				stream >> Unknown2;

				// 7 Event Type (1 byte - number - used as index to retrieve 'Event Name')
				stream >> EventType;
				if(EventType == 4) strEventType = "Information";
				
				// 8 String Count (2 bytes - The number of strings in the event in decimal)
				stream >> StringCount;
				
				// 9 Category (2 bytes - decimal value)
				stream >> Category;
				if(Category == 0) strCategory = "None";
				
				
				// 10 SID? (8 bytes - possibly the decimal value of the SID)
				stream.readRawData(SID, sizeof(SID));
				
				// 11 Unknown? (8 bytes - possibly related to the SID)
				stream.readRawData(Unknown3, sizeof(Unknown3));
				
				// 12 Unknown? (11 bytes)
				stream.readRawData(Unknown4, sizeof(Unknown4));
				
				// 13 Source Name (Variable Length in words (4 bytes) with at least the last two bytes being null and 0 or more bytes of null padding up to the length of a full word)
				Source = readString(stream);
				
				// 14 Computer Name (Variable Length in words (4 bytes) with at least the last two bytes being null and 0 or more bytes of null padding up to the length of a full word)
				ComputerName = readString(stream);
				
				// 15 String1 (Variable Length - Also known as the 'Message' - Variable Length in words (4 bytes) with at least the last two bytes being null and 0 or more bytes of null padding up to the length of a full word.)
				Message = readString(stream);
				
				// 16 String'n' (Depending on the number of strings specified by
				{
					char *strn = new char[StringCount+1];
					strn[StringCount] = 0x00;
					stream.readRawData(strn, StringCount);
					Message1 = QString(strn);
				}
				
				// 17 Unknown? (8 bytes)
				stream.readRawData(Unknown5, sizeof(Unknown5));
			}
			
			void print()
			{
				
				
				std::cout << "/ Event \\____________________________________________________\r\n";
				std::cout << "| Date: [" << DateWritten << "]\t Source: [" << Source.toStdString() << "] |\r\n";
				std::cout << "| Time: [" << DateCreated << "]\t Category: (" << Category << ") " << strCategory.toStdString() << " |\r\n";
				std::cout << "| Type: [" << (int)EventType << ") " << strEventType.toStdString() << "]\t EventID: [" << EventID << "] |\r\n";
				
				// MessageNumber
				
				
				
				std::cout << "| Unknown1: " << (int)Unknown1 << "; ";
				std::cout << "Unknown2: " << (int)Unknown2 << "; ";
				std::cout << "StringCount: " << StringCount << "; ";
				std::cout << "Category: " << Category << "; ";
				std::cout << "SID: " << SID << "; ";
				std::cout << "Unknown3: " << Unknown3 << "; ";
				std::cout << "Unknown4: " << Unknown4 << ";";
				std::cout << "Message: " << Message.toStdString() << "; ";
				std::cout << "ComputerName: " << ComputerName.toStdString() << "; ";
				std::cout << "Message1: " << Message1.toStdString() << "; ";
			
				std::cout << "\r\n";
			}
		};
		
		void read()
		{
			if(!m_bOpen) return;
			QDataStream stream(m_file);
			
			// I don't know what is it:
			
			int nOffset = 32;
			char data[nOffset];
			stream.readRawData(data, nOffset);

			while(!stream.atEnd())
			{
				quint32 unknown;
				stream >> unknown;

				// 0 Message Separator (4 bytes - Separator is (1001100011001100100110001100101 - bin) or (4c664c65 - hex) or (LfLe - ascii))
				if(unknown == 0x4c664c65) // !!! found separator
				{
					_EVENTLOGRECORD evnt;
					evnt.read(stream);					
					evnt.print();
				}
			}
		}
	
	private:
		QVector<_EVENTLOGRECORD> m_evtlogs;
		QFile *m_file;
		bool m_bOpen;
};



int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		// std::cout << argv[0] << " <log filename>" << std::endl;
        // return -1;
	};

	QString filename = QString(argv[1]);

	//for(int i = 0; i < 10; i++)
	{
		winEventLog log(QString("SysEvent.Evt"));
		log.read();
	}
	
    std::cout << "\r\n fuck off \r\n";    
    return 0;
	
    /*if((argc < 3) | !(strcmp(argv[1], "-?")) | !(strcmp(argv[1], "--help")))
    {
        std::cout << "NO_1" << std::endl;
        return false;
    }
    else if (!strcmp(argv[1], "-l"))
    {
        if (argc == 3)
        {
            mode_loglist = 1;
            DB_PATH = argv[2];
        }
        else
        {
            std::cout << "ERROR: Incorrect usage for log list mode" << std::endl;
            return false;
        }
    }
    else if (!strcmp(argv[1], "-m"))
    {
        if (argc == 4)
        {
            mode_meta = 1;
            DB_PATH = argv[2];
            LOG = argv[3];
        }
        else
        {
            std::cout << "ERROR: Incorrect usage for meta information mode" << std::endl;
            return false;
        }
    }
    else if (argc >= 3)
    {
        DB_PATH = argv[argc - 2];
        LOG = argv[argc - 1];

        for(int i = 0; i < argc - 2; i++)
        {
            if (!strcmp(argv[i], "-v"))
            {
                print_verbose = 1;
            }
            else if (!strcmp(argv[i], "-H"))
            {
                print_header = 0;
            }
            else if (!strcmp(argv[i], "-h"))
            {
                print_header = 1;
            }
            else
            {
                std::cout << "ERROR: Unrecognized option " << argv[i] << std::endl;
                return false;
            }
        }
    }
    else
    {
        std::cout << "ERROR: Incorrect usage for log parse command" << std::endl;
        return false;
    }
	

    if (mode_loglist)
    {
        QDirIterator dirIt(DB_PATH+"/services", QDir::NoSymLinks | QDir::Files, QDirIterator::Subdirectories);
        while (dirIt.hasNext())
        {
            std::cout << dirIt.next().toStdString() << std::endl;
        }
        if (print_verbose)
        {
            std::cout << "INFO: Opening message repository " << DB_PATH.toStdString() << std::endl;
            //строка 161.
        }
    }
	
	*/
    return true;
}
