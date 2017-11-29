#pragma once 
#include "enum_macros.h"

#define REG_ENUM_OpenFileMode() \
	REG_ENUM(OpenFileMode) \
		ENUM(OpenFileMode, Read) \
		ENUM(OpenFileMode, Write) \
		ENUM(OpenFileMode, EraseExisiting) \
	ENUM_END(OpenFileMode, Append)

#define REG_ENUM_NodeClass() \
	REG_ENUM(NodeClass) \
		ENUM(NodeClass, Unspecified) \
		ENUM(NodeClass, Object) \
		ENUM(NodeClass, Variable) \
		ENUM(NodeClass, Method) \
		ENUM(NodeClass, ObjectType) \
		ENUM(NodeClass, VariableType) \
		ENUM(NodeClass, ReferenceType) \
		ENUM(NodeClass, DataType) \
	ENUM_END(NodeClass, View)

#define REG_ENUM_ApplicationType() \
	REG_ENUM(ApplicationType) \
		ENUM(ApplicationType, Server) \
		ENUM(ApplicationType, Client) \
		ENUM(ApplicationType, ClientAndServer) \
	ENUM_END(ApplicationType, DiscoveryServer)

#define REG_ENUM_MessageSecurityMode() \
	REG_ENUM(MessageSecurityMode) \
		ENUM(MessageSecurityMode, Invalid) \
		ENUM(MessageSecurityMode, None) \
		ENUM(MessageSecurityMode, Sign) \
	ENUM_END(MessageSecurityMode, SignAndEncrypt)

#define REG_ENUM_UserTokenType() \
	REG_ENUM(UserTokenType) \
		ENUM(UserTokenType, Anonymous) \
		ENUM(UserTokenType, UserName) \
		ENUM(UserTokenType, Certificate) \
	ENUM_END(UserTokenType, IssuedToken)

#define REG_ENUM_SecurityTokenRequestType() \
	REG_ENUM(SecurityTokenRequestType) \
		ENUM(SecurityTokenRequestType, Issue) \
	ENUM_END(SecurityTokenRequestType, Renew)

#define REG_ENUM_NodeAttributesMask() \
	REG_ENUM(NodeAttributesMask) \
		ENUM(NodeAttributesMask, None) \
		ENUM(NodeAttributesMask, AccessLevel) \
		ENUM(NodeAttributesMask, ArrayDimensions) \
		ENUM(NodeAttributesMask, BrowseName) \
		ENUM(NodeAttributesMask, ContainsNoLoops) \
		ENUM(NodeAttributesMask, DataType) \
		ENUM(NodeAttributesMask, Description) \
		ENUM(NodeAttributesMask, DisplayName) \
		ENUM(NodeAttributesMask, EventNotifier) \
		ENUM(NodeAttributesMask, Executable) \
		ENUM(NodeAttributesMask, Historizing) \
		ENUM(NodeAttributesMask, InverseName) \
		ENUM(NodeAttributesMask, IsAbstract) \
		ENUM(NodeAttributesMask, MinimumSamplingInterval) \
		ENUM(NodeAttributesMask, NodeClass) \
		ENUM(NodeAttributesMask, NodeId) \
		ENUM(NodeAttributesMask, Symmetric) \
		ENUM(NodeAttributesMask, UserAccessLevel) \
		ENUM(NodeAttributesMask, UserExecutable) \
		ENUM(NodeAttributesMask, UserWriteMask) \
		ENUM(NodeAttributesMask, ValueRank) \
		ENUM(NodeAttributesMask, WriteMask) \
		ENUM(NodeAttributesMask, Value) \
		ENUM(NodeAttributesMask, All) \
		ENUM(NodeAttributesMask, BaseNode) \
		ENUM(NodeAttributesMask, Object) \
		ENUM(NodeAttributesMask, ObjectTypeOrDataType) \
		ENUM(NodeAttributesMask, Variable) \
		ENUM(NodeAttributesMask, VariableType) \
		ENUM(NodeAttributesMask, Method) \
		ENUM(NodeAttributesMask, ReferenceType) \
	ENUM_END(NodeAttributesMask, View)

