#pragma once
#include "afxwin.h"


// CNumoneDlg �Ի���

class CNumoneDlg : public CDialog
{
	DECLARE_DYNAMIC(CNumoneDlg)

public:
	CNumoneDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNumoneDlg();

// �Ի�������
	enum { IDD = IDD_NUM_ONE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_numone;
	CFont m_editfont;
	CEdit m_edit_one;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedOk();
};
