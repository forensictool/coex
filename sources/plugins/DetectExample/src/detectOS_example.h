#include "coex.h"

#include <QString>

class DetectExample : coex::IDetectOperationSystem {
	public:
		virtual coex::ITypeOperationSystem* detect(QString path);
		virtual QString author();
};

extern "C"
{
	coex::IDetectOperationSystem* createDetectOperationSystem();
}
