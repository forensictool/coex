#ifndef __COEX_DB_H__
#define __COEX_DB_H__

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class CoexDB
{
  public:
  	CoexDB();
  	~CoexDB();
  	CoexDB(const QString& filename);
  	bool connect(const QString& filename);
  	bool insert(const QString&);
    void disconnect();

  private:
  	bool m_bOpen;
  	QSqlDatabase m_sdb;
};

#endif //__COEX_DB_H__