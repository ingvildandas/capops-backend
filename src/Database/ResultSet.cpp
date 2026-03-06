#include <sqlite3.h>
#include <string>
#include <stdexcept>

#include "Database/ResultSet.hpp"

ResultSet::ResultSet(sqlite3_stmt* stmt) : _stmt(stmt), _hasRow(false)
{
    if (!_stmt)
    {
        throw std::invalid_argument("ResultSet received null statement");
    }
}

ResultSet::~ResultSet()
{
    if (_stmt) { sqlite3_finalize(_stmt); }
}

ResultSet::ResultSet(ResultSet&& other) noexcept
    : _stmt(other._stmt), _hasRow(other._hasRow)
{
    other._stmt = nullptr;
}

ResultSet& ResultSet::operator=(ResultSet&& other) noexcept
{
    if (this != &other)
    {
        if (_stmt) { sqlite3_finalize(_stmt); }

        _stmt = other._stmt;
        _hasRow = other._hasRow;
        other._stmt = nullptr;
    }
    return *this;
}

bool ResultSet::next()
{
    int rc = sqlite3_step(_stmt);
    _hasRow = (rc == SQLITE_ROW);
    return _hasRow;
}

int ResultSet::getInt(int column) const
{
    if (!_hasRow)
    {
        throw std::logic_error("No current row");
    }

    return sqlite3_column_int(_stmt, column);
}

std::string ResultSet::getString(int column) const
{
    if (!_hasRow)
    {
        throw std::logic_error("No current row");
    }

    const unsigned char* text = sqlite3_column_text(_stmt, column);
    return text ? reinterpret_cast<const char*>(text) : "";
}

bool ResultSet::isNull(int column) const
{
    return sqlite3_column_type(_stmt, column) == SQLITE_NULL;
}

int ResultSet::columnCount() const
{
    return sqlite3_column_count(_stmt);
}

std::string ResultSet::columnName(int column) const
{
    return sqlite3_column_name(_stmt, column);
}