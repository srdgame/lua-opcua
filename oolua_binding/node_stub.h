#pragma once

#include <opc/ua/node.h>

#include "oolua.h"


OOLUA_PROXY(OpcUa::Node)
	OOLUA_TAGS(
        No_default_constructor
		, Equal_op
		)
	OOLUA_MFUNC_CONST(GetId)
	OOLUA_MFUNC_CONST(GetBrowseName)
	OOLUA_MFUNC_CONST(GetParent)
	OOLUA_MEM_FUNC_CONST_RENAME(GetChildren_byId, vector_Node, GetChildren, const OpcUa::ReferenceId&)
	OOLUA_MEM_FUNC_CONST_RENAME(GetChildren, vector_Node, GetChildren)
OOLUA_PROXY_END

OOLUA_PROXY(vector_Node)
	OOLUA_MEM_FUNC(void, push_back, class_::const_reference)
	OOLUA_MFUNC(pop_back)
	OOLUA_MFUNC_CONST(size)
OOLUA_PROXY_END

