#include <fstream>
#include <string>
#include "In.h"
#include "Error.h"
#include <iostream>

using namespace std;

namespace In
{
	IN getin(wchar_t* infile)
	{
		IN in;
		ifstream file;
		file.open(infile);

		if (!file.is_open())throw ERROR_THROW(110);
		in.text = new unsigned char[IN_MAX_LEN_TEXT];

		unsigned char tempChar;
		int position = 0;
		int positionArray = 0;
		bool flagEmptyFile = true;
		bool flagLiteral = false;

		while ((tempChar = file.get()) && !file.eof())
		{
			flagEmptyFile = false;
			if (tempChar == IN_CODE_ENDL && in.text[positionArray - 1] != IN_CODE_ENDL)	// перенос строки
			{
				in.text[positionArray++] = IN_CODE_ENDL;
				in.size++;
				in.lines++;
				position = 0;
				continue;
			}
			switch (in.code[tempChar])
			{
			case IN::S:
			case IN::B:
			case IN::V:
			case IN::T:	// разрешение
			{
				if (tempChar != IN_CODE_ENDL)
				{
				in.text[positionArray++] = tempChar;
				in.size++;
				position++;
				}
				break;
			}

			case IN::Q:
			{
				if (!flagLiteral)flagLiteral = true;
				else flagLiteral = false;
				in.text[positionArray++] = tempChar;
				in.size++;
				position++;
				break;
			}

			case IN::F:
			{	// запрет
				if (flagLiteral)
				{
					in.text[positionArray++] = tempChar;
					in.size++;
					position++;
					break;
				}
				throw ERROR_THROW_IN(111, in.lines, position + 1);
				break;
			}
			default:
			{
				cout << tempChar << endl;
				in.text[positionArray++] = in.code[tempChar];
				in.size++;
				position++;
				break;
			}
			}
		}
		in.text[positionArray++] = '\0';
		if (flagEmptyFile) throw ERROR_THROW(113);
		if (in.size == 0) in.lines = 0;
		file.close();
		return in;
	}
}