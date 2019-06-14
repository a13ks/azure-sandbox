#include <string>
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

int main()
{
    std::string test_str("123");
    test(test_str.c_str());
    return 0;
}