#include "CreateWindowApp.h"

#include "../../types.h"
#include "../Misc/RTTI/RTTI Tests/RTTITests.h"
#include "../Misc/Hashing.h"
#include "../Misc/RTTI/TypeId.h"

int main();

void CreateWindowApp::AppEntry()
{
	main();
}

int main()
{
	i32 x = 64;
	i32 y = 64;
	i32 z = x * y;
	(void)z;

	const bool test_hashing_result = HashingTests::TestFNV1();
	(void)test_hashing_result;

	const bool test_rtti_result = RTTITests::TestBasicTypes();
	(void)test_rtti_result;

	constexpr bool test_rtti_pp_result = RTTITests::TestBasicTypes_pp();
	(void)test_rtti_pp_result;

	constexpr bool test_rtti_ct_result = RTTITests::TestBasicTypes_ct();
	(void)test_rtti_ct_result;

	std::string_view str_tid = typeid(int).name();
	(void)str_tid;

	std::string_view str_ct = GetTypeName_ct<int>();
	(void)str_ct;

	std::string_view str_pp = TYPE_NAME(int);
	(void)str_pp;

	return 0;
}
