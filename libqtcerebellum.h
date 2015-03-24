#ifndef LIBQTCEREBELLUM_H
#define LIBQTCEREBELLUM_H

#include "libqtcerebellum_global.h"

#include <QObject>
#include <QByteArray>

#include <zmq.hpp>

#include "message.h"

namespace QCerebellum {

static const QString MSG_OK = "OK";

class LIBQTCEREBELLUMSHARED_EXPORT Socket : public QObject
{
    Q_OBJECT

    zmq::context_t context;
    zmq::socket_t socket;

    QString server_addr;

protected:
    void pushMessage(const Message &a);
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

    Socket& operator<<(const OMessage &a);
    Socket& operator>>(IMessage &a);

};

}

#endif // LIBQTCEREBELLUM_H
