
// VmpHandleDlg.h : ͷ�ļ�
//

#pragma once
#include "dragedit.h"
#include "afxcmn.h"
#include "afxwin.h"

#include <string>
#include <vector>
#include <set>
#include <stdio.h>
#include <algorithm>

#define  StlCotainer std::vector<DWORD>
#define  StlInsert(vec,Value) vec.push_back(Value)

// CVmpHandleDlg �Ի���
class CVmpHandleDlg : public CDialog
{
// ����
public:
	CVmpHandleDlg(CWnd* pParent = NULL);	// ��׼���캯��

	virtual ~CVmpHandleDlg();
// �Ի�������
	enum { IDD = IDD_VMPHANDLE_DIALOG };
	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;
	CEdit m_editAdd;
	CStatic m_tip;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CDragEdit m_EditFile;
	CListCtrl m_list;
	StlCotainer vec;
	HANDLE  m_hEventForThread;
public:
	afx_msg void OnBnClickedOk();
	void LoadTraceData();
	void InsertListControl();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	enum ProState{None,Start,Finish};
	int UpProcessState(ProState Sate);
	afx_msg void OnBnClickedCalcOffset();
	afx_msg void OnBnClickedBtnOpen();
};
