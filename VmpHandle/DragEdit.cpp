// DragEdit.cpp : implementation file
//

#include "stdafx.h"
#include "DragEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDragEdit

CDragEdit::CDragEdit()
{
	m_tipBtnCtr=NULL;
	typedef BOOL(__stdcall * MsMessageFilter)(UINT message, DWORD dwFlag);
	HMODULE hMod = LoadLibrary(_T("user32.dll"));
	if (hMod)
	{
		MsMessageFilter  MsChangeWinMessageFilter;
		MsChangeWinMessageFilter = (MsMessageFilter)GetProcAddress(hMod, "ChangeWindowMessageFilter");
		if (MsChangeWinMessageFilter)
		{
			MsChangeWinMessageFilter(WM_DROPFILES, 1);
			MsChangeWinMessageFilter(0x0049, 1);// 0x0049 == WM_COPYGLOBALDATA
		}
		//FreeLibrary(hMod);
	}
}

CDragEdit::~CDragEdit()
{
	if (m_tipBtnCtr)
	{ 
		delete m_tipBtnCtr;
		m_tipBtnCtr = NULL;
	}
}


BEGIN_MESSAGE_MAP(CDragEdit, CEdit)
	//{{AFX_MSG_MAP(CDragEdit)
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDragEdit message handlers
#include <malloc.h>

void CDragEdit::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: Add your message handler code here and/or call default
	WORD wNumFileDropped = DragQueryFile(hDropInfo, -1, NULL, 0);
	CString firstFile = _T("");
	for (WORD x = 0; x < wNumFileDropped; x++){
		WORD wPathnameSize = DragQueryFile(hDropInfo, x, NULL, 0)+4;
		TCHAR* npszFile = (TCHAR*)LocalAlloc(LPTR, wPathnameSize*sizeof(TCHAR));
		if (npszFile == NULL){
			continue;
		}

		DragQueryFile(hDropInfo, x, npszFile, wPathnameSize*sizeof(TCHAR));
		if (firstFile == ""){
			firstFile = npszFile;
		}

		LocalFree(npszFile);
	}
	DragFinish(hDropInfo);
	SetWindowText(firstFile);
	UpdateData(FALSE);
	//	CEdit::OnDropFiles(hDropInfo);
}

BOOL CDragEdit::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (m_tipBtnCtr==NULL)
	{
		m_tipBtnCtr = new CToolTipCtrl;
		m_tipBtnCtr->Create(this);
		m_tipBtnCtr->SetDelayTime(100);
		m_tipBtnCtr->AddTool(this, _T("�����ļ�"));
		m_tipBtnCtr->SetMaxTipWidth(123);
		m_tipBtnCtr->Activate(TRUE);
	}
	if (pMsg->message == WM_MOUSEMOVE || pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_LBUTTONUP)
	{
		if(m_tipBtnCtr)
			m_tipBtnCtr->RelayEvent(pMsg); 
	}
	return CEdit::PreTranslateMessage(pMsg);
}