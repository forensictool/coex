#include "coex.h"

#include <QString>

class DetectExample : coex::IDetectOperationSystem {
	public:
		virtual coex::ITypeOperationSystem* detect(QString path);
		virtual QString name();
		virtual QString author();
		virtual QVector<coex::ITypeOperationSystem *> getSupportsOS();
};

extern "C"
{
	coex::IDetectOperationSystem* createDetectOperationSystem();
}
