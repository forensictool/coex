#include "taskFirefox.h"
#include "xml.h"
#include <iostream>
#include <QDirIterator>
#include <QString>
#include <QRegExp>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTextStream>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QCoreApplication>
#include <QLibrary>
#include <QDebug>
#include <QByteArray>
#include <stdio.h>
/*#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>*/

#define PRBool   int
#define PRUint32 unsigned int
#define PR_TRUE  1
#define PR_FALSE 0

typedef enum
{
	siBuffer = 0,
	siClearDataBuffer = 1,
	siCipherDataBuffer,
	siDERCertBuffer,
	siEncodedCertBuffer,
	siDERNameBuffer,
	siEncodedNameBuffer,
	siAsciiNameString,
	siAsciiString,
	siDEROID,
	siUnsignedInteger,
	siUTCTime,
	siGeneralizedTime
} SECItemType;

struct SECItem
{
	SECItemType type;
	unsigned char *data;
	size_t len;
};

typedef enum
{
	SECWouldBlock = -2,
	SECFailure = -1,
	SECSuccess = 0
} SECStatus;

typedef SECStatus(*NSS_Init) (char *);
typedef SECStatus(*NSS_Shutdown) (void);
typedef struct PK11SlotInfoStr PK11SlotInfo;
typedef SECStatus(*PK11_Authenticate) (PK11SlotInfo *, PRBool, void *);
typedef SECStatus(*PK11SDR_Decrypt) (SECItem *, SECItem *, void *);
typedef PK11SlotInfo * (*PK11_GetInternalKeySlot) (void);
typedef void(*PK11_FreeSlot) (PK11SlotInfo *);

NSS_Init NSSInit;
NSS_Shutdown NSSShutdown;
PK11_GetInternalKeySlot PK11GetInternalKeySlot;
PK11_FreeSlot           PK11FreeSlot;
PK11_Authenticate       PK11Authenticate;
PK11SDR_Decrypt         PK11SDRDecrypt;

TaskExample::TaskExample()
{
	m_bDebug = false;
};

QString TaskExample::help()
{
	return "\t--debug - viewing debug messages";
};

QString TaskExample::name()
{
	return "firefox-win";
};

QString TaskExample::author()
{
	return "Rachkovan Oleg";
};

QString TaskExample::description()
{
	return "search file db";
};

bool TaskExample::isSupportOS(const coex::ITypeOperationSystem *os)
{
	return (os->platform() == "Windows");
};

void TaskExample::setOption(QStringList options)
{
	/*
	 *
	 * */
	if(options.contains("--debug"))
		m_bDebug = true;
};

void TaskExample::LoadLibrary()
{
	QLibrary lib("/usr/lib/firefox/libnss3.so");
	QLibrary lib2("/usr/lib/firefox/libmozsqlite3.so");
	QLibrary lib3("/usr/lib/firefox/libnspr4.so");
	QLibrary lib4("/usr/lib/firefox/libnssutil3.so");
	QLibrary lib5("/usr/lib/firefox/libplc4.so");
	QLibrary lib6("/usr/lib/firefox/libplds4.so");
	lib2.load();
	lib3.load();
	lib4.load();
	lib5.load();
	lib6.load();
	NSSInit = (NSS_Init) lib.resolve("NSS_Init");
	NSSShutdown = (NSS_Shutdown) lib.resolve("NSS_Shutdown");
	PK11Authenticate = (PK11_Authenticate) lib.resolve("PK11_Authenticate");
	PK11SDRDecrypt = (PK11SDR_Decrypt) lib.resolve("PK11SDR_Decrypt");
	PK11GetInternalKeySlot = (PK11_GetInternalKeySlot) lib.resolve("PK11_GetInternalKeySlot");
	PK11FreeSlot = (PK11_FreeSlot) lib.resolve("PK11_FreeSlot");
}

/*QString TaskExample::findPath(QString fileName)
{
    QDirIterator dirPath(config->inputFolder() + "/Users/", fileName, QDir::Files | QDir::Dirs | QDir::NoSymLinks | QDir::Hidden, QDirIterator::Subdirectories);
    while (dirPath.hasNext())
        {
            QString str = QString("%1").arg(dirPath.next());
            QFileInfo fInfo(str);
            return fInfo.absoluteFilePath();
        }
}*/

