#pragma once
#include <fstream>
#include "In.h"
#include "Parm.h"
#include "Error.h"
#pragma warning(disable: 4996)

using namespace std;

namespace Log //работа с протоколом
{
	struct LOG //протокол
	{
		wchar_t logfile[PARM_MAX_SIZE]; //имя файла протокола
		std::ofstream* stream;          //выходной поток протокола
	};
	static LOG INITLOG = { L" ",  NULL };        //структура для начальной инициализации лог
	LOG getlog(wchar_t logfile[]);                   //сформировать структуру лог
	void WriteLine(LOG log, const char* c, ...);     //вывести в протокол конкатенацию строк
	void WriteLine(LOG log, const wchar_t* c, ...);  //вывести в протокол конкатенацию строк
	void WriteLog(LOG log);                          //вывести в протокол заголовок
	void WriteParm(LOG log, Parm::PARM parm);        //инф о выходных потоках
	void WriteIn(LOG log, In::IN in);                //инф о входном потоке
	void WriteError(LOG log, Error::ERROR error);    //инф об ошибке
	void Close(LOG log);                             //закрыть протокол
	void WriteError(LOG log, char* msg);
};