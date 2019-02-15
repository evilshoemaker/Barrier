#include "CarNumberParser.h"

#include <QRegularExpression>

CarNumberParser::CarNumberParser(QObject *parent) : QObject(parent)
{

}

QString CarNumberParser::number()
{
    return number_;
}

void CarNumberParser::setNumber(const QString &number)
{
    if (number_ == number)
        return;

    number_ = number;
    emit numberChanged();

	if (number.isEmpty())
	{
		setChar1("");
		setDigital("");
		setChar2("");
		setRegion("");
		return;
	}

	QRegularExpression re("^(?<char1>[A-ZА-Я])(?<number>\\d\\d\\d)(?<char2>[A-ZА-Я][A-ZА-Я])(?<region>\\d\\d?[\\d])$");
    QRegularExpressionMatch match = re.match(number_);
    if (match.hasMatch()) {
        setChar1(match.captured("char1"));
        setDigital(match.captured("number"));
        setChar2(match.captured("char2"));
        setRegion(match.captured("region"));
    }
}

QString CarNumberParser::char1()
{
    return char1_;
}

void CarNumberParser::setChar1(const QString &char1)
{
    if (char1_ == char1)
        return;

    char1_ = char1;
    emit char1Changed();
}

QString CarNumberParser::char2()
{
    return char2_;
}

void CarNumberParser::setChar2(const QString &char2)
{
    if (char2_ == char2)
        return;

    char2_ = char2;
    emit char2Changed();
}

QString CarNumberParser::digital()
{
    return digital_;
}

void CarNumberParser::setDigital(const QString &digital)
{
    if (digital_ == digital)
        return;

    digital_ = digital;
    emit digitalChanged();
}

QString CarNumberParser::region()
{
    return region_;
}

void CarNumberParser::setRegion(const QString &region)
{
    if (region_ == region)
        return;

    region_ = region;
    emit regionChanged();
}
