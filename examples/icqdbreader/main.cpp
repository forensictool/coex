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

// third party library
#include "qdbftable.h"
#include "qdbfrecord.h"


int main(int argc, char *argv[])
{
	QString filePath = "657182629.db";
	QDbf::QDbfTable table;
	if (!table.open(filePath)) {
		std::cout << "file open error";
		return -1;
	}

	while (table.next()) {
		QString output;
		QDbf::QDbfRecord record = table.record();
		/*for (int i = 0; i < record.count(); ++i) {
			output.append(record.fieldName(i));
			output.append(QLatin1String(": "));
			output.append(record.value(i).toString().trimmed());
			output.append(QLatin1String("; "));
		}
		qDebug() << output;*/
	}

	table.close();
	return 0;
}
