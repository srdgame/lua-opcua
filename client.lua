local opcua = require 'opcua'

local client = opcua.Client.new(false)
client:Connect("opc.tcp://127.0.0.1:4840/freeopcua/server/")

local root = client:GetRootNode()
print("Root:", root, root.BrowseName)

local objects = client:GetObjectsNode()
for _,v in ipairs(objects:GetChildren()) do
	print(v, v.BrowseName)
	for _,v in ipairs(v:GetChildren()) do
		print(v, v.BrowseName)
	end
end

local idx = client:GetNamespaceIndex("http://examples.freeopcua.github.io");
print(idx)
local var = objects:GetChild({idx..":NewObject", "MyVariable"})
print('MyVariable', var)
local var = objects:GetChild({idx..":NewObject"})
print('NewObject', var)
print('MyVariable', var:GetChild("MyVariable"))
client:DeleteNodes(var, true)

print('DONE')


