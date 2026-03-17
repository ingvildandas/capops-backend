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
    RiskEventId INTEGER PRIMARY KEY,
    SectorId INTEGER NOT NULL,
    Acknowledged INTEGER NOT NULL CHECK (Acknowledged IN (0,1)),
    RiskSeverity TEXT NOT NULL,
    CreatedTimestamp TEXT NOT NULL,
    AcknowledgedTimestamp TEXT,
    Message TEXT
);

CREATE INDEX IF NOT EXISTS idx_riskevent_sector
ON RiskEvent (SectorId);

CREATE INDEX IF NOT EXISTS idx_riskevent_created
ON RiskEvent (CreatedTimestamp);