#include <test/tools/ossfuzz/protoToAbiV2.h>
#include <boost/range/algorithm_ext/erase.hpp>
#include <libsolidity/codegen/YulUtilFunctions.h>
#include <libdevcore/Whiskers.h>

using namespace dev::test::abiv2fuzzer;
using namespace std;
using namespace dev::solidity;

string ProtoConverter::createAlphaNum(string const& _strBytes) const
{
	string tmp{_strBytes};
	if (!tmp.empty())
	{
		boost::range::remove_erase_if(tmp, [=](char c) -> bool {
			return !(std::isalpha(c) || std::isdigit(c));
		});
		tmp = tmp.substr(0, 32);
	}
	return tmp;
}

void ProtoConverter::visit(SignedIntegerType const& _x)
{
	unsigned width = 8 * ((_x.width() % 32) + 1);
	std::string type = "int" + std::to_string(width);
	m_types.push_back(type);
	m_output << Whiskers(R"(
	<type> x_<index> = )")
	("type", type)
	("index", std::to_string(m_numGlobals++))
	.render();
	visit(_x.value(), width);
	m_output << ";\n";
}

void ProtoConverter::visit(UnsignedIntegerType const& _x)
{
	unsigned width = 8 * ((_x.width() % 32) + 1);
	std::string type = "uint" + std::to_string(width);
	m_types.push_back(type);
	m_output << Whiskers(R"(
	<type> x_<index> = )")
	("type", type)
	("index", std::to_string(m_numGlobals++))
	.render();
	visit(_x.value(), width);
	m_output << ";\n";
}

void ProtoConverter::visit(SignedIntegerValue const& _x, unsigned _width)
{
	s256 value = generateSigned(_x.value64(), _x.value128(), _x.value192(), _x.value256());
	switch (_width)
	{
	case 8:
		m_output << s8(value);
		break;
	case 16:
		m_output << s16(value);
		break;
	case 24:
		m_output << s24(value);
		break;
	case 32:
		m_output << s32(value);
		break;
	case 40:
		m_output << s40(value);
		break;
	case 48:
		m_output << s48(value);
		break;
	case 56:
		m_output << s56(value);
		break;
	case 64:
		m_output << s64(value);
		break;
	case 72:
		m_output << s72(value);
		break;
	case 80:
		m_output << s80(value);
		break;
	case 88:
		m_output << s88(value);
		break;
	case 96:
		m_output << s96(value);
		break;
	case 104:
		m_output << s104(value);
		break;
	case 112:
		m_output << s112(value);
		break;
	case 120:
		m_output << s120(value);
		break;
	case 128:
		m_output << s128(value);
		break;
	case 136:
		m_output << s136(value);
		break;
	case 144:
		m_output << s144(value);
		break;
	case 152:
		m_output << s152(value);
		break;
	case 160:
		m_output << s160(value);
		break;
	case 168:
		m_output << s168(value);
		break;
	case 176:
		m_output << s176(value);
		break;
	case 184:
		m_output << s184(value);
		break;
	case 192:
		m_output << s192(value);
		break;
	case 200:
		m_output << s200(value);
		break;
	case 208:
		m_output << s208(value);
		break;
	case 216:
		m_output << s216(value);
		break;
	case 224:
		m_output << s224(value);
		break;
	case 232:
		m_output << s232(value);
		break;
	case 240:
		m_output << s240(value);
		break;
	case 248:
		m_output << s248(value);
		break;
	case 256:
		m_output << s256(value);
		break;
	}
}

