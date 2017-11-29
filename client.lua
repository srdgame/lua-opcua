local opcua = require 'opcua'

local function test_variant(var)
	print('Print Value: ', var, var:Value())
	print('Type: ', var:Type(), var:IsArray(), var:IsScalar(), var:IsNul())
	print('Calculate', (tonumber(var:Value()) or 0) + 1)
end

local function main()
	print('test', opcua.test.new(11).value)
	print('BOOLEAN enum', opcua.VariantType.BOOLEAN)

	test_variant( opcua.Variant.new(11))
	test_variant( opcua.Variant.new("11"))
	test_variant( opcua.Variant.new(0.2))
	test_variant( opcua.Variant.new("0.2"))
	test_variant( opcua.Variant.new(false))

	print('DateTime Current', opcua.DateTime.Current())
	node = opcua.Node.new()
	print(node)
	print(node.Id)
	print(pcall(node.GetBrowseName, node))
	print(node.Parent)

	print(node.AccessLevel)
	node.AccessLevel = 15

end

local client = opcua.Client.new(true)
client:Connect("opc.tcp://127.0.0.1:4840/freeopcua/server/")

local root = client:GetRootNode()
print("Root:", root, root.BrowseName)

for _,v in ipairs(root:GetChildren()) do
	print(v, v.BrowseName)
end

main()
