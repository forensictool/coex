#include <QCoreApplication>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QFileInfo>
#include <QDateTime>
#include <QCryptographicHash>
#include <QDir>
#include <QDirIterator>
#include <QStringList>


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
void writeMedia(QString path,QXmlStreamWriter &xmlWriter,int mode,QString id,QString datecreate,QString datemodify,QString type,bool meta)
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
            write_field(xmlWriter,"application","media_scanner");
            write_field(xmlWriter,"doc_type",type);
            write_field(xmlWriter,"media_path",path);
            write_field(xmlWriter,"image_datecreate",datecreate);
            write_field(xmlWriter,"image_datemodify",datemodify);
            if (meta == 0)
            {
                xmlWriter.writeEndElement();
            }
    }

    if (mode==3)
    {
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
    }
}

};

void read_id3(QFile &file, QXmlStreamWriter &xmlWriter)
{
    QByteArray buffer, header, title, artist, album, year, all;
    if (file.open(QIODevice::ReadOnly))
    {
        all = file.readAll();
        buffer = all.right(128);
        header = buffer.left(3);
        title = buffer.mid(3, 30);
        artist = buffer.mid(33, 30);
        album = buffer.mid(63, 30);
        year = buffer.mid(93, 4);
    }
    file.close();
    QString titlestr(title), artstr(artist), albumstr(album), yearstr(year);
    xmlWriter.writeStartElement("metadata");
    XMLwriter start;
    start.write_field(xmlWriter, "title",titlestr);
    start.write_field(xmlWriter, "artist",artstr);
    start.write_field(xmlWriter, "album",albumstr);
    start.write_field(xmlWriter, "year",yearstr);
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
}

void read_jfif(QFile &file, QXmlStreamWriter &xmlWriter)
{
    QByteArray all, width, height, xres, yres, bpp, densunit;
    int pointer;
    if (file.open(QIODevice::ReadOnly))
    {
        all = file.readAll();
        QByteArray app0 = QByteArray::fromHex("FFE0");
        pointer = all.indexOf(app0);
        pointer += 11; //skipping to densunit part
        densunit = all.mid(pointer, 1);
        pointer += 1; //to x res
        xres = all.mid(pointer, 2);
        pointer += 2; //to y res
        yres = all.mid(pointer, 2);
        QByteArray sof0 = QByteArray::fromHex("FFC0");
        pointer = all.indexOf(sof0);
        pointer += 4; //skipping to bpp part
        bpp = all.mid(pointer, 1);
        pointer += 1; //to width
        width = all.mid(pointer, 2);
        pointer += 2; //to height
        height = all.mid(pointer, 2);
    }
    QDataStream ds(&width, QIODevice::ReadOnly);
    quint16 intw;
    ds >> intw;
    QString strw = QString::number(intw);
    QDataStream ds1(&height, QIODevice::ReadOnly);
    quint16 inth;
    ds1 >> inth;
    QString strh = QString::number(inth);
    QDataStream ds2(&xres, QIODevice::ReadOnly);
    quint16 intx;
    ds2 >> intx;
    QString strx = QString::number(intx);
    QDataStream ds3(&yres, QIODevice::ReadOnly);
    quint16 inty;
    ds3 >> inty;
    QString stry = QString::number(inty);
    QDataStream ds4(&bpp, QIODevice::ReadOnly);
    quint8 intbpp;
    ds4 >> intbpp;
    QString strbpp = QString::number(intbpp);
    QDataStream ds5(&densunit, QIODevice::ReadOnly);
    quint16 intdens;
    ds5 >> intdens;
    QString strdens;
    switch (intdens)
    {
        case 0:
            strdens = "no units";
            break;
        case 1:
            strdens = "ppi";
            break;
        case 2:
            strdens = "ppc";
            break;
    }
    xmlWriter.writeStartElement("metadata");
    XMLwriter start;
    start.write_field(xmlWriter, "bits per pixel",strbpp);
    start.write_field(xmlWriter, "width",strw);
    start.write_field(xmlWriter, "height",strh);
    start.write_field(xmlWriter, "density units",strdens);
    start.write_field(xmlWriter, "x resolution",strx);
    start.write_field(xmlWriter, "y resolution",stry);
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
}

