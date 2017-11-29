#pragma once
#include "enum_macros.h"

#define REG_ENUM_AttributeId() \
	REG_ENUM(AttributeId) \
		ENUM(AttributeId, NodeId) \
		ENUM(AttributeId, NodeClass) \
		ENUM(AttributeId, BrowseName) \
		ENUM(AttributeId, DisplayName) \
		ENUM(AttributeId, Description) \
		ENUM(AttributeId, WriteMask) \
		ENUM(AttributeId, UserWriteMask) \
		ENUM(AttributeId, IsAbstract) \
		ENUM(AttributeId, Symmetric) \
		ENUM(AttributeId, InverseName) \
		ENUM(AttributeId, ContainsNoLoops) \
		ENUM(AttributeId, EventNotifier) \
		ENUM(AttributeId, Value) \
		ENUM(AttributeId, DataType) \
		ENUM(AttributeId, ValueRank) \
		ENUM(AttributeId, ArrayDimensions) \
		ENUM(AttributeId, AccessLevel) \
		ENUM(AttributeId, UserAccessLevel) \
		ENUM(AttributeId, MinimumSamplingInterval) \
		ENUM(AttributeId, Historizing) \
		ENUM(AttributeId, Executable) \
		ENUM(AttributeId, UserExecutable) \
	ENUM_END(AttributeId, Unknown)


