#ifndef __HOOK_NTOPENTHREAD_H__
#define __HOOK_NTOPENTHREAD_H__

#include "GlobalFunction.h"

//�Զ���NtOpenThread InLine Hook����ת��ַ
ULONG g_NtOpenThreadJmpAddr;
//������������HOOK����ʼ��ַ
ULONG g_MyHookedNtOpenThreadAddr;
#pragma PAGECODE
__declspec(naked) NTSTATUS __stdcall MyNtOpenThread_Win7()
{
	_asm
	{
		push dword ptr [ebp-0F0h]
		push dword ptr [ebp-0ECh]
		call g_OriginPointAddr
		jmp g_NtOpenThreadJmpAddr
	}
}

#pragma PAGECODE
VOID HookNtOpenThread_Win7()
{
// 	8409fd0d ffb510ffffff    push    dword ptr [ebp-0F0h]
// 	8409fd13 ffb514ffffff    push    dword ptr [ebp-0ECh]
// 	8409fd19 e846d9feff      call    nt!ObOpenObjectByPointer (8408d664)
	char pCode[] = 
	{
		(char)0xff, (char)0xb5,	(char)0x10, 
		(char)0xff, (char)0xff, (char)0xff, 
		(char)0xff, (char)0xb5, (char)0x14, 
		(char)0xff, (char)0xff, (char)0xff,	(char)0xe8
	};
	//�����볤��
	SIZE_T nLen = sizeof(pCode);
	//��ȡԭ��PsOpenThread��ַ
	ULONG uOriginPsOpenThreadAddr = GetServiceOldAddr(L"PsOpenThread");
	//KdPrint(("PsOpenProcess��ַ:%x\n",uOriginPsOpenThreadAddr));
	//������������HOOK����ʼ��ַ
	g_MyHookedNtOpenThreadAddr = SearchCode(uOriginPsOpenThreadAddr, pCode, nLen) - nLen;
	//KdPrint(("HOOK����ʼ��ַ:%x\n",g_MyHookedNtOpenThreadAddr));
	//������Զ���InLine Hook����ת��ַ
	g_NtOpenThreadJmpAddr = g_MyHookedNtOpenThreadAddr + nLen + 4;
	//KdPrint(("�Զ���InLine Hook����ת��ַ:%x\n",g_NtOpenThreadJmpAddr));

	int nJmpAddr = (int)MyNtOpenThread_Win7 - g_MyHookedNtOpenThreadAddr - 5;
	WPON();
	__asm
	{
		mov eax,g_MyHookedNtOpenThreadAddr
		mov byte ptr [eax],0xE9
		mov ebx,nJmpAddr	
		mov dword ptr [eax+1],ebx
	}
	WPOFF();
}

#pragma PAGECODE
VOID UnHookNtOpenThread_Win7()
{
	char pCode[] = 
	{
		(char)0xff, (char)0xb5,	(char)0x10, 
		(char)0xff, (char)0xff, (char)0xff, 
		(char)0xff, (char)0xb5, (char)0x14, 
		(char)0xff, (char)0xff, (char)0xff,	(char)0xe8
	};
	WPON();
	RtlMoveMemory((char*)g_MyHookedNtOpenThreadAddr, pCode, 5);
	WPOFF();
}

#endif