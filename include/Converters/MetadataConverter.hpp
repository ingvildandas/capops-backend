#pragma once

class Metadata;
class MetadataProto;
class QJsonObject;

class MetadataConverter
{
public:
    static QJsonObject toJson(const Metadata& metadata);
    static Metadata fromProto(const MetadataProto& protoMetadata);

    MetadataConverter() = delete;
};