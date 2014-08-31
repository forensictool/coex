#include "coex.h"

#include <QString>

class DetectKernel32Win : coex::IDetectOperationSystem {
	public:
		DetectKernel32Win();
		virtual coex::ITypeOperationSystem* detect(QString path);
		virtual QString name();
		virtual QString author();
		virtual QVector<coex::ITypeOperationSystem *> getSupportsOS();
	private:	
		coex::ITypeOperationSystem* m_pWindows95;
		coex::ITypeOperationSystem* m_pWindows98;
		coex::ITypeOperationSystem* m_pWindowsXP;
		coex::ITypeOperationSystem* m_pWindowsVista;
		coex::ITypeOperationSystem* m_pWindows7;
		coex::ITypeOperationSystem* m_pWindows8;
};

extern "C"
{
	coex::IDetectOperationSystem* createDetectOperationSystem();
}
