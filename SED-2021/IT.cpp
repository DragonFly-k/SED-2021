#include "stdafx.h"
#include <iomanip>
#include "IT.h"
namespace IT
{
	IdTable Create(int size)
	{
		IdTable* New = new IdTable;
		if (size > TI_MAXSIZE)throw ERROR_THROW(118);
		New->maxsize = size;
		New->size = 0;
		New->table = new Entry[size];
		return *New;
	}

	void Add(IdTable& idtable, Entry entry)
	{
		if (idtable.size == idtable.maxsize) throw ERROR_THROW(118);	//переполнение
		idtable.table[idtable.size++] = entry;
	}

	Entry GetEntry(IdTable& idtable, int n)
	{
		return idtable.table[n];
	}

	int IsId(IdTable& idtable, char id[ID_MAXSIZE], char block[ID_MAXSIZE])		//обычный поиск
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (!strcmp(idtable.table[i].id, id) && !strcmp(idtable.table[i].parrentBlock, block)) return i;
			if (!strcmp(idtable.table[i].id, id) && idtable.table[i].idtype == F && !strcmp(idtable.table[i].parrentBlock, TI_BLOCK_DEFAULT))
				return i;
		}
		return TI_NULLIDX;
	}

	int IsId(IdTable& idtable, char* block, IDDATATYPE type, char* literal)		//поиск литерала
	{
		int val = atoi(literal);
		for (int i = 0; i < idtable.size; i++)
		{
			if (idtable.table[i].id[0] == 'L' && (!strcmp(idtable.table[i].parrentBlock, block)))
			{
				switch (type)
				{
				case IT::INT:
				{
					if (idtable.table[i].iddatatype == IT::INT && (idtable.table[i].value.vint == val))return i;
					break;
				}
				case IT::STR:
				{
					if (idtable.table[i].iddatatype == IT::STR && (!strcmp(idtable.table[i].value.vstr.str, literal)))return i;
					break;
				}
				}
			}
		}
		return TI_NULLIDX;
	}

	int IsId(IdTable& idtable, char* id)		//для библиотечных функций
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (!strcmp(idtable.table[i].id, id)) return i;
		}
		return TI_NULLIDX;
	}

	void ShowTable(IdTable* idtable, const wchar_t* in)
	{
		int i = 0;
		wchar_t id[300];
		for (; in[i] != '\0'; i++) id[i] = in[i];
		id[i] = '\0';
		std::ofstream* idStream = new std::ofstream;
		idStream->open("ID.txt");

		if (idStream->is_open())
		{
			int i, numberOP = 0;
			*(idStream) << setfill('-') << setw(87) << '-' << endl;
			*(idStream) << "   №" << " | " << "Идентификатор" << " | " << "Тип данных" << " | " << "Тип идентификатора" << " | " << "Индекс в ТЛ" << " | " << "Значение    " << endl;
			*(idStream) << setw(87) << '-' << endl;
			for (i = 0; i < idtable->size; i++)
			{
				*(idStream) << setfill(' ') << setw(4) << std::right << i << " | ";
				*(idStream) << setw(13) << left << idtable->table[i].id << " | ";
				switch (idtable->table[i].iddatatype)
				{
				case  IT::INT:
				{
					*(idStream) << setw(10) << left;
					*(idStream) << "real" << " | ";
					break;
				}
				case  IT::STR:
				{
					*(idStream) << setw(10) << left;
					*(idStream) << "char" << " | ";
					break;
				}
				default:
					*(idStream) << setw(10) << left << "unknown" << " | "; break;
				}
				switch (idtable->table[i].idtype)
				{

				case IT::V:
					*(idStream) << setw(18) << left << "переменная" << " | ";
					break;

				case IT::F:
					*(idStream) << setw(18) << left << "функция" << " | ";
					break;

				case IT::P:
					*(idStream) << setw(18) << left << "параметр" << " | ";
					break;

				case IT::L:
					*(idStream) << setw(18) << left << "литерал" << " | ";
					break;
				case IT::A:
					*(idStream) << setw(18) << left << "операция" << " | ";
					numberOP++;
					break;
				default:
					*(idStream) << setw(18) << left << "unknown" << " | ";
					break;

				}
				*(idStream) << setw(11) << left << idtable->table[i].idxfirstLE << " | ";
				if (idtable->table[i].iddatatype == IT::INT && (idtable->table[i].idtype == IT::V || idtable->table[i].idtype == IT::L)) {
					*(idStream) << setw(18) << left << idtable->table[i].value.vint;
				}
				else if (idtable->table[i].iddatatype == IT::STR && (idtable->table[i].idtype == IT::V || idtable->table[i].idtype == IT::L)) {
					*(idStream) << "[" << idtable->table[i].value.vstr.len << "]\"" << idtable->table[i].value.vstr.str << "\"";
				}
				else *(idStream) << "-";
				*(idStream) << endl;
			}
			*(idStream) << setfill('-') << setw(87) << '-' << endl;
			*(idStream) << "Количество идентификаторов: " << i - numberOP << endl;
			*(idStream) << setw(87) << '-' << endl;
		}
	}

	void Delete(IdTable& idtable)
	{
		delete[] idtable.table;
		idtable = {};
	}
}
