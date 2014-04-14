#ifndef __DRIVER_HEAD_H__
#define __DRIVER_HEAD_H__

#ifdef __cplusplus
extern "C"
{
#endif
#include <NTDDK.h> //���������Ҫ��C��ʽ�����ͷ�ļ�
#ifdef __cplusplus
}
#endif 

#include <windef.h>

#define INITCODE code_seg("INIT") 
#define PAGECODE code_seg("PAGE")/*�ڴ治��ʱ�������û���Ӳ��*/

#define hook_code CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define unhook_code CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

typedef struct _ServiceDescriptorTable 
{
	PVOID ServiceTableBase;		//System Service Dispatch Table �Ļ���ַ  
	PVOID ServiceCounterTable;	//������ SSDT ��ÿ�����񱻵��ô����ļ����������������һ����sysenter ���¡� 
	unsigned int NumberOfServices;//�� ServiceTableBase �����ķ������Ŀ��  
	PVOID ParamTableBase;		//����ÿ��ϵͳ��������ֽ�����Ļ���ַ-ϵͳ��������� 
}*PServiceDescriptorTable; 
extern "C" extern PServiceDescriptorTable KeServiceDescriptorTable;

#endif