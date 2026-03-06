#include <QMap>
#include <QObject>
#include <QPointer>
#include <QString>
#include <QStringList>
#include <QWebSocket>

#include "Managers/WebSocketSessionManager.hpp"
#include "Dtos/FlightDataDto.hpp"

WebSocketSessionManager::WebSocketSessionManager(QObject* parent)
    : QObject(parent)
{}

QStringList WebSocketSessionManager::getActiveSessionIds() const
{
    return QStringList({});
}

int WebSocketSessionManager::getActiveSessionCount() const
{
    return 0;
}

QString WebSocketSessionManager::registerSession(QWebSocket* socket)
{
    return QString("");
}

void WebSocketSessionManager::removeSession(const QString& sessionId)
{}

void WebSocketSessionManager::broadcast(const FlightDataDto& payload)
{}

void WebSocketSessionManager::sendToClient
(
    const QString& sessionId, 
    const QString& msg
)
{}
