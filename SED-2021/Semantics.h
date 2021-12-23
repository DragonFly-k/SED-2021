#pragma once
#include "stdafx.h"
#define SEM_ERROR_SIRES 700
namespace Semantic
{
	struct Entry
	{
		int index;
		int countOfParam;
		IT::IDDATATYPE types[9];
	};

	struct Functions
	{
		int maxsize;
		int size;
		Entry* table;
	};

	Functions Create(int size);
	void SemanticAnalysis(Lex::Tables* tables);
	void CheckTypesMapping(Lex::Tables* tables);
	void FillFunction(Functions& functions, IT::IdTable& idenTables);
	void AddFunc(Functions& functions, Entry entry);
	void CheckFuncitionParams(Functions& functions, Lex::Tables& tales);
	bool isEqual(Entry& entry1, Entry& entry2);
	void CheckBuiltInFunParam(LT::LexTable& lextable, IT::IdTable& idtable);
	void CheckForReturnType(LT::LexTable& lextable, IT::IdTable& idtable);
	void CheckCondAndStreams(LT::LexTable& lextable, IT::IdTable& idtable);
	void AddParrentBlockToId(Lex::Tables& tables);

}