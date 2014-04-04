#ifndef __GLOBALFUNCTION_H__
#define __GLOBALFUNCTION_H__

#include "DriverHead.h"

VOID RemovePageProtect()
{
	//ȥ������
	_asm
	{
		cli
		mov eax,cr0
		and eax, not 10000h
		mov cr0,eax
	}
}

VOID ResetPageProtect()
{
	//��ԭ����
	__asm
	{
		mov eax,cr0
		or eax,10000h
		mov cr0,eax
		sti
	}
}

//����������->Ѱ�ҵ�ַ
ULONG SearchCode(int StartingAddr,char* pCode,int Length)
{
	char Destination[256]="";
	int i=5000;
	while (i--)
	{
		RtlMoveMemory(Destination,(char*)StartingAddr,Length);
		if (RtlCompareMemory(pCode,Destination,Length)==Length)
		{
			return StartingAddr+Length;
		}
		StartingAddr++;
	}
	return 0;
}

//���SSDT����ԭʼ��ַ
ULONG GetServiceOldAddr(PCWSTR FunName)
{
	UNICODE_STRING _FunName;
	RtlInitUnicodeString(&_FunName,FunName);
	return (ULONG)MmGetSystemRoutineAddress(&_FunName);
}

#endif