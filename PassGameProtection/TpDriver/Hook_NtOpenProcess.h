#ifndef __HOOK_NTOPENPROCESS_H__
#define __HOOK_NTOPENPROCESS_H__

#include "GlobalFunction.h"
//�Զ���NtOpenProcess InLine Hook����ת��ַ
ULONG g_NtOpenProcessJmpAddr;
//ԭ��ObOpenObjectByPointer��ַ
ULONG g_OriginPointAddr;

#pragma PAGECODE
__declspec(naked) NTSTATUS __stdcall MyNtOpenProcess_Win7(
	PHANDLE ProcessHandle,
	ACCESS_MASK DesiredAccess,
	POBJECT_ATTRIBUTES ObjectAttributes,
	PCLIENT_ID ClientId) 
{
	_asm
	{
		push dword ptr [ebp-0F4h]
		push dword ptr [ebp-0F0h]
		push g_NtOpenProcessJmpAddr
		jmp g_OriginPointAddr
	}
}

#pragma PAGECODE
VOID HookNtOpenProcess_Win7()
{
//  NtOpenProcess------------------------------------------------------------
// 	840199f8 ff75fc          push    dword ptr [ebp-4]
// 	840199fb ff75fc          push    dword ptr [ebp-4]
// 	840199fe ff750c          push    dword ptr [ebp+0Ch]
// 	84019a01 ff7508          push    dword ptr [ebp+8]
// 	84019a04 e863440600      call    nt!PsRevertThreadToSelf+0x6bb (8407de6c)

//	PsOpenProcess-------------------------------------------------------------
//	00017068 f9906800 d5e883e5 8bffe07c
// 	8407e075 8d85fcfeffff    lea     eax,[ebp-104h]
// 	8407e07b 50              push    eax
// 	8407e07c ff7514          push    dword ptr [ebp+14h]
// 	8407e07f ff352c00f783    push    dword ptr [nt!PsProcessType (83f7002c)]
// 	8407e085 53              push    ebx
// 	8407e086 8d8580feffff    lea     eax,[ebp-180h]
// 	8407e08c 50              push    eax
// 	8407e08d ffb50cffffff    push    dword ptr [ebp-0F4h]
// 	8407e093 ffb510ffffff    push    dword ptr [ebp-0F0h]
//	8407e099 e8c655fdff      call    nt!ObOpenObjectByPointer (84053664)-----HOOK��λ��

	//ObOpenObjectByPointerƫ������0x22D
	//8407de6c - 840199dc = 0x64490
	//������
	char pCode[] = 
	{
		(char)0xff, (char)0xb5,	(char)0x0c, 
		(char)0xff, (char)0xff, (char)0xff, 
		(char)0xff, (char)0xb5, (char)0x10, 
		(char)0xff, (char)0xff, (char)0xff,	(char)0xe8
	};
	//�����볤��
	SIZE_T nLen = sizeof(pCode);
	//��ȡԭ��PsOpenProcess��ַ
	ULONG uOriginPsOpenProcessAddr = GetServiceOldAddr(L"PsRevertThreadToSelf") + 0x6bb;
	KdPrint(("PsOpenProcess��ַ:%x\n",uOriginPsOpenProcessAddr));
	//��ȡԭ��ObOpenObjectByPointer��ַ
	g_OriginPointAddr = GetServiceOldAddr(L"ObOpenObjectByPointer");
	//������������HOOK����ʼ��ַ
	ULONG uMyHookedNtOpenProcessAddr = SearchCode(uOriginPsOpenProcessAddr, pCode, nLen) - nLen;
	KdPrint(("HOOK����ʼ��ַ:%x\n",uMyHookedNtOpenProcessAddr));
	//������Զ���InLine Hook����ת��ַ
	g_NtOpenProcessJmpAddr = uMyHookedNtOpenProcessAddr + nLen + 4;
	KdPrint(("�Զ���InLine Hook����ת��ַ:%x\n",g_NtOpenProcessJmpAddr));
	//�����TP InLine Hook����ת��ַ
	ULONG uTPHookedNtOpenProcessJmpAddr = uMyHookedNtOpenProcessAddr + nLen - 1;
	KdPrint(("TP InLine Hook����ת��ַ:%x\n",uTPHookedNtOpenProcessJmpAddr));

	WPON();
	__asm
	{
		mov ebx,uMyHookedNtOpenProcessAddr
		mov byte ptr [ebx+0],0xE9
		lea eax,MyNtOpenProcess_Win7
		sub eax,uMyHookedNtOpenProcessAddr
		sub eax,5			//win7�²�һ����5��������
		mov [ebx+1],eax
	}
	WPOFF();
}

#pragma PAGECODE
VOID UnHookNtOpenProcess_Win7()
{
	WPON();	
	//UnHook

	WPOFF();
}

#endif