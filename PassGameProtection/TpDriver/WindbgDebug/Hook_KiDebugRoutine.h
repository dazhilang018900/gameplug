#ifndef __HOOK_KIDEBUGROUTINE_H__
#define __HOOK_KIDEBUGROUTINE_H__

#include "..\GlobalFunction.h"

//KiDebugRoutine�����洢
ULONG g_uKiDebugRoutine=0;
//HOOK��KiDebugRoutine�����͵�ַ
HookVariableAddr g_uKiDebugRoutineHookAddrs[3]={0};

//ת��win7�е�KiDebugRoutine����
#pragma PAGECODE
VOID MoveKiDebugRutine_Win7()
{
	//�õ�KdpTrap��ַ
	//////////////////////////////////////////////////////////////////////////
	//��λ�ȡδ����������ַ
	//////////////////////////////////////////////////////////////////////////
// 	ULONG uAddr = GetServiceOldAddr(L"KdpTrap");------Error
// 	//�����Զ����KiDebugRoutine����
// 	g_uKiDebugRoutine = uAddr;
// 
// 	//�õ�ԭ�ں�KiDispatchException��ַ
// 	uAddr=GetServiceOldAddr(L"KiDispatchException");

// 	83efc041 ff750c          push    dword ptr [ebp+0Ch]
// 	83efc044 ff7510          push    dword ptr [ebp+10h]
// 	83efc047 ff15bc19fb83    call    dword ptr [nt!KiDebugRoutine (83fb19bc)]
// 	char pCode[] = {(char)0xFF,(char)0x75,(char)0x0c,(char)0xFF,(char)0x75,(char)0x10,(char)0xFF};
// 	KdPrint(("KiDispatchException��ַ=%x\n",uAddr));
// 	uAddr = SearchCode(uAddr,pCode,sizeof(pCode));
// 	KdPrint(("KiDebugRoutine��һ����ַ=%x\n",uAddr));
// 	g_uKiDebugRoutineHookAddrs[0].uAddr = uAddr;
// 	g_uKiDebugRoutineHookAddrs[0].uVariableAddr = *(PULONG)uAddr;
// 	DisableWP();
// 	*(PULONG)uAddr=(ULONG)&g_uKiDebugRoutine;
// 	EnableWP();

// 	uAddr = SearchCode(uAddr,pCode,sizeof(pCode));
// 	g_uKiDebugRoutineHookAddrs[0].uAddr = uAddr;
// 	g_uKiDebugRoutineHookAddrs[0].uVariableAddr = *(PULONG)uAddr;
//	KdPrint(("KiDebugRoutine�ڶ�����ַ=%x\n",uAddr));
// 	DisableWP();
// 	*(PULONG)uAddr=(ULONG)&g_uKiDebugRoutine;
// 	EnableWP();
// 
// 	uAddr = SearchCode(uAddr,pCode,sizeof(pCode));
//	KdPrint(("KiDebugRoutine��������ַ=%x\n",uAddr));
// 	g_uKiDebugRoutineHookAddrs[0].uAddr = uAddr;
// 	g_uKiDebugRoutineHookAddrs[0].uVariableAddr = *(PULONG)uAddr;
// 	DisableWP();
// 	*(PULONG)uAddr=(ULONG)&g_uKiDebugRoutine;
// 	EnableWP();
}

#pragma PAGECODE
VOID ResetKiDebugRutine_Win7()
{
// 	for (int i = 0; i < 3; i++)
// 	{
// 		DisableWP();
// 		*(PULONG)g_uKiDebugRoutineHookAddrs[i].uAddr = g_uKiDebugRoutineHookAddrs[i].uVariableAddr;
// 		EnableWP();
// 	}
}

#endif