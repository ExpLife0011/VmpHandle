// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VmpHandleDlg.h"


// CMainDlg dialog

IMPLEMENT_DYNAMIC(CVmpHandleDlg, CDialog)

CVmpHandleDlg::CVmpHandleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVmpHandleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CVmpHandleDlg::~CVmpHandleDlg()
{
}

void CVmpHandleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Control(pDX, IDC_EDIT1, m_editFilePath);
}

// ���ɵ���Ϣӳ�亯��
BOOL CVmpHandleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	TCHAR MyDir[_MAX_PATH];  
	SHGetSpecialFolderPath(this->GetSafeHwnd(),MyDir,CSIDL_DESKTOP,0);
	_tcscat(MyDir,_T("\\log.txt"));
	m_editFilePath.SetWindowText(MyDir);


	char str[MAX_PATH+1] ={0};
	GetWindowTextA(m_hWnd,str,MAX_PATH);
	strcat(str," ����ʱ�䣺 ");
	strcat(str,__DATE__);
	strcat(str," ");
	strcat(str,__TIME__);
	strcat(str," By��ZhanYue");
	CString title;
	title = str;
	SetWindowText(title);

	m_tab.InsertItem(0,_T("Handle��ȡ"));
	m_tab.InsertItem(1,_T("���ָ������"));
	m_tab.InsertItem(2,_T("�Ĵ�������"));
	m_tab.InsertItem(3,_T("����"));
	m_tab.InsertItem(4,_T("����"));
	m_tab.InsertItem(5,_T("����"));
	m_paraHandle.Create(IDD_DLG_HANDLE,GetDlgItem(IDC_TAB1));
	m_paraCom.Create(IDD_DLG_COMMAND,GetDlgItem(IDC_TAB1));
	m_paraReg.Create(IDD_DLG_REGISTER,GetDlgItem(IDC_TAB1));
	m_paraAbout.Create(IDD_DLG_ABOUT,GetDlgItem(IDC_TAB1));


	//���IDC_TABTEST�ͻ�����С 
	//���IDC_TABTEST�ͻ�����С 
	CRect rs; 
	m_tab.GetClientRect(&rs); 
	//�����ӶԻ����ڸ������е�λ�� 
	rs.top+=20; 
	rs.bottom-=0; 
	rs.left+=1; 
	rs.right-=1; 
	 
	//�����ӶԻ���ߴ粢�ƶ���ָ��λ�� 
	m_paraHandle.MoveWindow(&rs); 
	m_paraCom.MoveWindow(&rs);
	m_paraReg.MoveWindow(&rs); 
	m_paraAbout.MoveWindow(&rs); 

	m_paraHandle.ShowWindow(TRUE);;
	m_paraCom.ShowWindow(FALSE);
	m_paraReg.ShowWindow(FALSE);
	m_paraAbout.ShowWindow(FALSE);
	m_tab.SetCurSel(0);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CVmpHandleDlg, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CVmpHandleDlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CVmpHandleDlg::OnBnClickedBtnOpen)
	ON_EN_CHANGE(IDC_EDIT1, &CVmpHandleDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CMainDlg message handlers

void CVmpHandleDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	int nCurSel = m_tab.GetCurSel();
	//int nCout = m_tab.GetItemCount();
	//for (int i = 0;i < nCout;i++)
	//{
	//	CWnd* phWnd = GetDlgItem(IDD_DLG_HANDLE+i);	
	//	if (phWnd)
	//	{
	//		if (i == nCurSel)
	//			::ShowWindow(phWnd->m_hWnd,SW_SHOW);
	//		else
	//			::ShowWindow(phWnd->m_hWnd,SW_HIDE);
	//	}
	//}
	switch(nCurSel)
	{
	case 0:
		m_paraHandle.ShowWindow(TRUE);
		m_paraCom.ShowWindow(FALSE);
		m_paraReg.ShowWindow(FALSE);
		m_paraAbout.ShowWindow(FALSE);
			break;
	case 1:
		m_paraHandle.ShowWindow(FALSE);
		m_paraCom.ShowWindow(TRUE);
		m_paraReg.ShowWindow(FALSE);
		m_paraAbout.ShowWindow(FALSE);
		break;
	case 2:
		m_paraHandle.ShowWindow(FALSE);
		m_paraCom.ShowWindow(FALSE);
		m_paraReg.ShowWindow(TRUE);
		m_paraAbout.ShowWindow(FALSE);
		break;
	case 3:
		m_paraHandle.ShowWindow(FALSE);
		m_paraCom.ShowWindow(FALSE);
		m_paraReg.ShowWindow(FALSE);
		m_paraAbout.ShowWindow(TRUE);
		break;
	default:
		break;
	}
	*pResult = 0;
}

void CVmpHandleDlg::OnBnClickedBtnOpen()
{
	// TODO: Add your control notification handler code here
	CFileDialog fileDlg(TRUE, _T("txt"), _T("log"));     
	fileDlg.m_ofn.lpstrTitle = _T("Open File");    
	fileDlg.m_ofn.lpstrFilter = _T("Text Files(*txt)\0*.txt\0All Files(*.*)\0*.*\0\0");  
	if(fileDlg.DoModal() == IDOK )
	{
		CString szStr;
		szStr = fileDlg.GetPathName();
		m_editFilePath.SetWindowText(szStr);

		m_paraHandle.SetFileName(szStr);
		m_paraCom.SetFileName(szStr);
		m_paraReg.SetFileName(szStr);
	}
}

void CVmpHandleDlg::OnEnChangeEdit1()
{
	CString szStr;
	m_editFilePath.GetWindowText(szStr);

	m_paraHandle.SetFileName(szStr);
	m_paraCom.SetFileName(szStr);
	m_paraReg.SetFileName(szStr);
}
