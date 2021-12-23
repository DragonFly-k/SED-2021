#include "stdafx.h"
#include "LT.h"
#include "Error.h"
#include <fstream>

namespace LT {
	LexTable Create(int size)
	{
		LexTable* lt = new LexTable;
		if (size > LT_MAXSIZE)throw ERROR_THROW(117);
		lt->maxsize = size;
		lt->size = 0;
		lt->table = new Entry[size];
		return *lt;
	}

	void Add(LexTable& lextable, Entry entry)
	{
		if (lextable.size == lextable.maxsize)throw ERROR_THROW(118);
		lextable.table[lextable.size] = entry;
		lextable.size++;
	}

	Entry GetEntry(LexTable& lextable, int n)
	{
		if (n >= lextable.size)throw ERROR_THROW(119);
		return lextable.table[n];
	}

	void LT::LexTable::writeLT(const wchar_t* in)
	{
		int i = 0;
		wchar_t Lex[300];
		for (; in[i] != '\0'; i++) Lex[i] = in[i];
		Lex[i] = '\0';
		std::ofstream* lexStream = new std::ofstream;
		lexStream->open("LT.txt");
		if (!lexStream->is_open())throw ERROR_THROW(119);		
		*lexStream << "=================" << endl;
		*lexStream << " Таблица лексем" << endl;
		*lexStream << "=================" << endl;
		if (lexStream->is_open())
		{ 
			int currentString = 0;
			(*lexStream) << '\n' << currentString + 1 << '\t';
			for (int i = 0; i < this->size;)
			{
				if (currentString == this->table[i].sn) (*lexStream) << this->table[i++].lexema;		
				else(*lexStream) << '\n' << currentString++ + 2 << '\t';
			}
		}
		else throw ERROR_THROW(125);
		lexStream->close();
		delete lexStream;
	}
	void LT::LexTable::writePBNLT(const wchar_t* in)
	{
		int i = 0;
		wchar_t Lex[300];
		for (; in[i] != '\0'; i++) Lex[i] = in[i];
		Lex[i] = '\0';
		std::ofstream* lexStream = new std::ofstream;
		lexStream->open("PbnLT.txt");
		if (!lexStream->is_open())throw ERROR_THROW(119);		
		*lexStream << "=============================" << endl;
		*lexStream << " Таблица лексем после ПОЛИЗ " << endl;
		*lexStream << "=============================" << endl;
		if (lexStream->is_open())
		{
			int currentString = 0;
			(*lexStream) << '\n' << currentString + 1 << '\t';
			for (int i = 0; i < this->size;)
			{
				if (currentString == this->table[i].sn) (*lexStream) << this->table[i++].lexema;
				else(*lexStream) << '\n' << currentString++ + 2 << '\t';
			}
		}
		else throw ERROR_THROW(125);
		lexStream->close();
		delete lexStream;
	}

	void Delete(LexTable& lextable)
	{
		delete[] lextable.table;
		lextable = {};
	}
}