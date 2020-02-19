#include <string>
#include <windows.h>
#include <stdio.h>

void test(const char* str)
{
    DWORD attr = GetFileAttributesA(str);

	if (attr == INVALID_FILE_ATTRIBUTES)
	{
		switch (GetLastError())
		{
		case ERROR_FILE_NOT_FOUND:
		case ERROR_PATH_NOT_FOUND:
		case ERROR_NOT_READY:
		case ERROR_INVALID_DRIVE:
			return;
		default:
			return;
		}
	}
	return;
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Goodbye!\n");
		return 1;
	}

	printf("Hello, %s!\n", argv[1]);
    return 0;
}