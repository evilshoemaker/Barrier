#ifndef UTIL_H
#define UTIL_H

#include <QtCore>

class Util
{
public:
    static QString createStringUuid();
	static QString sha1(const QString &data);
	static QByteArray makeJsonResult(const QString &result, const QString &message = "");
};

#endif // UTIL_H
