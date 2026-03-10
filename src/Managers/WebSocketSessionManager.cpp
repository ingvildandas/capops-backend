#include <QHash>
#include <QObject>
#include <QPointer>
#include <QString>
#include <QStringList>
#include <QUuid>
#include <QWebSocket>

#include "Managers/WebSocketSessionManager.hpp"
#include "Dtos/FlightDataDto.hpp"

WebSocketSessionManager::WebSocketSessionManager(QObject* parent)
    : QObject(parent)
{}

QString WebSocketSessionManager::getSessionId(QWebSocket* socket) const
{
    for (auto [sessionId, activeSocket] : _activeSessions.asKeyValueRange())
    {
        if (socket == qobject_cast<QWebSocket*>(activeSocket))
        {
            return sessionId;
        }
    }

    return QString("");
}

QStringList WebSocketSessionManager::getActiveSessionIds() const
{
    return QStringList(_activeSessions.keys());
}

int WebSocketSessionManager::getActiveSessionCount() const
{
    return _activeSessions.size();
}

QString WebSocketSessionManager::registerSession(QWebSocket* socket)
{
    QString sessionId = QUuid::createUuid().toString();
    _activeSessions.insert(sessionId, socket);
    return sessionId;
}

void WebSocketSessionManager::removeSession(const QString& sessionId)
{
    auto socket = _activeSessions.take(sessionId);
    if (socket) 
    {
        socket->close();
        socket->deleteLater();
    }
}

void WebSocketSessionManager::broadcast(const FlightDataDto& payload)
{}

void WebSocketSessionManager::sendToClient
(
    const QString& sessionId, 
    const QString& msg
)
{}
