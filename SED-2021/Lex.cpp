#include "stdafx.h"
#include "Lex.h"
#include <stack>
namespace Lex
{
	stack<char*> parrentBlock;
	bool isPar = false;
	bool mainIsDeclared = false;
	int countLiteral = 0;

	Words* DivisionIntoTokens(In::IN text)
	{
		Words* tokens = new Words();
		Word entry;
		char buff[IN_MAX_LEN_TEXT];
		int posInBuff = 0;
		int line = 0;

		for (int i = 0, posInLine = 0; i < text.size; posInLine++)
		{
			switch (text.code[text.text[i]])
			{
			case In::IN::T:
			{
				while (text.code[text.text[i]] == In::IN::T)buff[posInBuff++] = text.text[i++];
				ADDWORD
				break;
			}
			case In::IN::S: 
			{
				if (text.text[i++] == IN_CODE_ENDL)
				{
					line++; posInLine = 0; 
				}
				break; 
			}
			case In::IN::B:
			case In::IN::V:
			{
				buff[posInBuff++] = text.text[i++];
				ADDWORD
				break;
			}
			case In::IN::Q:
			{
				buff[posInBuff++] = text.text[i++];
				do
				{
					if (text.code[text.text[i]] == In::IN::E)throw ERROR_THROW_IN(128, line, -1);
					buff[posInBuff++] = text.text[i];
				} while (text.code[text.text[i++]] != In::IN::Q);
				ADDWORD
				break;
			}
			}
		}
		return tokens;
	}

	Tables LexAnalysis(Words* tokens)
	{
		Tables table;
		IT::Entry tempIT;
		parrentBlock.push((char*)TI_BLOCK_DEFAULT);
		table.idenTable = IT::Create(TI_MAXSIZE);
		table.lexTable = LT::Create(TI_MAXSIZE);
		char* lex = (char*)"";
		int tokenCount = tokens->arr.size();

		for (int i = 0; i < tokenCount; i++)
		{
			lex = tokens->arr.front().token;
			char resAn = AnalysisToken(lex, &table);
			if (resAn == '\0')
			{
				if (CheckForIntegerLiteral(tokens))
				{
					bool binar = false;
					if (lex[1] == 'z')binar = true;
					if (binar)
					{
						char buff[20];
						int res = 0;
						int j = 0;
						for (int i = 0; i < strlen(lex) - 2; i++)
							if (lex[strlen(lex) - 1 - i] == '1')
							{
								res += pow(2, i);
								j++;
							}
						char* result = itoa(res, buff, 10);
						int refInID = IT::IsId(table.idenTable, parrentBlock.top(), IT::IDDATATYPE::INT, result);
						LT::Add(table.lexTable, AddLex(LEX_LITERAL, tokens, refInID, &table.idenTable));
						tempIT.idtype = IT::L;
						tempIT.iddatatype = IT::INT;
						if (refInID == TI_NULLIDX)AddID(result, &table, tempIT);
					}
					else
					{
						int refInID = IT::IsId(table.idenTable, parrentBlock.top(), IT::IDDATATYPE::INT, lex);
						LT::Add(table.lexTable, AddLex(LEX_LITERAL, tokens, refInID, &table.idenTable));
						tempIT.idtype = IT::L;
						tempIT.iddatatype = IT::INT;
						if (refInID == TI_NULLIDX)AddID(lex, &table, tempIT);
					}
				}
				else if (CheckForStringLiteral(tokens))
				{
					int refInID = IT::IsId(table.idenTable, parrentBlock.top(), IT::IDDATATYPE::STR, lex);
					LT::Add(table.lexTable, AddLex(LEX_LITERAL, tokens, refInID, &table.idenTable));
					tempIT.idtype = IT::L;
					tempIT.iddatatype = IT::STR;
					if (refInID == TI_NULLIDX)AddID(lex, &table, tempIT);
				}
				else if (CheckId(tokens))
				{
					int refInID = IT::IsId(table.idenTable, lex, parrentBlock.top());
					LT::Add(table.lexTable, AddLex(LEX_ID, tokens, refInID, &table.idenTable));
					if (refInID == TI_NULLIDX)
					{
						if (!(CHECKFORDECLARE) && !isPar && !(LIBFOO))throw ERROR_THROW_IN(126, LINE, SYM);		// ������������� ������������� id
						if (!strcmp(parrentBlock.top(), TI_BLOCK_DEFAULT) && (tempIT.idtype != IT::F || table.lexTable.table[table.lexTable.size - 4].lexema == LEX_CREATE))throw ERROR_THROW_IN(129, LINE, SYM);
						AddID(lex, &table, tempIT);
					}
					else if (CHECKFORDECLARE)throw ERROR_THROW_IN(130, LINE, SYM);		// ��������������� ��������������
				}
			}
			else
			{
				AnalysisItString(&tempIT, resAn, tokens);
				if ((strcmp(lex, "stringLen") == 0) || (strcmp(lex, "StrConcat") == 0))
				{
					int k = IT::IsId(table.idenTable, lex);
					if (k == TI_NULLIDX)
					{
						AddID(lex, &table, tempIT);
						LT::Add(table.lexTable, AddLex(resAn, tokens, table.idenTable.size - 1, &table.idenTable));
					}
					else LT::Add(table.lexTable, AddLex(resAn, tokens, k, &table.idenTable));
				}
				else LT::Add(table.lexTable, AddLex(resAn, tokens, -2, &table.idenTable));
			}
			tokens->arr.pop_front();
		}
		if (!mainIsDeclared)throw ERROR_THROW(124);
		cout << "����������� ������ ��������" << endl;
		return table;
	}

