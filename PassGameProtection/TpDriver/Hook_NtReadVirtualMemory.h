#ifndef __HOOK_NTREADVIRTUALMEMORY_H__
#define __HOOK_NTREADVIRTUALMEMORY_H__

#include "GlobalFunction.h"
ULONG g_OriginNtReadVirtualMemoryAddr;
ULONG g_NtReadPushAddr;
//HOOK的起始地址
ULONG g_MyHookNtReadVirtualMemoryAddr;

#pragma PAGECODE
__declspec(naked) VOID __stdcall MyNtReadVirtualMemory()
{
// 	if (CheckProcessName("DNF.exe") || CheckProcessName("TenSafe_1.exe") || CheckProcessName("Client.exe"))
// 	{
// 		__asm
// 		{
// 			jmp g_OriginNtReadVirtualMemoryAddr
// 		}
// 	}
	_asm
	{
		push 0x18
		push g_NtReadPushAddr
		jmp g_MyHookNtReadVirtualMemoryAddr
	}
}

#pragma PAGECODE
VOID HookNtReadVirtualMemory()
{
// 	nt!NtReadVirtualMemory:  SSDT 399=0x63C---win7

// 	mov eax, A040DF8C
// 	jmp eax
// 	call 8449CBA8

// 	840a182c 6a18            push    18h
// 	840a182e 68287ae983      push    offset nt! ?? ::FNODOBFM::`string'+0x3ea8 (83e97a28)
// 	840a1833 e870e3e1ff      call    nt!_SEH_prolog4 (83ebfba8)
	//HOOK的起始地址
	g_OriginNtReadVirtualMemoryAddr = (ULONG)KeServiceDescriptorTable->ServiceCounterTable+0x63C;
	KdPrint(("NtReadVirtualMemory=%x\n",g_OriginNtReadVirtualMemoryAddr));
	//NtRead第二个push的地址
	g_NtReadPushAddr = *((ULONG*)(g_OriginNtReadVirtualMemoryAddr+3));
	KdPrint(("NtRead第二个push的地址=%x\n",g_NtReadPushAddr));
	//跳转地址
	g_MyHookNtReadVirtualMemoryAddr = g_OriginNtReadVirtualMemoryAddr + 7;
	KdPrint(("NtReadVirtualMemory中Call的地址=%x\n",g_MyHookNtReadVirtualMemoryAddr));
// 	WPON();
// 	__asm
// 	{
// 		mov eax,KeServiceDescriptorTable
// 		mov eax,[eax]
// 		add eax,0x63C
// 		lea ebx,MyNtReadVirtualMemory
// 		mov [eax],ebx
// 	}
// 	WPOFF();
}

#pragma PAGECODE
VOID UnHookNtReadVirtualMemory()
{
// 	WPON();
// 	__asm
// 	{
// 		mov eax,KeServiceDescriptorTable
// 		mov eax,[eax]
// 		add eax,0x63C
// 		mov ebx,g_OriginNtReadVirtualMemoryAddr
// 		mov [eax],ebx
// 	}
// 	WPOFF();
}

#endif