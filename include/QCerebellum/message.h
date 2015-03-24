#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QByteArray>

namespace QCerebellum {

static const QString HEADER_SET = "set";
static const QString HEADER_GET = "get";

static const QString MSG_EMPTY = "empty";

/**
 * @brief The Message class
 * Abstract message interface
 */

class Message
{
protected:
    QString name;
    explicit Message(const QString &n) : name(n) {}

public:
    virtual const QString& getName() const { return name; }
    virtual const QByteArray getValue() const = 0;

    virtual void setName(const QString &n) { name = n; }
    virtual void setValue(const QByteArray &a) = 0;
};

/**
 * @brief The IMessage class
 * Abstract input message interface
 */
class IMessage : public Message
{
protected:
    explicit IMessage(const QString &name) : Message(name) {}
};

/**
 * @brief The OMessage class
 * Abstract output message interface
 */
class OMessage : public Message
{
protected:
    explicit OMessage(const QString &name) : Message(name) {}
};

} // namespace

#include "msgtypes.h"

#endif // MESSAGE_H
