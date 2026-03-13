#include <QDateTime>
#include <QJsonObject>

#include "Converters/MetadataConverter.hpp"
#include "Models/Metadata.hpp"
#include "Proto/FlightData.hpp"

QJsonObject MetadataConverter::toJson(const Metadata& metadata)
{
    return 
    {
        { "version", Metadata::getVersion() },
        { "timestamp", metadata.getTimestamp().toString() }
    };
}
Metadata MetadataConverter::fromProto(const MetadataProto& protoMetadata)
{
    // QDateTime timestamp = QDateTime::fromString(protoMetadata.timestamp());
    QDateTime timestamp = QDateTime::fromString("2026-01-01T00:00:00.001Z");
    return Metadata(timestamp);
}