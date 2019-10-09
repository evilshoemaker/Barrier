#include "Settings.h"

#include "core/Variables.h"

Settings &Settings::instance()
{
	static Settings instance;
	return instance;
}

QString Settings::adminLogin()
{
    return settings_->value(ADMIN_LOGIN, "admin").toString();
}

void Settings::setAdminLogin(const QString &login)
{
    settings_->setValue(ADMIN_LOGIN, login);
}

QString Settings::adminPassword()
{
    return settings_->value(ADMIN_PASSWORD_HASH, "d033e22ae348aeb5660fc2140aec35850c4da997").toString();
}

void Settings::setAdminPassword(const QString &password)
{
    settings_->setValue(ADMIN_PASSWORD_HASH, password);
}

QString Settings::operatorLogin()
{
    return settings_->value(OPERATOR_LOGIN, "operator").toString();
}

void Settings::setOperatorLogin(const QString &login)
{
    settings_->setValue(OPERATOR_LOGIN, login);
}

QString Settings::operatorPassword()
{
    return settings_->value(OPERATOR_PASSWORD_HASH, "fe96dd39756ac41b74283a9292652d366d73931f").toString();
}

void Settings::setOperatorPassword(const QString &password)
{
    settings_->setValue(OPERATOR_PASSWORD_HASH, password);
}

void Settings::save()
{
	settings_->sync();
}

Settings::Settings() :
	settings_(new QSettings(Variables::settingsFilePath(), QSettings::IniFormat))
{

}