	void AddID(char* token, Tables* tables, IT::Entry tempIT)
	{
		if (isPar)
		{
			if (!(CHECKPARM))throw ERROR_THROW_IN(127, LEXLINE, LEXPOS);		// ������ ���������� ����������
			tempIT.idtype = IT::P;
		}
		if (tempIT.idtype != IT::L) strcpy_s(tempIT.id, token);
		else
		{
			sprintf(tempIT.id, "L%d", countLiteral);
			countLiteral++;
		} 
		tempIT.idxfirstLE = tables->lexTable.size - 1;
		strcpy_s(tempIT.parrentBlock, parrentBlock.top());

		switch (tempIT.iddatatype)
		{
		case IT::STR:
		{
			if (tempIT.idtype != IT::L)
			{
				tempIT.value.vstr.str[0] = TI_STR_DEFAULT;
				tempIT.value.vstr.len = 0;
			}
			else
			{
				strcpy(tempIT.value.vstr.str, token);
				tempIT.value.vstr.len = strlen(token);
			}
			break;
		}
		case IT::INT:
		{
			if (tempIT.idtype != IT::L) tempIT.value.vint = TI_INT_DEFAULT;
			else tempIT.value.vint = atoi(token);
			break;
		}
		}
		IT::Add(tables->idenTable, tempIT);

		if (tempIT.idtype == IT::F && (strcmp(tempIT.id, "stringLen") != 0) && (strcmp(tempIT.id, "StrConcat") != 0))
			parrentBlock.push(tables->idenTable.table[tables->idenTable.size - 1].id);
	}

	char CheckForArithmAndBrack(char* lexem, Tables* tables)
	{
		switch (lexem[0])
		{
		case LEX_OPERSNOTEQUAL:
		case LEX_OPERSEQUAL:
		case LEX_LESS:
		case LEX_MORE:		
		case LEX_EQUAL_SIGN:
		case LEX_OPEN_DEF:
		case LEX_CLOSE_DEF:
		case LEX_COMMA:
		case LEX_LEFTBRACE:
		case LEX_RIGHTBRACE:
			return lexem[0];
		case LEX_SEMICOLON:
		{
			if (tables->lexTable.table[tables->lexTable.size - 1].lexema == LEX_CLOSE_DEF)
			{
				int brBalance = 1;
				for (int i = tables->lexTable.size - 2; i != -1; i--) //�������� �� ��� �������� ������
				{
					switch (tables->lexTable.table[i].lexema)
					{
					case LEX_OPEN_DEF: {brBalance--; break; }
					case LEX_CLOSE_DEF: {brBalance++; break; }
					}
				}
				if (brBalance != 0)throw ERROR_THROW_IN(116, LEXLINE, LEXPOS);		//�������� ���������� ������
				parrentBlock.pop();
			}
			return LEX_SEMICOLON;
		}
		case LEX_MODULO:
		case LEX_PLUS:
		case LEX_MINUS:
		case LEX_STAR:
		case LEX_DIRSLASH:
		{
			IT::Entry tempIT;
			strcpy(tempIT.id, lexem);
			tempIT.idxfirstLE = tables->lexTable.size;
			tempIT.idtype = IT::IDTYPE::A;
			tempIT.iddatatype = IT::IDDATATYPE::INT;
			IT::Add(tables->idenTable, tempIT);
			return LEX_ARITHMETIC;
		}
		case LEX_LEFTHESIS:
		{
			if (CHECKFORPARMS)isPar = true;
			return LEX_LEFTHESIS;
		}
		case LEX_RIGHTHESIS:
		{
			if (isPar)isPar = false;
			return LEX_RIGHTHESIS;
		}
		default: return '\0';
		}
	}