void ProtoConverter::visit(UnsignedIntegerValue const& _x, unsigned _width)
{
	u256 value = generateUnsigned(_x.value64(), _x.value128(), _x.value192(), _x.value256());
	switch (_width)
	{
	case 8:
		m_output << u8(value);
		break;
	case 16:
		m_output << u16(value);
		break;
	case 24:
		m_output << u24(value);
		break;
	case 32:
		m_output << u32(value);
		break;
	case 40:
		m_output << u40(value);
		break;
	case 48:
		m_output << u48(value);
		break;
	case 56:
		m_output << u56(value);
		break;
	case 64:
		m_output << u64(value);
		break;
	case 72:
		m_output << u72(value);
		break;
	case 80:
		m_output << u80(value);
		break;
	case 88:
		m_output << u88(value);
		break;
	case 96:
		m_output << u96(value);
		break;
	case 104:
		m_output << u104(value);
		break;
	case 112:
		m_output << u112(value);
		break;
	case 120:
		m_output << u120(value);
		break;
	case 128:
		m_output << u128(value);
		break;
	case 136:
		m_output << u136(value);
		break;
	case 144:
		m_output << u144(value);
		break;
	case 152:
		m_output << u152(value);
		break;
	case 160:
		m_output << u160(value);
		break;
	case 168:
		m_output << u168(value);
		break;
	case 176:
		m_output << u176(value);
		break;
	case 184:
		m_output << u184(value);
		break;
	case 192:
		m_output << u192(value);
		break;
	case 200:
		m_output << u200(value);
		break;
	case 208:
		m_output << u208(value);
		break;
	case 216:
		m_output << u216(value);
		break;
	case 224:
		m_output << u224(value);
		break;
	case 232:
		m_output << u232(value);
		break;
	case 240:
		m_output << u240(value);
		break;
	case 248:
		m_output << u248(value);
		break;
	case 256:
		m_output << u256(value);
		break;
	}
}

// Value is enclosed within double quote e.g., "hello"
void ProtoConverter::visit(FixedByteArrayValue const& _x, unsigned _width)
{
	auto numAvailableBytes = static_cast<unsigned>(_x.value().size());
	auto usedBytes = min(_width, numAvailableBytes);
	// Length of string has to be at most usedBytes
	m_output << "\"" << createAlphaNum(_x.value()).substr(0, usedBytes) << "\"";
}

void ProtoConverter::visit(DynamicByteType const& _x)
{
	std::string type = (m_isContractScope ? "bytes": "bytes memory");
	m_output << Whiskers(R"(
	<type> x_<i> = )")
	("type", type)
	("i", std::to_string(m_numGlobals++))
	.render();
	visit(_x.value());
	m_output << ";\n";
	m_types.push_back(type);
}

void ProtoConverter::visit(DynamicStringType const& _x)
{
	std::string type = (m_isContractScope ? "string": "string memory");
	m_output << Whiskers(R"(
	<type> x_<i> = )")
	("type", type)
	("i", std::to_string(m_numGlobals++))
	.render();
	visit(_x.value());
	m_output << ";\n";
	m_types.push_back(type);
}

void ProtoConverter::visit(DynamicByteValue const& _x)
{
	// TODO: A bytes stream can be longer than 32 bytes
	// FIXME: This creates a value whose size is at most 32 bytes.
	m_output << "\"" << createAlphaNum(_x.value()) << "\"";
}

void ProtoConverter::visit(DynamicStringValue const& _x)
{
	m_output << "\"" << createAlphaNum(_x.value()) << "\"";
}

void ProtoConverter::visit(AddressValue const& _x)
{
	m_output << Whiskers(R"(address(<value>))")
	("value", u160(generateUnsigned(_x.value64(), _x.value128(), _x.value160(), 0)).str())
	.render();
}

void ProtoConverter::visit(Type const& _x)
{
	switch (_x.type_oneof_case())
	{
	case Type::kStype:
		visit(_x.stype());
		break;
	case Type::kDtype:
		visit(_x.dtype());
		break;
	case Type::TYPE_ONEOF_NOT_SET:
		break;
	}
}

void ProtoConverter::visit(VarDecl const& _x)
{
	visit(_x.type());
}

void ProtoConverter::visit(Statement const& _x)
{
	switch (_x.statement_oneof_case())
	{
	case Statement::kDecl:
		visit(_x.decl());
		break;
	case Statement::kAssignment:
		visit(_x.assignment());
		break;
	case Statement::kStructdef:
		visit(_x.structdef());
		break;
	case Statement::STATEMENT_ONEOF_NOT_SET:
		break;
	}
}

void ProtoConverter::visit(Assignment const&)
{
}

