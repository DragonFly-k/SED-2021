#pragma once
#include "stdafx.h"

#define	HEAD ".586\n.model flat, stdcall\nincludelib libucrt.lib\nincludelib kernel32.lib\nincludelib \"D:\\лабы\\€п\\курсач\\SED-2021\\Debug\\SED2021Lib.lib\"\nExitProcess PROTO : DWORD"

#define LIBPROTOS "\nWriteW PROTO: SDWORD\nWriteN PROTO: DWORD\nstringLen PROTO: DWORD\nStrConcat PROTO: DWORD, :DWORD\n.stack 4096"

#define CONST "\n.CONST\nnull_division BYTE \'ERROR: DIVISION BY ZERO\', 0\n"

#define END \
"\n\tcall ExitProcess"\
"\nSMTH:"\
"\n\tpush offset null_division"\
"\n\tcall WriteW"\
"\n\tjmp konec"\
"\nkonec:"\
"\n\tpush -1"\
"\n\tcall ExitProcess"\
"\nmain ENDP\nend main"

namespace Generation
{
	void CodeGeneration(Lex::Tables& tables);
}