#ifndef __XMLREADER_ICQCONTACTS_H__
#define __XMLREADER_ICQCONTACTS_H__

//#include <QtXml>
#include <QVector>
//#include "ICQContact.h"
/*!
 * \brief The XMLReader_ICQContacts class
 */

class XMLReader_ICQContacts {
	public:
		XMLReader_ICQContacts();
        bool read(QString inputFile, QString outPath);
        //void write(QString outputFile);

	private:
		//все прочитанные записи будем хранить в специальном массиве (вектор)
        //QVector<ICQContact> m_vContacts;
};

#endif // __XMLREADER_ICQCONTACTS_H__
