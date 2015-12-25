#include "taskThunderbird.h"
#include <QDebug>
#include <iostream>
#include <QDirIterator>
#include <QString>
#include <QRegExp>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTextStream>

void XMLwriter::write_field(QXmlStreamWriter &xmlWriter, QString sName, QString sValue)
    {
        xmlWriter.writeStartElement("field");
        xmlWriter.writeAttribute("name", sName);
        xmlWriter.writeCharacters(sValue);
        xmlWriter.writeEndElement();
    }

void XMLwriter::writeFile(QXmlStreamWriter &xmlWriter, int mode, QString name)
    {
        if (mode == 1) {
            xmlWriter.setAutoFormatting(true);
            xmlWriter.setAutoFormattingIndent(2);
            xmlWriter.writeStartDocument();
            xmlWriter.writeStartElement("add");
        }

        else if (mode == 2) {
            xmlWriter.writeStartElement("file");
            write_field(xmlWriter, "name", name);
        }

        else if (mode == 3) {
            xmlWriter.writeEndElement();
            xmlWriter.writeEndDocument();
        }

        else if (mode == 4) {
            xmlWriter.writeEndElement();
        }
    }

void XMLwriter::writeMessage(QXmlStreamWriter &xmlWriter, QString date, QString from, QString to, QString text)
    {
        xmlWriter.writeStartElement("message");
        write_field(xmlWriter, "date", date);
        write_field(xmlWriter, "from", from);
        write_field(xmlWriter, "to", to);
        write_field(xmlWriter, "text", text);
        xmlWriter.writeEndElement();
    }

TaskExample::TaskExample() {
	m_bDebug = false;
};

QString TaskExample::help() {
	return "\t--debug - viewing debug messages";
};

QString TaskExample::name() {
	return "ThunderbirdWin";
};

QString TaskExample::author() {
	return "Yuriy Tereshchenko";
};

QString TaskExample::description() {
	return "search messages";
};

bool TaskExample::isSupportOS(const coex::ITypeOperationSystem *os) {
	return (os->platform() == "Windows");
};

void TaskExample::setOption(QStringList options) {
	/*
	 * 
	 * */
	if(options.contains("--debug"))
		m_bDebug = true;
};

void TaskExample::pars(QString str, QXmlStreamWriter *xmlWriter)
{
    XMLwriter start;
    QString date, from, to, text;
    QRegExp rx1("\\nDate: ([^\\n]*)\\n");
    QRegExp rx2("\\nFrom: .*([a-z][\\w\\.]*\\w@\\w[\\w\\.]*\\.\\w*).*\\nSubject:");
    QRegExp rx3("\\nTo: .*([a-z][\\w\\.]*\\w@\\w[\\w\\.]*\\.\\w*).*\\nSubject:");
    QRegExp rx4("\\nContent-Transfer-Encoding: 8bit\\s*(\\S.*\\S)\\s*[0-3]\\d\\.[01]\\d\\.\\d{4} [0-2]\\d:[0-5]\\d, [^\\n]*\\n> ");
    rx1.indexIn(str);
    rx2.indexIn(str);
    rx3.indexIn(str);
    rx4.indexIn(str);
    date = rx1.cap(1);
    from = rx2.cap(1);
    to = rx3.cap(1);
    text = rx4.cap(1);
    start.writeMessage(*xmlWriter, date, from, to, text);
}

void TaskExample::openfile(QString input, QXmlStreamWriter *xmlWriter)
{
    XMLwriter start;
    QFile f(input);
    if (f.open(QIODevice::ReadOnly))
    {
        start.writeFile(*xmlWriter, 2, input);
        QTextStream in(&f);
        QString str = in.readAll();
        QStringList list;
        list = str.split(QRegExp("(From \\r\\n)|(From \\n\\r)|From \\r|From \\n"));
        for (int i = 1; i < list.size(); ++i)
        {
            QString temp = list[i];
            pars(temp, xmlWriter);
        }
        start.writeFile(*xmlWriter, 4, NULL);
    }
    else qDebug() << "Файл не открылся";
}

bool TaskExample::execute(const coex::IConfig *config) {
	if(m_bDebug) {
		std::cout << "  !!! debug mode on.\n";
		std::cout << "InputFolder: " << config->inputFolder().toStdString() << "\n";
	};

	QString xmlpath(config->outputFolder()+"/thunderbird/messages.xml");
    QFile xmlfile(xmlpath);
    xmlfile.open(QFile::WriteOnly);
    QXmlStreamWriter xmlWriter(&xmlfile);
    XMLwriter start;
    start.writeFile(xmlWriter, 1, NULL);
    QStringList ext;
    ext << "&*-";
    QDirIterator dirPath(config->inputFolder() + "/Users/", ext, QDir::Files | QDir::Dirs | QDir::NoSymLinks | QDir::Hidden, QDirIterator::Subdirectories);
    while (dirPath.hasNext())
    {
        QString str = QString("%1").arg(dirPath.next());
        QFileInfo fInfo(str);
        QFile file(fInfo.absoluteFilePath());
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            openfile(str, &xmlWriter);
        }
    }
    start.writeFile(xmlWriter, 3, NULL);

	return true;
};

coex::ITask* createTask() {
	return (coex::ITask*)(new TaskExample());
}
