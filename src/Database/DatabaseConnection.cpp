#include <stdexcept>

#include "Database/DatabaseConnection.hpp"

DatabaseConnection::DatabaseConnection(const std::string& filename)
{
    if (sqlite3_open_v2(filename.c_str(), &_handle, SQLITE_OPEN_READWRITE, NULL) != SQLITE_OK)
    {
        std::string errorMessage = std::string("Cannot open database connection: ")
            + sqlite3_errmsg(_handle);
        throw std::runtime_error(errorMessage);
    }
}

DatabaseConnection::~DatabaseConnection()
{
    if (_handle)
    {
        sqlite3_close(_handle);
    }
}

sqlite3* DatabaseConnection::getHandle()
{
    return _handle;
}

sqlite3_stmt* DatabaseConnection::prepareStatement(const std::string& query)
{
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(_handle, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::string errorMessage = std::string("Cannot prepare statement: ") 
            + sqlite3_errmsg( _handle);
        throw std::runtime_error(errorMessage);
    }

    return stmt;
}

void DatabaseConnection::bindText(sqlite3_stmt* stmt, int index, const std::string& value)
{
    if (sqlite3_bind_text(stmt, index, value.c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK)
    {
        throw std::runtime_error("Cannot bind text parameter");
    }
}

void DatabaseConnection::bindInt(sqlite3_stmt* stmt, int index, int value)
{
    if (sqlite3_bind_int(stmt, index, value) != SQLITE_OK)
    {
        throw std::runtime_error("Cannot bind int parameter");
    }
}

void DatabaseConnection::bindBool(sqlite3_stmt* stmt, int index, bool value)
{
    if (sqlite3_bind_int(stmt, index, value ? 1 : 0) != SQLITE_OK)
    {
        throw std::runtime_error("Cannot bind bool parameter");
    }
}

void DatabaseConnection::finalizeStatement(sqlite3_stmt* stmt)
{
    if (sqlite3_finalize(stmt) != SQLITE_OK)
    {
        std::string errorMessage = std::string("Cannot finalize statement: ") 
            + sqlite3_errmsg(_handle);
        throw std::runtime_error(errorMessage);
    }
}

ResultSet DatabaseConnection::finalizeStatementWithResult(sqlite3_stmt* stmt)
{
    if (sqlite3_finalize(stmt) != SQLITE_OK)
    {
        std::string errorMessage = std::string("Cannot finalize statement: ") 
            + sqlite3_errmsg(_handle);
        throw std::runtime_error(errorMessage);
    }

    return ResultSet(stmt);
}