#include "Error.h"

namespace Error
{
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "Недопустимый код ошибки"), ERROR_ENTRY(1, "Системный сбой"),
		ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),ERROR_ENTRY_NODEF(5),ERROR_ENTRY_NODEF(6),
		ERROR_ENTRY_NODEF(7),ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),ERROR_ENTRY_NODEF10(10),ERROR_ENTRY_NODEF10(20),
		ERROR_ENTRY_NODEF10(30),ERROR_ENTRY_NODEF10(40),ERROR_ENTRY_NODEF10(50),ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),
		ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),

		ERROR_ENTRY(100, "Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),

		ERROR_ENTRY(104, "Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),

		ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, "Недопустимый символ в исходном коде (-in)"),
		ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113, "Файл, переданный как -in:, пуст"),
		ERROR_ENTRY(114, "Не удалось создать выходной файл"),
		ERROR_ENTRY_NODEF(115),

		ERROR_ENTRY(116, "Кол-во открывающих и закрывающих процедурных скобок не совпадает"),
		ERROR_ENTRY(117, "Таблица лексем переполнена"),
		ERROR_ENTRY(118, "Таблица идентификаторов переполнена"),
		ERROR_ENTRY(119, "Не удалось создать файл с лексемами / идентификаторами"),
		ERROR_ENTRY(120, "Превышена длинна строкового литерала"),
		ERROR_ENTRY(121, "Превышена длинна идентификатора"),
		ERROR_ENTRY(122, "Запрещенные символы в имени идетификатора"),
		ERROR_ENTRY(123, "Слишком большое значение целочисленного литерала"),
		ERROR_ENTRY(124, "Не объявлена точка входа в программу ( start )"),
		ERROR_ENTRY(125, "Определено несколько точек входа в программу ( start )"),
		ERROR_ENTRY(126, "Использование необъявленного идентификатора"),
		ERROR_ENTRY(127, "Неверное оъявление параметров"),
		ERROR_ENTRY(128, "Не найдена закрывающая кавычка строкового литерала"),
		ERROR_ENTRY(129, "Запрещенный элемент в глобальной области видимости"),
		ERROR_ENTRY(130, "Повторное определение идентификатора"),
		ERROR_ENTRY(131,"Ошибка представленя числа в 2-ой системы счисления"),

		ERROR_ENTRY_NODEF(132),ERROR_ENTRY_NODEF(133),ERROR_ENTRY_NODEF(134),ERROR_ENTRY_NODEF(135),ERROR_ENTRY_NODEF(136),
		ERROR_ENTRY_NODEF(137),ERROR_ENTRY_NODEF(138),ERROR_ENTRY_NODEF(139),ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),ERROR_ENTRY_NODEF100(200), 
		ERROR_ENTRY_NODEF100(300),ERROR_ENTRY_NODEF100(400),ERROR_ENTRY_NODEF100(500),

		ERROR_ENTRY(600, "Неверная структура программы"),
		ERROR_ENTRY(601, "Ошибочный оператор"),
		ERROR_ENTRY(602, "Ошибка в выражении"),
		ERROR_ENTRY(603, "Ошибка в выражении со знаком функции"),
		ERROR_ENTRY(604, "Ошибка в формальных параметрах функции"),
		ERROR_ENTRY(605, "Ошибка в фактических параметрах функции"),
		ERROR_ENTRY(606, "Ошибка в условии условного оператора вызываемой функции"),
		ERROR_ENTRY_NODEF(607),ERROR_ENTRY_NODEF(608),ERROR_ENTRY_NODEF(609),ERROR_ENTRY_NODEF10(610),ERROR_ENTRY_NODEF10(620),	
		ERROR_ENTRY_NODEF10(630),ERROR_ENTRY_NODEF10(640),ERROR_ENTRY_NODEF10(650),ERROR_ENTRY_NODEF10(660),ERROR_ENTRY_NODEF10(670),
		ERROR_ENTRY_NODEF10(680),ERROR_ENTRY_NODEF10(690),

		ERROR_ENTRY(700, "Идентификатор не является левосторонним выражением"),
		ERROR_ENTRY(701, "Оператор не перегружен для работы со строками"),
		ERROR_ENTRY(702, "В вызове функции отсутствуют скруглые скобки ()"),
		ERROR_ENTRY(703, "Несоответствие типов в выражении"),
		ERROR_ENTRY(704, "Ошибка в выражении"),
		ERROR_ENTRY(705, "Превышено максимальное кол-во параметров функции"),
		ERROR_ENTRY(706, "Превышено максимальное кол-во функции"),
		ERROR_ENTRY(707, "Несоответствие формальных и фактических параметров функции"),
		ERROR_ENTRY(708, "Несоответствие формальных и фактических параметров встроенной функции"),
		ERROR_ENTRY(709, "Тип возвращаемого значения не соответствует типу функции"),
		ERROR_ENTRY(710, "В функции отсутствует возвращаемое значение"),
		ERROR_ENTRY(711, "Превышено максимальное значение int "),
		ERROR_ENTRY(712, "Неверное выражение с Write"),
		ERROR_ENTRY(713, "Неверное выражение в блоке if"),
		ERROR_ENTRY(714, "Главная функция entry может возвращать только значение типа INT"),
		ERROR_ENTRY_NODEF(715),ERROR_ENTRY_NODEF(716),ERROR_ENTRY_NODEF(717),ERROR_ENTRY_NODEF(718),ERROR_ENTRY_NODEF(719),
		ERROR_ENTRY_NODEF10(720),ERROR_ENTRY_NODEF10(730),ERROR_ENTRY_NODEF10(740),ERROR_ENTRY_NODEF10(750),ERROR_ENTRY_NODEF10(760),
		ERROR_ENTRY_NODEF10(770),ERROR_ENTRY_NODEF10(780),ERROR_ENTRY_NODEF10(790),ERROR_ENTRY_NODEF100(800),ERROR_ENTRY_NODEF100(900)
	};

	ERROR geterror(int id)
	{
		if (0 < id < ERROR_MAX_ENTRY)
			return errors[id];
		else
			return ERROR_ENTRY(0, "");
	}

	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		ERROR e;

		if (0 < id < ERROR_MAX_ENTRY)
		{
			e = errors[id];
			e.errorPosition.col = col;
			e.errorPosition.line = line;
			return e;
		}
		else
			return ERROR_ENTRY(0, "");
	}
}