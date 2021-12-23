#pragma once
#define	LT_MAXSIZE			1024		// ������������ ���������� ��-�� � ������� ������	
#define	LT_TI_NULLXDX		0xffffffff  // ��� �������� ������� ���������������				
#define	LEX_REAL        	'n'			// ������� ��� real
#define	LEX_CHAR			'w'			// ������� ��� char
#define	LEX_TYPE			't'			// ������� ��� �����
#define	LEX_ID				'i'			// ������� ��� ��������������
#define	LEX_LITERAL			'l'			// ������� ��� ��������
#define	LEX_DEF		    	'p'			// ������� ��� def
#define	LEX_CREATE			'c'			// ������� ��� create
#define	LEX_OUT				'o'			// ������� ��� out
#define	LEX_WRITE		    'r'			// ������� ��� write
#define	LEX_START			'e'			// ������� ��� ������� �������
#define	LEX_IF				'm'			// ������� ��� ��������� ���������
#define	LEX_ELSE			'a'			// ������� ��� ��������� ��������� (2)
#define	LEX_STRLEN			's'			// ������� ��� ������������ �������
#define	LEX_CONCAT  	    'x'			// ������� ��� ������������ �������
#define	LEX_OPEN_DEF		'['			// ������� ��� ����������� ����������� ������
#define	LEX_CLOSE_DEF		']'			// ������� ��� ����������� ����������� ������
#define	LEX_ARITHMETIC		'v'			// ������� ��� �������������� ������
#define	LEX_SEMICOLON		';'			// ������� ��� ;
#define	LEX_COMMA			','			// ������� ��� ,
#define	LEX_LEFTBRACE		'{'			// ������� ��� {
#define	LEX_RIGHTBRACE		'}'			// ������� ��� }
#define	LEX_LEFTHESIS		'('			// ������� ��� (
#define	LEX_RIGHTHESIS		')'			// ������� ��� )
#define	LEX_PLUS			'+'			// ������� ��� +
#define	LEX_MINUS			'-'			// ������� ��� -
#define	LEX_STAR			'*'			// ������� ��� *
#define	LEX_DIRSLASH		'/'			// ������� ��� /
#define	LEX_MODULO			'%'			// ������� ��� ������� �� ������
#define	LEX_EQUAL_SIGN		'='			// ������� ��� =
#define LEX_LESS			'<'			// ������� ��� <
#define LEX_MORE			'>'			// ������� ��� >
#define LEX_OPERSEQUAL		'&'			// ������� ��� ��� ==
#define LEX_OPERSNOTEQUAL	'!'			// ������� ��� ��� !=

namespace LT
{
	struct Entry	//������ ������� ������
	{
		char lexema;	//�������
		int sn;			//����� ������ � �������� ������
		int idxTI;		//������ � ������� ��������������� ��� LT_TI_NULLIDX
		int posInStr;
	};

	struct LexTable		//��������� ������� ������
	{
		int maxsize;	//������� ������� ������ < LT_MAXSIZE
		int size;		//������� ������ ������� ������ < maxsize
		Entry* table;	//������ ����� ������� ������
		void writeLT(const wchar_t* in);
		void writePBNLT(const wchar_t* in);
	};

	LexTable Create(	//������� ������� ������
		int size	//������� ������� ������ < LT_MAXSIZE
	);
	void Add(	//�������� ������ � ������� ������
		LexTable& lextable,		//��������� ������� ������
		Entry entry		//������ ������� ������
	);

	Entry GetEntry(		//�������� ������ ������� ������
		LexTable& lextable,		//��������� ������� ������
		int n		//����� ���������� ������
	);

	void Delete(LexTable& lextable);	//������� ������� ������ (���������� ������)
}
