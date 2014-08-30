#ifndef EVT_READER_H
#define EVT_READER_H

#include "../coex/task.h"
#include <QMap>
#include <QFile>
#include <QDateTime>
#include <QTextStream>
#include <iostream>
#include <QXmlStreamWriter>

class _EVENTLOGRECORD 
{
	public:
        _EVENTLOGRECORD();
        ~_EVENTLOGRECORD();
		
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
			
        virtual void setEventID(quint32 id);
        virtual void read(QDataStream &stream);
        virtual void print(QTextStream &stream);
        virtual void xmlPrint(QXmlStreamWriter &stream);
};

//читалка файла
class winEventLog
{
	public:
        winEventLog(QString filename, QString outFilename);
        ~winEventLog();

        virtual void read();

	private:
		QVector<_EVENTLOGRECORD> m_evtlogs;
		QFile *m_file;
        QFile *m_outFile;
		bool m_bOpen;
        bool m_bOutOpen;
};

#endif
