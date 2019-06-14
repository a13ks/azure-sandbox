#include <string>
#include <windows.h>

void test(const char* str)
{
    DWORD attr = GetFileAttributesW(str);
}

int main()
{
    std::string test_str("123");
    test(test_str.c_str());
    return 0;
}