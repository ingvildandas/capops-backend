#pragma once

#include <QObject>
#include <QWebSocketServer>

class WebSocketController;

class WebSocketServer : public QObject
{
    Q_OBJECT

public:
    WebSocketServer
    (
        quint16 port, 
        QObject* parent = nullptr
    );

    quint16 getPort() const;

    void start();
    void registerWebSocketController(WebSocketController& webSocketController);

private:
    quint16 _port;
    QWebSocketServer _server;

    WebSocketController* _webSocketController;
    
private slots:
    void onNewConnection();
};