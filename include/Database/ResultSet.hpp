#pragma once

#include <sqlite3.h>
#include <string>

class ResultSet
{
public:
    explicit ResultSet(sqlite3_stmt* stmt);
    ~ResultSet();

    // Prevent making copies of objects
    ResultSet(const ResultSet&) = delete;
    ResultSet& operator=(const ResultSet&) = delete;
    
    // Promise the move constructor and assignment operator to never throw any exceptions
    ResultSet(ResultSet&& other) noexcept;
    ResultSet& operator=(ResultSet&& other) noexcept;

    bool next();

    int getInt(int column) const;
    std::string getString(int column) const;
    bool isNull(int column) const;

    int columnCount() const;
    std::string columnName(int column) const;
private:
    sqlite3_stmt* _stmt;
    bool _hasRow;
};