#ifndef VARIABLES_H
#define VARIABLES_H

#include <QtCore>

class Variables
{
public:
    static QString databaseFilePath();

	static QString settingsFilePath();

	static QString logFileFolderPath();

	static QString logFilePath();
};

#endif // VARIABLES_H
