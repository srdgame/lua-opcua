#pragma once

#include <opc/ua/event.h>
#include <opc/ua/node.h>

#include "oolua.h"

OOLUA_PROXY(OpcUa::MessageId)
	OOLUA_ENUMS(
			OOLUA_ENUM(INVALID)
			)
OOLUA_PROXY_END

OOLUA_PROXY(OpcUa::VariantType)
	OOLUA_ENUMS(
			OOLUA_ENUM(NUL)
			OOLUA_ENUM(BOOLEAN)
			OOLUA_ENUM(SBYTE)
			OOLUA_ENUM(BYTE)
			OOLUA_ENUM(INT16)
			OOLUA_ENUM(UINT16)
			OOLUA_ENUM(INT32)
			OOLUA_ENUM(UINT32)
			OOLUA_ENUM(INT64)
			OOLUA_ENUM(UINT64)
			OOLUA_ENUM(FLOAT)
			OOLUA_ENUM(DOUBLE)
			OOLUA_ENUM(STRING)
			OOLUA_ENUM(DATE_TIME)
			OOLUA_ENUM(GUId)
			OOLUA_ENUM(BYTE_STRING)
			OOLUA_ENUM(XML_ELEMENT)
			OOLUA_ENUM(NODE_Id)
			OOLUA_ENUM(EXPANDED_NODE_Id)
			OOLUA_ENUM(STATUS_CODE)
			OOLUA_ENUM(QUALIFIED_NAME)
			OOLUA_ENUM(LOCALIZED_TEXT)
			OOLUA_ENUM(EXTENSION_OBJECT)
			OOLUA_ENUM(DATA_VALUE)
			OOLUA_ENUM(VARIANT)
			OOLUA_ENUM(DIAGNOSTIC_INFO)
			)
OOLUA_PROXY_END


OOLUA_PROXY(OpcUa::Variant)
	OOLUA_CTORS(
			OOLUA_CTOR(bool)
			OOLUA_CTOR(long)
			OOLUA_CTOR(double)
			OOLUA_CTOR(std::string)
			OOLUA_CTOR(OpcUa::MessageId)
			OOLUA_CTOR(OpcUa::ReferenceId)
			OOLUA_CTOR(OpcUa::ObjectId)
			OOLUA_CTOR(OpcUa::ExpandedObjectId)
			OOLUA_CTOR(OpcUa::VariantType)
			)
	OOLUA_TAGS(
			Equal_op
			, Not_equal_op
			)
	
    OOLUA_MFUNC_CONST(IsArray)
    OOLUA_MFUNC_CONST(IsScalar)
    OOLUA_MFUNC_CONST(IsNul)
	OOLUA_MEM_FUNC_CONST_RENAME(AsBool, bool, As)
	OOLUA_MEM_FUNC_CONST_RENAME(AsInt, long, As)
	OOLUA_MEM_FUNC_CONST_RENAME(AsFloat, double, As)
	OOLUA_MEM_FUNC_CONST_RENAME(AsString, std::string, As)
	OOLUA_MFUNC_CONST(Type)
	OOLUA_MFUNC_CONST(ToString)
OOLUA_PROXY_END

OOLUA_PROXY(OpcUa::NodeIdEncoding)
	OOLUA_ENUMS(
			OOLUA_ENUM(EV_TWO_BYTE)
			OOLUA_ENUM(EV_FOUR_BYTE)
			OOLUA_ENUM(EV_NUMERIC)
			OOLUA_ENUM(EV_STRING)
			OOLUA_ENUM(EV_GUId)
			OOLUA_ENUM(EV_BYTE_STRING)
			OOLUA_ENUM(EV_Server_INDEX_FLAG)
			OOLUA_ENUM(EV_NAMESPACE_URI_FLAG)
			OOLUA_ENUM(EV_VALUE_MASK)
	)
OOLUA_PROXY_END

OOLUA_PROXY(OpcUa::Guid)
	OOLUA_TAGS(
		No_default_constructor
		, Equal_op
		, Less_op
		)
	OOLUA_MGET_MSET(Data1)
	OOLUA_MGET_MSET(Data2)
	OOLUA_MGET_MSET(Data3)
	/*
	 * OOLUA_MGET_MSET(Data4)
	 */
OOLUA_PROXY_END

OOLUA_PROXY(OpcUa::NodeId::TwoByteDataType)
	OOLUA_MGET_MSET(Identifier)
OOLUA_PROXY_END

OOLUA_PROXY(OpcUa::NodeId::FourByteDataType)
	OOLUA_MGET_MSET(NamespaceIndex)
	OOLUA_MGET_MSET(Identifier)
OOLUA_PROXY_END

OOLUA_PROXY(OpcUa::NodeId::NumericDataType)
	OOLUA_MGET_MSET(NamespaceIndex)
	OOLUA_MGET_MSET(Identifier)
OOLUA_PROXY_END

OOLUA_PROXY(OpcUa::NodeId::StringDataType)
	OOLUA_MGET_MSET(NamespaceIndex)
	OOLUA_MGET_MSET(Identifier)
OOLUA_PROXY_END

OOLUA_PROXY(OpcUa::NodeId::BinaryDataType)
	OOLUA_MGET_MSET(NamespaceIndex)
	OOLUA_MGET_MSET(Identifier)
