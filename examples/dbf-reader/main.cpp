#include <QCoreApplication>
#include <iostream>
#include <QStringList>
#include <QString>
#include <QFile>
#include <QStringList>
#include <QDataStream>
#include <QIODevice>
#include <QVector>
#include <QMap>
#include <QDateTime>
#include <QDirIterator>
#include <QChar>
#include <QVariant>

// third party library
#include "qdbftable.h"
#include "qdbfrecord.h"


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "please usage: " << argv[0] << " <file.dbf>\n\n";
		return -1;
	}
	QString filePath(argv[1]);
	QFile file(filePath);
	if(!file.exists()) {
		std::cout << "file not exists\n\n";
		return -1;
	}
	
	QFileInfo fileInfo(file);
	
	std::cout << " **** information about file **** \n"
		<< " file.size() = " <<  file.size() << "\n"
		<< " absolute path = " << fileInfo.absoluteFilePath().toStdString() << "\n"
		<< "\n";
	
	QDbf::QDbfTable table(fileInfo.absoluteFilePath());
	
	/*IBM866,
       Windows1251,
        
	setCodepage(QDbfTable::Codepage codepage)*/
	
	if (!table.open()) {
		std::cout << "file open error: ";
		
		QDbf::QDbfTable::DbfTableError err = table.error();
		
		if (err == QDbf::QDbfTable::NoError)
			std::cout << "NoError";
		if (err == QDbf::QDbfTable::OpenError)
			std::cout << "OpenError";
		if (err == QDbf::QDbfTable::ReadError)
			std::cout << "ReadError";
		if (err == QDbf::QDbfTable::WriteError)
			std::cout << "WriteError";
		if (err == QDbf::QDbfTable::PermissionsError)
			std::cout << "PermissionsError";
		if (err == QDbf::QDbfTable::UnspecifiedError)
			std::cout << "UnspecifiedError";

		std::cout << "\n\n";
		return -1;
	}

	while (table.next()) {
		QString output;
		QDbf::QDbfRecord record = table.record();
		for (int i = 0; i < record.count(); ++i) {
			output.append(record.fieldName(i));
			output.append(QLatin1String(": "));
			output.append(record.value(i).toString().trimmed());
			output.append(QLatin1String("; "));
		}
		std::cout << output.toStdString() << "\n";
	}

	table.close();
		std::cout << "\n\n";
	return 0;
}
