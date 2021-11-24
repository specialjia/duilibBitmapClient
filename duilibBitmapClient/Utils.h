#pragma once
#include <atlstr.h>
#include <string>

class Utils
{
public:
	static CString GetFileName(CString path);
	static std::string w2a(std::wstring strW);
	static std::string w2u(std::wstring strW);
};
