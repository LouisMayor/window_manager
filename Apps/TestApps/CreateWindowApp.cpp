#include "CreateWindowApp.h"

#include "../../types.h"
#include "../Misc/Hashing.h"

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

	const bool test_result = HashingTests::TestFNV1();
	(void)test_result;

	return 0;
}
