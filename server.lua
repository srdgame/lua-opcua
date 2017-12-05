local opcua = require 'opcua'

local server = opcua.Server.new(true)
server:SetEndpoint("opc.tcp://127.0.0.1:4840/freeopcua/server/")
server:SetServerURI("urn:://exampleserver.freeopcua.github.io")
server:Start()

--print(server:GetNamespaceIndex("http://examples.freeopcua.github.io"))
local idx = server:RegisterNamespace("http://examples.freeopcua.github.io")
print(idx)
print(server:GetNamespaceIndex("http://examples.freeopcua.github.io"))
idx = server:RegisterNamespace("http://examples.freeopcua.github.io")
print(idx)
local objects = server:GetObjectsNode()
local nid = opcua.NodeId.new(99, idx)
local qn = opcua.QualifiedName.new("NewObject", idx)

local newobject = objects:AddObject(nid, qn)

local myvar = newobject:AddVariable(idx, "MyVariable", opcua.Variant.new(8))
local myprop = newobject:AddVariable(idx, "MyProperty", opcua.Variant.new(8.8))
--[[
local mymethod = newobject:AddMethod(idx, "MyMethod", function(context, arguments)
	print("MyMethod called!")
	return {opcua.Variant.new(0)}
end)
]]--

local root = server:GetRootNode()
print("Root node is", root)
print("Children are:")
for _, v in ipairs(root:GetChildren()) do
	print("\t", v)
end

local counter = 0
myvar.Value = opcua.Variant.new(counter)

server:EnableEventNotification()

local ev = opcua.Event.new(opcua.NodeId.new(opcua.ObjectId.BaseEventType))
ev.Severity = 2
ev.SourceNode = opcua.NodeId.new(opcua.ObjectId.Server)
ev.SourceName = "Event from FreeOpcUA"
ev.Time = opcua.DateTime.Current()

print("Ctrl-C to exit")

while true do
	counter = counter + 1
	--myvar.Value = opcua.Variant.new(counter)
	local val = opcua.DataValue.new(counter)
	val:SetSourceTimestamp(opcua.DateTime.Current()) --FromTimeT(timestamp)
	val:SetServerTimestamp(opcua.DateTime.Current()) --FromTimeT(timestamp)
	myvar.DataValue = val

	local msg = "This is event number: "..counter
	ev.Message = opcua.LocalizedText.new(msg)
	server:TriggerEvent(ev)
	os.execute("sleep 1")
	--os.execute("sleep 5")
end

server:Stop()
