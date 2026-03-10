#pragma once

#include <QObject>
#include <QHttpServerRequest>
#include <QHttpServerResponse>

class QString;
class QWebSocket;
class WebSocketSessionManager;

class WebSocketController : public QObject
{
    Q_OBJECT

public:
    explicit WebSocketController(
        WebSocketSessionManager& sessionManager, 
        QObject* parent = nullptr
    );
    
    void handleNewConnection(QWebSocket* socket);

private:
    WebSocketSessionManager& _sessionManager;

private slots:
    void onDisconnected(QString sessionId);
    
};