char* TaskExample::Crack(QString cipher, QString profile)
{
	PK11SlotInfo *slot = 0;
	SECStatus status;
	SECItem in, out;
	char *result = "";
	char *p = profile.toLocal8Bit().data();
	SECStatus initiated = SECSuccess;
	initiated = (*NSSInit)(p);
	if (initiated == SECSuccess)
	{
		QByteArray plain = QByteArray::fromBase64(cipher.toUtf8());
		slot = (*PK11GetInternalKeySlot)();
		if (slot != NULL)
		{
			status = PK11Authenticate(slot, PR_TRUE, NULL);
			if (status == SECSuccess)
			{
				out.data = 0;
				out.len = 0;
				in.data = (unsigned char*)plain.constData();
				in.len = plain.size();
				status = (*PK11SDRDecrypt) (&in, &out, NULL);
				if (status == SECSuccess)
				{
					result = (char*)out.data;
					int len2 = out.len;
					result[len2] = '\0';
				}
				else
					result = "Error on decryption!";
			}
			else
				result = "Error on authenticate!";
			(*PK11FreeSlot) (slot);
		}
		else result = "Get Internal Slot error!";
		(*NSS_Shutdown());
	}
	else if (initiated == SECFailure) result = "failure";
	else result = "failure2";
	return result;
}

