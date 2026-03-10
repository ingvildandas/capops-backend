#include "WebSocketServer.hpp"

#include <QDebug>
#include <QHostAddress>
#include <QWebSocket>

#include "../Controllers/WebSocketController.hpp"

WebSocketServer::WebSocketServer(
    quint16 port,
    WebSocketController& controller,
    QObject* parent
)
    : QObject(parent), _port(port), _controller(controller),
        _server("CaoOps WebSocket Server", QWebSocketServer::NonSecureMode)
{}

bool WebSocketServer::start()
{
    if (!_server.listen(QHostAddress::Any, _port))
    {
        qCritical() << "WebSocket server failed to start";
        return false;
    }

    connect(
        &_server,
        &QWebSocketServer::newConnection,
        this,
        &WebSocketServer::onNewConnection
    );

    qDebug() << "WebSocket server listening on port" << _port;

    return true;
}

void WebSocketServer::onNewConnection()
{
    auto socket = _server.nextPendingConnection();
    _controller.handleNewConnection(socket);
}