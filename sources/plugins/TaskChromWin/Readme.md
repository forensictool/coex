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
TaskChromeWin searches for an installed copy of Google Chrome after which it reads internet history, search history, download history, bookmarks, browser version, installed extensions and accounts data. After that the plugin writes the data to and XML file.

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

* QString input - Path to browser
* QString output - Path to an XML file (output)

Reads "preferences" file which contains version, settings and current user data.

```
void TaskChromWin::bookmarks(QString input, QString output)
```

* QString input - Path to browser
* QString output - Path to an XML file (output)

Reads bookmarks.

```
void TaskChromWin::history(QString input, QString output)
```

* QString input - Path to browser
* QString output - Path to an XML file (output)

Reads browser history.

```
void TaskChromWin::extension(QString input, QString output)
```

* QString input - Path to browser
* QString output - Path to an XML file (output)

Reads installed extensions data.

```
void TaskChromWin::login(QString input, QString output)
```

* QString input - Path to browser
* QString output - Path to an XML file (output)

Reads saved logins.