	void AnalysisItString(IT::Entry* tempIT, char& lexem, Words* tokens)
	{
		switch (lexem)
		{
		case LEX_REAL:
		{
			tempIT->iddatatype = IT::INT;
			lexem = LEX_TYPE;
			break;
		}
		case LEX_CHAR:
		{
			tempIT->iddatatype = IT::STR;
			lexem = LEX_TYPE;
			break;
		}
		case LEX_START:
		{
			if (mainIsDeclared)throw ERROR_THROW_IN(125, LINE, SYM);		//�������� �� ������������� ���������� start
			mainIsDeclared = true;
			parrentBlock.push((char*)TI_BLOCK_MAIN);
			strcpy_s(tempIT->parrentBlock, parrentBlock.top());
			break;
		}
		case LEX_DEF:
		{
			tempIT->idtype = IT::IDTYPE::F;
			break;
		}
		case LEX_CREATE:
		{
			tempIT->idtype = IT::IDTYPE::V;
			break;
		}
		case LEX_CONCAT:
		{
			tempIT->idtype = IT::IDTYPE::F;
			strcpy_s(tempIT->parrentBlock, TI_BLOCK_DEFAULT);
			tempIT->iddatatype = IT::IDDATATYPE::STR;
			break;
		}
		case LEX_STRLEN:
		{
			tempIT->idtype = IT::IDTYPE::F;
			strcpy_s(tempIT->parrentBlock, TI_BLOCK_DEFAULT);
			tempIT->iddatatype = IT::IDDATATYPE::INT;
			break;
		}
		default: break;
		}
	}

	char AnalysisToken(char* lex, Tables* tables)
	{
		char resLex[FST_COUNT] = { LEX_CREATE , LEX_REAL, LEX_CHAR, LEX_DEF, LEX_START, LEX_WRITE , LEX_OUT, LEX_IF, LEX_ELSE, LEX_CONCAT, LEX_STRLEN };
		FST::FST tokens[FST_COUNT] = { FST::FST(lex, A_CREATE), FST::FST(lex, A_REAL),FST::FST(lex,A_CHAR), FST::FST(lex, A_DEF), FST::FST(lex, A_START), FST::FST(lex, A_WRITE), FST::FST(lex, A_OUT), FST::FST(lex, A_IF), FST::FST(lex, A_ELSE), FST::FST(lex, A_CONCAT), FST::FST(lex, A_STRLEN)};

		for (int i = 0; i < FST_COUNT; i++)
		if (FST::execute(tokens[i])) return resLex[i];
		return CheckForArithmAndBrack(lex, tables);
	}

	bool CheckForStringLiteral(Words* tokens)
	{
		char* lex = tokens->arr.front().token;
		if (lex[0] == '\'')
		{
			if (strlen(lex) > 100)throw ERROR_THROW_IN(120, LINE, SYM);		//������� ������� �������
			return true;
		}
		return false;
	}

	bool CheckForIntegerLiteral(Words* tokens)
	{
		char* lex = tokens->arr.front().token;
		bool binar = false;
		if (lex[1] == 'z')
			binar = true;

		for (int i = 0; i < strlen(lex); i++)
		{

			if (binar && (lex[i] < '0' || lex[i] > '1'))
			{
				if (i != 1)
				{
					throw ERROR_THROW_IN(123, LINE, SYM);
				}
			}
			else if (lex[i] < '0' || lex[i] > '9')
			{
				return false;
			}
		}
		if ((atoll(lex) > pow(2, 31)) || (atoll(lex) < pow(-2, 31)))throw ERROR_THROW_IN(123, LINE, SYM); // ������� ������� ��������
		return true;
	}

	bool CheckId(Words* tokens)
	{
		char* lex = tokens->arr.front().token;
		int len = strlen(lex);
		if (len > ID_MAXSIZE)throw ERROR_THROW_IN(121, LINE, SYM);							// ������� �������
		for (int i = 0; i < len; i++) 
		{
          if (lex[i] < 'a' || lex[i] > 'z')throw ERROR_THROW_IN(122, LINE, SYM);			// ������ ���������� id
		}		
		return true;
	}

	LT::Entry AddLex(char lex, Words* tokens, int refID, IT::IdTable* idenTable)
	{
		LT::Entry temp;
		temp.lexema = lex;
		temp.sn = LINE;
		temp.posInStr = SYM;

		switch (refID)
		{
		case LT_TI_NULLXDX:
		{
			temp.idxTI = idenTable->size;
			break;
		}
		case -2:
		{
			temp.idxTI = LT_TI_NULLXDX;
			break;
		}
		default:
		{
			temp.idxTI = refID;
			break;
		}
		}
		if (temp.lexema == LEX_ARITHMETIC)temp.idxTI = idenTable->size - 1;
		return temp;
	}
}