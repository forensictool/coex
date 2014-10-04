#include "coexDb.h"

#include <iostream>

CoexDB::CoexDB(){}
//-----------------------------------------------------------------------

CoexDB::CoexDB(const QString& filename)
{
  m_bOpen = this->connect(filename);
}
//-----------------------------------------------------------------------

CoexDB::~CoexDB(){}
//-----------------------------------------------------------------------

bool CoexDB::connect(const QString& filename)
{
  m_sdb = QSqlDatabase::addDatabase("QSQLITE");
  m_sdb.setDatabaseName(filename);
  bool bOpen = m_sdb.open();
  
  if (bOpen) 
  {
    QSqlQuery pragma_query(m_sdb);
    pragma_query.exec("PRAGMA auto_vacuum = 1");
    QSqlQuery query("SELECT name FROM sqlite_master WHERE type='table' AND name='dictionary';");
    if (!query.next()) 
    {
      // table not exists try create it
      QSqlQuery query_create(m_sdb);
      QString strQuery = 
      " CREATE TABLE dictionary ("
      " id INTEGER PRIMARY KEY AUTOINCREMENT, "
      " word varchar(50) NOT NULL)";
      query_create.exec(strQuery);
    }
  }    
  return bOpen;
}
//-----------------------------------------------------------------------

void CoexDB::disconnect()
{
  return;
}
//-----------------------------------------------------------------------

bool CoexDB::insert(const QString& data)
{
  if(!this->m_bOpen)
    return(false);
  QSqlQuery query(m_sdb);
  query.prepare("INSERT INTO dictionary(id, word) VALUES(NULL, :data)");
  query.bindValue(":data", QVariant(data));
  if(!query.exec())
  {
    std::cout << "Error: " << query.lastError().text().toStdString() << std::endl;
    return(false);
  }
  return(true);
}