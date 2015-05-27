#include <QCoreApplication>
#include <stdlib.h>
#include <iostream>
#include <QString>
#include <QDir>
#include <QFile>
#include <QList>
#include <fstream>
#include <QTextStream>
#include <QByteArrayMatcher>

using namespace std;

QString temp_path = "temp";
QString source_path = "/media/mrb4el/System/";

void copying(QString source, QString destination)
{

    cout << "Copy: " << source.toStdString() << " to " << destination.toStdString() << " ";
    if(QFile::copy(source, destination))
    {
        cout << "OK" << endl;
    }
    else cout << "FAIL" << endl;
}


// Copying source files.
void preparing()
{
    QDir().mkdir(temp_path);
    cout << "Temp folder created." << endl;

    QString source;
    QString destination;
    QString what = "SAM";

    QString raw_files[5] {"SAM", "SECURITY", "SOFTWARE", "SYSTEM", "DEFAULT"};

    for(int i = 0; i < 5; i++)
    {
        what = raw_files[i];
        source = source_path + "Windows/System32/config/" + what;
        destination = temp_path + "/" + what;

        copying(source, destination);
    }
}

//
struct element
{
    int id;
    QString children;
    QString content;
};

struct valuevs
{
    int id;
    QString name;
    QString value;
};

int id_list = 0;
int id_v_list = 0;

QList<element> Elements;
QList<valuevs> Values;

void adding(QString name, QString value)
{
    valuevs current;
    current.id = id_v_list;
    id_v_list++;

    current.name = name;
    current.value = value;

    Values.append(current);
}

void creation(QString name)
{
    element current;

    current.id = id_list;
    id_list++;

    current.children = "";
    current.content = name;


    Elements.append(current);
}

// Поиск родительского элемента
int search_parent(QString name, int right_border)
{
    int id = 0;
    int min = Elements.size();

    for(int i=0; i < Elements.size(); i++)
    {
        if(Elements[i].content == name)
        {
            if((right_border - i) < min) min = (right_border - i);
        }
    }
    id = right_border - min;
    return id;
}

void view_child(int id, string tabu)
{
    string temp = Elements[id].content.toStdString();

    if(Elements[id].children.length() != 0)
    {

        cout << tabu << "<" << temp << ">" << endl;

        if(Elements[id].children.section("/", 0, 0) != "v")
        {
            int i = 1;
            while(Elements[id].children.section("/", i, i) != "")
            {
                int sub_id = Elements[id].children.section("/", i, i).toInt();

                if(sub_id !=0)
                {
                    view_child(sub_id, tabu + "  ");
                }
                i++;
            }
        }
        if(Elements[id].children.section("/", 0, 0) == "v")
        {

            Elements[id].children.remove(0,1);

            int i = 1;
            while(Elements[id].children.section("/", i, i) != "")
            {
                int temp = Elements[id].children.section("/", i).toInt();

                cout << tabu << "  " << Values[temp].name.toStdString() << "=" << Values[temp].value.toStdString() << endl;
                i++;
            }
        }
        cout << tabu << "</" << temp << ">" << endl;
    }
    else
    {
        cout << tabu << "<" << temp << ">" << endl;
        cout << tabu << "</" << temp << ">" << endl;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    bool debug = true;
    //preparing();
/*
    creation("First");
    creation("Second");
    creation("Third");

    Elements[0].children = 1;

    for(int i =0; i < Elements.size(); i++)
    {
        cout << "id:" << Elements[i].id << endl;
        cout << "name:" << Elements[i].content.toStdString() << endl;
        cout << "children:" << Elements[i].children.toStdString() << endl;
    }
*/

    QFile file;
    file.setFileName("temp/reg.reg");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream stream(&file);

    QString ya_stroka;
    QString ethalon_ne_text;
    QString helpful;
    QString name;
    QString value;

    ya_stroka = stream.readLine();

    ya_stroka = stream.readLine();

    ethalon_ne_text = ya_stroka;

    int sostav = -1;

    bool stop = false;

    while(!stop)
    {
        ya_stroka = stream.readLine();
        ya_stroka = ya_stroka.trimmed();
        if (ya_stroka.isNull())
        {
            cout << "FUCK" << endl;
            ya_stroka = ethalon_ne_text;
            stop = true;
        }
        if(ya_stroka != ethalon_ne_text)
        {
            cout << ya_stroka.toStdString() << endl;

            // Составная строка
            sostav = ya_stroka.indexOf(",\\");
            if(sostav != -1)
            {
                helpful = ya_stroka;
                helpful = helpful.replace(",\\", ",");

                while(sostav != -1)
                {
                    helpful = ya_stroka;
                    helpful = helpful.replace(",\\", ",");

                    ya_stroka = stream.readLine();
                    ya_stroka=ya_stroka.trimmed();
                    ya_stroka=ya_stroka.replace(",\\", ",");

                    helpful += ya_stroka;
                    sostav = ya_stroka.indexOf(",\\");
                }
                ya_stroka = helpful;
            }

            // Ветка
            if(ya_stroka[0] == '[')
            {
                // Для корня
                if(ya_stroka.indexOf("\\") == -1)
                {
                    ya_stroka = ya_stroka.replace("]", "");
                    ya_stroka = ya_stroka.replace("[", "");

                    creation(ya_stroka);
                }
                // Для ветвей
                else
                {
                    name = ya_stroka.section('\\', -1);
                    name=name.replace("]", "");

                    creation(name);

                    name = ya_stroka.section('\\', -2, -2);
                    name = name.replace("[", "");

                    int parent = search_parent(name, id_list);

                    Elements[parent].children += "/";
                    Elements[parent].children += QString::number(id_list-1);
                }
            }
            // Значения полей
            if(ya_stroka[0] == '"')
            {
                name = ya_stroka.section("=", 0, 0);
                name.replace('"', "");

                value = ya_stroka.section("=", 1, 1);

                adding(name, value);

                if(Elements[id_list-1].children.isEmpty()) Elements[id_list-1].children+="v";
                Elements[id_list-1].children+="/";
                Elements[id_list-1].children+=QString::number(id_v_list-1);
            }
        }
    }

    file.close();

    cout << "VIEWING:\n" << endl;

    view_child(0, "");

    return a.exec();
}

