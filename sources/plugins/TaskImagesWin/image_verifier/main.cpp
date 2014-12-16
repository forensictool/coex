#include <QCoreApplication>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QDataStream>
#include <QXmlStreamWriter>
#include <QFileInfo>
#include <QDateTime>
#include <QCryptographicHash>

class XMLwriter
{

public:
void write_field(QXmlStreamWriter &xmlWriter,QString sName,QString sValue)
{
    xmlWriter.writeStartElement("field");
    xmlWriter.writeAttribute("name",sName);
    xmlWriter.writeCharacters(sValue);
    xmlWriter.writeEndElement();
}


public:
void writeImage(QString path,QString result,QXmlStreamWriter &xmlWriter,int mode,QString id,QString datecreate,QString datemodify,QString containsarchive)
{
    if (mode==1)
    {
            xmlWriter.setAutoFormatting(true);
            xmlWriter.setAutoFormattingIndent(2);
            xmlWriter.writeStartDocument();
            xmlWriter.writeStartElement("add");
    }

    if (mode==2)
    {
            xmlWriter.writeStartElement("doc");
            write_field(xmlWriter,"id",id);
            write_field(xmlWriter,"application","images");
            write_field(xmlWriter,"doc_type","image");
            write_field(xmlWriter,"image_result",result);
            write_field(xmlWriter,"contains_archive",containsarchive);
            write_field(xmlWriter,"image_path",path);
            write_field(xmlWriter,"image_datecreate",datecreate);
            write_field(xmlWriter,"image_datemodify",datemodify);
            xmlWriter.writeEndElement();
    }

    if (mode==3)
    {
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
    }
}

};

void verify_image(QString imagename, QXmlStreamWriter *xmlWriter)
{
    QFile file(imagename);
    QFileInfo fileinfo(imagename);
    QByteArray buffer, md5;
    quint8 byte;
    XMLwriter start;
    QString id, path, datecreate, datemodify, result, containsarchive="false";
    path = fileinfo.canonicalFilePath();
    datecreate = fileinfo.created().toString();
    datemodify = fileinfo.lastModified().toString();
    if (file.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&file);
        if (imagename.endsWith("png", Qt::CaseInsensitive))
        {
            for (int i=0; i<4; i++)
            {
                stream >> byte;
                buffer.append(byte);
            }
            if (buffer.toHex() == "89504e47")
            {
                result = "correct";
            }
            else
            {
                result = "incorrect";
            }
            QByteArray archive;
            archive = file.readAll();
            if (archive.toHex().endsWith("ae426082") || result == "incorrect")
            {
                containsarchive = "false";
            }
            else
            {
                containsarchive = "true";
            }
            md5 = file.readAll();
            id = "png_" + QCryptographicHash::hash(md5, QCryptographicHash::Md5).toHex();
        }
        if (imagename.endsWith("gif", Qt::CaseInsensitive))
        {
            for (int i=0; i<3; i++)
            {
                stream >> byte;
                buffer.append(byte);
            }
            if (buffer.toHex() == "474946")
            {
                result = "correct";
            }
            else
            {
                result = "incorrect";
            }
            md5 = file.readAll();
            id = "gif_" + QCryptographicHash::hash(md5, QCryptographicHash::Md5).toHex();
        }
        if (imagename.endsWith("bmp", Qt::CaseInsensitive))
        {
            for (int i=0; i<2; i++)
            {
                stream >> byte;
                buffer.append(byte);
            }
            if (buffer.toHex() == "424d")
            {
                result = "correct";
            }
            else
            {
                result = "incorrect";
            }
            md5 = file.readAll();
            id = "bmp_" + QCryptographicHash::hash(md5, QCryptographicHash::Md5).toHex();
        }
        if (imagename.endsWith("tiff", Qt::CaseInsensitive) || imagename.endsWith("tif", Qt::CaseInsensitive))
        {
            for (int i=0; i<3; i++)
            {
                stream >> byte;
                buffer.append(byte);
            }
            if (buffer.toHex() == "49492a")
            {
                result = "correct";
            }
            else
            {
                result = "incorrect";
            }
            md5 = file.readAll();
            id = "tiff_" + QCryptographicHash::hash(md5, QCryptographicHash::Md5).toHex();
        }
        if (imagename.endsWith("jpeg", Qt::CaseInsensitive) || imagename.endsWith("jpg", Qt::CaseInsensitive))
        {
            for (int i=0; i<2; i++)
            {
                stream >> byte;
                buffer.append(byte);
            }
            if (buffer.toHex() == "ffd8")
            {
                result = "correct";
            }
            else
            {
                result = "incorrect";
            }
            QByteArray archive;
            archive = file.readAll();
            if (archive.toHex().endsWith("ffd9") || result == "incorrect")
            {
                containsarchive = "false";
            }
            else
            {
                containsarchive = "true";
            }
            md5 = file.readAll();
            id = "jpg_" + QCryptographicHash::hash(md5, QCryptographicHash::Md5).toHex();
        }
    }
    file.close();
    qDebug()<<"file name ="<<imagename<<" header ="<<buffer.toHex()<<" image_result ="<<result<<" contains_archive= "<<containsarchive;
    start.writeImage(path,result,*xmlWriter,2,id,datecreate,datemodify,containsarchive);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString xmlpath("XML/xml.xml");
    QFile xmlfile(xmlpath);
    xmlfile.open(QFile::WriteOnly);
    QXmlStreamWriter xmlWriter(&xmlfile);
    XMLwriter start;
    start.writeImage(NULL,NULL,xmlWriter,1,NULL,NULL,NULL,NULL);
    verify_image("pic_bmp.bmp", &xmlWriter);
    verify_image("pic_gif.gif", &xmlWriter);
    verify_image("pic_jpg.jpg", &xmlWriter);
    verify_image("pic_tiff.tiff", &xmlWriter);
    verify_image("pic_png.png", &xmlWriter);
    verify_image("text_bmp.bmp", &xmlWriter);
    verify_image("text_gif.gif", &xmlWriter);
    verify_image("text_jpg.jpg", &xmlWriter);
    verify_image("text_tiff.tiff", &xmlWriter);
    verify_image("text_png.png", &xmlWriter);
    verify_image("archive_jpg.jpg", &xmlWriter);
    verify_image("archive_png.png", &xmlWriter);
    start.writeImage(NULL,NULL,xmlWriter,3,NULL,NULL,NULL,NULL);
}
