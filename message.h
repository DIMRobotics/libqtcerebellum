#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QByteArray>

namespace QCerebellum {

static const QString HEADER_SET = "set";
static const QString HEADER_GET = "get";

class Message
{
protected:
    QString name;
    QByteArray value;

public:
    Message() : name("") {}
    explicit Message(const QString &n) : name(n) {}
    explicit Message(const QString &n, const QByteArray &a) : name(n), value(a) {}

    virtual const QString& getHeader() const = 0;
    virtual const QString& getName() const { return name; }
    virtual const QByteArray& getValue() const { return value; }

    virtual void setName(const QString &n) { name = n; }
    virtual void setValue(const QByteArray &a) { value = a; }
};

class IMessage : public Message
{
public:
    IMessage();
    explicit IMessage(const QString &name) : Message(name) {}
    explicit IMessage(const QString &name, const QByteArray &arr) : Message(name, arr) {}
    virtual const QString& getHeader() const { return HEADER_SET; }

};

class OMessage : public Message
{
public:
    OMessage();
    explicit OMessage(const QString &name) : Message(name) {}
    explicit OMessage(const QString &name, const QByteArray &arr) : Message(name, arr) {}
    virtual const QString& getHeader() const { return HEADER_GET; }
};

} // namespace

#endif // MESSAGE_H