#define REG_ENUM_AttributeWriteMask() \
	REG_ENUM(AttributeWriteMask) \
		ENUM(AttributeWriteMask, None) \
		ENUM(AttributeWriteMask, AccessLevel) \
		ENUM(AttributeWriteMask, ArrayDimensions) \
		ENUM(AttributeWriteMask, BrowseName) \
		ENUM(AttributeWriteMask, ContainsNoLoops) \
		ENUM(AttributeWriteMask, DataType) \
		ENUM(AttributeWriteMask, Description) \
		ENUM(AttributeWriteMask, DisplayName) \
		ENUM(AttributeWriteMask, EventNotifier) \
		ENUM(AttributeWriteMask, Executable) \
		ENUM(AttributeWriteMask, Historizing) \
		ENUM(AttributeWriteMask, InverseName) \
		ENUM(AttributeWriteMask, IsAbstract) \
		ENUM(AttributeWriteMask, MinimumSamplingInterval) \
		ENUM(AttributeWriteMask, NodeClass) \
		ENUM(AttributeWriteMask, NodeId) \
		ENUM(AttributeWriteMask, Symmetric) \
		ENUM(AttributeWriteMask, UserAccessLevel) \
		ENUM(AttributeWriteMask, UserExecutable) \
		ENUM(AttributeWriteMask, UserWriteMask) \
		ENUM(AttributeWriteMask, ValueRank) \
		ENUM(AttributeWriteMask, WriteMask) \
	ENUM_END(AttributeWriteMask, ValueForVariableType)

#define REG_ENUM_BrowseDirection() \
	REG_ENUM(BrowseDirection) \
		ENUM(BrowseDirection, Forward) \
		ENUM(BrowseDirection, Inverse) \
	ENUM_END(BrowseDirection, Both)

#define REG_ENUM_BrowseResultMask() \
	REG_ENUM(BrowseResultMask) \
		ENUM(BrowseResultMask, None) \
		ENUM(BrowseResultMask, ReferenceTypeId) \
		ENUM(BrowseResultMask, IsForward) \
		ENUM(BrowseResultMask, NodeClass) \
		ENUM(BrowseResultMask, BrowseName) \
		ENUM(BrowseResultMask, DisplayName) \
		ENUM(BrowseResultMask, TypeDefinition) \
		ENUM(BrowseResultMask, All) \
		ENUM(BrowseResultMask, ReferenceTypeInfo) \
	ENUM_END(BrowseResultMask, TargetInfo)

#define REG_ENUM_ComplianceLevel() \
	REG_ENUM(ComplianceLevel) \
		ENUM(ComplianceLevel, Untested) \
		ENUM(ComplianceLevel, Partial) \
		ENUM(ComplianceLevel, SelfTested) \
	ENUM_END(ComplianceLevel, Certified)

#define REG_ENUM_FilterOperator() \
	REG_ENUM(FilterOperator) \
		ENUM(FilterOperator, Equals) \
		ENUM(FilterOperator, IsNull) \
		ENUM(FilterOperator, GreaterThan) \
		ENUM(FilterOperator, LessThan) \
		ENUM(FilterOperator, GreaterThanOrEqual) \
		ENUM(FilterOperator, LessThanOrEqual) \
		ENUM(FilterOperator, Like) \
		ENUM(FilterOperator, Not) \
		ENUM(FilterOperator, Between) \
		ENUM(FilterOperator, InList) \
		ENUM(FilterOperator, And) \
		ENUM(FilterOperator, Or) \
		ENUM(FilterOperator, Cast) \
		ENUM(FilterOperator, InView) \
		ENUM(FilterOperator, OfType) \
		ENUM(FilterOperator, RelatedTo) \
		ENUM(FilterOperator, BitwiseAnd) \
	ENUM_END(FilterOperator, BitwiseOr)

#define REG_ENUM_TimestampsToReturn() \
	REG_ENUM(TimestampsToReturn) \
		ENUM(TimestampsToReturn, Source) \
		ENUM(TimestampsToReturn, Server) \
		ENUM(TimestampsToReturn, Both) \
	ENUM_END(TimestampsToReturn, Neither)

