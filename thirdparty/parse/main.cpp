#include <QCoreApplication>
#include <iostream>
#include <QStringList>
#include <QString>
#include <QFile>
#include <QStringList>
#include <QDataStream>
#include <QIODevice>
#include <QVector>
#include <QMap>
#include <QDateTime>
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

// helpers function

qint32 readQInt32asLittleEndian(QDataStream &stream)
{
	QDataStream::ByteOrder bo = stream.byteOrder();
	stream.setByteOrder(QDataStream::LittleEndian);
	quint32 res;
	stream >> res;
	stream.setByteOrder(bo);
	return res;
}

qint16 readQInt16asLittleEndian(QDataStream &stream)
{
	QDataStream::ByteOrder bo = stream.byteOrder();
	stream.setByteOrder(QDataStream::LittleEndian);
	quint16 res;
	stream >> res;
	stream.setByteOrder(bo);
	return res;
}

QString readString(QDataStream &stream)
{
	QString res = "";
	while(true || !stream.atEnd())
	{
		char data[2];
		stream.readRawData(data, 2);
		
		if (data[0] == 0x00)
			break;
	
		if(data[0] != 0x00)
			res += QChar::fromAscii(data[0]);
	}
	return res;
}

QString EventTypeToString(quint16 type)
{
	if((type & 0x0001) == 0x0001) return "Error event";
	if((type & 0x0010) == 0x0010) return "Failure Audit event";
	if((type & 0x0008) == 0x0008) return "Success Audit event";
	if((type & 0x0004) == 0x0004) return "Information event";
	if((type & 0x0002) == 0x0002) return "Warning event";
	return "";
}
			
QString EventCategoryToString(quint16 type)
{
	// TODO:
	if(type == 0) return "None";
	return "Unknown";
}

class _EVENTLOGRECORD 
{
	public:
		_EVENTLOGRECORD() {};
		~_EVENTLOGRECORD() 
		{
				// delete Bytes;
		};
		
		char *Bytes;
		
		quint32 Length;
		quint32 Reserved;
		quint32 RecordNumber;
		quint32 TimeGenerated;
		quint32 TimeWritten;
		quint32 EventID;
		quint16 EventType;
		quint16 NumStrings;
		quint16 EventCategory;
		quint16 ReservedFlags;
		quint32 ClosingRecordNumber;
		quint32 StringOffset;
		quint32 UserSidLength;
		quint32 UserSidOffset;
		quint32 DataLength;
		quint32 DataOffset;

		QMap<QString, QString> MapData;
	
		// http://msdn.microsoft.com/en-us/library/windows/desktop/aa363651%28v=vs.85%29.aspx
		
		void setEventID(quint32 id)
		{
			// TODO
			quint8 Sev = id >> 30;
			
			QString Severity = "";
			if(Sev == 0x00) Severity = "Success";
			if(Sev == 0x01) Severity = "Informational";
			if(Sev == 0x02) Severity = "Warning";
			if(Sev == 0x03) Severity = "Error";
			MapData["EventID_SeverityToString"] = Severity;
			MapData["EventID_Severity"] = QString::number(Sev);
			
			quint8 C = id >> 29;
			C = C & 0x01;
			MapData["EventID_CustomerBit"] = QString::number(C);
			if(C == 0x00)
				MapData["EventID_CustomerBitToString"] = "System code";
			else 
				MapData["EventID_CustomerBitToString"] = "Customer code";
			
			quint8 R = id >> 28;
			R = R & 0x01;
			MapData["EventID_ReservedBit"] = QString::number(R);
			
			quint16 F = id >> 16;
			F = F & 0x0FFF;
			MapData["EventID_Facility"] = QString::number(F);
			
			EventID = (id & 0x0000FFFF);
			MapData["EventID_Code"] = QString::number(EventID);
		}

