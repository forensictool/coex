#ifndef __TASK_SEARCH_ARCHIVE_H__
#define __TASK_SEARCH_ARCHIVE_H__

#include "coex.h"

#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDateTime>
/*!
    \brief Дочерний класс
    \author IgorPolyakov
    \version 1.0
    \date Вт. марта 17 16:13:27 NOVT 2015
    \warning Данный класс полноченно работет только с zip архивами
    \bug 	Перечисление известных ошибок
    \todo 	Добавить rar, 7z

    Плагин для COEX. Осуществляет поиск архивных файлов. Извлекает информацию о них, создает отчет.
*/
class TaskSearchArchive : coex::ITask
{
public:
    TaskSearchArchive();
    virtual QString help();
    virtual QString name();
    virtual QString author();
    virtual QString description();

    virtual bool isSupportOS(const coex::ITypeOperationSystem *os);
    virtual void setOption(QStringList);
    QString listZip(QString zipFile);
    void determineTypeArchive(QString path);
    virtual bool execute(const coex::IConfig *config);
private:
    bool m_bDebug;
};

extern "C"
{
    coex::ITask* createTask();
}

#endif // __TASK_SEARCH_ARCHIVE_H__