OOLUA_PROXY_END

OOLUA_PROXY(OpcUa::NodeId::GuidDataType)
	OOLUA_MGET_MSET(NamespaceIndex)
	OOLUA_MGET_MSET(Identifier)
OOLUA_PROXY_END

typedef std::vector<uint8_t> vector_uint8;

OOLUA_PROXY(vector_uint8)
	OOLUA_MEM_FUNC(void, push_back, class_::const_reference)
	OOLUA_MFUNC(pop_back)
	OOLUA_MFUNC_CONST(size)
OOLUA_PROXY_END

OOLUA_PROXY(OpcUa::NodeId)
	OOLUA_CTORS(
		OOLUA_CTOR(OpcUa::MessageId)
		OOLUA_CTOR(OpcUa::ReferenceId)
		OOLUA_CTOR(OpcUa::ObjectId)
		OOLUA_CTOR(OpcUa::ExpandedObjectId)
		OOLUA_CTOR(uint32_t, uint16_t)
		OOLUA_CTOR(std::string, uint16_t)
	)
	OOLUA_TAGS(
			Equal_op
			, Less_op
			, Not_equal_op
			)
	OOLUA_MGET_MSET(Encoding)
	OOLUA_MGET_MSET(NamespaceURI)
	OOLUA_MGET_MSET(ServerIndex)

	OOLUA_MGET_MSET(TwoByteData)
	OOLUA_MGET_MSET(FourByteData)
	OOLUA_MGET_MSET(NumericData)
	OOLUA_MGET_MSET(StringData)
	OOLUA_MGET_MSET(BinaryData)
	OOLUA_MGET_MSET(GuidData)

	OOLUA_MFUNC_CONST(GetEncodingValue)
	OOLUA_MFUNC_CONST(IsNull)
	OOLUA_MFUNC_CONST(HasNullIdentifier)
	OOLUA_MFUNC_CONST(HasNamespaceURI)
	OOLUA_MFUNC_CONST(HasServerIndex)

	OOLUA_MFUNC(SetNamespaceURI)
	OOLUA_MFUNC(SetServerIndex)
	OOLUA_MFUNC(SetNamespaceIndex)

	OOLUA_MFUNC_CONST(IsInteger)
	OOLUA_MFUNC_CONST(IsString)
	OOLUA_MFUNC_CONST(IsBinary)
	OOLUA_MFUNC_CONST(IsGuid)

	OOLUA_MFUNC_CONST(GetNamespaceIndex)
	OOLUA_MFUNC_CONST(GetIntegerIdentifier)
	OOLUA_MFUNC_CONST(GetStringIdentifier)
	OOLUA_MFUNC_CONST(GetBinaryIdentifier)
	OOLUA_MFUNC_CONST(GetGuidIdentifier)
OOLUA_PROXY_END

OOLUA_PROXY(OpcUa::ByteString)
	OOLUA_MGET_MSET(Data)
	OOLUA_CTORS(
		OOLUA_CTOR(vector_uint8)
	)
	OOLUA_TAGS(
		Equal_op
	)
OOLUA_PROXY_END

OOLUA_PROXY(OpcUa::IntegerId)
	OOLUA_CTORS(
		OOLUA_CTOR(uint32_t)
	)
OOLUA_PROXY_END

OOLUA_PROXY(OpcUa::QualifiedName)
	OOLUA_CTORS(
		OOLUA_CTOR(uint16_t, const std::string&)
		OOLUA_CTOR(const std::string&, uint16_t)
		OOLUA_CTOR(const std::string&)
	)
	OOLUA_TAGS(
		Equal_op
		, Less_op
	)
	OOLUA_MGET_MSET(NamespaceIndex)
	OOLUA_MGET_MSET(Name)
OOLUA_PROXY_END

OOLUA_PROXY(OpcUa::RelativePathElement)
	OOLUA_MGET_MSET(ReferenceTypeId)
	OOLUA_MGET_MSET(IsInverse)
	OOLUA_MGET_MSET(IncludeSubtypes)
	OOLUA_MGET_MSET(TargetName)
OOLUA_PROXY_END

typedef std::vector<OpcUa::RelativePathElement> vector_RelativePathElement;

OOLUA_PROXY(vector_RelativePathElement)
	OOLUA_MEM_FUNC(void, push_back, class_::const_reference)
	OOLUA_MFUNC(pop_back)
	OOLUA_MFUNC_CONST(size)
OOLUA_PROXY_END

OOLUA_PROXY(OpcUa::RelativePath)
	OOLUA_MGET_MSET(Elements)
OOLUA_PROXY_END

OOLUA_PROXY(OpcUa::LocalizedText)
	OOLUA_CTORS(
		OOLUA_CTOR(const std::string&)
		OOLUA_CTOR(const char*)
		OOLUA_CTOR(const std::string&, const std::string&)
		OOLUA_CTOR(const char*, const char*)
	)
	OOLUA_TAGS(
		Equal_op
	)
	OOLUA_MGET_MSET(Encoding)
	OOLUA_MGET_MSET(Locale)
	OOLUA_MGET_MSET(Text)
OOLUA_PROXY_END