		void read(QDataStream &stream)
		{
			stream >> Reserved;				
			if(Reserved != 0x4c664c65)
				return;

			MapData["Reserved"] = "0x4c664c65";

			RecordNumber = readQInt32asLittleEndian(stream);
			MapData["RecordNumber"] = QString::number(RecordNumber);

			// 2 Date Created (4 bytes, little endian, decimal value in epoch)
			TimeGenerated = readQInt32asLittleEndian(stream);
			QDateTime dtTimeGenerated = QDateTime::fromTime_t(TimeGenerated);
			MapData["TimeGenerated"] = QString::number(TimeGenerated);
			MapData["TimeGeneratedToDate"] = dtTimeGenerated.toUTC().toString("yyyy-MM-dd");
			MapData["TimeGeneratedToTime"] = dtTimeGenerated.toUTC().toString("hh:mm:ss");
			MapData["TimeGeneratedToDateTime"] = dtTimeGenerated.toUTC().toString("yyyy-MM-dd hh:mm:ss");
		
			// 3 Date Written (4 bytes, little endian, decimal value in epoch)
			TimeWritten = readQInt32asLittleEndian(stream);
			QDateTime dtTimeWritten = QDateTime::fromTime_t(TimeWritten);
			MapData["TimeWritten"] = QString::number(TimeWritten);
			MapData["TimeWrittenToDate"] = dtTimeWritten.toUTC().toString("yyyy-MM-dd");
			MapData["TimeWrittenToTime"] = dtTimeWritten.toUTC().toString("hh:mm:ss");
			MapData["TimeWrittenToDateTime"] = dtTimeWritten.toUTC().toString("yyyy-MM-dd hh:mm:ss");
			
			// 4 Event ID (4 bytes, little endian, decimal value)
			// !!! TODO 
			EventID = readQInt32asLittleEndian(stream);
			MapData["EventID"] = QString::number(EventID);
			setEventID(EventID);

			// 7 Event Type (2 byte - number - used as index to retrieve 'Event Name')
			EventType = readQInt16asLittleEndian(stream);
			MapData["EventType"] = QString::number(EventType);
			MapData["EventTypeToString"] = EventTypeToString(EventType);
			
			// 8 String Count (2 bytes - The number of strings in the event in decimal)
			// stream >> NumStrings;
			NumStrings = readQInt16asLittleEndian(stream);
			MapData["NumStrings"] = QString::number(NumStrings);
			
			// 9 Event Category (2 bytes - decimal value)
			stream >> EventCategory;
			MapData["EventCategory"] = QString::number(EventCategory);
			MapData["EventCategoryToString"] = EventCategoryToString(EventCategory);

			// ReservedFlags
			stream >> ReservedFlags;
			MapData["ReservedFlags"] = QString::number(ReservedFlags);
			
			// ClosingRecordNumber
			stream >> ClosingRecordNumber;
			MapData["ClosingRecordNumber"] = QString::number(ClosingRecordNumber);
			
			// StringOffset
			// stream >> StringOffset;
			StringOffset = readQInt32asLittleEndian(stream);
			MapData["StringOffset"] = QString::number(StringOffset);
			
			// UserSidLength
			UserSidLength = readQInt32asLittleEndian(stream);
			MapData["UserSidLength"] = QString::number(UserSidLength);
			if(UserSidLength == 0)
				MapData["User"] = "N/A";
			
			
			// UserSidOffset
			UserSidOffset = readQInt32asLittleEndian(stream);
			MapData["UserSidOffset"] = QString::number(UserSidOffset);
			
			// DataLength
			DataLength = readQInt32asLittleEndian(stream);
			MapData["DataLength"] = QString::number(DataLength);
			
			// DataOffset
			DataOffset = readQInt32asLittleEndian(stream);
			MapData["DataOffset"] = QString::number(DataOffset);
			
			if(NumStrings > 0)
			{
				QStringList list;
				QString str = readString(stream);
				
				while(str.count() > 0)
				{
					list << str;
					str = readString(stream);
				}

				int nSize = list.size();
				MapData["NumStrings_Real"] = QString::number(nSize);
				
				if(nSize > 0) MapData["Source"] = list[0];
				if(nSize > 1) MapData["Computer"] = list[1];
				if(nSize > 2)
				{
					QString Description;
					for(int i = 2; i < nSize; i++)
					{
						if(Description.count() > 0 && list[i].count() > 0)
							Description += " ";
						Description += list[i];
					}
					MapData["Description"] = Description + ".";
				}
			}

			// 17 Unknown? (8 bytes)
			// stream.readRawData(Unknown5, sizeof(Unknown5));
		};
	
		void print()
		{
			std::cout << "Event: \r\n";
			QMapIterator<QString, QString> i(MapData);
			while (i.hasNext()) {
				i.next();
				std::cout << "\t" << i.key().toStdString() << " = " << i.value().toStdString() << "\r\n";
			}
		};
};


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
			m_evtlogs.clear();
			if(m_bOpen) m_file->close();
		}

		void read()
		{
			if(!m_bOpen) return;
			QDataStream stream(m_file);
			while(!stream.atEnd())
			{
				_EVENTLOGRECORD evnt;
				evnt.Length = readQInt32asLittleEndian(stream)-4;
				evnt.MapData["Length"] = QString::number(evnt.Length);
				
				if(evnt.Length == 0xfffffffc || int(evnt.Length) < 0)
					return;
				
				evnt.Bytes = new char[evnt.Length];
				stream.readRawData(evnt.Bytes, evnt.Length);
				QByteArray ba(evnt.Bytes, evnt.Length);
				evnt.MapData["Data"] = ba.toBase64();
				
				QDataStream streamRecord(ba);
				evnt.read(streamRecord);
				evnt.print();
				m_evtlogs.push_back(evnt);
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
