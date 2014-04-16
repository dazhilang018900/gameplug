#ifndef __HOOK_NTPROTECTVIRTUALMEMORY_H__
#define __HOOK_NTPROTECTVIRTUALMEMORY_H__

#include "GlobalFunction.h"

ULONG g_OriginNtProtectVirtualMemoryAddr;
ULONG g_NtProtectPushAddr;
//HOOK����ʼ��ַ
ULONG g_MyHookNtProtectVirtualMemoryAddr;

#pragma PAGECODE
__declspec(naked) VOID __stdcall MyNtProtectVirtualMemory()
{
	__asm
	{
		push 0x38
		push g_NtProtectPushAddr
		jmp g_MyHookNtProtectVirtualMemoryAddr
	}
}

#pragma PAGECODE
VOID HookNtProtectVirtualMemory()
{
// 	NtProtectVirtualMemory---SSDT 215=0xD7*4=0x35C
// 	0x8464D403		6A 38			push 38      
// 	0x8464D405		68 482A4684		push 84462A48     
// 	0x8464D40A		E8 99B7E3FF		call 84488BA8    
// 	0x8464D40F		FF75 14			push dword ptr [ebp+14]      
// 	0x8464D412		E8 CAE9E3FF		call 8448BDE1   
	g_OriginNtProtectVirtualMemoryAddr = *((ULONG*)((ULONG)KeServiceDescriptorTable->ServiceTableBase+0x35C));
	KdPrint(("NtReadVirtualMemory=%x\n",g_OriginNtProtectVirtualMemoryAddr));
	//NtProtect�ڶ���push�ĵ�ַ
	g_NtProtectPushAddr = *((ULONG*)(g_OriginNtProtectVirtualMemoryAddr+3));
	KdPrint(("NtRead�ڶ���push�ĵ�ַ=%x\n",g_NtProtectPushAddr));
	//��ת��ַ
	g_MyHookNtProtectVirtualMemoryAddr = g_OriginNtProtectVirtualMemoryAddr + 7;
	KdPrint(("NtReadVirtualMemory��Call�ĵ�ַ=%x\n",g_MyHookNtProtectVirtualMemoryAddr));
	WPON();
	__asm
	{
		mov eax,KeServiceDescriptorTable
		mov eax,[eax]
		add eax,0x35C
		lea ebx,MyNtProtectVirtualMemory
		mov [eax],ebx
	}
	WPOFF();
}

#pragma PAGECODE
VOID UnHookNtProtectVirtualMemory()
{
	WPON();
	__asm
	{
		mov eax,KeServiceDescriptorTable
		mov eax,[eax]
		add eax,0x35C
		mov ebx,g_OriginNtProtectVirtualMemoryAddr
		mov [eax],ebx
	}
	WPOFF();
}

#endif