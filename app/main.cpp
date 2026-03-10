#include <QCoreApplication>
#include <QDebug>
#include <QHostAddress>
#include <QHttpServer>
#include <QObject>
#include <QTcpServer>
#include <QtGlobal>
#include <QWebSocketServer>

#include "Database/DatabaseConnection.hpp"
#include "Http/HttpRouter.hpp"
#include "Controllers/RiskEventController.hpp"
#include "Controllers/WebSocketController.hpp"
#include "Managers/FlightDataStateManager.hpp"
#include "Managers/WebSocketSessionManager.hpp"
#include "Repositories/RiskEventRepository.hpp"
#include "Services/RiskEventService.hpp"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    QHttpServer httpServer;

    auto conn = DatabaseConnection("capops.db");
    qDebug() << "Database connection successful";
    
    RiskEventRepository riskEventRepository(conn);
    FlightDataStateManager flightDataStateManager;
    RiskEventService riskEventService(riskEventRepository, flightDataStateManager);
    RiskEventController riskEventController(riskEventService);
    
    HttpRouter router(httpServer);
    router.registerRiskEventController(riskEventController);

    QTcpServer tcpServer;
    if (!tcpServer.listen(QHostAddress::Any, 8080))
    {
        qCritical() << "HTTP server failed to start";
        return -1;
    }

    httpServer.bind(&tcpServer);
    
    qDebug() << "HTTP server listening on port 8080";

    WebSocketSessionManager webSocketSessionManager;
    WebSocketController webSocketController(webSocketSessionManager);

    QWebSocketServer wsServer
    (
        "CaoOps WebScoket Server", 
        QWebSocketServer::NonSecureMode
    );
    if (!wsServer.listen(QHostAddress::Any, 8081))
    {
        qCritical() << "WebSocket server failed to start";
        return -1;
    }

    qDebug() << "Websocket server listening on port 8081";

    QObject::connect(
        &wsServer,
        &QWebSocketServer::newConnection,
        [&]() {
            QWebSocket* socket = wsServer.nextPendingConnection();
            webSocketController.handleNewConnection(socket);
        }
    );

    return app.exec();
}