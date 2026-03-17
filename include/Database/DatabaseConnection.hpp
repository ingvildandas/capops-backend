#pragma once

#include <string>
#include <sqlite3.h>

#include "ResultSet.hpp"

class DatabaseConnection
{
public:
    explicit DatabaseConnection(const std::string& filename);
    ~DatabaseConnection();

    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;

    DatabaseConnection(DatabaseConnection&&) noexcept;
    DatabaseConnection& operator=(DatabaseConnection&&) noexcept;

    sqlite3* getHandle();
    sqlite3_stmt* prepareStatement(const std::string& query);

    void bindText(sqlite3_stmt* stmt, int index, const std::string& value);
    void bindInt(sqlite3_stmt* stmt, int index, int value);
    void bindBool(sqlite3_stmt* stmt, int index, bool value);
    
    void finalizeStatement(sqlite3_stmt* stmt);
    ResultSet finalizeStatementWithResult(sqlite3_stmt* stmt);
private:
    sqlite3* _handle{nullptr};
};