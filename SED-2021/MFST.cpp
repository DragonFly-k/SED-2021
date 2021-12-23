#include "MFST.h"

template<class T>T getStackElement(const std::stack<T>& st, size_t element)
{
	using base = std::stack<T>;
	struct acces : base { using base::c; };
	return (st.* & acces::c)[element];
}

namespace MFST
{
	MfstState::MfstState()									 // ����������� �� ���������
	{
		lenta_position = 0;									 //������� �� �����
		nrule = -1;											 //����� �������� �������
		nrulechain = -1;									 //����� ������� �������
	}

	MfstState::MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain)	//����������� (������� �� �����, ���� ��������, ����� ������� ������� � �������� �������)
	{
		lenta_position = pposition;						//������� �� �����
		st = pst;										//���� ��������
		nrulechain = pnrulechain;						//����� �������� ������� � �������
	}

	MfstState::MfstState(short pposition, MFSTSTSTACK pst, short pnrule, short pnrulechain)
	{						//����������� (������� �� �����, ���� ��������,����� �������� �������, ����� ������� �������)
		lenta_position = pposition;						//������� � �����
		st = pst;										//���� ��������
		nrule = pnrule;									//����� �������� �������
		nrulechain = pnrulechain;						//����� ������� �������
	}

	Mfst::MfstDiagnosis::MfstDiagnosis()
	{
		lenta_position = -1;
		rc_step = SURPRISE;
		nrule = -1;
		nrule_chain = -1;
	}

	Mfst::MfstDiagnosis::MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain)  //�����������
	{						    //(������� �� �����, ��� ���������� ����, ����� �������, ����� ������� �������)
		lenta_position = plenta_position;		//������� �� �����
		rc_step = prc_step;						//��� ���������� ����
		nrule = pnrule;							//����� �������
		nrule_chain = pnrule_chain;				//����� ������� �������
	}

	Mfst::Mfst() { lenta = 0; lenta_size = lenta_position = 0; }		  //����������� �� ��������� 

	Mfst::Mfst(Lex::Tables plex, GRB::Greibach pgrebach)				  //(��������� ������ ������������ �����������, ���������� �������)
	{
		grebach = pgrebach;												   //�������
		Lex = plex;														   //��� ������ ���� �����������
		lenta = new short[lenta_size = Lex.lexTable.size];				   //������ ����� = ������� ������ ������� ������
		using namespace GRB;
		for (int k = 0; k < lenta_size; ++k)							   //������� � ����� ���������
			lenta[k] = TS(Lex.lexTable.table[k].lexema);
		lenta_position = 0;
		st.push(grebach.stbottomT);											//��������� ��� �����
		st.push(grebach.startN);											//��������� ��������� ������
		nrulechain = -1;													//���������� ������� ����� -1
	}

	Mfst::RC_STEP Mfst::step(Log::LOG log)	//��������� ��� ��������
	{
		RC_STEP rc = SURPRISE;			//��� �������� = ������ ��������
		if (lenta_position < lenta_size)
		{
			if (ISNS(st.top()))							  //��������� ��������� ������� ����� � ��������� ���������� �� ��
			{
				GRB::Rule rule;
				if ((nrule = grebach.getRule(st.top(), rule)) >= 0)	 //�������, ���� ����� ������� ���� ��� ������, ���� ��� �� ����
				{
					GRB::Rule::Chain chain;
					if ((nrulechain = rule.getNextChain(lenta[lenta_position], chain, nrulechain + 1)) >= 0)
					{									   //�������� ��������� ������� � ������� � �����, ���� ���������� -1
						char lbuf[256];
						char rbuf[256];
						char sbuf[256];
						MFST_TRACE1(log)						   //�����
							savestate(log);				   //��������� ��������� ��������
						st.pop();						   //��������� �������� �����.
						push_chain(chain);				   //��������� ������� ������� � ����
						rc = NS_OK;						//������� ������� � �������... ������� �������� � ����
						MFST_TRACE2(log)					  //�����
					}
					else
					{
						MFST_TRACE4("TNS_NORULECHAIN/NS_NORULE", log);	  //�����
						savediagnosis(NS_NORULECHAIN);				//��� ����������
						rc = restate(log) ? NS_NORULECHAIN : NS_NORULE; //������������ ��������� ��������
					}
				}
				else rc = NS_ERROR;				   //����������� �������������� ������ ����������
			}
			else if ((st.top() == lenta[lenta_position]))	  //���� ������� ������ ����� ����� ������� �����
			{
				++lenta_position;							//���������� �����
				st.pop();								   //������� �����
				nrulechain = -1;						  //����� �������� ������� ����� -1
				rc = TS_OK;
				char sbuf[256], lbuf[256];
				MFST_TRACE3(log)
			}
			else
			{
				MFST_TRACE4("TS_NOK/NS_NORULECHAIN", log);
				rc = restate(log) ? TS_NOK : NS_NORULECHAIN;
			}
		}
		else
		{
			rc = LENTA_END;
			MFST_TRACE4("LENTA_END", log);
		}
		return rc;
	}

	bool Mfst::push_chain(GRB::Rule::Chain chain)		 //��������� ������� ������� � ���� (������� �������)
	{
		for (int k = chain.size - 1; k >= 0; --k)			//� = ������ �������-1. ������� ������� � ����
			st.push(chain.nt[k]);
		return true;
	}

	bool Mfst::savestate(Log::LOG log)								   //��������� ��������� ��������
	{
		storestate.push(MfstState(lenta_position, st, nrule, nrulechain)); //���� ��� ���������� ���������. ������� ����������� ���������
		MFST_TRACE6("SAVESTATE:", storestate.size(), log);
		return true;
	}

	bool Mfst::restate(Log::LOG log)							//������������ ��������� ��������
	{
		bool rc = false;
		MfstState state;
		if (rc = (storestate.size() > 0))
		{
			state = storestate.top();
			lenta_position = state.lenta_position;
			st = state.st;
			nrule = state.nrule;
			nrulechain = state.nrulechain;
			storestate.pop();
			MFST_TRACE5("RESTATE", log);
			char rbuf[256], lbuf[256], sbuf[256];
			MFST_TRACE2(log)
		}
		return rc;
	}

	bool Mfst::savediagnosis(RC_STEP prc_step)
	{
		bool rc = false;
		short k = 0;
		while (k < MFST_DIAGN_NUMBER && lenta_position <= diagnosis[k].lenta_position) ++k;
		if (rc = (k < MFST_DIAGN_NUMBER))
		{
			diagnosis[k] = MfstDiagnosis(lenta_position, prc_step, nrule, nrulechain);
			for (short j = k + 1; j < MFST_DIAGN_NUMBER; ++j)
				diagnosis[j].lenta_position = -1;
		}
		return rc;
	}

	bool Mfst::start(Log::LOG log)
	{
		bool rc = false;
		RC_STEP rc_step = SURPRISE;
		char buf[MFST_DIAGN_MAXSIZE];
		rc_step = step(log);
		while (rc_step == NS_OK || rc_step == NS_NORULECHAIN || rc_step == TS_OK || rc_step == TS_NOK)
			rc_step = step(log);
		switch (rc_step)
		{
		case LENTA_END:
			MFST_TRACE4("------->LENTA_END", log);
			*(log.stream) << std::setfill('-') << std::setw(100) << ' ' << std::setfill(' ') << std::endl;
			sprintf_s(buf, MFST_DIAGN_MAXSIZE, "%d: ����� ����� %d, �������������� ������ �������� ��� ������", 0, lenta_size);
			*(log.stream) << buf << std::endl;
			rc = true;
			break;
		case NS_NORULE:
			MFST_TRACE4("------>NS_NORULE", log);
			*(log.stream) << std::setfill('-') << std::setw(100) << ' ' << std::setfill(' ') << std::endl;
			throw getDiagnosis(buf);
			break;
		case NS_NORULECHAIN:
			MFST_TRACE4("------>NS_NORULENORULECHAIN", log);
			break;
		case NS_ERROR:
			MFST_TRACE4("------>NS_ERROR", log);
			break;
		case SURPRISE:
			MFST_TRACE4("------>SURPRISE", log);
			break;
		}
		return rc;
	}

	char* Mfst::getCSt(char* buf)	//��������� ����� ���������� ����� ��� �����������
	{
		for (int k = (signed)st.size() - 1; k >= 0; --k)
		{
			short p = getStackElement(st, k);
			buf[st.size() - 1 - k] = GRB::Rule::Chain::alphabet_to_char(p);
		}
		buf[st.size()] = 0x00;
		return buf;
	}

	char* Mfst::getCLenta(char* buf, short pos, short n)	//��������� ����� ���������� ����� � �������� ������� �������� ���������� ��������  ��� �����������,
	{
		short i, k = (pos + n < lenta_size) ? pos + n : lenta_size;
		for (i = pos; i < k; ++i)
			buf[i - pos] = GRB::Rule::Chain::alphabet_to_char(lenta[i]);
		buf[i - pos] = 0x00;
		return buf;
	}

	char* Mfst::getDiagnosis(char* buf)
	{
		char* temp = new char[300];
		temp[0] = '\0';
		int errid = 0;
		int lpos = -1;
		for (int i = 0; i < 3; i++)
		{
			if (i < MFST_DIAGN_NUMBER && (lpos = diagnosis[i].lenta_position) >= 0)
			{
				errid = grebach.getRule(diagnosis[i].nrule).iderror;
				Error::ERROR err = Error::geterror(errid);
				sprintf_s(buf, MFST_DIAGN_MAXSIZE, "������ %d : %s\n ������ %d \t  ������� %d\n", err.id, err.message, Lex.lexTable.table[lpos].sn, Lex.lexTable.table[lpos].posInStr);
				strcat_s(temp, 300, buf);
			}
		}
		return temp;
	}

	void Mfst::printrules(Log::LOG& log)
	{
		MfstState state;
		GRB::Rule rule;
		for (unsigned short k = 0; k < storestate.size(); ++k)
		{
			state = getStackElement(storestate, k);
			rule = grebach.getRule(state.nrule);
			char rbuf[256];
			MFST_TRACE7(log)
		}
	}

	bool Mfst::savededucation()
	{
		MfstState state;
		GRB::Rule rule;
		deducation.nrules = new short[deducation.size = storestate.size()];
		deducation.nrulechains = new short[deducation.size];
		for (unsigned short k = 0; k < storestate.size(); ++k)
		{
			state = getStackElement(storestate, k);
			deducation.nrules[k] = state.nrule;
			deducation.nrulechains[k] = state.nrulechain;
		}
		return true;
	}
};