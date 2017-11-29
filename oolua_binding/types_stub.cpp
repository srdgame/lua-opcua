#include "types_stub.h"

OOLUA_EXPORT_NO_FUNCTIONS(OpcUa::MessageId)
OOLUA_EXPORT_NO_FUNCTIONS(OpcUa::VariantType)

OOLUA_EXPORT_FUNCTIONS(OpcUa::Variant)
OOLUA_EXPORT_FUNCTIONS_CONST(OpcUa::Variant, IsArray, IsScalar, IsNul, AsBool, AsInt, AsFloat, AsString, Type, ToString)

OOLUA_EXPORT_NO_FUNCTIONS(OpcUa::Guid)

OOLUA_EXPORT_NO_FUNCTIONS(OpcUa::NodeId::TwoByteDataType)
OOLUA_EXPORT_NO_FUNCTIONS(OpcUa::NodeId::FourByteDataType)
OOLUA_EXPORT_NO_FUNCTIONS(OpcUa::NodeId::NumericDataType)
OOLUA_EXPORT_NO_FUNCTIONS(OpcUa::NodeId::StringDataType)
OOLUA_EXPORT_NO_FUNCTIONS(OpcUa::NodeId::BinaryDataType)
OOLUA_EXPORT_NO_FUNCTIONS(OpcUa::NodeId::GuidDataType)

OOLUA_EXPORT_FUNCTIONS(vector_uint8, push_back, pop_back)
OOLUA_EXPORT_FUNCTIONS_CONST(vector_uint8, size)

OOLUA_EXPORT_FUNCTIONS(OpcUa::NodeId, SetNamespaceURI, SetServerIndex, SetNamespaceIndex)
OOLUA_EXPORT_FUNCTIONS_CONST(OpcUa::NodeId, GetEncodingValue, IsNull, HasNullIdentifier, HasNamespaceURI, HasServerIndex, IsInteger, IsString, IsBinary, IsGuid, GetNamespaceIndex, GetIntegerIdentifier, GetStringIdentifier, GetBinaryIdentifier, GetGuidIdentifier)

OOLUA_EXPORT_NO_FUNCTIONS(OpcUa::ByteString)
OOLUA_EXPORT_NO_FUNCTIONS(OpcUa::IntegerId)
OOLUA_EXPORT_NO_FUNCTIONS(OpcUa::QualifiedName)

OOLUA_EXPORT_NO_FUNCTIONS(OpcUa::RelativePathElement)

OOLUA_EXPORT_FUNCTIONS(vector_RelativePathElement, push_back, pop_back)
OOLUA_EXPORT_FUNCTIONS_CONST(vector_RelativePathElement, size)

OOLUA_EXPORT_NO_FUNCTIONS(OpcUa::RelativePath)

OOLUA_EXPORT_NO_FUNCTIONS(OpcUa::LocalizedText)

