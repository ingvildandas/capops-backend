-- =========================================================
-- CapOps SQLite Database Schema
-- Database file: capops.db
-- =========================================================

-- Enable foreign key enforcement
PRAGMA foreign_keys = ON;

-- =========================================================
-- Table: RiskEvent
-- =========================================================
CREATE TABLE IF NOT EXISTS RiskEvent (
    riskEventId INTEGER PRIMARY KEY,
    sectorId INTEGER NOT NULL,
    acknowledged INTEGER NOT NULL CHECK (acknowledged IN (0,1)),
    riskSeverity TEXT NOT NULL,
    createdTimestamp TEXT NOT NULL,
    acknowledgedTimestamp TEXT,
    message TEXT
);

CREATE INDEX IF NOT EXISTS idx_riskevent_sector
ON RiskEvent (sectorId);

CREATE INDEX IF NOT EXISTS idx_riskevent_created
ON RiskEvent (createdTimestamp);