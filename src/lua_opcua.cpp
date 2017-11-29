#define SOL_CHECK_ARGUMENTS 1
#include <sol/sol.hpp>

#include <opc/common/logger.h>
#include <opc/common/exception.h>
#include <opc/ua/node.h>
#include <opc/ua/event.h>
#include <opc/ua/client/client.h>
#include <opc/ua/server/server.h>

#include "opcua_enums.h"
#include "messageid_enums.h"
#include "objectid_enums.h"
#include "status_code_enums.h"
#include "attribute_id_enums.h"

using namespace OpcUa;

namespace lua_opcua {
	struct test {
		int value;
		test() = default;
		test(int val) : value(val) {}
	};
	sol::table open_opcua(sol::this_state L) {
		sol::state_view lua(L);
		sol::table module = lua.create_table();

		module.new_usertype<test>("test",
			sol::constructors<test(), test(int)>(),
			"value", &test::value
		);

		module.new_enum("VariantType",
			"NUL", VariantType::NUL,
			"BOOLEAN", VariantType::BOOLEAN,
			"SBYTE", VariantType::SBYTE,
			"BYTE", VariantType::BYTE,
			"INT16", VariantType::INT16,
			"UINT16", VariantType::UINT16,
			"INT32", VariantType::INT32,
			"UINT32", VariantType::UINT32,
			"INT64", VariantType::INT64,
			"UINT64", VariantType::UINT64,
			"FLOAT", VariantType::FLOAT,
			"DOUBLE", VariantType::DOUBLE,
			"STRING", VariantType::STRING,
			"DATE_TIME", VariantType::DATE_TIME,
			"GUID", VariantType::GUId,
			"BYTE_STRING", VariantType::BYTE_STRING,
			"NODE_ID", VariantType::NODE_Id,
			"EXPANDED_NODE_ID", VariantType::EXPANDED_NODE_Id,
			"STATUS_CODE", VariantType::STATUS_CODE,
			"QUALIFIED_NAME", VariantType::QUALIFIED_NAME,
			"LOCALIZED_TEXT", VariantType::LOCALIZED_TEXT,
			"EXTENSION_OBJECT", VariantType::EXTENSION_OBJECT,
			"DATA_VALUE", VariantType::DATA_VALUE,
			"VARIANT", VariantType::VARIANT,
			"DIAGNOSTIC_INFO", VariantType::DIAGNOSTIC_INFO
		);

		REG_ENUM_MessageId()
		REG_ENUM_ReferenceId()
		REG_ENUM_ObjectId()
		REG_ENUM_ExpandedObjectId()

		module.new_usertype<Variant>("Variant",
			sol::constructors< Variant(), Variant(bool), Variant(int), Variant(long), Variant(double), Variant(const char*), Variant(MessageId), Variant(ReferenceId), Variant(ObjectId), Variant(ExpandedObjectId) >(),
			"Dimensions", &Variant::Dimensions,
			"IsArray", &Variant::IsArray,
			"IsScalar", &Variant::IsScalar,
			"IsNul", &Variant::IsNul,
			"Value", &Variant::ToString,
			"Type", &Variant::Type,
			sol::meta_function::to_string, [](Variant& var) { return var.ToString(); }
		);

		module.new_enum("NodeIdEncoding",
			"EV_TWO_BYTE", NodeIdEncoding::EV_TWO_BYTE,
			"EV_FOUR_BYTE", NodeIdEncoding::EV_FOUR_BYTE,
			"EV_NUMERIC", NodeIdEncoding::EV_NUMERIC,
			"EV_STRING", NodeIdEncoding::EV_STRING,
			"EV_GUID", NodeIdEncoding::EV_GUId,
			"EV_BYTE_STRING", NodeIdEncoding::EV_BYTE_STRING,
			"EV_SERVER_INDEX_FLAG", NodeIdEncoding::EV_Server_INDEX_FLAG,
			"EV_NAMESPACE_URI_FLAG", NodeIdEncoding::EV_NAMESPACE_URI_FLAG,
			"EV_VALUE_MASK", NodeIdEncoding::EV_VALUE_MASK
		);
		module.new_usertype<NodeId>("NodeId",
			sol::constructors< NodeId(), NodeId(ExpandedNodeId), NodeId(MessageId), NodeId(ReferenceId), NodeId(ObjectId), NodeId(ExpandedObjectId), NodeId(uint32_t, uint16_t), NodeId(std::string, uint16_t) >(),
			"Encoding", &NodeId::Encoding,
			"NamespaceURI", &NodeId::NamespaceURI,
			"ServerIndex", &NodeId::ServerIndex,
			"IsNull", &NodeId::IsNull,
			"HasNullIdentifier", &NodeId::HasNullIdentifier,
			"HasNamespaceURI", &NodeId::HasNamespaceURI,
			"HasServerIndex", &NodeId::HasServerIndex,
			"SetNamepaceURI", &NodeId::SetNamespaceURI,
			"SetServerIndex", &NodeId::SetServerIndex,
			"SetNamespaceIndex", &NodeId::SetNamespaceIndex,
			"IsInteger", &NodeId::IsInteger,
			"IsString", &NodeId::IsString,
			"IsBinary", &NodeId::IsBinary,
			"IsGuid", &NodeId::IsGuid,
			"GetNamespaceIndex", &NodeId::GetNamespaceIndex,
			"GetIntegerIdentifier", &NodeId::GetIntegerIdentifier,
			"GetStringIdentifier", &NodeId::GetStringIdentifier,
			"GetBinaryIdentifier", &NodeId::GetBinaryIdentifier,
			"GetGuidIdentifier", &NodeId::GetGuidIdentifier,
			sol::meta_function::to_string, [](NodeId& id) { 
				std::stringstream ss;
				ss << "Encoding: " << id.Encoding << " NamespaceURI: " << id.NamespaceURI << " ServerIndex: " << id.ServerIndex;
				return ss.str();
			}
		);
		module.new_usertype<ExpandedNodeId>("ExpandedNodeId",
			sol::constructors< ExpandedNodeId(), ExpandedNodeId(NodeId), ExpandedNodeId(MessageId), ExpandedNodeId(ReferenceId), ExpandedNodeId(ObjectId), ExpandedNodeId(ExpandedObjectId), ExpandedNodeId(uint32_t, uint16_t), ExpandedNodeId(std::string, uint16_t) >(),
			sol::base_classes, sol::bases<NodeId>()
		);

		module.new_usertype<QualifiedName>("QualifiedName",
			sol::constructors< QualifiedName(), QualifiedName(uint16_t, const std::string&), QualifiedName(const std::string&, uint16_t) >(),
			"NamespaceIndex", &QualifiedName::NamespaceIndex,
			"Name", &QualifiedName::Name
		);

		REG_ENUM_StatusCode()

		module.new_usertype<DateTime>("DateTime",
			sol::constructors< DateTime(), DateTime(int64_t) >(),
			"Value", &DateTime::Value,
			"Current", &DateTime::Current,
			"FromTimeT", &DateTime::FromTimeT,
			"ToTimeT", &DateTime::ToTimeT
		);

		module.new_usertype<DataValue>("DataValue",
			sol::constructors< DataValue(), DataValue(const Variant&), DataValue(long), DataValue(double), DataValue(std::string), DataValue(const char*) >(),
			"Encoding", &DataValue::Encoding,
			"Value", &DataValue::Value,
			"Status", &DataValue::Status,
			"SourceTimestamp", &DataValue::SourceTimestamp,
			"SourcePicoseconds", &DataValue::SourcePicoseconds,
			"ServerTimestamp", &DataValue::ServerTimestamp,
			"ServerPicoseconds", &DataValue::ServerPicoseconds,
			"SetSourceTimestamp", &DataValue::SetSourceTimestamp,
			"SetServerTimestamp", &DataValue::SetServerTimestamp
		);

		REG_ENUM_AttributeId()

		module.new_enum("VariableAccessLevel",
			"CurrentRead", VariableAccessLevel::CurrentRead,
			"CurrentWrite", VariableAccessLevel::CurrentWrite,
			"HistoryRead", VariableAccessLevel::HistoryRead,
			"HistoryWrite", VariableAccessLevel::HistoryWrite,
			"SemanticChange", VariableAccessLevel::SemanticChange
		);
		module.new_usertype<LocalizedText>("LocalizedText",
			sol::constructors< LocalizedText(), LocalizedText(const std::string&), LocalizedText(const char*), LocalizedText(const std::string&, const std::string&), LocalizedText(const char*, const char*) >(),
			"Encoding", &LocalizedText::Encoding,
			"Locale", &LocalizedText::Locale,
			"Text", &LocalizedText::Text
		);
		module.new_enum("NodeClass",
			"Unspecified", NodeClass::Unspecified,
			"Object", NodeClass::Object,
			"Variable", NodeClass::Variable,
			"Method", NodeClass::Method,
			"ObjectType", NodeClass::ObjectType,
			"VariableType", NodeClass::VariableType,
			"ReferenceType", NodeClass::ReferenceType,
			"DataType", NodeClass::DataType,
			"View", NodeClass::View
		);

		REG_ENUM_AttributeWriteMask()

		module.new_usertype<Node>("Node",
			sol::constructors< Node(), Node(Services::SharedPtr), Node(Services::SharedPtr, NodeId) >(),
			"Id", sol::property(&Node::GetId),
			//"GetId", &Node::GetId, //Reach max binding methods count, so disable this
			"BrowseName", sol::property(&Node::GetBrowseName),
			"GetBrowseName", &Node::GetBrowseName,
			"Parent", sol::property(&Node::GetParent),
			//"GetParent", &Node::GetParent, //Reach max binding methods count, so disable this
			"GetChildren", sol::overload(
				static_cast<std::vector<Node> (Node::*)(const OpcUa::ReferenceId&) const >(&Node::GetChildren), 
				static_cast<std::vector<Node> (Node::*)() const >(&Node::GetChildren)
			),
			"GetChild", sol::overload(
				static_cast<Node (Node::*)(const std::vector<OpcUa::QualifiedName>&) const >(&Node::GetChild),
				static_cast<Node (Node::*)(const std::vector<std::string> &) const >(&Node::GetChild),
				static_cast<Node (Node::*)(const std::string &) const >(&Node::GetChild)
			),
			"GetProperties", &Node::GetProperties,
			"GetVariables", &Node::GetVariables,
			"IsValid", &Node::IsValid,

			"GetAttribute", &Node::GetAttribute,
			"SetAttribute", &Node::SetAttribute,

			"AccessLevel", sol::property(&Node::GetAccessLevel, &Node::SetAccessLevel),
			"Description", sol::property(&Node::GetDescription, &Node::SetDescription),
			"NodeClass", sol::property(&Node::GetNodeClass, &Node::SetNodeClass),
			"UserAccessLevel", sol::property(&Node::GetUserAccessLevel, &Node::SetUserAccessLevel),
			"UserWriteMask", sol::property(&Node::GetUserWriteMask, &Node::SetUserWriteMask),
			"WriteMask", sol::property(&Node::GetWriteMask, &Node::SetWriteMask),

			//"Value", sol::property(sol::overload(&Node::GetValue, &Node::GetDataValue), sol::overload(static_cast<void (Node::*)(const Variant&) const >(&Node::SetValue), static_cast<void (Node::*)(const DataValue&) const >(&Node::SetValue)))
			"Value", sol::property(&Node::GetValue, static_cast<void (Node::*)(const Variant&) const >(&Node::SetValue)),
			"DataValue", sol::property(&Node::GetDataValue, static_cast<void (Node::*)(const DataValue&) const >(&Node::SetValue)),

			"DataType", sol::property(&Node::GetDataType),

			"CallMethod", &Node::CallMethod,
			"CallMethods", &Node::CallMethods,

			"AddFolder", sol::overload(
				static_cast<Node (Node::*)(const NodeId&, const QualifiedName&) const >(&Node::AddFolder),
				static_cast<Node (Node::*)(const std::string&, const std::string&) const >(&Node::AddFolder),
				static_cast<Node (Node::*)(uint32_t, const std::string&) const >(&Node::AddFolder)
			),
			"AddObject", sol::overload(
				static_cast<Node (Node::*)(const NodeId&, const QualifiedName&) const >(&Node::AddObject),
				static_cast<Node (Node::*)(const std::string&, const std::string&) const >(&Node::AddObject),
				static_cast<Node (Node::*)(uint32_t, const std::string&) const >(&Node::AddObject)
			),
			"AddVariable", sol::overload(
				static_cast<Node (Node::*)(const NodeId&, const QualifiedName&, const Variant&) const >(&Node::AddVariable),
				static_cast<Node (Node::*)(const std::string&, const std::string&, const Variant&) const >(&Node::AddVariable),
				static_cast<Node (Node::*)(uint32_t, const std::string&, const Variant&) const >(&Node::AddVariable)
			),
			"AddProperty", sol::overload(
				static_cast<Node (Node::*)(const NodeId&, const QualifiedName&, const Variant&) const >(&Node::AddProperty),
				static_cast<Node (Node::*)(const std::string&, const std::string&, const Variant&) const >(&Node::AddProperty),
				static_cast<Node (Node::*)(uint32_t, const std::string&, const Variant&) const >(&Node::AddProperty)
			),

			/*
			"AddMethod", sol::overload(
				static_cast<Node (Node::*)(const NodeId&, const QualifiedName&, std::function<std::vector<Variant>(NodeId, std::vector<Variant>)> ) const >(&Node::AddMethod),
				static_cast<Node (Node::*)(const std::string&, const std::string&, std::function<std::vector<Variant>(NodeId, std::vector<Variant>)>) const >(&Node::AddMethod),
				static_cast<Node (Node::*)(uint32_t, const std::string&, std::function<std::vector<Variant>(NodeId, std::vector<Variant>)>) const >(&Node::AddMethod)
			),
			*/

			"Server", sol::property(&Node::GetServices),

			sol::meta_function::to_string, [](Node& obj) { return obj.ToString(); }
		);

		module.new_usertype<Event>("Event",
			sol::constructors< Event(), Event(const Node&), Event(const NodeId&) >(),
			"Id", &Event::EventId,
			"Type", &Event::EventType,
			"LocalTime", &Event::LocalTime,
			"ReceiveTime", &Event::ReceiveTime,
			"Time", &Event::Time,
			"Message", &Event::Message,
			"Severity", &Event::Severity,
			"SourceNode", &Event::SourceNode,
			"SourceName", &Event::SourceName,
			"SetValue", sol::overload(
				static_cast<void (Event::*)(const std::vector<QualifiedName> &, Variant) >(&Event::SetValue), 
				static_cast<void (Event::*)(AttributeId, Variant) >(&Event::SetValue),
				static_cast<void (Event::*)(const QualifiedName&, Variant) >(&Event::SetValue),
				static_cast<void (Event::*)(const std::string&, Variant) >(&Event::SetValue)
			),
			"GetValue", sol::overload(
				static_cast<Variant (Event::*)(const std::vector<QualifiedName>&) const>(&Event::GetValue), 
				static_cast<Variant (Event::*)(AttributeId) const>(&Event::GetValue),
				static_cast<Variant (Event::*)(const QualifiedName&) const>(&Event::GetValue),
				static_cast<Variant (Event::*)(const std::string&) const>(&Event::GetValue)
			),
			"GetValueKeys", &Event::GetValueKeys
		);
		module.new_usertype<UaClient>("Client",
			sol::constructors< UaClient(bool), UaClient(std::shared_ptr<spdlog::logger>) >(),
			"SessionName", sol::property(&UaClient::GetSessionName, &UaClient::SetSessionName),
			"Connect", sol::overload(
				static_cast<void (UaClient::*)(const std::string &) >(&UaClient::Connect),
				static_cast<void (UaClient::*)(const EndpointDescription&) >(&UaClient::Connect)
			),
			"Disconnect", &UaClient::Disconnect,
			"Abort", &UaClient::Abort,
			"GetServerEndpoints", sol::overload(
				static_cast<std::vector<EndpointDescription> (UaClient::*)(const std::string&) >(&UaClient::GetServerEndpoints),
				static_cast<std::vector<EndpointDescription> (UaClient::*)() >(&UaClient::GetServerEndpoints)
			),
			"SelectEndpoint", &UaClient::SelectEndpoint,
			"GetEndpoint", &UaClient::GetEndpoint,
			"ApplicationURI", sol::property(&UaClient::GetApplicationURI, &UaClient::SetApplicationURI),
			"ProductURI", sol::property(&UaClient::GetProductURI, &UaClient::SetProductURI),
			"SecurityPolicy", sol::property(&UaClient::GetSecurityPolicy, &UaClient::SetSecurityPolicy),
			"GetServerNamespaces", &UaClient::GetServerNamespaces,
			"GetNamespaceIndex", &UaClient::GetNamespaceIndex,
			"GetNode", sol::overload(
				static_cast<Node (UaClient::*)(const NodeId&) const>(&UaClient::GetNode),
				static_cast<Node (UaClient::*)(const std::string&) const>(&UaClient::GetNode)
			),
			"GetRootNode", &UaClient::GetRootNode,
			"GetObjectsNode", &UaClient::GetObjectsNode,
			"GetServerNode", &UaClient::GetServerNode,
			"DeleteNodes", &UaClient::DeleteNodes,
			"CreateSubscription", &UaClient::CreateSubscription,
			"CreateServerOperations", &UaClient::CreateServerOperations
		);
		module.new_usertype<UaServer>("Server",
			sol::constructors< UaServer(), UaServer(bool), UaServer(const Common::Logger::SharedPtr &) >(),
			"SetEndpoint", &UaServer::SetEndpoint,
			"SetProductURI", &UaServer::SetProductURI,
			"SetServerURI", &UaServer::SetServerURI,
			"SetServerName", &UaServer::SetServerName,
			"AddAddressSpace", &UaServer::AddAddressSpace,
			"EnableEventNotification", &UaServer::EnableEventNotification,
			"RegisterNamespace", &UaServer::RegisterNamespace,
			"GetNamespaceIndex", &UaServer::GetNamespaceIndex,
			"Start", &UaServer::Start,
			"Stop", &UaServer::Stop,
			"GetNode", sol::overload(
				static_cast<Node (UaServer::*)(const NodeId &) const>(&UaServer::GetNode),
				static_cast<Node (UaServer::*)(const std::string &) const>(&UaServer::GetNode)
			),
			"GetRootNode", &UaServer::GetRootNode,
			"GetObjectsNode", &UaServer::GetObjectsNode,
			"GetServerNode", &UaServer::GetServerNode,
			"GetNodeFromPath", sol::overload(
				static_cast<Node (UaServer::*)(const std::vector<QualifiedName> &) const>(&UaServer::GetNodeFromPath),
				static_cast<Node (UaServer::*)(const std::vector<std::string> &) const>(&UaServer::GetNodeFromPath)
			),
			"TriggerEvent", &UaServer::TriggerEvent,
			"CreateSubscription", &UaServer::CreateSubscription,
			"CreateServerOperations", &UaServer::CreateServerOperations
		);

		return module;
	}
}

extern "C" int luaopen_opcua(lua_State *L) {
	return sol::stack::call_lua(L, 1, lua_opcua::open_opcua);
}
