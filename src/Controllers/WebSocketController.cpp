#include <QObject>
#include <QWebSocket>

#include "Controllers/WebSocketController.hpp"
#include "Managers/WebSocketSessionManager.hpp"

WebSocketController::WebSocketController
(
        WebSocketSessionManager& sessionManager, 
        QObject* parent
)
    : _sessionManager(sessionManager), QObject(parent)
{}

void WebSocketController::handleNewConnection(QWebSocket* socket)
{
    QString sessionId = _sessionManager.registerSession(socket);

    connect
    (
        socket, 
        &QWebSocket::disconnected, 
        this, 
        &WebSocketController::onDisconnected
    );
}

void WebSocketController::onDisconnected()
{
    auto socket = qobject_cast<QWebSocket*>(sender());
    if (!socket) return;

    //_sessionManager.removeSession(socket);
}