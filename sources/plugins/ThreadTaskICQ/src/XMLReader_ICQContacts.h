#ifndef __XMLREADER_ICQCONTACTS_H__
#define __XMLREADER_ICQCONTACTS_H__

#include <QVector>

class XMLReader_ICQContacts {
	public:
//		XMLReader_ICQContacts();
        bool read(QString inputFile, QString outPath);
};

#endif // __XMLREADER_ICQCONTACTS_H__
