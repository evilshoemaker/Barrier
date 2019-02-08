#include "Variables.h"


QString Variables::databaseFilePath()
{
	QString defaultPath = qApp->applicationDirPath() + "/database/";

	QDir defautDir(defaultPath);
	if (!defautDir.exists())
		defautDir.mkpath(defaultPath);

	QString databaseName = defaultPath + "database.db";

	return databaseName;
}

QString Variables::settingsFilePath()
{
	return QDir::toNativeSeparators(qApp->applicationDirPath() + "/config.ini");
}

QString Variables::logFileFolderPath()
{
	static QString dirName = QCoreApplication::applicationDirPath()
			+ QDir::separator()
			+ QString("logs")
			+ QDir::separator();

	QDir savingDir;
	if (!savingDir.mkpath(dirName))
		return QString();

	return dirName;
}

QString Variables::logFilePath()
{
	static QString logFileFolder = logFileFolderPath();
	return logFileFolder + QString("log-%1").arg(QDate::currentDate().toString("yyyy.MM.dd.txt"));
}
