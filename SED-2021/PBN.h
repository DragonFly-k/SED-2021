#pragma once
#include "IT.h"
#include "LT.h"
#include <stack>
#include "Lex.h"

#define SEARCHEXPR tables.lexTable.table[i].lexema == LEX_EQUAL_SIGN || tables.lexTable.table[i].lexema == LEX_WRITE ||\
 tables.lexTable.table[i].lexema == LEX_OUT

namespace PN
{
	struct Pos
	{
		int startEx;
		int endEx;
		LT::Entry* express;
	};

	void PolishNotation(Lex::Tables& tables);
	void GetExrp(LT::LexTable lexTable, Pos& pos);
	int	Convertation(Pos& pos, IT::IdTable* idenTable);
	short ArithmPrioritys(LT::Entry str, IT::IdTable* idenTable);
	void ShiftAndWriteLT(Lex::Tables& Tables, Pos* pos, int newLen);
}