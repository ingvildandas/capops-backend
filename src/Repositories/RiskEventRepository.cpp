#include <string>
#include <vector>

#include <QDateTime>
#include <QString>

#include "Repositories/RiskEventRepository.hpp"
#include "Database/DatabaseConnection.hpp"
#include "Database/ResultSet.hpp"
#include "Exceptions/DatabaseException.hpp"
#include "Models/RiskEvent.hpp"

RiskEventRepository::RiskEventRepository(DatabaseConnection& conn)
    : _conn(conn)
{}

RiskEvent RiskEventRepository::selectById(const int riskEventId)
{
    std::string query = std::string("")
        + "SELECT "
        + "     RiskEvent.RiskEventId,"
        + "     RiskEvent.SectorId,"
        + "     RiskEvent.Acknowledged,"
        + "     RiskEvent.RiskSeverity,"
        + "     RiskEvent.CreatedTimestamp,"
        + "     RiskEvent.AcknowledgedTimestamp,"
        + "     RiskEvent.Message"
        + "FROM RiskEvent "
        + "WHERE RiskEvent.RiskEventId = ?;";

    sqlite3_stmt* stmt = _conn.prepareStatement(query);
    _conn.bindInt(stmt, 1, riskEventId);
    ResultSet result = _conn.finalizeStatementWithResult(stmt);

    if (!result.next())
    {
        throw DatabaseException("RiskEvent instance not found in database");
    }
    if (result.getInt(0) != riskEventId)
    {
        throw DatabaseException("Retrieved RiskEventId does not match requested id");
    }

    int sectorId = result.getInt(1);
    bool acknowledged = result.getInt(2) != 0;
    QString riskSeverity = QString::fromStdString(result.getString(3));
    QDateTime createdTimestamp = 
        QDateTime::fromString(QString::fromStdString(result.getString(4)));
    QDateTime acknowledgedTimestamp = 
        QDateTime::fromString(QString::fromStdString(result.getString(5)));
    QString message = QString::fromStdString(result.getString(6));

    return RiskEvent
    (
        riskEventId, 
        sectorId, 
        acknowledged, 
        riskSeverity, 
        createdTimestamp, 
        acknowledgedTimestamp, 
        message
    );
}

std::vector<RiskEvent> RiskEventRepository::selectMultipleByCount
(
    const int count
)
{
    std::string query = std::string("")
        + "SELECT "
        + "     RiskEvent.RiskEventId,"
        + "     RiskEvent.SectorId,"
        + "     RiskEvent.Acknowledged,"
        + "     RiskEvent.RiskSeverity,"
        + "     RiskEvent.CreatedTimestamp,"
        + "     RiskEvent.AcknowledgedTimestamp,"
        + "     RiskEvent.Message"
        + "FROM RiskEvent "
        + "ORDER BY RiskEvent.CreatedTimestamp DESC "
        + "LIMIT ?;";
    
    sqlite3_stmt* stmt = _conn.prepareStatement(query);
    _conn.bindInt(stmt, 1, count);
    ResultSet result = _conn.finalizeStatementWithResult(stmt);

    std::vector<RiskEvent> riskEvents;
    while (result.next())
    {
        int riskEventId = result.getInt(0);
        int sectorId = result.getInt(1);
        bool acknowledged = result.getInt(2) != 0;
        QString riskSeverity = QString::fromStdString(result.getString(3));
        QDateTime createdTimestamp = 
            QDateTime::fromString(QString::fromStdString(result.getString(4)));
        QDateTime acknowledgedTimestamp = 
            QDateTime::fromString(QString::fromStdString(result.getString(5)));
        QString message = QString::fromStdString(result.getString(6));

        riskEvents.push_back(RiskEvent
        (
            riskEventId, 
            sectorId, 
            acknowledged, 
            riskSeverity, 
            createdTimestamp, 
            acknowledgedTimestamp, 
            message
        ));
    }
    return riskEvents;
}

