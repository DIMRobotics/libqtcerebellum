#ifndef LIBQTCEREBELLUM_H
#define LIBQTCEREBELLUM_H

#include "qtcerebellum_global.h"

#include <QObject>
#include <QByteArray>

#include <zmq.hpp>

#include "message.h"

namespace QCerebellum {

static const QString MSG_OK = "OK";

class LIBQTCEREBELLUMSHARED_EXPORT Socket : public QObject
{
    Q_OBJECT

public:
    zmq::context_t context;
    zmq::socket_t socket;

    bool srv_online;
    bool brd_online;

    QString server_addr;

protected:
    bool pushMessage(const QString &s, const Message &a);
    bool popIMessage(IMessage &a);
    bool getReply();

public:
    explicit Socket(QObject *parent = 0);
    explicit Socket(const QString &s, QObject *parent = 0);

    virtual ~Socket();

    void connectToServer(const QString &s);
    void closeConnection();

    bool send(const OMessage &a);
    bool recv(IMessage &a);

    bool serverOnline() { return srv_online; }

    Socket& operator<<(const OMessage &a) { send(a); return *this; }
    Socket& operator>>(IMessage &a) { recv(a); return *this; }

};

}

Q_DECLARE_METATYPE(QCerebellum::PositionMessage)

#endif // LIBQTCEREBELLUM_H
