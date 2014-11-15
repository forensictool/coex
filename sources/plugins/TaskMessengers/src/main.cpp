#include <QCoreApplication>
#include <QtXml>
#include <QTextStream>
#include <iostream>
#include "ICQContact.h" // класс для хранения данных
#include "XMLReader_ICQContacts.h" // тут реализация по чтению и записи

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	XMLReader_ICQContacts reader; // создаем экземпляр класса
	
	if (argc != 3)
	{
		std::cout << "Usage: " << argv[0] << " <inputfile> <outputfile>\n\n";
		return -1;
	}
	
	QString sInputFile = QString(argv[1]);
	QString sOutputFile = QString(argv[2]);

	if (reader.read(sInputFile))
	{
		reader.write(sOutputFile);
	};

	// нет необходимости ждать завершения
    // return a.exec();
    // выходим сразу
    return 0;
}