#define REG_ENUM_HistoryUpdateType() \
	REG_ENUM(HistoryUpdateType) \
		ENUM(HistoryUpdateType, Insert) \
		ENUM(HistoryUpdateType, Replace) \
		ENUM(HistoryUpdateType, Update) \
	ENUM_END(HistoryUpdateType, Delete)


#define REG_ENUM_PerformUpdateType() \
	REG_ENUM(PerformUpdateType) \
		ENUM(PerformUpdateType, Insert) \
		ENUM(PerformUpdateType, Replace) \
		ENUM(PerformUpdateType, Update) \
	ENUM_END(PerformUpdateType, Remove)


#define REG_ENUM_MonitoringMode() \
	REG_ENUM(MonitoringMode) \
		ENUM(MonitoringMode, Disabled) \
		ENUM(MonitoringMode, Sampling) \
	ENUM_END(MonitoringMode, Reporting)


#define REG_ENUM_DataChangeTrigger() \
	REG_ENUM(DataChangeTrigger) \
		ENUM(DataChangeTrigger, Status) \
		ENUM(DataChangeTrigger, StatusValue) \
	ENUM_END(DataChangeTrigger, StatusValueTimestamp)


#define REG_ENUM_DeadbandType() \
	REG_ENUM(DeadbandType) \
		ENUM(DeadbandType, None) \
		ENUM(DeadbandType, Absolute) \
	ENUM_END(DeadbandType, Percent)

#define REG_ENUM_EnumeratedTestType() \
	REG_ENUM(EnumeratedTestType) \
		ENUM(EnumeratedTestType, Red) \
		ENUM(EnumeratedTestType, Yellow) \
	ENUM_END(EnumeratedTestType, Green)

#define REG_ENUM_RedundancySupport() \
	REG_ENUM(RedundancySupport) \
		ENUM(RedundancySupport, None) \
		ENUM(RedundancySupport, Cold) \
		ENUM(RedundancySupport, Warm) \
		ENUM(RedundancySupport, Hot) \
		ENUM(RedundancySupport, Transparent) \
	ENUM_END(RedundancySupport, HotAndMirrored)

#define REG_ENUM_ServerState() \
	REG_ENUM(ServerState) \
		ENUM(ServerState, Running) \
		ENUM(ServerState, Failed) \
		ENUM(ServerState, NoConfiguration) \
		ENUM(ServerState, Suspended) \
		ENUM(ServerState, Shutdown) \
		ENUM(ServerState, Test) \
		ENUM(ServerState, CommunicationFault) \
	ENUM_END(ServerState, Unknown)

#define REG_ENUM_ModelChangeStructureVerbMask() \
	REG_ENUM(ModelChangeStructureVerbMask) \
		ENUM(ModelChangeStructureVerbMask, NodeAdded) \
		ENUM(ModelChangeStructureVerbMask, NodeDeleted) \
		ENUM(ModelChangeStructureVerbMask, ReferenceAdded) \
		ENUM(ModelChangeStructureVerbMask, ReferenceDeleted) \
	ENUM_END(ModelChangeStructureVerbMask, DataTypeChanged)

#define REG_ENUM_AxisScaleEnumeration() \
	REG_ENUM(AxisScaleEnumeration) \
		ENUM(AxisScaleEnumeration, Linear) \
		ENUM(AxisScaleEnumeration, Log) \
	ENUM_END(AxisScaleEnumeration, Ln)

#define REG_ENUM_ExceptionDeviationFormat() \
	REG_ENUM(ExceptionDeviationFormat) \
		ENUM(ExceptionDeviationFormat, AbsoluteValue) \
		ENUM(ExceptionDeviationFormat, PercentOfRange) \
		ENUM(ExceptionDeviationFormat, PercentOfValue) \
		ENUM(ExceptionDeviationFormat, PercentOfEURange) \
	ENUM_END(ExceptionDeviationFormat, Unknown)

