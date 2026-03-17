#pragma once

#include <QObject>
#include <QPointer>
#include <QHash>
#include <QStringList>

class FlightData;
class QString;
class QWebSocket;

class WebSocketSessionManager : public QObject
{
    Q_OBJECT

public:
    explicit WebSocketSessionManager(QObject* parent = nullptr);

    QString getSessionId(QWebSocket* socket) const;
    QStringList getActiveSessionIds() const;
    int getActiveSessionCount() const;

    QString registerSession(QWebSocket* socket);
    void removeSession(const QString& sessionId);

    void broadcast(const FlightData& dto);
    void sendToClient(const QString& sessionId, const QString& msg);
    
private:
    QHash<QString, QPointer<QWebSocket>> _activeSessions; 
};

