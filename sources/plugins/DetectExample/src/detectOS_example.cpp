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
	 * if not you just NULL returned
	 * */
	return NULL;
};

QString DetectExample::author() {
	/*
	 * return name of developer
	 * */
	return "sea-kg";
};

coex::IDetectOperationSystem* createDetectOperationSystem() {
	return (coex::IDetectOperationSystem*)(new DetectExample());
}
