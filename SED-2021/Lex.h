#pragma once
#include "stdafx.h"
#include "LT.h"
#include "IT.h"
#include <list>

#define ADDWORD buff[posInBuff] = '\0';\
				 posInBuff = 0;\
				 strcpy_s(entry.token, buff); \
				 entry.line = line; \
				 entry.symInLine = posInLine;\
				 tokens->Add(entry);

#define CHECKFORPARMS tables->lexTable.table[tables->lexTable.size-1].lexema==LEX_ID &&\
				      tables->idenTable.table[tables->lexTable.table[tables->lexTable.size-1].idxTI].idtype==IT::F &&\
				      tables->lexTable.table[tables->lexTable.size-2].lexema==LEX_DEF

#define LIBFOO table.lexTable.table[table.lexTable.size-3].lexema == LEX_STRLEN || table.lexTable.table[table.lexTable.size-3].lexema == LEX_CONCAT|| table.lexTable.table[table.lexTable.size-5].lexema == LEX_CONCAT


#define CHECKFORDECLARE (table.lexTable.table[table.lexTable.size-3].lexema==LEX_TYPE && table.lexTable.table[table.lexTable.size-2].lexema==LEX_DEF ) ||\
	(table.lexTable.table[table.lexTable.size-2].lexema==LEX_TYPE && table.lexTable.table[table.lexTable.size-3].lexema==LEX_CREATE ) || \
	(table.lexTable.table[table.lexTable.size-2].lexema==LEX_DEF && table.lexTable.table[table.lexTable.size-3].lexema==LEX_TYPE &&\
    table.lexTable.table[table.lexTable.size-4].lexema==LEX_CREATE)

#define CHECKPARM (tables->lexTable.table[tables->lexTable.size-2].lexema==LEX_TYPE) &&\
 (tables->lexTable.table[tables->lexTable.size-3].lexema==LEX_COMMA || tables->lexTable.table[tables->lexTable.size-3].lexema==LEX_LEFTHESIS)

#define LINE tokens->arr.front().line

#define SYM tokens->arr.front().symInLine

#define LEXLINE tables->lexTable.table[tables->lexTable.size-1].sn

#define LEXPOS tables->lexTable.table[tables->lexTable.size-1].posInStr

namespace Lex
{
	struct Tables
	{
		LT::LexTable lexTable;
		IT::IdTable idenTable;
	};

	struct Word
	{
		char token[255];
		int line;
		int symInLine;
	};

	class Words
	{
	public:
		list<Word> arr;

		void Add(Word entry)
		{
			arr.push_back(entry);
		}

		void Delete()
		{
			arr.pop_front();
		}

	};

	Words* DivisionIntoTokens(In::IN in);
	Tables LexAnalysis(Words* words);
	char AnalysisToken(char* lex, Tables* tables);
	bool CheckForStringLiteral(Words* words);
	bool CheckForIntegerLiteral(Words* words);
	bool CheckId(Words* words);
	LT::Entry AddLex(char lex, Words* words, int refID, IT::IdTable* idenTable);
	void AnalysisItString(IT::Entry* tempIT, char& lexem, Words* words);
	char CheckForArithmAndBrack(char* lexem, Tables* table);
	void AddID(char* token, Tables* tables, IT::Entry tempIT);

#define FST_COUNT 11

#define A_DEF   4,\
				FST::NODE(1, FST::RELATION('d', 1)),\
				FST::NODE(1, FST::RELATION('e', 2)),\
				FST::NODE(1, FST::RELATION('f', 3)),\
				FST::NODE()		

#define A_REAL  5,\
				FST::NODE(1, FST::RELATION('r', 1)),\
				FST::NODE(1, FST::RELATION('e', 2)),\
				FST::NODE(1, FST::RELATION('a', 3)),\
                FST::NODE(1, FST::RELATION('l', 4)),\
				FST::NODE()

#define A_CREATE 7,\
				FST::NODE(1, FST::RELATION('c', 1)),\
				FST::NODE(1, FST::RELATION('r', 2)),\
				FST::NODE(1, FST::RELATION('e', 3)),\
				FST::NODE(1, FST::RELATION('a', 4)),\
				FST::NODE(1, FST::RELATION('t', 5)),\
				FST::NODE(1, FST::RELATION('e', 6)),\
				FST::NODE()

#define A_OUT   4,\
				FST::NODE(1, FST::RELATION('o', 1)),\
				FST::NODE(1, FST::RELATION('u', 2)),\
				FST::NODE(1, FST::RELATION('t', 3)),\
				FST::NODE()

#define A_CHAR  5,\
				FST::NODE(1, FST::RELATION('c', 1)),\
				FST::NODE(1, FST::RELATION('h', 2)),\
				FST::NODE(1, FST::RELATION('a', 3)),\
				FST::NODE(1, FST::RELATION('r', 4)),\
				FST::NODE()	

#define A_WRITE 6,\
				FST::NODE(1, FST::RELATION('w', 1)),\
				FST::NODE(1, FST::RELATION('r', 2)),\
				FST::NODE(1, FST::RELATION('i', 3)),\
				FST::NODE(1, FST::RELATION('t', 4)),\
				FST::NODE(1, FST::RELATION('e', 5)),\
				FST::NODE()

#define A_START 6,\
				FST::NODE(1, FST::RELATION('s', 1)),\
				FST::NODE(1, FST::RELATION('t', 2)),\
				FST::NODE(1, FST::RELATION('a', 3)),\
				FST::NODE(1, FST::RELATION('r', 4)),\
				FST::NODE(1, FST::RELATION('t', 5)),\
				FST::NODE()

#define A_IF 3,\
				FST::NODE(1, FST::RELATION('i', 1)),\
				FST::NODE(1, FST::RELATION('f', 2)),\
				FST::NODE()

#define A_ELSE 5,\
				FST::NODE(1, FST::RELATION('e', 1)),\
				FST::NODE(1, FST::RELATION('l', 2)),\
				FST::NODE(1, FST::RELATION('s', 3)),\
				FST::NODE(1, FST::RELATION('e', 4)),\
				FST::NODE()

#define A_CONCAT 10,\
				FST::NODE(1, FST::RELATION('S', 1)),\
				FST::NODE(1, FST::RELATION('t', 2)),\
				FST::NODE(1, FST::RELATION('r', 3)),\
				FST::NODE(1, FST::RELATION('C', 4)),\
				FST::NODE(1, FST::RELATION('o', 5)),\
				FST::NODE(1, FST::RELATION('n', 6)),\
				FST::NODE(1, FST::RELATION('c', 7)),\
				FST::NODE(1, FST::RELATION('a', 8)),\
				FST::NODE(1, FST::RELATION('t', 9)),\
				FST::NODE()

#define A_STRLEN 10,\
				FST::NODE(1, FST::RELATION('s', 1)),\
				FST::NODE(1, FST::RELATION('t', 2)),\
				FST::NODE(1, FST::RELATION('r', 3)),\
				FST::NODE(1, FST::RELATION('i', 4)),\
				FST::NODE(1, FST::RELATION('n', 5)),\
				FST::NODE(1, FST::RELATION('g', 6)),\
				FST::NODE(1, FST::RELATION('L', 7)),\
				FST::NODE(1, FST::RELATION('e', 8)),\
				FST::NODE(1, FST::RELATION('n', 9)),\
				FST::NODE()
}