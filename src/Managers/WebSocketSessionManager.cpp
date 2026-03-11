#include <QByteArray>
#include <QHash>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QPointer>
#include <QString>
#include <QStringList>
#include <QUuid>
#include <QWebSocket>

#include "Converters/FlightDataDtoConverter.hpp"
#include "Dtos/FlightDataDto.hpp"
#include "Managers/WebSocketSessionManager.hpp"

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
    socket->setParent(this);
    QString sessionId = QUuid::createUuid().toString(QUuid::WithoutBraces);
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

void WebSocketSessionManager::broadcast(const FlightDataDto& dto)
{
    if (getActiveSessionCount() == 0) return;
    
    QJsonObject json = FlightDataDtoConverter::toJson(dto);
    QByteArray payload = QJsonDocument(json).toJson(QJsonDocument::Compact);

    for (auto [sessionId, socket] : _activeSessions.asKeyValueRange())
    {
        if (!socket) continue;
        if (socket->state() != QAbstractSocket::ConnectedState) continue;

        socket->sendBinaryMessage(payload);
    }
}

void WebSocketSessionManager::sendToClient
(
    const QString& sessionId, 
    const QString& msg
)
{
    QWebSocket* socket = _activeSessions.value(sessionId, nullptr);
    if (!socket) return;
    if (socket->state() != QAbstractSocket::ConnectedState) return;
    
    socket->sendBinaryMessage(msg.toUtf8());
}
