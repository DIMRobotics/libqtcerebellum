#include <QCerebellum/qtcerebellum.h>

#include <QDebug>

using namespace QCerebellum;

Socket::Socket(QObject *parent) :
    QObject(parent),
    context(1),
    socket(context, ZMQ_REQ),
    srv_online(false),
    brd_online(false)
{
}

Socket::Socket(const QString &s, QObject *parent) :
    QObject(parent),
    context(1),
    socket(context, ZMQ_REQ)
{
    connectToServer(s);
}

Socket::~Socket()
{
    closeConnection();
    socket.close();
}

void Socket::connectToServer(const QString &s)
{
    server_addr = s;
    socket.connect(s.toStdString().c_str());

    int timeout = 500;
    socket.setsockopt(ZMQ_SNDTIMEO, &timeout, sizeof(timeout));
    socket.setsockopt(ZMQ_RCVTIMEO, &timeout, sizeof(timeout));
}

void Socket::closeConnection()
{
    //socket.disconnect(server_addr.toStdString().c_str());
}

bool Socket::pushMessage(const QString &header, const Message &a)
{
    /* Create 3 messages and send them one after another (with MORE flag) */
    try {
        socket.send((void *) header.toStdString().c_str(), header.length(), ZMQ_SNDMORE);
        socket.send((void *) a.getName().toStdString().c_str(), a.getName().length(), ZMQ_SNDMORE);
        socket.send((void *) a.getValue().constData(), a.getValue().length());
    } catch (zmq::error_t &e) {
        srv_online = false;
        return false;
    }
    srv_online = true;
    return true;
}

bool Socket::getReply()
{
    qint64 more = 0;
    size_t more_size = sizeof(more);

    zmq::message_t m(16);
    if (!socket.recv(&m)) {
        srv_online = false;
        return false;
    }

    srv_online = true;
    socket.getsockopt(ZMQ_RCVMORE, &more, &more_size);

    if (more) {
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
    qint64 more = 0;
    size_t more_size = sizeof(more);

    qint32 timeout;
    size_t timeout_size = sizeof(timeout);

    /* Receive 3 messages one after another */
    zmq::message_t msg(256);
    try {
        socket.getsockopt(ZMQ_RCVTIMEO, &timeout, &timeout_size);
    } catch (...) {
        qDebug() << "Error getting sockopt: " << zmq_strerror(zmq_errno());
    }

    assert(timeout == 500);

    if (!socket.recv(&msg)) {
        srv_online = false;
        qDebug() << "Server is offline";
        return false;
    }

    srv_online = true;
    socket.getsockopt(ZMQ_RCVMORE, &more, &more_size);

    if (!more) {
        if (QByteArray((const char *) msg.data(), msg.size()) == "BAD") {
            qWarning() << "Server answered BAD";
            // throw RequestErrorException
            return false;
        }
        //throw BadReplyException;
        qWarning() << "Wrong IMessage stream: 2 parts required, 1 given";
        return false;
    }

    a.setName(QByteArray((const char *) msg.data(), msg.size()));


    if(!socket.recv(&msg)) {
        srv_online = false;
        return false;
    }

    srv_online = true;
    socket.getsockopt(ZMQ_RCVMORE, &more, &more_size);

    if (more) {
        // throw BadReplyException;
        qWarning() << "Wrong IMessage stream: 2 parts required, more given";
        return false;
    }

    a.setValue(QByteArray((const char *) msg.data(), msg.size()));

    return true;
}

bool Socket::send(const OMessage &a)
{
    pushMessage(HEADER_SET, a);
    return getReply();
}

bool Socket::recv(IMessage &a)
{
    a.setValue(QByteArray());
    pushMessage(HEADER_GET, a);
    return popIMessage(a);
}
