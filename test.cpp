#include <string>
#include <stdio.h>

#if _WIN32

#include <windows.h>

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

#endif

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "Goodbye!\n");
		return 1;
	}

	fprintf(stdout, "Hello, %s!\n", argv[1]);
    return 0;
}