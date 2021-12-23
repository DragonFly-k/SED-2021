#include "stdafx.h"
using namespace std;

int wmain(int argc, wchar_t* argv[])
{
	Log::LOG log = Log::INITLOG;
	setlocale(LC_ALL, "Russian");
	Parm::PARM parm;
	try
	{
		parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		In::IN in = In::getin(parm.in);
		Log::WriteLine(log, "SED2021: ", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		Log::WriteIn(log, in);
		Lex::Words* tokens = Lex::DivisionIntoTokens(in);
		Lex::Tables lex = Lex::LexAnalysis(tokens);							
		log = Log::getlog(parm.out);
		MFST_TRACE_START(log);
		MFST::Mfst mfst(lex, GRB::getGreibach());
		mfst.start(log);
		mfst.savededucation();
		mfst.printrules(log);
		Log::Close(log);
		Semantic::SemanticAnalysis(&lex);
		lex.lexTable.writeLT(parm.in);
		PN::PolishNotation(lex);
		Generation::CodeGeneration(lex);
		IT::ShowTable(&lex.idenTable, parm.in);
		lex.lexTable.writePBNLT(parm.in);
		LT::Delete(lex.lexTable);
		IT::Delete(lex.idenTable);
	}
	catch (Error::ERROR e)
	{
		if (e.id != 100)
		{
			log = Log::getlog(parm.log);
			Log::WriteError(log, e);
			Log::Close(log);
		}
		else
		{
			cout << "Ошибка!" << endl;
			cout << e.message << endl;
		}
	}
	catch (char* e)
	{
		Log::Close(log);
		log = Log::getlog(parm.log);
		Log::WriteError(log, e);
		Log::Close(log);
	}
	system("pause");
	return 0;
}