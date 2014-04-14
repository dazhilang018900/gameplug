
// PassGameProtectionDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#define hook_code CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define unhook_code CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

// CPassGameProtectionDlg �Ի���
class CPassGameProtectionDlg : public CDialogEx
{
// ����
public:
	CPassGameProtectionDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PASSGAMEPROTECTION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	HANDLE GetDevice();
	BOOL LoadDriver();	
	void UnLoadDriver();
	BOOL SendIRP(int code,LPVOID inBuffer,DWORD intBufferSize,LPVOID outBuffer,DWORD outBufferSize);

private:
	HANDLE hDevice;
public:
	afx_msg void OnBnClickedBtnFindSyspath();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnStop();
	CString m_strSysPath;
	CString m_strSysName;
	CButton m_btnStartSys;
	CButton m_btnStopSys;
	CButton m_btnStartService;
	CButton m_btnStopService;
	afx_msg void OnBnClickedBtnStartService();
	afx_msg void OnBnClickedBtnStopService();
};
