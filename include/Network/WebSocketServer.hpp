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
        WebSocketController& controller, 
        QObject* parent = nullptr
    );

    bool start();

private:
    quint16 _port;
    WebSocketController& _controller;

    QWebSocketServer m_server;

private slots:
    void onNewConnection();
};