#include "Utils.h"

CString Utils::GetFileName(CString path)
{
	int intCharPosition;

	//Find "\\",Get The File's Name
	intCharPosition = path.ReverseFind(L'\\');

	if (-1 != intCharPosition)
	{
		path = path.Right(path.GetLength() - intCharPosition - 1);
	}

	return path;
}

std::string wcharToString(std::wstring str, DWORD nCodePage)
{
	int nLen = ::WideCharToMultiByte(nCodePage, 0, str.c_str(), str.length(), NULL, 0, NULL, NULL) + 2;
	char* p = (char*)malloc(nLen);
	memset(p, 0, nLen);
	::WideCharToMultiByte(nCodePage, 0, str.c_str(), str.length(), p, nLen, NULL, NULL);
	std::string strR = p;
	free(p);
	return strR;
}
std::string Utils::w2a(std::wstring strW)
{
	return wcharToString(strW, CP_ACP);
}

std::string Utils::w2u(std::wstring strW)
{
	return wcharToString(strW, CP_UTF8);
}
