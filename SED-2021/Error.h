#pragma once 
#define ERRORMASSAGE_MAX_SIZE 200//максималная длина сообщения об ошибке
#define ERROR_MAX_ENTRY 1000 //кол элементов таблицы ошибок

#define ERROR_THROW(id) Error::geterror(id);
#define ERROR_THROW_IN(id, l, c) Error::geterrorin(id, l,c );
#define ERROR_ENTRY(id, m) {id, m, {-1,-1}} //элемент таблицы ошибок
      
#define ERROR_ENTRY_NODEF(id) ERROR_ENTRY(-id,"Неопределённая ошибка") //1 неопределенный элемент таблицы ошибок
//10 неопределенных элементов таблицы ошибок
#define ERROR_ENTRY_NODEF10(id)  ERROR_ENTRY_NODEF(id + 0), ERROR_ENTRY_NODEF(id + 1),ERROR_ENTRY_NODEF(id + 2),ERROR_ENTRY_NODEF(id + 3),\
								 ERROR_ENTRY_NODEF(id + 4), ERROR_ENTRY_NODEF(id + 5), ERROR_ENTRY_NODEF(id + 6),ERROR_ENTRY_NODEF(id + 7),\
								 ERROR_ENTRY_NODEF(id + 8), ERROR_ENTRY_NODEF(id + 9)
//100 неопределенных элементов таблицы ошибок
#define ERROR_ENTRY_NODEF100(id)  ERROR_ENTRY_NODEF10(id + 0), ERROR_ENTRY_NODEF10(id + 10),ERROR_ENTRY_NODEF10(id + 20),ERROR_ENTRY_NODEF10(id + 30),\
								  ERROR_ENTRY_NODEF10(id + 40), ERROR_ENTRY_NODEF10(id + 50), ERROR_ENTRY_NODEF10(id + 60),ERROR_ENTRY_NODEF10(id + 70),\
								  ERROR_ENTRY_NODEF10(id + 80), ERROR_ENTRY_NODEF10(id + 90)

namespace Error
{
	struct ERROR // тип исключения
	{
		int id; //код ошибки
		char message[ERRORMASSAGE_MAX_SIZE];// сообщение об ошибке
		struct IN   // расширения для ошибок при обработке входных данных
		{
			short line; //номер строки
			short col;  //позиция в строке
		} errorPosition;
	};
	ERROR geterror(int id);                             //ERROR_THROW
	ERROR geterrorin(int id, int line, int col);        //ERROR_THROW_IN
};