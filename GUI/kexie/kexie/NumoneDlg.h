#pragma once
#include "afxwin.h"


// CNumoneDlg 对话框

class CNumoneDlg : public CDialog
{
	DECLARE_DYNAMIC(CNumoneDlg)

public:
	CNumoneDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNumoneDlg();

// 对话框数据
	enum { IDD = IDD_NUM_ONE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_numone;
	CFont m_editfont;
	CEdit m_edit_one;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedOk();
};
