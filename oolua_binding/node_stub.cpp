#include "types_stub.h"
#include "node_stub.h"

OOLUA_EXPORT_FUNCTIONS(OpcUa::Node)
OOLUA_EXPORT_FUNCTIONS_CONST(OpcUa::Node, GetId, GetBrowseName, GetParent, GetChildren_byId, GetChildren)

OOLUA_EXPORT_FUNCTIONS(vector_Node, push_back, pop_back)
OOLUA_EXPORT_FUNCTIONS_CONST(vector_Node, size)

