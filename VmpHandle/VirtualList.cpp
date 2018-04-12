// VirtualList.cpp : implementation file
//

#include "stdafx.h"
#include "VmpHandle.h"
#include "VirtualList.h"
#include "ClipboardHelper.h"

// CVirtualList

IMPLEMENT_DYNAMIC(CVirtualList, CListCtrl)

CVirtualList::CVirtualList()
{

}

CVirtualList::~CVirtualList()
{
}

BEGIN_MESSAGE_MAP(CVirtualList, CListCtrl)
END_MESSAGE_MAP()



// CVirtualList message handlers


int CVirtualList::InsertItemDataCallBack(NMHDR* pNMHDR,std::vector<SearchResult*>& pVec)
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM* pItem= &(pDispInfo)->item;
	int iItemIndx= pItem->iItem;
	if (pItem->mask & LVIF_TEXT) //�ַ�����������Ч
	{
		CString szTmp;
		switch(pItem->iSubItem){
		case 0: //��������������
			{
				TCHAR bufId[20]={0};
				_itot(pItem->iItem+1,bufId,10);
				szTmp = bufId;
			}
			break;
		case 1: //�������2
			szTmp = pVec[iItemIndx]->szAddress;
			break;
		case 2: //�������3
			szTmp = pVec[iItemIndx]->szThread;
			break;
		case 3: //�������4
			szTmp = pVec[iItemIndx]->szCom;
			break;
		case 4: //�������5
			szTmp = pVec[iItemIndx]->szReg;
			break;
		}
		lstrcpy(pItem->pszText,szTmp);
	}
	return 0;
}

bool CVirtualList::CopyItemTextToClipboard(NMHDR* pNMHDR, bool bAppendOnly)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	TCHAR buf[MAX_PATH+1]={0};
	GetItemText(pNMItemActivate->iItem,pNMItemActivate->iSubItem,buf,MAX_PATH);
	CopyTextToClipboard(buf,FALSE);
	return false;
}