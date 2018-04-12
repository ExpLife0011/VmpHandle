
// VmpHandleDlg.h : ͷ�ļ�
//

#pragma once
#include "dragedit.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "resource.h"
#include "MyListCtrl.h"

#include <string>
#include <vector>
#include <set>
#include <stdio.h>
#include <algorithm>


#define  StlCotainer std::vector<DWORD>
#define  StlInsert(vec,Value) vec.push_back(Value)

// CVmpHandleDlg �Ի���
class CParaHandle : public CDialog
{
// ����
public:
	CParaHandle(CWnd* pParent = NULL);	// ��׼���캯��

	virtual ~CParaHandle();
// �Ի�������
	enum { IDD = IDD_DLG_HANDLE };
	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	CEdit m_editAdd;
	CStatic m_tip;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CMyListCtrl m_list;
	StlCotainer vec;
	HANDLE  m_hEventForThread;
	int m_nParaHandle;
	int GetParaValue(void);
	CString m_szFileName;
	int SetFileName(CString szFileName);
public:
	afx_msg void OnBnClickedOk();
	void LoadTraceData();
	void InsertListControl();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	enum ProState{None,Start,Finish};
	int UpProcessState(ProState Sate);
	afx_msg void OnBnClickedCalcOffset();
};
