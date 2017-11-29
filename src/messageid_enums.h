#pragma once 
#include "enum_macros.h"

#define REG_ENUM_MessageId() \
	REG_ENUM(MessageId) \
		ENUM(MessageId, INVALID) \
		ENUM(MessageId, ACTIVATE_SESSION_REQUEST) \
		ENUM(MessageId, ACTIVATE_SESSION_RESPONSE) \
		ENUM(MessageId, BROWSE_REQUEST) \
		ENUM(MessageId, BROWSE_RESPONSE) \
		ENUM(MessageId, BROWSE_NEXT_REQUEST) \
		ENUM(MessageId, BROWSE_NEXT_RESPONSE) \
		ENUM(MessageId, CLOSE_SECURE_CHANNEL_REQUEST) \
		ENUM(MessageId, CREATE_SESSION_REQUEST) \
		ENUM(MessageId, CREATE_SESSION_RESPONSE) \
		ENUM_RENAME(MessageId, FIND_SERVERS_REQUEST, FIND_ServerS_REQUEST) \
		ENUM_RENAME(MessageId, FIND_SERVERS_RESPONSE, FIND_ServerS_RESPONSE) \
		ENUM(MessageId, GET_ENDPOINTS_REQUEST) \
		ENUM(MessageId, GET_ENDPOINTS_RESPONSE) \
		ENUM(MessageId, OPEN_SECURE_CHANNEL_REQUEST) \
		ENUM(MessageId, OPEN_SECURE_CHANNEL_RESPONSE) \
		ENUM_RENAME(MessageId, TRANSLATE_BROWSE_PATHS_TO_NODE_IDS_REQUEST, TRANSLATE_BROWSE_PATHS_TO_NODE_IdS_REQUEST) \
		ENUM_RENAME(MessageId, TRANSLATE_BROWSE_PATHS_TO_NODE_IDS_RESPONSE, TRANSLATE_BROWSE_PATHS_TO_NODE_IdS_RESPONSE) \
		ENUM(MessageId, REGISTER_NODES_REQUEST) \
		ENUM(MessageId, REGISTER_NODES_RESPONSE) \
		ENUM(MessageId, UNREGISTER_NODES_REQUEST) \
		ENUM(MessageId, UNREGISTER_NODES_RESPONSE) \
		ENUM(MessageId, READ_REQUEST) \
		ENUM(MessageId, READ_RESPONSE) \
		ENUM(MessageId, WRITE_REQUEST) \
		ENUM(MessageId, WRITE_RESPONSE) \
		ENUM(MessageId, CALL_REQUEST) \
		ENUM(MessageId, CALL_RESPONSE) \
		ENUM(MessageId, CREATE_MONITORED_ITEMS_REQUEST) \
		ENUM(MessageId, CREATE_MONITORED_ITEMS_RESPONSE) \
		ENUM(MessageId, DELETE_MONITORED_ITEMS_REQUEST) \
		ENUM(MessageId, DELETE_MONITORED_ITEMS_RESPONSE) \
		ENUM(MessageId, CREATE_SUBSCRIPTION_REQUEST) \
		ENUM(MessageId, CREATE_SUBSCRIPTION_RESPONSE) \
		ENUM(MessageId, DELETE_SUBSCRIPTION_REQUEST) \
		ENUM(MessageId, DELETE_SUBSCRIPTION_RESPONSE) \
		ENUM(MessageId, MODIFY_SUBSCRIPTION_REQUEST) \
		ENUM(MessageId, MODIFY_SUBSCRIPTION_RESPONSE) \
		ENUM(MessageId, PUBLISH_REQUEST) \
		ENUM(MessageId, PUBLISH_RESPONSE) \
		ENUM(MessageId, REPUBLISH_REQUEST) \
		ENUM(MessageId, REPUBLISH_RESPONSE) \
		ENUM(MessageId, SET_PUBLISHING_MODE_REQUEST) \
		ENUM(MessageId, SET_PUBLISHING_MODE_RESPONSE) \
		ENUM(MessageId, ADD_NODES_REQUEST) \
		ENUM(MessageId, ADD_NODES_RESPONSE) \
		ENUM(MessageId, DELETE_NODES_REQUEST) \
		ENUM(MessageId, DELETE_NODES_RESPONSE) \
		ENUM(MessageId, ADD_REFERENCES_REQUEST) \
		ENUM(MessageId, ADD_REFERENCES_RESPONSE) \
		ENUM(MessageId, DELETE_REFERENCES_REQUEST) \
		ENUM(MessageId, DELETE_REFERENCES_RESPONSE) \
	ENUM_END(MessageId, SERVICE_FAULT)