std::vector<RiskEvent> RiskEventRepository::selectMultipleByAcknowledged
(
    const int count, 
    const bool acknowledged
)
{
    std::string query = std::string("")
        + "SELECT "
        + "     RiskEvent.RiskEventId,"
        + "     RiskEvent.SectorId,"
        + "     RiskEvent.Acknowledged,"
        + "     RiskEvent.RiskSeverity,"
        + "     RiskEvent.CreatedTimestamp,"
        + "     RiskEvent.AcknowledgedTimestamp,"
        + "     RiskEvent.Message"
        + "FROM RiskEvent "
        + "WHERE RiskEvent.Acknowledged = ? "
        + "ORDER BY RiskEvent.CreatedTimestamp DESC "
        + "LIMIT ?;";
    
    sqlite3_stmt* stmt = _conn.prepareStatement(query);
    _conn.bindBool(stmt, 1, acknowledged);
    _conn.bindInt(stmt, 2, count);
    ResultSet result = _conn.finalizeStatementWithResult(stmt);

    std::vector<RiskEvent> riskEvents;
    while (result.next())
    {
        int riskEventId = result.getInt(0);
        int sectorId = result.getInt(1);
        bool acknowledged = result.getInt(2) != 0;
        QString riskSeverity = QString::fromStdString(result.getString(3));
        QDateTime createdTimestamp = 
            QDateTime::fromString(QString::fromStdString(result.getString(4)));
        QDateTime acknowledgedTimestamp = 
            QDateTime::fromString(QString::fromStdString(result.getString(5)));
        QString message = QString::fromStdString(result.getString(6));

        riskEvents.push_back(RiskEvent
        (
            riskEventId, 
            sectorId, 
            acknowledged, 
            riskSeverity, 
            createdTimestamp, 
            acknowledgedTimestamp, 
            message
        ));
    }
    return riskEvents;
}

std::vector<RiskEvent> RiskEventRepository::selectMultipleByTimestamps
(
    const int count,
    const QDateTime& from,
    const QDateTime& to
)
{
    std::string query = std::string("")
        + "SELECT "
        + "     RiskEvent.RiskEventId,"
        + "     RiskEvent.SectorId,"
        + "     RiskEvent.Acknowledged,"
        + "     RiskEvent.RiskSeverity,"
        + "     RiskEvent.CreatedTimestamp,"
        + "     RiskEvent.AcknowledgedTimestamp,"
        + "     RiskEvent.Message"
        + "FROM RiskEvent "
        + "WHERE RiskEvent.CreatedTimestamp BETWEEN ? AND ? "
        + "ORDER BY RiskEvent.CreatedTimestamp DESC "
        + "LIMIT ?;";
    
    sqlite3_stmt* stmt = _conn.prepareStatement(query);
    _conn.bindText(stmt, 1, from.toString("yyyy-MM-dd HH:mm:ss.zzz").toStdString());
    _conn.bindText(stmt, 2, to.toString("yyyy-MM-dd HH:mm:ss.zzz").toStdString());
    _conn.bindInt(stmt, 3, count);
    ResultSet result = _conn.finalizeStatementWithResult(stmt);

    std::vector<RiskEvent> riskEvents;
    while (result.next())
    {
        int riskEventId = result.getInt(0);
        int sectorId = result.getInt(1);
        bool acknowledged = result.getInt(2) != 0;
        QString riskSeverity = QString::fromStdString(result.getString(3));
        QDateTime createdTimestamp = 
            QDateTime::fromString(QString::fromStdString(result.getString(4)));
        QDateTime acknowledgedTimestamp = 
            QDateTime::fromString(QString::fromStdString(result.getString(5)));
        QString message = QString::fromStdString(result.getString(6));

        riskEvents.push_back(RiskEvent
        (
            riskEventId, 
            sectorId, 
            acknowledged, 
            riskSeverity, 
            createdTimestamp, 
            acknowledgedTimestamp, 
            message
        ));
    }
    return riskEvents;
}

std::vector<RiskEvent> RiskEventRepository::selectMultipleByParameters
(
    const int count,
    const bool acknowledged,
    const QDateTime& from,
    const QDateTime& to
)
{
    std::string query = std::string("")
        + "SELECT "
        + "     RiskEvent.RiskEventId,"
        + "     RiskEvent.SectorId,"
        + "     RiskEvent.Acknowledged,"
        + "     RiskEvent.RiskSeverity,"
        + "     RiskEvent.CreatedTimestamp,"
        + "     RiskEvent.AcknowledgedTimestamp,"
        + "     RiskEvent.Message"
        + "FROM RiskEvent "
        + "WHERE RiskEvent.Acknowledged = ? "
        + "AND RiskEvent.CreatedTimestamp BETWEEN ? AND ? "
        + "ORDER BY RiskEvent.CreatedTimestamp DESC "
        + "LIMIT ?;";
    
    sqlite3_stmt* stmt = _conn.prepareStatement(query);
    _conn.bindBool(stmt, 1, acknowledged);
    _conn.bindText(stmt, 2, from.toString("yyyy-MM-dd HH:mm:ss.zzz").toStdString());
    _conn.bindText(stmt, 3, to.toString("yyyy-MM-dd HH:mm:ss.zzz").toStdString());
    _conn.bindInt(stmt, 4, count);
    ResultSet result = _conn.finalizeStatementWithResult(stmt);

    std::vector<RiskEvent> riskEvents;
    while (result.next())
    {
        int riskEventId = result.getInt(0);
        int sectorId = result.getInt(1);
        bool acknowledged = result.getInt(2) != 0;
        QString riskSeverity = QString::fromStdString(result.getString(3));
        QDateTime createdTimestamp = 
            QDateTime::fromString(QString::fromStdString(result.getString(4)));
        QDateTime acknowledgedTimestamp = 
            QDateTime::fromString(QString::fromStdString(result.getString(5)));
        QString message = QString::fromStdString(result.getString(6));

        riskEvents.push_back(RiskEvent
        (
            riskEventId, 
            sectorId, 
            acknowledged, 
            riskSeverity, 
            createdTimestamp, 
            acknowledgedTimestamp, 
            message
        ));
    }

    return riskEvents;
}

