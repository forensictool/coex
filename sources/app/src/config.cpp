#include "config.h"

#include <QDirIterator>
#include <QLibrary>

#include "unistd.h"

Config::Config() {
	m_pTypeOS = NULL;
};

QString Config::inputFolder() const {
	return m_qmArguments.value("inputFolder");
};

QString Config::outputFolder() const {
	return m_qmArguments.value("outputFolder");
};

const coex::ITypeOperationSystem* Config::typeOS() const {
	return m_pTypeOS;
};

void Config::setInputFolder(QString path) {
	m_sInputFolder = path;
};

void Config::setOutputFolder(QString path) {
	m_sOutputFolder = path;
};

void Config::setTypeOS(coex::ITypeOperationSystem* pTypeOS) {
	m_pTypeOS = pTypeOS;
};

bool Config::isUnknownOS() {
	if (m_pTypeOS != NULL && m_pTypeOS->platform() != "")
		return false;
	return true;
};

bool Config::isWindows() {
	if (m_pTypeOS != NULL && m_pTypeOS->platform() != "Windows")
		return true;
	return false;
};

bool Config::isLinux() {
	if (m_pTypeOS != NULL && m_pTypeOS->platform() != "Linux")
		return true;
	return false;
};

coex::IConfig* createConfig() {
	return (coex::IConfig *) new Config();
}
//------------------------------------------------------------------------------------

bool Config::getArgumentsValues(int argc, char **argv, QString shortopts)
{
  if(argc < 3)
    return false;
  int pr = 0;
  while((pr = getopt(argc, argv, shortopts.toAscii().data())) != -1)
    {
      switch (pr)
        {
        case 'i':
          this->m_qmArguments.insert("inputFolder", optarg);
          break;
        case 'o':
          this->m_qmArguments.insert("outputFolder", optarg);
          break;
        default:
          break;
        }
    }
  return false;
}
