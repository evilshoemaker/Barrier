#include "WebFace.h"

#include <QSettings>
#include <QDebug>

#include "httplistener.h"
#include "httpsessionstore.h"

#include "RequestMapper.h"

#include "core/Settings.h"

WebFace::WebFace(QObject *parent)
    : QObject (parent)
{

}

void WebFace::init()
{
    QSettings* sessionSettings=new QSettings(SETTINGS_FILE, QSettings::IniFormat, this);
    sessionSettings->beginGroup("sessions");
    RequestMapper::sessionStore = new HttpSessionStore(sessionSettings, this);

    QSettings* templateSettings=new QSettings(SETTINGS_FILE, QSettings::IniFormat, this);
    templateSettings->beginGroup("templates");
    RequestMapper::templateCache = new TemplateCache(templateSettings, this);

    QSettings* fileSettings = new QSettings(SETTINGS_FILE, QSettings::IniFormat, this);
    fileSettings->beginGroup("files");
    RequestMapper::staticFileController = new StaticFileController(fileSettings, this);

    QSettings *listenerSettings = new QSettings(SETTINGS_FILE, QSettings::IniFormat, this);
    listenerSettings->beginGroup("listener");
    new HttpListener(listenerSettings, new RequestMapper(this), this);
}
