local opcua = require 'opcua'

local client = opcua.Client.new(false)
client:Connect("opc.tcp://127.0.0.1:4840/freeopcua/server/")

local root = client:GetRootNode()
print("Root:", root, root.BrowseName)

for _,v in ipairs(root:GetChildren()) do
	print(v, v.BrowseName)

	v.Description = opcua.LocalizedText.new("AAA")
	print('Description', v.Description)
end


