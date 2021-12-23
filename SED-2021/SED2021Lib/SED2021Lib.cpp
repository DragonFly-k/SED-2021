#include "pch.h"
#include <iostream>
#include <sstream>
#pragma warning(disable : 4996) 

extern "C"
{
	int __stdcall stringLen(char* source)
	{
		int result = 0;
		while (source[result] != '\0')
		{
			result++;
		}
		return result;
	}

	char* __stdcall StrConcat(char* source, char* result)
	{
		int res1 = 0, res2 = 0;
		while (result[res1] != '\0')
		{
			res1++;
		}
		while (source[res2] != '\0')
		{
			res2++;
		}
		if (res1 + res2 > 20) std::cout << "Lines will be truncated" << std::endl;
		char r[20];
		int rlen = 0;
		for (int i = 0; source[i] != '\0'; i++)
		{
			if (rlen >= 18) break;
			r[rlen] = source[i];
			rlen++;
		}
		for (int i = 0; result[i] != '\0'; i++)
		{
			if (rlen >= 18) break;
			r[rlen] = result[i];
			rlen++;
		}
		r[rlen++] = '\0';
		return r;
	}

	void __stdcall WriteW(char* value)
	{
		setlocale(0, "");
		std::cout << value << std::endl;
	}

	void __stdcall WriteN(int value)
	{
		std::cout << value << std::endl;
	}
}