void ProtoConverter::visit(StaticType const& _x)
{
	switch (_x.static_type_oneof_case())
	{
	case StaticType::kInteger:
		visit(_x.integer());
		break;
	case StaticType::kFbarray:
		visit(_x.fbarray());
		break;
	case StaticType::kAddress:
		visit(_x.address());
		break;
	case StaticType::kFsarray:
		visit(_x.fsarray());
		break;
	case StaticType::STATIC_TYPE_ONEOF_NOT_SET:
		break;
	}
}

void ProtoConverter::visit(StructType const&)
{
}

void ProtoConverter::visit(AddressType const& _x)
{
	switch (_x.atype())
	{
	case AddressType::ADDRESS:
		m_output << Whiskers(R"(
	address x_<i> = )"
		)
		("i", std::to_string(m_numGlobals++))
		.render();
		m_types.push_back("address");
		break;
	case AddressType::PAYABLE:
		m_output << Whiskers(R"(
	address payable x_<i> = )"
		)
		("i", std::to_string(m_numGlobals++))
		.render();
		m_types.push_back("address payable");
		break;
	}
	visit(_x.value());
	m_output << ";\n";
}

void ProtoConverter::visit(DynamicType const& _x)
{
	switch (_x.dynamic_type_oneof_case())
	{
	case DynamicType::kStructtype:
		visit(_x.structtype());
		break;
	case DynamicType::kDynbytearray:
		visit(_x.dynbytearray());
		break;
	case DynamicType::DYNAMIC_TYPE_ONEOF_NOT_SET:
		break;
	}
}

void ProtoConverter::visit(IntegerType const& _x)
{
	switch (_x.integer_type_case())
	{
	case IntegerType::kSint:
		visit(_x.sint());
		break;
	case IntegerType::kUint:
		visit(_x.uint());
		break;
	case IntegerType::INTEGER_TYPE_NOT_SET:
		break;
	}
}

void ProtoConverter::visit(StructTypeDefinition const&)
{
#if 0
	m_output << "struct S_" << m_numStructs++ << " {";
	for (auto const& m: _x.t())
		visit(m);
	m_output << " }\n";
#endif
}

void ProtoConverter::visit(FixedByteArrayType const& _x)
{
	unsigned numBytes = (_x.width() % 32) + 1;
	std::string type = "bytes" + std::to_string(numBytes);
	m_types.push_back(type);
	m_output << Whiskers(R"(
	<type> x_<i> = )"
	)
	("type", type)
	("i", std::to_string(m_numGlobals++))
	.render();
	visit(_x.value(), numBytes);
	m_output << ";\n";
}

void ProtoConverter::visit(DynamicByteArrayType const& _x)
{
	switch (_x.dynamic_byte_oneof_case())
	{
	case DynamicByteArrayType::kByte:
		visit(_x.byte());
		break;
	case DynamicByteArrayType::kString:
		visit(_x.string());
		break;
	case DynamicByteArrayType::DYNAMIC_BYTE_ONEOF_NOT_SET:
		break;
	}
}

void ProtoConverter::visit(FixedSizeArrayType const&)
{
#if 0
	visit(_x.type());
	m_output << "[" << _x.size() << "]";
#endif
}

// Called by g()
std::string ProtoConverter::equalityChecksAsString()
{
	ostringstream out;
	if (m_numGlobals > 0)
	{
		for (unsigned i = 0; i < m_numGlobals; i++)
			if (m_types[i] == "string")
				out << Whiskers(R"(
		return stringCompare(g_<i>, x_<i>);
				)")("i", std::to_string(i)).render();
			else if (m_types[i] == "bytes")
				out << Whiskers(R"(
		return bytesCompare(g_<i>, x_<i>);
				)")("i", std::to_string(i)).render();
			else
				out << Whiskers(R"(
		if (g_<i> != x_<i>) return false;
				)")("i", std::to_string(i)).render();
	}
	return out.str();
}

