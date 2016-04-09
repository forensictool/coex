#include "ICQContact.h"

// реализация методов конкретного класса находить в отдельном файле

ICQContact::ICQContact()
{
	
};

void ICQContact::setEmail(QString sValue)
{
	m_sEmail = sValue;
};

void ICQContact::setNick(QString sValue)
{
	m_sNick = sValue;
};

QString ICQContact::email()
{
	return m_sEmail;
};

QString ICQContact::nick()
{
	return m_sNick;
};
