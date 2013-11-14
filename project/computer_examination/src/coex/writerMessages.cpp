#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "writerMessages.h"
namespace coex
{
        writerMessages::writerMessages(QString fileName, QString messangerName)
        {
            m_bOpened = true;
            m_pFile = new QFile(fileName);
            if (!m_pFile->open(QIODevice::WriteOnly))
            {
                //std::cout << " failed task\n";
                m_bOpened = false;
                return;
            }
            m_pXmlWriter = new QXmlStreamWriter();
            m_pXmlWriter->setDevice(m_pFile);

            m_pXmlWriter->setAutoFormatting(true);
            m_pXmlWriter->writeStartDocument();
            m_pXmlWriter->writeStartElement("Messages ");
            m_pXmlWriter->writeAttribute("Messenger" ,messangerName);
        }

        writerMessages::~writerMessages()
        {
            m_pXmlWriter->writeEndElement();
            m_pXmlWriter->writeEndDocument();
            delete m_pXmlWriter;
            delete m_pFile;
        }

        bool writerMessages::opened()
        {
            return m_bOpened;
        }
        //like pidgin
        void writerMessages::writeMessage(
            QString author,
            QString dataTime,
            QString message,
            QString account
        )
        {
            if (!m_bOpened)return;
            m_pXmlWriter->writeStartElement("message");
            m_pXmlWriter->writeAttribute("author" ,author);
            m_pXmlWriter->writeAttribute("dataTime" ,dataTime);
            m_pXmlWriter->writeAttribute("account" ,account);
            m_pXmlWriter->writeCharacters(message);
            m_pXmlWriter->writeEndElement();
        }

        // like skype
        void writerMessages::writeMessage(
            QString actionType,
            QString actionTime,
            QString userName,
            QString displayName,
            QString chatMessage,
            QString chatID
        )
        {
            if (!m_bOpened)return;
            m_pXmlWriter->writeStartElement("message");
            m_pXmlWriter->writeAttribute("actionType" ,actionType);
            m_pXmlWriter->writeAttribute("actionTime" ,actionTime);
            m_pXmlWriter->writeAttribute("userName" ,userName);
            m_pXmlWriter->writeAttribute("displayName" ,displayName);
            m_pXmlWriter->writeAttribute("chatMessage" ,chatMessage);
            m_pXmlWriter->writeAttribute("chatID" ,chatID);
            m_pXmlWriter->writeCharacters(chatMessage);
            m_pXmlWriter->writeEndElement();
        };
}
