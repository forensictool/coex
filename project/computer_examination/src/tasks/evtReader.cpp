#include "evtReader.h"

//флаги для параметров
//скорее всего выпилить...


// вспомогательные ридеры для чтения бинарыных последовательностей определенной длинны
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
            res += data[0]; //QChar::fromAscii(data[0]);
        /*
         * короче не знает он что такое этот фром аски, пробовал инклюды разные и доставлял либы, не помогло
         */
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

//экземпляр записи в evt файле

        _EVENTLOGRECORD::_EVENTLOGRECORD() {}
        _EVENTLOGRECORD::~_EVENTLOGRECORD()
		{
				// delete Bytes;
        }
		
	
		// http://msdn.microsoft.com/en-us/library/windows/desktop/aa363651%28v=vs.85%29.aspx
		
        void _EVENTLOGRECORD::setEventID(quint32 id)
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

        void _EVENTLOGRECORD::read(QDataStream &stream)
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
        }
	
        void _EVENTLOGRECORD::print()
		{
			std::cout << "Event: \r\n";
			QMapIterator<QString, QString> i(MapData);
			while (i.hasNext()) {
				i.next();
				std::cout << "\t" << i.key().toStdString() << " = " << i.value().toStdString() << "\r\n";
			}
        }

//читалка файла

        winEventLog::winEventLog(QString filename)
		{
			m_file = new QFile(filename);
			m_bOpen = m_file->open(QIODevice::ReadOnly);
		}
		
        winEventLog::~winEventLog()
		{
			m_evtlogs.clear();
			if(m_bOpen) m_file->close();
		}

        void winEventLog::read()
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

