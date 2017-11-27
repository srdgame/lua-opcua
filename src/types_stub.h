#include <opc/ua/event.h>

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
	)
OOLUA_PROXY_END

OOLUA_PROXY(OpcUa::NodeId)
OOLUA_PROXY_END