void read_riff(QFile &file, QXmlStreamWriter &xmlWriter)
{
    QByteArray all, width, height, chnl, smpl;
    int pointer, wdint, htint;
    if (file.open(QIODevice::ReadOnly))
    {
        all = file.readAll();
        pointer = all.indexOf("strf"); //skip to vids
        pointer += 12; //skip to width
        width = all.mid(pointer, 4);
        pointer += 4; //skip to height
        height = all.mid(pointer, 4);
        pointer = all.indexOf("strf", pointer); //skip to auds
        pointer += 10; // skip to channels
        chnl = all.mid(pointer, 2);
        pointer += 2; //skip to sample rate
        smpl = all.mid(pointer, 2);
    }
    wdint = *reinterpret_cast<const int*>(width.data());
    htint = *reinterpret_cast<const int*>(height.data());
    QDataStream ds(&chnl, QIODevice::ReadOnly);
    ds.setByteOrder(QDataStream::LittleEndian);
    quint16 chint;
    ds >> chint;
    QString strch = QString::number(chint);
    QDataStream ds1(&smpl, QIODevice::ReadOnly);
    ds1.setByteOrder(QDataStream::LittleEndian);
    quint16 smplint;
    ds1 >> smplint;
    QString strsmpl = QString::number(smplint);
    QString strwd = QString::number(wdint);
    QString strht = QString::number(htint);
    xmlWriter.writeStartElement("metadata");
    XMLwriter start;
    start.write_field(xmlWriter, "video width",strwd);
    start.write_field(xmlWriter, "video height",strht);
    start.write_field(xmlWriter, "audio channels",strch);
    start.write_field(xmlWriter, "audio sample rate",strsmpl);
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
}

void scan_media(QString medianame, QXmlStreamWriter *xmlWriter)
{
    QStringList videoexts = (QStringList() << "mp4" << "mkv" << "avi" << "wmv" << "mov");
    QStringList imageexts = (QStringList() << "png" << "jpg" << "tiff" << "gif" << "bmp" << "jpeg" << "tif");
    QStringList musicexts = (QStringList() << "wma" << "mp3" << "flac" << "ape" << "wav" << "wave");
    QFile file(medianame);
    QFileInfo fileinfo(medianame);
    QByteArray md5;
    XMLwriter start;
    QString id, path, datecreate, datemodify, ext, type;
    bool meta = 0;
    path = fileinfo.canonicalFilePath();
    datecreate = fileinfo.created().toString();
    datemodify = fileinfo.lastModified().toString();
    ext = fileinfo.suffix();
    if (videoexts.contains(ext))
        type = "video";
    else if (imageexts.contains(ext))
        type = "image";
    else if (musicexts.contains(ext))
        type = "music";
    if (file.open(QIODevice::ReadOnly))
    {
        md5 = file.readAll();
        id = ext + "_" + QCryptographicHash::hash(md5, QCryptographicHash::Md5).toHex();
        if (ext == "mp3" || ext == "jpg" || ext == "avi")
        {
            meta = 1;
        }
    }
    file.close();
    qDebug()<<"file name ="<<medianame;
    start.writeMedia(path,*xmlWriter,2,id,datecreate,datemodify,type,meta);
    if (meta == 1 && ext == "mp3")
    {
        read_id3(file, *xmlWriter);
    }
    else if (meta == 1 && ext == "jpg")
    {
        read_jfif(file, *xmlWriter);
    }
    else if (meta == 1 && ext == "avi")
    {
        read_riff(file, *xmlWriter);
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList extensions = (QStringList() << "*.png" << "*.jpg" << "*.tiff" << "*.gif" << "*.bmp" << "*.jpeg" << "*.tif"
                                            << "*.mp4" << "*.mkv" << "*.avi" << "*.wmv" << "*.wma" << "*.mp3" << "*.flac" << "*.ape"
                                            << "*.mov" << "*.wav" << "*.wave");
    QDir dir("D:\\University\\Testfolder");
    QString xmlpath("D:\\University\\Testfolder\\Xml.xml");
    QFile xmlfile(xmlpath);
    xmlfile.open(QFile::WriteOnly);
    QXmlStreamWriter xmlWriter(&xmlfile);
    XMLwriter start;
    start.writeMedia(NULL,xmlWriter,1,NULL,NULL,NULL,NULL,NULL);
    QDirIterator fileListDirit("D:\\University\\Testfolder", extensions, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while (fileListDirit.hasNext())
    {
        QString str = QString("%1").arg(fileListDirit.next());
        QFileInfo fInfo(str);
        QFile file(fInfo.absoluteFilePath());
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            scan_media(str, &xmlWriter);
    }
    start.writeMedia(NULL,xmlWriter,3,NULL,NULL,NULL,NULL,NULL);
}
