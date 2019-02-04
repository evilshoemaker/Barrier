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
