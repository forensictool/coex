#include "config.h"

#include <QDirIterator>
#include <QLibrary>

Config::Config() {
	m_pTypeOS = NULL;
};

QString Config::inputFolder() const {
	return m_sInputFolder;
};

QString Config::outputFolder() const {
	return m_sOutputFolder;
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
