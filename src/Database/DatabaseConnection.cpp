#include <stdexcept>

#include "Database/DatabaseConnection.hpp"

DatabaseConnection::DatabaseConnection(const std::string& filename)
{
    if (sqlite3_open_v2(filename.c_str(), &_databaseConnection, SQLITE_OPEN_READWRITE, NULL) != SQLITE_OK)
    {
        std::string errorMessage = std::string("Cannot open database connection: ")
            + sqlite3_errmsg(_databaseConnection);
        throw std::runtime_error(errorMessage);
    }
}

DatabaseConnection::~DatabaseConnection()
{
    if (_databaseConnection)
    {
        sqlite3_close(_databaseConnection);
    }
}

sqlite3* DatabaseConnection::getHandle()
{
    return _databaseConnection;
}

void DatabaseConnection::execute(const std::string& query)
{
    char* errorMsg = nullptr;

    if (sqlite3_exec(_databaseConnection, query.c_str(), nullptr, nullptr, &errorMsg) != SQLITE_OK)
    {
        std::string error = errorMsg;
        sqlite3_free(errorMsg);
        throw std::runtime_error(error);
    }
}

ResultSet DatabaseConnection::executeResult(const std::string& query)
{
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(_databaseConnection, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::string errorMessage = std::string("Cannot prepare statement: ") 
            + sqlite3_errmsg( _databaseConnection);
        throw std::runtime_error(errorMessage);
    }

    return ResultSet(stmt);
}