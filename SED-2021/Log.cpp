#include <iostream>
#include <ctime>
#include <stdarg.h>
#include "Parm.h"
#include "Log.h"

namespace Log
{
	LOG getlog(wchar_t logfile[])
	{
		LOG log;
		log.stream = new ofstream;
		log.stream->open(logfile);
		if (!log.stream->is_open()) { throw ERROR_THROW(112) };
		wcscpy_s(log.logfile, logfile);
		return log;
	}

	void WriteLine(LOG log, const char* c, ...)
	{
		char* ptr = (char*)c;
		va_list arg;
		va_start(arg, c);
		while (ptr != "")
		{
			(*log.stream) << ptr;
			ptr = va_arg(arg, char*);
		}
		(*log.stream) << '\n';
		va_end(arg);
	}

	void WriteLine(LOG log, const wchar_t* c, ...)
	{
		va_list arg;
		va_start(arg, c);
		char* buf;
		while (c != L"")
		{
			buf = new char[wcslen(c) + 1];
			wcstombs(buf, c, wcslen(c) + 1);
			(*log.stream) << buf;
			c = va_arg(arg, const wchar_t*);
			delete[] buf;
		}
		(*log.stream) << '\n';
		va_end(arg);
	}

	void WriteLog(LOG log)
	{
		char date[100];
		tm local;
		time_t currentTime;
		currentTime = time(NULL);
		localtime_s(&local, &currentTime);	//������� ��������� �����, �������������� � ���������
		strftime(date, 100, "%d.%m.%Y \n�����: %H:%M:%S\n", &local);
		(*log.stream) << "-----��������----- " << endl << "����: " << date << endl;
	}

	void WriteParm(LOG log, Parm::PARM parm)
	{
		char symbol; int i = 0;
		(*log.stream) << "----���������-----" << "\n";
		(*log.stream) << (char*)PARM_IN;
		symbol = wctob(parm.in[i]);
		while (symbol != EOF)
		{
			(*log.stream) << symbol;
			i++;
			symbol = wctob(parm.in[i]);
		}
		(*log.stream) << '\n'; i = 0;
		(*log.stream) << (char*)PARM_OUT;
		symbol = wctob(parm.out[i]);
		while (symbol != EOF)
		{
			(*log.stream) << symbol;
			i++;
			symbol = wctob(parm.out[i]);
		}
		(*log.stream) << '\n'; i = 0;
		(*log.stream) << (char*)PARM_LOG;
		symbol = wctob(parm.log[i]);
		while (symbol != EOF)
		{
			(*log.stream) << symbol;
			i++;
			symbol = wctob(parm.log[i]);
		}
		(*log.stream) << '\n';
	}

	void WriteIn(LOG log, In::IN in)
	{
		(*log.stream) << "-----�������� ������----- " << endl;
		(*log.stream) << "���������� ��������: " << in.size << endl;
		(*log.stream) << "���������� �����: " << in.lines << endl;
		(*log.stream) << "���������������: " << in.ignor << endl;
	}

	void WriteError(LOG log, Error::ERROR error)
	{
		cout << "������ " << error.id << ':' << error.message << endl;
		if (error.id == 100)return;
		(*log.stream) << "������ " << error.id << ':' << error.message << endl;
		if (error.errorPosition.line != -1)
		{
			(*log.stream) << "������ " << error.errorPosition.line << "\t�������: " << error.errorPosition.col << endl;
			cout << "������ " << error.errorPosition.line  << "\t�������: " << error.errorPosition.col << endl;
		}
	}

	void WriteError(LOG log, char* msg)
	{
		cout << msg << endl;
		(*log.stream) << msg;
	}

	void Close(LOG log)
	{
		log.stream->close();
		delete log.stream;
	}
}