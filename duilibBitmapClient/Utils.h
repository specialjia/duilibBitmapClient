#pragma once
#include <atlstr.h>
#include <string>

class Utils
{
public:
	static std::wstring GetFileName1(std::wstring path);
	static std::string w2a(std::wstring strW);
	static std::string w2u(std::wstring strW);
};
