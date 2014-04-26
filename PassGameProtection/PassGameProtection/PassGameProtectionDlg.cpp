
// PassGameProtectionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PassGameProtection.h"
#include "PassGameProtectionDlg.h"
#include "afxdialogex.h"
#include "winsvc.h"
#include <winioctl.h> 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CPassGameProtectionDlg �Ի���
CPassGameProtectionDlg::CPassGameProtectionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPassGameProtectionDlg::IDD, pParent)
	, m_strSysPath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPassGameProtectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SYSPATH, m_strSysPath);
	DDX_Control(pDX, IDC_BTN_START, m_btnStartSys);
	DDX_Control(pDX, IDC_BTN_STOP, m_btnStopSys);
	DDX_Control(pDX, IDC_BTN_START_SERVICE, m_btnStartService);
	DDX_Control(pDX, IDC_BTN_STOP_SERVICE, m_btnStopService);
	DDX_Control(pDX, IDC_BTN_STARTDEBUG, m_btnStartDebug);
	DDX_Control(pDX, IDC_BTN_STOPDEBUG, m_btnStopDebug);
}

BEGIN_MESSAGE_MAP(CPassGameProtectionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_FIND_SYSPATH, &CPassGameProtectionDlg::OnBnClickedBtnFindSyspath)
	ON_BN_CLICKED(IDC_BTN_START, &CPassGameProtectionDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, &CPassGameProtectionDlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_START_SERVICE, &CPassGameProtectionDlg::OnBnClickedBtnStartService)
	ON_BN_CLICKED(IDC_BTN_STOP_SERVICE, &CPassGameProtectionDlg::OnBnClickedBtnStopService)
	ON_BN_CLICKED(IDC_BTN_STARTDEBUG, &CPassGameProtectionDlg::OnBnClickedBtnStartdebug)
	ON_BN_CLICKED(IDC_BTN_STOPDEBUG, &CPassGameProtectionDlg::OnBnClickedBtnStopdebug)
END_MESSAGE_MAP()


// CPassGameProtectionDlg ��Ϣ�������
BOOL CPassGameProtectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPassGameProtectionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPassGameProtectionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPassGameProtectionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//���������ļ�
void CPassGameProtectionDlg::OnBnClickedBtnFindSyspath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(
		TRUE, 
		NULL, 
		NULL, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		NULL, 
		this);
	if (dlg.DoModal() == IDOK)
	{
		m_strSysPath = dlg.GetPathName();
		m_strSysName = dlg.GetFileName();
		UpdateData(FALSE);
	}
}

//��������
void CPassGameProtectionDlg::OnBnClickedBtnStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_strSysPath = m_strSysPath.Trim();
	if (!m_strSysPath.IsEmpty() && LoadDriver())
	{
		hDevice = GetDevice();
		if (hDevice != INVALID_HANDLE_VALUE)
		{
			//�ı䰴ť״̬
			m_btnStartSys.EnableWindow(FALSE);
			m_btnStartService.EnableWindow(TRUE);
			m_btnStopService.EnableWindow(FALSE);
			m_btnStopSys.EnableWindow(TRUE);
			return;
		}		
	}

	MessageBox("��ѡ����ȷ����������","����",MB_OK|MB_ICONHAND);
}

//��������
BOOL CPassGameProtectionDlg::LoadDriver()
{
	BOOL bRet = FALSE;
	SC_HANDLE hServiceDDK = NULL; //��������ķ�����
	SC_HANDLE hServiceMgr = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);//������������
	if (hServiceMgr == NULL)
	{
		return bRet;
	}
	hServiceDDK=CreateService(
		hServiceMgr,//���������
		m_strSysName.LockBuffer(),	//������ע����е�����
		m_strSysName.LockBuffer(),	//ע������������ DisplayNameֵ
		SERVICE_ALL_ACCESS,			//���������ķ���Ȩ��
		SERVICE_KERNEL_DRIVER,		//��ʾ���ص�������
		SERVICE_DEMAND_START,		// ע������������ Start ֵ  
		SERVICE_ERROR_IGNORE,		// ע������������ ErrorControl ֵ  
		m_strSysPath.LockBuffer(),	// ע������������ ImagePath ֵ  
		NULL,	//Ҫ��������� �û���
		NULL,	//�����֤��ǩ
		NULL,	//�������ķ��������
		NULL,   //�û��˻�����
		NULL);
	if (hServiceDDK == NULL)
	{
		//�������ʧ��,��ֱ�Ӵ�
		hServiceDDK = OpenService(hServiceMgr, m_strSysName.LockBuffer(), SERVICE_ALL_ACCESS);
		if (hServiceDDK == NULL)
		{
			CloseServiceHandle(hServiceMgr);
			return bRet;
		}
	}
	if (StartService(hServiceDDK,NULL,NULL) != NULL)
	{
		bRet = TRUE;
	}

	CloseServiceHandle(hServiceDDK);
	CloseServiceHandle(hServiceMgr);
	return bRet;
}

