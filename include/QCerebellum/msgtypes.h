#ifndef POSITIONMESSAGE_H
#define POSITIONMESSAGE_H

#include "message.h"

namespace QCerebellum {

/**
 * @brief The BinaryIMessage class
 * Basic binary input class
 */
class BinaryIMessage : public IMessage
{
    QByteArray arr;

public:
    BinaryIMessage(const QString &name) : IMessage(name) {}

    void setValue(const QByteArray &a) { arr = a; }
    const QByteArray getValue() const { return arr; }
};

/**
 * @brief The PositionMessage class
 * Message describing robot position on flat area (X, Y, Theta)
 */
class PositionMessage : public IMessage
{

public:
    double x;
    double y;
    double theta;

    PositionMessage() : IMessage("position") {}
    PositionMessage(double _x, double _y, double _theta) :
        IMessage("position"),
        x(_x),
        y(_y),
        theta(_theta)
    {}

    void setValue(const QByteArray &a);
    const QByteArray getValue() const;
};

class TwistMessage : public OMessage
{

public:
    double left;
    double right;
    double distance;

    TwistMessage(double _left = 0, double _right = 0, double _distance = 0) :
        OMessage("twist"),
        left(_left),
        right(_right),
        distance(_distance)
    {}

    void setValue(const QByteArray &a);
    const QByteArray getValue() const;
};

}

#endif // POSITIONMESSAGE_H
