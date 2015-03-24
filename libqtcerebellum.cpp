#include "libqtcerebellum.h"

#include <QDebug>

using namespace QCerebellum;

Socket::Socket(QObject *parent) :
    QObject(parent),
    context(1),
    socket(context, ZMQ_REQ)
{

}

Socket::Socket(const QString &s, QObject *parent) :
    QObject(parent),
    context(1),
    socket(context, ZMQ_REQ)
{
    connectToServer(s);
}

void Socket::connectToServer(const QString &s)
{
    server_addr = s;
    socket.connect(s.toStdString().c_str());
}

void Socket::closeConnection()
{
    socket.disconnect(server_addr.toStdString().c_str());
}

void Socket::pushMessage(const Message &a)
{
    /* Create 3 messages and send them one after another (with MORE flag) */
    socket.send((void *) a.getHeader().toStdString().c_str(), a.getHeader().length(), ZMQ_MORE);
    socket.send((void *) a.getName().toStdString().c_str(), a.getName().length(), ZMQ_MORE);
    socket.send((void *) a.getValue().constData(), a.getValue().length());
}

bool Socket::getReply()
{
    zmq::message_t m(16);
    socket.recv(&m);

    if (m.more()) {
        qWarning() << "Wrong OMessage reply stream: 1 part required, more given";
        return false;
    }

    if (MSG_OK == QByteArray((const char *) m.data(), m.size()))
        return true;
    else
        return false;
}

bool Socket::popIMessage(IMessage &a)
{
    /* Receive 3 messages one after another */
    zmq::message_t msg(256);
    socket.recv(&msg);

    if (!msg.more()) {
        //throw BadReplyException;
        qWarning() << "Wrong IMessage stream: 2 parts required, 1 given";
        return false;
    }

    a.setName(QByteArray((const char *) msg.data(), msg.size()));

    socket.recv(&msg);

    if (msg.more()) {
        // throw BadReplyException;
        qWarning() << "Wrong IMessage stream: 2 parts required, more given";
        return false;
    }

    a.setValue(QByteArray((const char *) msg.data(), msg.size()));

    return true;
}

bool Socket::send(const OMessage &a)
{
    pushMessage(a);
    return getReply();
}

bool Socket::recv(IMessage &a)
{
    a.setValue(QByteArray());
    pushMessage(a);
    return popIMessage(a);
}

Socket& Socket::operator<<(const OMessage &a)
{
    send(a);
    return *this;
}

Socket& Socket::operator>>(IMessage &a)
{
    recv(a);
    return *this;
}