#define REG_ENUM_ReferenceId() \
	REG_ENUM(ReferenceId) \
		ENUM(ReferenceId, References) \
		ENUM(ReferenceId, NonHierarchicalReferences) \
		ENUM(ReferenceId, HierarchicalReferences) \
		ENUM(ReferenceId, HasChild) \
		ENUM(ReferenceId, Organizes) \
		ENUM(ReferenceId, HasEventSource) \
		ENUM(ReferenceId, HasModellingRule) \
		ENUM(ReferenceId, HasEncoding) \
		ENUM(ReferenceId, HasDescription) \
		ENUM(ReferenceId, HasTypeDefinition) \
		ENUM(ReferenceId, GeneratesEvent) \
		ENUM(ReferenceId, Aggregates) \
		ENUM(ReferenceId, HasSubtype) \
		ENUM(ReferenceId, HasProperty) \
		ENUM(ReferenceId, HasComponent) \
		ENUM(ReferenceId, HasNotifier) \
		ENUM(ReferenceId, HasOrderedComponent) \
		ENUM(ReferenceId, HasModelParent) \
		ENUM(ReferenceId, FromState) \
		ENUM(ReferenceId, ToState) \
		ENUM(ReferenceId, HasCause) \
		ENUM(ReferenceId, HasEffect) \
		ENUM(ReferenceId, HasHistoricalConfiguration) \
		ENUM(ReferenceId, HasHistoricalEventConfiguration) \
		ENUM(ReferenceId, HasSubStateMachine) \
		ENUM(ReferenceId, HasEventHistory) \
		ENUM(ReferenceId, AlwaysGeneratesEvent) \
		ENUM(ReferenceId, HasTrueSubState) \
		ENUM(ReferenceId, HasFalseSubState) \
		ENUM(ReferenceId, HasCondition) \
	ENUM_END(ReferenceId, Unknown)

#define REG_ENUM_ExpandedObjectId() \
	REG_ENUM(ExpandedObjectId) \
		ENUM(ExpandedObjectId, Null) \
		ENUM(ExpandedObjectId, ObjectAttribute) \
		ENUM(ExpandedObjectId, VariableAttribute) \
		ENUM(ExpandedObjectId, MethodAttribute) \
		ENUM(ExpandedObjectId, ObjectTypeAttribute) \
		ENUM(ExpandedObjectId, VariableTypeAttribute) \
		ENUM(ExpandedObjectId, ReferenceTypeAttribute) \
		ENUM(ExpandedObjectId, DataTypeAttribute) \
		ENUM(ExpandedObjectId, ViewAttribute) \
		ENUM(ExpandedObjectId, DataChangeNotification) \
		ENUM(ExpandedObjectId, EventNotificationList) \
		ENUM(ExpandedObjectId, StatusChangeNotification) \
		ENUM(ExpandedObjectId, DataChangeFilter) \
		ENUM(ExpandedObjectId, EventFilter) \
		ENUM(ExpandedObjectId, AggregateFilter) \
		ENUM(ExpandedObjectId, ElementOperand) \
		ENUM(ExpandedObjectId, LiteralOperand) \
		ENUM(ExpandedObjectId, AttributeOperand) \
	ENUM_END(ExpandedObjectId, SimpleAttributeOperand)



