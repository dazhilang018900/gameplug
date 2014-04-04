#include "MyDriverSys.h"
#include "Hook_NtOpenProcess.h"
#include "Hook_KiAttachProcess.h"
#include "Hook_NtReadVirtualMemory.h"
#include "Hook_NtWriteVirtualMemory.h"

#pragma INITCODE
extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject,PUNICODE_STRING B)
{
	KdPrint(("��ʼ����----"));
	HookNtOpenProcess_Win7();
	HookNtReadVirtualMemory();
	HookNtWriteVirtualMemory();

	CreateMyDevice(pDriverObject);
	pDriverObject->DriverUnload=Driver_Unload;

	return STATUS_SUCCESS;
}

//�����豸
NTSTATUS CreateMyDevice(IN PDRIVER_OBJECT pDriverObject)
{
	NTSTATUS status;
	//���ش���
	PDEVICE_OBJECT pDevobj;

	UNICODE_STRING devName;
	UNICODE_STRING symLinkName;
	//��devName��ʼ��
	RtlInitUnicodeString(&devName,L"\\Device\\Boris_Device");

	//�����豸
	status = IoCreateDevice(pDriverObject,0,&devName,FILE_DEVICE_UNKNOWN,0,TRUE,&pDevobj);
	if (!NT_SUCCESS(status))
	{
		if (status == STATUS_INSUFFICIENT_RESOURCES)
		{
			KdPrint(("��Դ����\n"));
		}
		else if (status == STATUS_OBJECT_NAME_EXISTS)
		{
			KdPrint(("�豸�����Ѵ���\n"));
		}
		else if (status == STATUS_OBJECT_NAME_COLLISION)
		{
			KdPrint(("�������г�ͻ\n"));
		}
		return status;
	}

	pDevobj->Flags |= DO_BUFFERED_IO;

	//������������
	RtlInitUnicodeString(&symLinkName,L"\\??\\MyDriverLinkName");
	status = IoCreateSymbolicLink(&symLinkName,&devName);
	if (!NT_SUCCESS(status))
	{
		IoDeleteDevice(pDevobj);
		return status;
	}
	return STATUS_SUCCESS;
}

#pragma PAGECODE
VOID Driver_Unload(IN PDRIVER_OBJECT pDriverObject)
{
	PDEVICE_OBJECT pDev;
	UNICODE_STRING symName;

	UnHookNtOpenProcess_Win7();
	UnHookNtReadVirtualMemory();
	UnHookNtWriteVirtualMemory();
	
	//ɾ����������
	RtlInitUnicodeString(&symName,L"\\??\\MyDriverLinkName");
	IoDeleteSymbolicLink(&symName);
	//ɾ���豸
	pDev = pDriverObject->DeviceObject;
	IoDeleteDevice(pDev);

	KdPrint(("�����ɹ���ж��...OK-----------\n"));
}