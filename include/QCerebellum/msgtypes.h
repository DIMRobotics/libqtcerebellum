#ifndef POSITIONMESSAGE_H
#define POSITIONMESSAGE_H

#include "message.h"

#include <QVector>

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

    PositionMessage() :
        IMessage("position"),
        x(0),
        y(0),
        theta(0)
    {}
    PositionMessage(double _x, double _y, double _theta) :
        IMessage("position"),
        x(_x),
        y(_y),
        theta(_theta)
    {}

    void setValue(const QByteArray &a);
};

/**
 * @brief The TwistMessage class
 * Describes basic movement command for robot chassis:
 * speeds of left and right wheels and distance
 */
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

/**
 * @brief The DynamicsMessage class
 * Describes movement dynamics such as
 * acceleration and brake forces
 */
class DynamicsMessage : public OMessage
{

public:
    double acceleration;
    double brake_force;
    double ebrake_force;

    DynamicsMessage(double _acc, double _brake, double _ebrake) :
        OMessage("dynamics"),
        acceleration(_acc),
        brake_force(_brake),
        ebrake_force(_ebrake)
    {}

    void setValue(const QByteArray &a);
    const QByteArray getValue() const;
};

class ODetectMessage : public IMessage
{
    qint32 len;
    QVector<double> values;

public:

    ODetectMessage() :
        IMessage("odetect"),
        len(0)
    {}

    void setValue(const QByteArray &a);

    int length() { return len; }
    double getSensorData(int index) { return values[index]; }
    double operator[](int i) { return values[i]; }
};

}
#endif // POSITIONMESSAGE_H
