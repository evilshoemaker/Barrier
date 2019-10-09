#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings
{
public:
	static Settings &instance();

    QString adminLogin();
    void setAdminLogin(const QString &login);

    QString adminPassword();
    void setAdminPassword(const QString &password);

    QString operatorLogin();
    void setOperatorLogin(const QString &login);

    QString operatorPassword();
    void setOperatorPassword(const QString &password);

	void save();

private:
	Settings();

	QSettings *settings_;

    const QString ADMIN_LOGIN = "authorization/adminLogin";
    const QString ADMIN_PASSWORD_HASH = "authorization/adminPassword";

    const QString OPERATOR_LOGIN = "authorization/operatorLogin";
    const QString OPERATOR_PASSWORD_HASH = "authorization/operatorPassword";
};

#endif // SETTINGS_H
