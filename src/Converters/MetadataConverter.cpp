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
        { "timestamp", metadata.getTimestamp().toString(Qt::ISODateWithMs) }
    };
}
Metadata MetadataConverter::fromProto(const MetadataProto& protoMetadata)
{
    QDateTime timestamp = 
        QDateTime::fromString
        (
            QString::fromStdString(protoMetadata.timestamp()), 
            Qt::ISODate
        );
    return Metadata(timestamp);
}