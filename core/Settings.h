#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings
{
public:
	static Settings &instance();

	QString login();
	void setLogin(const QString &login);

	QString password();
	void setPassword(const QString &password);

	void save();

private:
	Settings();

	QSettings *settings_;

	const QString LOGIN = "authorization/login";
	const QString PASSWORD_HASH = "authorization/password";
};

#endif // SETTINGS_H
