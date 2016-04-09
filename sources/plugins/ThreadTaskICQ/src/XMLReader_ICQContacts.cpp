#include "XMLReader_ICQContacts.h"
#include "writerMessages.h"
#include <QDebug>
#include <QDir>

bool XMLReader_ICQContacts::read(QString inputFile, QString outPath)
{
    QFile file(inputFile);
    {
        QDir dir(outPath);
        dir.mkdir("icq");
    }
    writerMessagesICQ icqContacts(outPath + "//icq/contacts.xml");

	
    if(file.open(QIODevice::ReadOnly)) {
        QXmlStreamReader xml(&file);

        do {
            xml.readNext();
			if (xml.qualifiedName() == "c")
			{
                QString mail, nick;
				if(xml.attributes().value("email") != "")
                    mail = xml.attributes().value("email").toString();

				if(xml.attributes().value("nick") != "")
                    nick = xml.attributes().value("nick").toString();

                icqContacts.writeContactList(mail, nick);
			}
        } while(!xml.atEnd());
        // закрываем файл если удалось его открыть
		file.close();
		return true;
    }
    return false;
}

