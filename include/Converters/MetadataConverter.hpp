#pragma once

class IEnvironmentManager;
class Metadata;
class MetadataProto;
class QJsonObject;

class MetadataConverter
{
public:
    static Metadata fromJson(const QJsonObject& json);
    static QJsonObject toJson
    (
        const Metadata& metadata,
        const IEnvironmentManager& envManager
    );
    static Metadata fromProto(const MetadataProto& protoMetadata);

    MetadataConverter() = delete;
};