#include "detectOS_example.h"

#include <QFile>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QIODevice>
#include <QList>
#include <iostream>

coex::ITypeOperationSystem* DetectExample::detect(QString path) {
	/*
	 * here you try detect and return coex::ITypeOperationSystem*
	 * if you don't detect then you must return NULL
	 * */
	return NULL;
};

QString DetectExample::name() {
	/*
	 * returned name of implementation
	 * */
	return "detectExample";
};

QString DetectExample::author() {
	/*
	 * returned name of developer
	 * */
	return "Evgenii Sopov";
};

QVector<coex::ITypeOperationSystem *> DetectExample::getSupportsOS() {
	QVector<coex::ITypeOperationSystem *> supportsOS;
	/*
	 * returned list of suppotrs os for detection
	 * */
	return supportsOS;
};

coex::IDetectOperationSystem* createDetectOperationSystem() {
	return (coex::IDetectOperationSystem*)(new DetectExample());
}
