#include "Util.h"


QString Util::createStringUuid()
{
	return QUuid::createUuid().toString().remove(QRegExp("[{}]"));
}

QString Util::sha1(const QString &data)
{
	return QString(QCryptographicHash::hash(data.toUtf8(), QCryptographicHash::Sha1).toHex());
}

QByteArray Util::makeJsonResult(const QString &result, const QString &message)
{
	QString json = "{ \"result\":\"%1\", \"message\":\"%2\" }";
	return json.arg(result, message).toUtf8();
}