std::string ProtoConverter::typedParametersAsString()
{
	ostringstream out;
	for (unsigned i = 0; i < m_numGlobals; i++)
	{
		if (i == m_numGlobals - 1)
			if (m_types[i] == "bytes" || m_types[i] == "string")
				out << Whiskers(R"(<type> memory g_<i>)")
				("type", m_types[i])
				("i", std::to_string(i))
				.render();
			else
				out << Whiskers(R"(<type> g_<i>)")
						("type", m_types[i])
						("i", std::to_string(i))
						.render();
		else
			if (m_types[i] == "bytes" || m_types[i] == "string")
				out << Whiskers(R"(<type> memory g_<i>, )")
						("type", m_types[i])
						("i", std::to_string(i))
						.render();
			else
				out << Whiskers(R"(<type> g_<i>, )")
						("type", m_types[i])
						("i", std::to_string(i))
						.render();
	}
	return out.str();
}

// Callee function
void ProtoConverter::visit(CoderFunction const&)
{
	// TODO: We should also mix memory and calldata here.
	// function g(uint a, uint16 b, S memory c, bool[] memory d, uint16[2] memory e)
	m_output << Whiskers(R"(
	function g(<parameters>) public view returns (bool) {
		<equality_checks>
		return true;
	}
)"
	)
	("parameters", typedParametersAsString())
	("equality_checks", equalityChecksAsString())
	.render();
}

// Caller function
void ProtoConverter::visit(TestFunction const&)
{

	m_output << Whiskers(R"(
	function f() public returns (bool) {
		return this.g(<parameter_names>);
	}
	)")
	("parameter_names", YulUtilFunctions::suffixedVariableNameList("x_", 0, m_numGlobals))
	.render();

//	for (auto const& s: _x.statements())
//		visit(s);

#if 0
	if (m_numGlobals > 0)
	{
		m_output << "(";
		for (unsigned i = 0; i < m_numGlobals; i++)
		{
			if (i == m_numGlobals - 1)
				m_output << m_types[i] << " y_" << i;
			else
				m_output << m_types[i] << " y_" << i << ", ";
		}
		m_output << ")";
		m_output << " = this.g(" << YulUtilFunctions::suffixedVariableNameList("x_", 0, m_numGlobals) << ");\n";

		for (unsigned i = 0; i < m_numGlobals; i++)
			m_output << "if (y_" << i << " != x_" << i << ") return false;\n";
	}
	m_output << "return true;\n";
#endif
}

void ProtoConverter::visit(ContractStatement const& _x)
{
	switch (_x.contract_stmt_oneof_case())
	{
	case ContractStatement::kDecl:
		visit(_x.decl());
		break;
	case ContractStatement::kStructdef:
		visit(_x.structdef());
		break;
	case ContractStatement::CONTRACT_STMT_ONEOF_NOT_SET:
		break;
	}
}

void ProtoConverter::writeHelperFunctions()
{
	m_output << Whiskers(R"(
	function stringCompare(string memory a, string memory b) internal pure returns (bool) {
		if(bytes(a).length != bytes(b).length) {
			return false;
		} else {
			return keccak256(bytes(a)) == keccak256(bytes(b));
		}
	}
	)").render();

	m_output << Whiskers(R"(
	function bytesCompare(bytes memory a, bytes memory b) internal pure returns (bool) {
		if(a.length != b.length)
			return false;
		for (uint i = 0; i < a.length; i++)
			if (a[i] != b[i])
				return false;
	}
	)").render();
}

void ProtoConverter::visit(Contract const& _x)
{
	// Pragmas are defined by SolidityCompilationFramework
	// Contract definition
	m_output << "contract C {\n";
	// Storage vars
	// Dynamic types
	//  struct S { uint16 u; int8 v; }
	// Var decls (mix of static and dynamic types)
	//  bool[] x;
	//  uint16 y;
	//  S s;
	for (auto const& cs: _x.cstatements())
		visit(cs);
	writeHelperFunctions();
	m_isContractScope = false;
	// Test function
	visit(_x.testfunction());
	// Coder function
	visit(_x.coderfunction());
	m_output << "}\n";
}

string ProtoConverter::contractToString(Contract const& _input)
{
	visit(_input);
	return m_output.str();
}