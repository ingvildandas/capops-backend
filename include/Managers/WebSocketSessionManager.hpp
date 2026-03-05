#pragma once

#include <QObject>
#include <QWebSocket>
#include <QMap>

class QString;
class FlightDataDto;

class WebSocketSessionManager : public QObject
{
    Q_OBJECT

public:
    static WebSocketSessionManager& instance();

    WebSocketSessionManager(const WebSocketSessionManager&) = delete;
    WebSocketSessionManager& operator=(const WebSocketSessionManager&) = delete;

    void registerSession(/*session*/);
    void removeSession(/*session*/);
    void broadcast(FlightDataDto& payload);
    void sendToClient(const QString& sessionId, const QString& msg);
    void listActiveSessions();

private:
    explicit WebSocketSessionManager(QObject* parent = nullptr);
    QMap<QString, QWebSocket *> _activeSessions; 
};

