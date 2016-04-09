#ifndef __ICQCONTACT_H__
#define __ICQCONTACT_H__

//#include <QtXml>

/*
 * Это просто вспомогательный класс для хранения структуры данных
 */

class ICQContact {
	public:
		ICQContact();
		
		/* доступ к объектам организуется через setter и getter
		 * По одной из нотаций по программированию
		 * */
		
		// setters
		void setEmail(QString sNewValue);
		void setNick(QString sNewValue);
		
		// getters
		QString email();
		QString nick();

	private:
		// для более легкого определения что за переменная и какого типа импользуется:
		// "венгерская нотация"
		// http://ru.wikipedia.org/wiki/%D0%92%D0%B5%D0%BD%D0%B3%D0%B5%D1%80%D1%81%D0%BA%D0%B0%D1%8F_%D0%BD%D0%BE%D1%82%D0%B0%D1%86%D0%B8%D1%8F
		// в данном случае "m_"  - что это member класса
		// "s" - тип данных string
		
		QString m_sNick;
		QString m_sEmail;
	
};

#endif // __ICQCONTACT_H__
