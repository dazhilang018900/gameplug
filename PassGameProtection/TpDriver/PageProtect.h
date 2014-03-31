#ifndef __PAGE_PROTECT_H__
#define __PAGE_PROTECT_H__

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


#endif