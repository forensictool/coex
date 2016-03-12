TaskChromeWin
====
----
Plugin Version
----
* Version 1.0

----
Author
----
Vladislav Shipovskoy

----
About
----
Плагин находит на жестком диске установленную версию браузера Google Chrome, и считывает данные об истории посещений, поисковых запросах, загруженных файлах, закладках, версии браузера, установленных расширениях и учетных записях. Затем выводит эти данные в формат XML.

----
Required OS
----
* Stable: Windows XP, Windows 7
* Unstable: Windows 8, Windows 8.1, Windows 10

----
Chrome Version
----
* Google Chrome Version 25 - current

----
Methods
----

```
void TaskChromWin::prefrences(QString input, QString output)
```

* QString input - путь до папки, где находится браузер
* QString output - путь до папки, куда плагин записывает выходной XML файл
Вычитывает json файл preferences, в котором хранятся данные о версии, настройках и текущем пользователе. Преобразует к нужному формату.

```
void TaskChromWin::bookmarks(QString input, QString output)
```

* QString input - путь до папки, где находится браузер
* QString output - путь до папки, куда плагин записывает выходной XML файл
Метод считывает данные о закладках. 

```
void TaskChromWin::history(QString input, QString output)
```

* QString input - путь до папки, где находится браузер
* QString output - путь до папки, куда плагин записывает выходной XML файл
Метод считывает данные об истории посещений.

```
void TaskChromWin::extension(QString input, QString output)
```

* QString input - путь до папки, где находится браузер
* QString output - путь до папки, куда плагин записывает выходной XML файл
Метод считывает данные о дополнениях Chrome.

```
void TaskChromWin::login(QString input, QString output)
```

* QString input - путь до папки, где находится браузер
* QString output - путь до папки, куда плагин записывает выходной XML файл
Метод считывает данные о сохраненных логинах учетных записей.