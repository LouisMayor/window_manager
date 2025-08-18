#include "CreateWindowApp.h"

#include "../../types.h"

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
	return 0;
}
