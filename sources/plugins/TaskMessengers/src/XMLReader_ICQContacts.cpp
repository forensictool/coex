#include "XMLReader_ICQContacts.h"
#include "writerMessages.h"
#include <QDebug>
#include <QDir>

XMLReader_ICQContacts::XMLReader_ICQContacts()
{
	
};
// --------------------------------------------------------------------

bool XMLReader_ICQContacts::read(QString inputFile, QString outPath)
{

    QFile file(inputFile);
    //m_vContacts.clear();


    {
        QDir dir(outPath);
        dir.mkdir("icq");
        //dir.mkdir("icq/messages");

    }
    writerMessagesPidgin icqContacts(outPath + "//icq/contacts.xml", "icq");

	
    if(file.open(QIODevice::ReadOnly)) {
        QXmlStreamReader xml(&file);

        do {
            xml.readNext();
			if (xml.qualifiedName() == "c")
			{
                //ICQContact tmp; // объявляем временный объект
                QString mail, nick;
				if(xml.attributes().value("email") != "")
                    //tmp.setEmail(xml.attributes().value("email").toString());
                    mail = xml.attributes().value("email").toString();
                    //qDebug()<< mail;
				if(xml.attributes().value("nick") != "")
                    //tmp.setNick(xml.attributes().value("nick").toString());
                    nick = xml.attributes().value("nick").toString();
                    //qDebug()<< nick;
                 //m_vContacts.push_back(tmp);
                icqContacts.writeContactList(mail, nick);

			}
        } while(!xml.atEnd());
        // закрываем файл если удалось его открыть
		file.close();
		return true;
    }
    return false;
};
// --------------------------------------------------------------------

/*void XMLReader_ICQContacts::write(QString outputFile)
{
	QFile file(outputFile);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) 
    {
        QTextStream out(&file);

		for(int i = 0; i < m_vContacts.size(); i++)
		{
			ICQContact tmp = m_vContacts[i];
			if (!tmp.email().isEmpty() || !tmp.nick().isEmpty())
			{
				out << "email: " << tmp.email() << " nick: " << tmp.nick() << endl;
				// временно дублируем ввывод в консоль
				qDebug() << "email: " << tmp.email() << " nick: " << tmp.nick();
			}
		}
        file.close();
    };
};*/
// --------------------------------------------------------------------
