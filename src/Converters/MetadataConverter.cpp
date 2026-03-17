#include <QDateTime>
#include <QJsonObject>

#include "Converters/MetadataConverter.hpp"
#include "Managers/EnvironmentManager.hpp"
#include "Models/Metadata.hpp"
#include "Proto/FlightData.hpp"

Metadata MetadataConverter::fromJson(const QJsonObject& json)
{
    QDateTime timestamp = QDateTime::fromString(json["timestamp"].toString());

    return Metadata(timestamp);
}

QJsonObject MetadataConverter::toJson
(
    const Metadata& metadata,
    const EnvironmentManager& envManager
)
{
    return 
    {
        { "version", envManager.getRestJsonContractVersion() },
        { "timestamp", metadata.getTimestamp().toString() }
    };
}
Metadata MetadataConverter::fromProto(const MetadataProto& protoMetadata)
{
    // QDateTime timestamp = QDateTime::fromString(protoMetadata.timestamp());
    QDateTime timestamp = QDateTime::fromString("2026-01-01T00:00:00.001Z");
    return Metadata(timestamp);
}