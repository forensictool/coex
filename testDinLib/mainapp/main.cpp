#include <QtGui>
#include <QtCore>
#include <iostream>

//int main(int argc, char** argv)
int main()
{
    //QApplication app(argc, argv);
    QString lbl("this is the example text");
    QLibrary lib("/home/mariarti/develop/testDinLib/test/dist/libdinlib.so.1.0.0");

    typedef QString (*Fct) (const QString&);
    Fct fct = (Fct)(lib.resolve("oddUpper"));
    if (fct) 
    {
        lbl = fct(lbl);
    }
    else
    {
    	std::cout << "sasay!!!" << std::endl;
    	return -1;
    }
    std::cout << lbl.toStdString() << std::endl;

    return 0;
    //return app.exec();
}