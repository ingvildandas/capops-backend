#include <QObject>
#include <QString>
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
        [this, sessionId](){ onDisconnected(sessionId); } 
    );
}

void WebSocketController::onDisconnected(const QString& sessionId)
{
    _sessionManager.removeSession(sessionId);
}