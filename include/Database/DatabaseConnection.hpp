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
    void execute(const std::string& query);
    ResultSet executeResult(const std::string& query);
private:
    sqlite3* _databaseConnection{nullptr};
};