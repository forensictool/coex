#ifndef __WRITER_MESSAGES_H__
#define __WRITER_MESSAGES_H__

#include <QString>
#include <QFile>
#include <QXmlStreamWriter>
namespace coex
{

	class writerMessages
	{
	public:
        writerMessages(QString fileName, QString messangerName);
		~writerMessages();

        bool opened();

          //about log file
        void writeInfoLog(
            QString chathID,
            QString account,
            QString data,
            QString protocol
        );

		//like pidgin
		void writeMessage(
			QString author, 
			QString dataTime, 
            QString message
		);

		// like skype
		void writeMessage(
            QString actionType,
            QString actionTime,
            QString userName,
            QString displayName,
            QString chatMessage,
            QString chatID
		);

    private:
        QFile *m_pFile;
        QXmlStreamWriter* m_pXmlWriter;
        bool m_bOpened;
	};

}
#endif //__WRITER_MESSAGES_H__