//ֹͣ����
void CPassGameProtectionDlg::OnBnClickedBtnStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UnLoadDriver();
	CloseHandle(hDevice);
	//�ı䰴ť״̬
	m_btnStartSys.EnableWindow(TRUE);
	m_btnStartService.EnableWindow(FALSE);
	m_btnStopService.EnableWindow(FALSE);
	m_btnStopSys.EnableWindow(FALSE);
}

//ж������
void CPassGameProtectionDlg::UnLoadDriver()
{
	SERVICE_STATUS SvrSta;
	SC_HANDLE hServiceDDK = NULL; //��������ķ�����
	SC_HANDLE hServiceMgr = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);	//������������
	if (hServiceMgr == NULL)
	{
		return;
	}
	//����Ҫ�رյ���������Ӧ�ķ���
	hServiceDDK=OpenService(hServiceMgr,m_strSysName,SERVICE_ALL_ACCESS);
	if (hServiceDDK==NULL)
	{
		return;
	}
	//ֹͣ����
	if (!ControlService(hServiceDDK,SERVICE_CONTROL_STOP,&SvrSta))
	{
		return;
	}
	//ɾ������
	if(!DeleteService(hServiceDDK))
	{
		return;
	}
	if (hServiceDDK!=NULL)
	{
		//�رմ򿪵��������
		CloseServiceHandle(hServiceDDK);
	}
	if (hServiceMgr!=NULL)
	{
		//�رշ�����������
		CloseServiceHandle(hServiceMgr);
	}
}

//��ȡ�������
HANDLE CPassGameProtectionDlg::GetDevice()
{
	hDevice = CreateFile("\\\\.\\MyDriverLinkName",//\\??\\MyDriverLinkNameָ���ļ�����ָ�� 
		GENERIC_READ|GENERIC_WRITE,	//����ģʽ��д/���� 
		0,							//����ģʽ
		NULL,						//ָ��ȫ���Ե�ָ��
		OPEN_EXISTING,				//��δ���
		FILE_ATTRIBUTE_NORMAL,		//�ļ�����
		NULL);						//���ڸ����ļ���� 
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		printf("��ȡ�������ʧ�ܣ�Eorror code is :%d\n",GetLastError());
		getchar();
		return INVALID_HANDLE_VALUE;
	}
	return hDevice;
}

//�������ļ���������
BOOL CPassGameProtectionDlg::SendIRP(int code,LPVOID inBuffer,DWORD intBufferSize,LPVOID outBuffer,DWORD outBufferSize)
{
	DWORD lpBytesReturned;

	return DeviceIoControl(hDevice,code,inBuffer,intBufferSize,outBuffer,outBufferSize,&lpBytesReturned,NULL);
}

//��������
void CPassGameProtectionDlg::OnBnClickedBtnStartService()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!SendIRP(hook_tp,NULL,0,NULL,0))
	{
		MessageBox("����ʧ��","Error!",MB_OK);
		return;
	}
	m_btnStartSys.EnableWindow(FALSE);
	m_btnStartService.EnableWindow(FALSE);
	m_btnStopService.EnableWindow(TRUE);
	m_btnStopSys.EnableWindow(TRUE);
}

//ֹͣ����
void CPassGameProtectionDlg::OnBnClickedBtnStopService()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (hDevice==INVALID_HANDLE_VALUE)
	{
		MessageBox( "���������豸ʧ��","Error",MB_OK|MB_ICONHAND);
		return;
	}
	if (!SendIRP(unhook_tp,NULL,0,NULL,0))
	{
		MessageBox("����ʧ��","Error",MB_OK);
		return;
	}
	m_btnStartSys.EnableWindow(FALSE);
	m_btnStartService.EnableWindow(TRUE);
	m_btnStopService.EnableWindow(FALSE);
	m_btnStopSys.EnableWindow(TRUE);
}

//����˫������ģʽ
void CPassGameProtectionDlg::OnBnClickedBtnStartdebug()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!SendIRP(hook_windbg,NULL,0,NULL,0))
	{
		MessageBox("����ʧ��","Error",MB_OK);
		return;
	}
}

//ֹͣ˫������
void CPassGameProtectionDlg::OnBnClickedBtnStopdebug()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!SendIRP(unhook_windbg,NULL,0,NULL,0))
	{
		MessageBox("����ʧ��","Error",MB_OK);
		return;
	}
}
