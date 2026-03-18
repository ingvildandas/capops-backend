#pragma once

class EnvironmentManager;
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
        const EnvironmentManager& envManager
    );
    static Metadata fromProto(const MetadataProto& protoMetadata);

    MetadataConverter() = delete;
};