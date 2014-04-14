#ifndef __GLOBALFUNCTION_H__
#define __GLOBALFUNCTION_H__

#include "DriverHead.h"

VOID WPON()
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

VOID WPOFF()
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

//����������Ѱ�ҵ�ַ
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

//ͨ�����ƻ��SSDT����ԭʼ��ַ
ULONG GetServiceOldAddr(PCWSTR FunName)
{
	UNICODE_STRING _FunName;
	RtlInitUnicodeString(&_FunName,FunName);
	return (ULONG)MmGetSystemRoutineAddress(&_FunName);
}

//�жϽ�������
extern"C" __declspec(dllimport) UCHAR* PsGetProcessImageFileName(IN PEPROCESS Process);
bool CheckProcessName(char* szName)
{
	//��ȡ��ǰ����
	PEPROCESS nEProcess = PsGetCurrentProcess();
	//��ȡ��������
	char* szProessaName = (char*)PsGetProcessImageFileName(nEProcess);
	//�ȽϽ�����
	if(strcmp(szProessaName,szName)==0)
	{		
		return true;
	}

	return false;
}

//��ȡCALL����ĵ�ַ--��ʱ�򲢲�����
ULONG GetCallAddr(ULONG nCallAddr)
{
	return (*((ULONG*)nCallAddr) + nCallAddr + 4);
}

//HOOK Call�ĵ�ַ
VOID CallHook(ULONG uFuncAddr, ULONG uCallAddr)
{
	ULONG nJmpAddr=uFuncAddr - uCallAddr - 4;
	WPON();
	__asm
	{
		mov eax,uCallAddr
		mov ebx,nJmpAddr
		mov dword ptr ds:[eax],ebx
	}
	WPOFF();
}

#endif