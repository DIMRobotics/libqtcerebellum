#include <QCerebellum/message.h>

#include <QDataStream>

using namespace QCerebellum;

void PositionMessage::setValue(const QByteArray &a)
{
    QDataStream stream(a);

    stream >> x >> y >> theta;
}

void TwistMessage::setValue(const QByteArray &a)
{
    QDataStream stream(a);

    stream >> left >> right >> distance;
}

const QByteArray TwistMessage::getValue() const
{
    QByteArray ret;
    QDataStream out(&ret, QIODevice::WriteOnly);

    out << left << right << distance;

    return ret;
}

void DynamicsMessage::setValue(const QByteArray &a)
{
    QDataStream stream(a);

    stream >> acceleration >> brake_force >> ebrake_force;
}

const QByteArray DynamicsMessage::getValue() const
{
    QByteArray ret;
    QDataStream out(&ret, QIODevice::WriteOnly);

    out << acceleration << brake_force << ebrake_force;

    return ret;
}

void ODetectMessage::setValue(const QByteArray &a)
{
    QDataStream stream(a);

    stream >> len;

    for (qint32 i = 0; i < len; i++)
        stream >> values[i];
}
