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

void WebSocketController::handleNewConnection(QWebSocket* socket) {}

void WebSocketController::onDisconnected() {}