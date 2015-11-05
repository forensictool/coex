#include "writerxml.h"

    void write_field(QXmlStreamWriter &xmlWriter,QString sName,QString sValue)
    {
        xmlWriter.writeStartElement("field");
        xmlWriter.writeAttribute("name",sName);
        xmlWriter.writeCharacters(sValue);
        xmlWriter.writeEndElement();
    }

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