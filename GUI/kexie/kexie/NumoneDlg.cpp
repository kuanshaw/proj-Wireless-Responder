// NumoneDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "kexie.h"
#include "NumoneDlg.h"
#include "afxdialogex.h"


// CNumoneDlg 对话框

IMPLEMENT_DYNAMIC(CNumoneDlg, CDialog)

CNumoneDlg::CNumoneDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNumoneDlg::IDD, pParent)
	, m_numone(_T(""))
{
}

CNumoneDlg::~CNumoneDlg()
{
}

void CNumoneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_numone);
	DDX_Control(pDX, IDC_EDIT1, m_edit_one);

	m_editfont.CreatePointFont(2000, _T("黑体"));
	m_edit_one.SetFont(&m_editfont);
}


BEGIN_MESSAGE_MAP(CNumoneDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, &CNumoneDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CNumoneDlg 消息处理程序


HBRUSH CNumoneDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd-> GetDlgCtrlID()==IDC_EDIT1)
	{
		pDC-> SetTextColor(RGB(255,0,0));			//设置字体颜色
		pDC-> SetBkMode(TRANSPARENT);				//设置字体背景为透明
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CNumoneDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
