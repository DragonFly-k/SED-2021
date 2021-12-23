#pragma once
#define ID_MAXSIZE		9				//������������ ���������� ������� � ��������������
#define TI_MAXSIZE		1024			// ������������ ���������� ��-�� � ������� ��������������� 
#define TI_INT_DEFAULT	0x0000	        // �������� �� ��������� ��� ���� integer 
#define TI_STR_DEFAULT	0x0			// �������� �� ��������� ��� ���� string 
#define TI_NULLIDX		-1   			// ��� �������� ������� ���������������
#define TI_STR_MAXSIZE	255
#define TI_BLOCK_DEFAULT "EXTERN"
#define TI_BLOCK_MAIN	"START"

namespace IT	// ������� �������������
{
	enum IDDATATYPE { DEF = 0, INT = 1, STR = 2};
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, A = 5 };		//���� ���������������: ����������, �������, ��������, �������
	struct Entry	//������ ������� ���������������
	{
		char parrentBlock[ID_MAXSIZE + 1];
		int			idxfirstLE;		//������ ������ ������ � ������� ������
		char		id[2 * ID_MAXSIZE];		//������������� (������������� ��������� �� ID_MAXSIZE)
		IDDATATYPE  iddatatype;		//��� ������
		IDTYPE		idtype;		//��� ��������������
		struct VALUE
		{
			int vint = NULL;	//�������� integer 
			struct
			{
				int len;	//���-�� �������� � string
				char str[TI_STR_MAXSIZE];	//������� string
			} vstr;		//�������� string
		} value;
	};

	struct IdTable		//��������� ������� ���������������
	{
		int maxsize;	//������� ������� ��������������� < TI_MAXSIZE
		int size;	//������� ������ ������� ��������������� < maxsize
		Entry* table;	//������ ����� ������� ���������������
	};

	IdTable Create(		//������� ������� ���������������
		int size		//������� ������� ��������������� < TI_MAXSIZE
	);

	void Add(	//�������� ������ � ������� ���������������
		IdTable& idtable,	//��������� ������� ���������������
		Entry entry		//������ ������� ���������������
	);

	int IsId(	//�������: ����� ������ (���� ����), TI_NULLIDX(���� ���)
		IdTable& idtable,	//��������� ������� ���������������
		char id[ID_MAXSIZE],		//�������������
		char block[ID_MAXSIZE]
	);

	int IsId(IdTable& idtable, char* block, IDDATATYPE type, char* literal);
	int IsId(IdTable& idtable, char* id);
	void ShowTable(IdTable* idtable, const wchar_t* in);
	void Delete(IdTable& idtable);		//������� ������� ������ (���������� ������)
	Entry GetEntry(IdTable& idtable, int n);
}