void RiskEventRepository::insert(const RiskEvent& riskEvent) 
{
    std::string query = std::string("")
        + "INSERT INTO RiskEvent ("
        + "     RiskEventId,"
        + "     SectorId,"
        + "     Acknowledged,"
        + "     RiskSeverity,"
        + "     CreatedTimestamp,"
        + "     AcknowledgedTimestamp,"
        + "     Message"
        + ") "
        + "VALUES (?, ?, ?, ?, ?, ?, ?);";
    
    sqlite3_stmt* stmt = _conn.prepareStatement(query);
    _conn.bindInt(stmt, 1, riskEvent.getRiskEventId());
    _conn.bindInt(stmt, 2, riskEvent.getSectorId());
    _conn.bindBool(stmt, 3, riskEvent.getAcknowledged());
    _conn.bindText(stmt, 4, riskEvent.getRiskSeverity().toStdString());
    _conn.bindText
    (
        stmt, 
        5, 
        riskEvent
            .getCreatedTimestamp()
            .toString("yyyy-MM-dd HH:mm:ss.zzz")
            .toStdString()
    );
    _conn.bindText
    (
        stmt, 
        6, 
        riskEvent
            .getAcknowledgedTimestamp()
            .toString("yyyy-MM-dd HH:mm:ss.zzz")
            .toStdString()
        );
    _conn.bindText(stmt, 7, riskEvent.getMessage().toStdString());

    _conn.finalizeStatement(stmt);
}

void RiskEventRepository::insertMultiple
(
    std::vector<RiskEvent>& riskEvents
) 
{
    std::string query = std::string("")
        + "INSERT INTO RiskEvent ("
        + "     RiskEventId,"
        + "     SectorId,"
        + "     Acknowledged,"
        + "     RiskSeverity,"
        + "     CreatedTimestamp,"
        + "     AcknowledgedTimestamp,"
        + "     Message"
        + ") "
        + "VALUES ";
    
    for (size_t i = 0; i < riskEvents.size(); ++i)
    {
        query += "(?, ?, ?, ?, ?, ?, ?)";
        if (i < riskEvents.size() - 1)
        {
            query += ", ";
        }
    }
    query += ";";
    sqlite3_stmt* stmt = _conn.prepareStatement(query);

    int paramIndex = 1;
    for (const RiskEvent& riskEvent : riskEvents)
    {
        _conn.bindInt(stmt, paramIndex++, riskEvent.getRiskEventId());
        _conn.bindInt(stmt, paramIndex++, riskEvent.getSectorId());
        _conn.bindBool(stmt, paramIndex++, riskEvent.getAcknowledged());
        _conn.bindText
        (
            stmt, 
            paramIndex++, 
            riskEvent.getRiskSeverity().toStdString()
        );
        _conn.bindText
        (
            stmt, 
            paramIndex++, 
            riskEvent
                .getCreatedTimestamp()
                .toString("yyyy-MM-dd HH:mm:ss.zzz")
                .toStdString()
        );
        _conn.bindText
        (
            stmt, 
            paramIndex++, 
            riskEvent
                .getAcknowledgedTimestamp()
                .toString("yyyy-MM-dd HH:mm:ss.zzz")
                .toStdString()
        );
        _conn.bindText
        (
            stmt, 
            paramIndex++, 
            riskEvent.getMessage().toStdString()
        );
    }
    _conn.finalizeStatement(stmt);
}

void RiskEventRepository::updateAcknowledged
(
    const int riskEventId, 
    const bool acknowledged
) 
{
    std::string query = std::string("")
        + "UPDATE RiskEvent "
        + "SET Acknowledged = ? "
        + "WHERE RiskEventId = ?;";
    
    sqlite3_stmt* stmt = _conn.prepareStatement(query);
    _conn.bindBool(stmt, 1, acknowledged);
    _conn.bindInt(stmt, 2, riskEventId);

    _conn.finalizeStatement(stmt);
}

void RiskEventRepository::deleteById(const int riskEventId) 
{
    std::string query = std::string("")
        + "DELETE FROM RiskEvent "
        + "WHERE RiskEventId = ?;";
    
    sqlite3_stmt* stmt = _conn.prepareStatement(query);
    _conn.bindInt(stmt, 1, riskEventId);

    _conn.finalizeStatement(stmt);
}

