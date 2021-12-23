#pragma once
#define	LT_MAXSIZE			1024		// максимальное количество эл-ов в таблице лексем	
#define	LT_TI_NULLXDX		0xffffffff  // нет элемента таблицы идентификаторов				
#define	LEX_REAL        	'n'			// лексема дл€ real
#define	LEX_CHAR			'w'			// лексема дл€ char
#define	LEX_TYPE			't'			// лексема дл€ типов
#define	LEX_ID				'i'			// лексема дл€ идентификатора
#define	LEX_LITERAL			'l'			// лексема дл€ литерала
#define	LEX_DEF		    	'p'			// лексема дл€ def
#define	LEX_CREATE			'c'			// лексема дл€ create
#define	LEX_OUT				'o'			// лексема дл€ out
#define	LEX_WRITE		    'r'			// лексема дл€ write
#define	LEX_START			'e'			// лексема дл€ главной функции
#define	LEX_IF				'm'			// лексема дл€ условного оператора
#define	LEX_ELSE			'a'			// лексема дл€ условного оператора (2)
#define	LEX_STRLEN			's'			// лексема дл€ библиотечной функции
#define	LEX_CONCAT  	    'x'			// лексема дл€ библиотечной функции
#define	LEX_OPEN_DEF		'['			// лексема дл€ открывающкй процедурной скобки
#define	LEX_CLOSE_DEF		']'			// лексема дл€ закрывающей процедурной скобки
#define	LEX_ARITHMETIC		'v'			// лексема дл€ арифметических знаков
#define	LEX_SEMICOLON		';'			// лексема дл€ ;
#define	LEX_COMMA			','			// лексема дл€ ,
#define	LEX_LEFTBRACE		'{'			// лексема дл€ {
#define	LEX_RIGHTBRACE		'}'			// лексема дл€ }
#define	LEX_LEFTHESIS		'('			// лексема дл€ (
#define	LEX_RIGHTHESIS		')'			// лексема дл€ )
#define	LEX_PLUS			'+'			// лексема дл€ +
#define	LEX_MINUS			'-'			// лексема дл€ -
#define	LEX_STAR			'*'			// лексема дл€ *
#define	LEX_DIRSLASH		'/'			// лексема дл€ /
#define	LEX_MODULO			'%'			// лексема дл€ делени€ по модулю
#define	LEX_EQUAL_SIGN		'='			// лексема дл€ =
#define LEX_LESS			'<'			// лексема дл€ <
#define LEX_MORE			'>'			// лексема дл€ >
#define LEX_OPERSEQUAL		'&'			// лексема дл€ дл€ ==
#define LEX_OPERSNOTEQUAL	'!'			// лексема дл€ дл€ !=

namespace LT
{
	struct Entry	//строка таблицы лексем
	{
		char lexema;	//лексема
		int sn;			//номер строки в исходном тексте
		int idxTI;		//индекс в таблице идентификаторов или LT_TI_NULLIDX
		int posInStr;
	};

	struct LexTable		//экземпл€р таблицы лексем
	{
		int maxsize;	//емкость таблицы лексем < LT_MAXSIZE
		int size;		//текущий размер таблицы лексем < maxsize
		Entry* table;	//массив строк таблицы лексем
		void writeLT(const wchar_t* in);
		void writePBNLT(const wchar_t* in);
	};

	LexTable Create(	//создать таблицу лексем
		int size	//емкость таблицы лексем < LT_MAXSIZE
	);
	void Add(	//добавить строку в таблицу лексем
		LexTable& lextable,		//экземпл€р таблицы лексем
		Entry entry		//строка таблицы лексем
	);

	Entry GetEntry(		//получить строку таблицы лексем
		LexTable& lextable,		//экземпл€р таблицы лексем
		int n		//номер получаемой строки
	);

	void Delete(LexTable& lextable);	//удалить таблицу лексем (освободить пам€ть)
}
