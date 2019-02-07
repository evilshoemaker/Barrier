#ifndef WEBFACE_H
#define WEBFACE_H

#include <QObject>

class WebFace : public QObject
{
    Q_OBJECT
public:
    explicit WebFace(QObject *parent = nullptr);
    void init();

private:
#ifndef QT_NO_DEBUG

#ifdef _WIN32
    const QString SETTINGS_FILE = ":/resources/http_server_debug_win_config.ini";
#else
    const QString SETTINGS_FILE = ":/resources/http_server_debug_config.ini";
#endif

#else
	const QString SETTINGS_FILE = ":/resources/http_server_config.ini";
#endif
    //const QString SETTINGS_FILE = ":/resources/http_server_config.ini";
};

#endif // WEBFACE_H
