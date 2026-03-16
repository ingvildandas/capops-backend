#include <QDebug>
#include <QHostAddress>
#include <QWebSocket>

#include "Network/WebSocketServer.hpp"
#include "Controllers/WebSocketController.hpp"
#include "Exceptions/WebSocketException.hpp"

WebSocketServer::WebSocketServer
(
    quint16 port,
    QObject* parent
)
    : QObject(parent), _port(port),
        _server("CaoOps WebSocket Server", QWebSocketServer::NonSecureMode)
{}

quint16 WebSocketServer::getPort() const
{
    return _port;
}

void WebSocketServer::start()
{
    if (!_server.listen(QHostAddress::Any, _port))
    {
        throw WebSocketException("Failed to start WebSocket server");
    }

    connect(
        &_server,
        &QWebSocketServer::newConnection,
        this,
        &WebSocketServer::onNewConnection
    );
}

void WebSocketServer::onNewConnection()
{
    if (!_webSocketController) return;

    auto socket = _server.nextPendingConnection();
    _webSocketController->handleNewConnection(socket);
}

void WebSocketServer::registerWebSocketController
(
    WebSocketController& webSocketController
)
{
    _webSocketController = &webSocketController;
}