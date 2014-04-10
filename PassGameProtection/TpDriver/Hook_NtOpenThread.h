#ifndef __HOOK_NTOPENTHREAD_H__
#define __HOOK_NTOPENTHREAD_H__

#include "GlobalFunction.h"

//�Զ���NtOpenThread InLine Hook����ת��ַ
ULONG g_NtOpenThreadJmpAddr;
#pragma PAGECODE
__declspec(naked) NTSTATUS __stdcall MyNtOpenThread_Win7()
{
	_asm
	{
		push dword ptr [ebp-0F0h]
		push dword ptr [ebp-0ECh]
		push g_NtOpenThreadJmpAddr
		jmp g_OriginPointAddr
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
	KdPrint(("PsOpenProcess��ַ:%x\n",uOriginPsOpenThreadAddr));
	//������������HOOK����ʼ��ַ
	ULONG uMyHookedNtOpenThreadAddr = SearchCode(uOriginPsOpenThreadAddr, pCode, nLen) - nLen;
	KdPrint(("HOOK����ʼ��ַ:%x\n",uMyHookedNtOpenThreadAddr));
	//������Զ���InLine Hook����ת��ַ
	g_NtOpenThreadJmpAddr = uMyHookedNtOpenThreadAddr + nLen + 4;
	KdPrint(("�Զ���InLine Hook����ת��ַ:%x\n",g_NtOpenThreadJmpAddr));

	WPON();
	__asm
	{
		mov ebx,uMyHookedNtOpenThreadAddr
		mov byte ptr [ebx+0],0xE9
		lea eax,MyNtOpenThread_Win7
		sub eax,uMyHookedNtOpenThreadAddr
		sub eax,5			//win7�²�һ����5��������
		mov [ebx+1],eax
	}
	WPOFF();
}

#pragma PAGECODE
VOID UnHookNtOpenThread_Win7()
{

}

#endif