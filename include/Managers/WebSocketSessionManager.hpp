#pragma once

#include <QObject>
#include <QPointer>
#include <QMap>

class QString;
class QStringList;
class QWebSocket;
class FlightDataDto;

class WebSocketSessionManager : public QObject
{
    Q_OBJECT

public:
    explicit WebSocketSessionManager(QObject* parent = nullptr);

    QStringList getActiveSessionIds() const;
    int getActiveSessionCount() const;

    QString registerSession(QWebSocket* socket);
    void removeSession(const QString& sessionId);

    void broadcast(const FlightDataDto& payload);
    void sendToClient(const QString& sessionId, const QString& msg);
    
private:
    QMap<QString, QPointer<QWebSocket>> _activeSessions; 
};

