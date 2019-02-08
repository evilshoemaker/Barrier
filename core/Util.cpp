#include "Util.h"


QString Util::createStringUuid()
{
	return QUuid::createUuid().toString().remove(QRegExp("[{}]"));
}

QString Util::sha1(const QString &data)
{
	return QString(QCryptographicHash::hash(data.toUtf8(), QCryptographicHash::Sha1).toHex());
}
