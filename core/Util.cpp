#include "Util.h"


QString Util::createStringUuid()
{
    return QUuid::createUuid().toString().remove(QRegExp("[{}]"));
}
