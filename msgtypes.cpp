#include <QCerebellum/message.h>

#include <QDataStream>

using namespace QCerebellum;

void PositionMessage::setValue(const QByteArray &a)
{
    QDataStream stream(a);

    stream >> x >> y >> theta;
}

const QByteArray PositionMessage::getValue() const
{
    QByteArray ret;
    QDataStream out(&ret, QIODevice::WriteOnly);

    out << x << y << theta;

    return ret;
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
