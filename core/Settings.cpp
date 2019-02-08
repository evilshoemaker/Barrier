#include "Settings.h"

#include "core/Variables.h"

Settings &Settings::instance()
{
	static Settings instance;
	return instance;
}

QString Settings::login()
{
	return settings_->value(LOGIN, "admin").toString();
}

void Settings::setLogin(const QString &login)
{
	settings_->setValue(LOGIN, login);
}

QString Settings::password()
{
	return settings_->value(PASSWORD_HASH, "d033e22ae348aeb5660fc2140aec35850c4da997").toString();
}

void Settings::setPassword(const QString &password)
{
	settings_->setValue(PASSWORD_HASH, password);
}

Settings::Settings() :
	settings_(new QSettings(Variables::settingsFilePath(), QSettings::IniFormat))
{

}
