#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QScreen>

#include <QFile>
#include <QSqlRecord>

#include "core/Variables.h"
#include "core/CarNumberParser.h"
#include "webface/WebFace.h"

#include "database/CarNumberInfoModel.h"
#include "database/CarNumberInfo.h"
#include "database/Database.h"
#include "database/DatabaseLogger.h"

#include <csignal>

void writeLogMessage(const QString &message)
{
	QFile file(Variables::logFilePath());
	if (!file.open(QIODevice::Append))
	{
		printf("%s \n", file.errorString().toStdString().c_str());
		return;
	}

	QTextStream log(&file);
	log << message;

	file.close();
}

void messageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	QString message;

	QString className;
	QString functionName;

	QRegExp classNameRegex("([\\w-]+)::");
	QRegExp functionNameRegex("::([\\w-]+)");

	if (classNameRegex.indexIn(context.function) == -1)
		className = QString("");
	else
		className = classNameRegex.cap(1);

	if (functionNameRegex.indexIn(context.function) == -1)
	{
		QRegExp functionNameRegex2("\\s([\\w-]+)\\(");

		functionNameRegex2.indexIn(context.function);
		functionName = functionNameRegex2.cap(1);
	}
	else
		functionName = functionNameRegex.cap(1);

	QRegExp fileNameRegex("/([\\w-.]+)$");
	fileNameRegex.indexIn(context.file);
	QString filename = fileNameRegex.cap(1);

	QRegExp classx("([\\w-]+)::([\\w-]+)");
	classx.indexIn(context.function);
	classx.cap(0);

	QDateTime dateTime = QDateTime::currentDateTime();

	message = dateTime.toString(QString("dd.MM.yyyy hh:mm:ss.zzz"));

	switch (type)
	{
	case QtInfoMsg:
		message += QString(" [Info]");
		break;
	case QtDebugMsg:
		message += QString(" [Debug]");
		break;
	case QtWarningMsg:
		message += QString(" [Warning]");
		break;
	case QtCriticalMsg:
		message += QString(" [Critical]");
		break;
	case QtFatalMsg:
		message += QString(" [Fatal]");
		break;
	}

	message += QString(" [%1] [%2] [%3:%4] %5\n").arg(className, functionName, filename).arg(context.line).arg(msg);

	/*#ifndef QT_DEBUG

	writeLogMessage(message);
#else

	QTextStream stream(stdout);
	stream.setCodec("IBM 866");
	stream << message << "\n";

#endif*/
	QTextStream stream(stdout);

	stream << qPrintable(message);
	writeLogMessage(message);

	if (type == QtFatalMsg)
		abort();
}

void ignoreSigpipe()
{
#if defined(Q_OS_WIN)
	return;
#else
	// install signal handler
	struct sigaction act;
	int r;
	memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	act.sa_flags = SA_RESTART;
	r = sigaction(SIGPIPE, &act, NULL);
	if (r)
	{
		qWarning() << "Sigaction failed with return value = " << QString::number(r);
	}
#endif
}

void registerMetaType()
{
	qRegisterMetaType<QList<QSqlRecord>>("QList<QSqlRecord>");
}

void qmlRegisterTypes()
{
    qmlRegisterType<CarNumberInfoModel>("app", 1, 0, "CarNumberInfoModel");
	qmlRegisterType<CarNumberInfo>("app", 1, 0, "CarNumberInfo");
    qmlRegisterType<CarNumberParser>("app", 1, 0, "CarNumberParser");
}

int main(int argc, char *argv[])
{
#ifndef QT_NO_DEBUG
	qDebug() << "Debug mode on";
#else
	qInstallMessageHandler(messageOutput);
#endif

	ignoreSigpipe();
	registerMetaType();
    qmlRegisterTypes();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);

	Database::emptySelect();

	WebFace webFace;
	webFace.init();

	QQmlApplicationEngine engine;

	engine.rootContext()->setContextProperty("databaseLogger", QVariant::fromValue(DatabaseLogger::instance()));

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
		return -1;

    return app.exec();
}