bool TaskExample::execute(const coex::IConfig *config)
{
	if(m_bDebug)
	{
		std::cout << "  !!! debug mode on.\n";
		std::cout << "InputFolder: " << config->inputFolder().toStdString() << "\n";
	};

	/*---------------History part---------------------*/

	QString path = config->inputFolder() + "/Users/";
	QDir dir(path);
	dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
	QFileInfoList users = dir.entryInfoList();
	QDir dirOut(config->outputFolder());
	dirOut.mkdir("firefox");
	QStringList foundFile;
	for( int i = 0; i < users.size(); i++)
	{
		QFileInfo fileInfo = users.at(i);
		path = fileInfo.absoluteFilePath() + "/AppData/Roaming/Mozilla/";
		QDirIterator dirPath (path, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
		while(dirPath.hasNext())
		{
			QFileInfo fileInfo = dirPath.next();
			if (fileInfo.fileName() == "places.sqlite")
				foundFile << fileInfo.absoluteFilePath();
		}
	}

	for (int i = 0; i < foundFile.size(); i++)
	{
		if( !QFile::exists(foundFile.at(i)) )
			return false;

		QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
		db.setDatabaseName( foundFile.at(i) );

		if( !db.open() )
			if(true)
				std::cout << "Not connected with this db" << foundFile.at(i).toStdString() <<  "\n\n";

		QString sql;
		QSqlQuery query(db);
		QSqlRecord rec = query.record();
		sql = "select * from moz_places;";// for each table from sqlite_master output *
		query.exec(sql);
		rec = query.record();
		//std::cout << "\nFOR " << foundFile.at(i).toStdString() << "\n\n";
		XMLwriter xmlOut(config->outputFolder() + "/firefox/history.xml");
		while( query.next() )
		{
			QString id = query.value(0).toString();
			QString content = query.value(1).toString();
			xmlOut.writeField(id, content);
			//std::cout << id << ": " << content.toStdString() << "\n\n";
		}
		db.close();
	}

	/*-----------------Password part------------------------*/

	int ver = 0;
	LoadLibrary();
	//ext << "compatibility.ini" << "signons.sqlite" << "logins.json";
	QStringList ext;
	ext << "compatibility.ini";
	QString path_to_file;
	QString path_to_folder;
	QDirIterator dirPath(config->inputFolder() + "/Users/", ext, QDir::Files | QDir::Dirs | QDir::NoSymLinks | QDir::Hidden, QDirIterator::Subdirectories);
	while (dirPath.hasNext())
	{
		QString str = QString("%1").arg(dirPath.next());
		QFileInfo fInfo(str);
		path_to_file = fInfo.absoluteFilePath();
		path_to_folder = fInfo.canonicalPath();
	}

	QFile f1(path_to_file);
	if (f1.open(QIODevice::ReadOnly))
	{
		QTextStream in(&f1);
		QString str = in.readAll();
		QRegExp rx1("\\nLastVersion=(\\d\\d)");
		rx1.indexIn(str);
		ver = rx1.cap(1).toInt();
	}
	else qDebug() << "Файл не открылся";

	if (ver == 0)
	{
		qDebug() << "dont have version";
	}

	else
	{
		XMLwriter xmlOutPasswords(config->outputFolder() + "/firefox/passwords.xml");

		if (ver < 32)
		{
			//XMLwriter passOut1(config->outputFolder()+"/firefox/passwords.xml");

			QStringList ext;
			ext << "signons.sqlite";
			QString path2;
			QDirIterator dirPath(config->inputFolder() + "/Users/", ext, QDir::Files | QDir::Dirs | QDir::NoSymLinks | QDir::Hidden, QDirIterator::Subdirectories);
			while (dirPath.hasNext())
			{
				QString str = QString("%1").arg(dirPath.next());
				QFileInfo fInfo(str);
				path2 = fInfo.absoluteFilePath();
			}

			QSqlDatabase db2 = QSqlDatabase::addDatabase("QSQLITE");
			db2.setDatabaseName(path2);
			bool ok = db2.open();
			if (ok)
			{
				QSqlQuery query2(db2);
				query2.exec("SELECT encryptedUsername, encryptedPassword, formSubmitURL FROM moz_logins");
				while (query2.next())
				{
					QString EncUn = query2.value(0).toString();
					QString EncPsw = query2.value(1).toString();
					QString Url = query2.value(2).toString();
				}
				db2.close();
			}
		}
		else
		{
			QStringList ext;
			ext << "logins.json";
			QString path_json;
			QDirIterator dirPath(config->inputFolder() + "/Users/", ext, QDir::Files | QDir::Dirs | QDir::NoSymLinks | QDir::Hidden, QDirIterator::Subdirectories);
			while (dirPath.hasNext())
			{
				QString str = QString("%1").arg(dirPath.next());
				QFileInfo fInfo(str);
				path_json = fInfo.absoluteFilePath();
			}

			QFile file_json(path_json);
			if (file_json.open(QIODevice::ReadOnly))
			{
				QTextStream in2(&file_json);
				QString str = in2.readAll();
				//QStringList url;
				//QStringList login;
				//QStringList pass;
				/*QJsonDocument jsonResponse = QJsonDocument::fromJson(str.toUtf8());
				QJsonObject jsonObject = jsonResponse.object();
				QJsonArray jsonArray = jsonObject["logins"].toArray();
				foreach (const QJsonValue & value, jsonArray)
				{
				    QJsonObject obj = value.toObject();
				    url.append(obj["formSubmitURL"].toString());
				    login.append(obj["encryptedUsername"].toString());
				    pass.append(obj["encryptedPassword"].toString());
				}*/
				QStringList list;
				list = str.split(QRegExp("\"id\""));
				for (int i = 1; i < list.size(); i++)
				{
					QRegExp rx1("\"formSubmitURL\":\"(.*)\",\"username");
					QRegExp rx2("\"encryptedUsername\":\"(.*)\",\"encryptedPassword");
					QRegExp rx3("\"encryptedPassword\":\"(.*)\",\"guid");
					rx1.indexIn(list[i]);
					rx2.indexIn(list[i]);
					rx3.indexIn(list[i]);
					QString url = rx1.cap(1);
					QString login = rx2.cap(1);
					QString password = rx3.cap(1);
					Crack(login, path_to_folder); Crack(password, path_to_folder);
					//qDebug() << url << "  " << Crack(login, path_to_folder) << "  " << Crack(password, path_to_folder);
					//QString text_login (Crack(login, path_to_folder));
					//QString text_paswrd (Crack(password, path_to_folder));
					xmlOutPasswords.writePasswords(url, Crack(login, path_to_folder), Crack(password, path_to_folder));
				}

			}
			else qDebug() << "Файл не открылся";

		}

	}




	return true;
};

coex::ITask* createTask()
{
	return (coex::ITask*)(new TaskExample());
}
