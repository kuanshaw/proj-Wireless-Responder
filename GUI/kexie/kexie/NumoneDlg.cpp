// NumoneDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "kexie.h"
#include "NumoneDlg.h"
#include "afxdialogex.h"


// CNumoneDlg �Ի���

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

	m_editfont.CreatePointFont(2000, _T("����"));
	m_edit_one.SetFont(&m_editfont);
}


BEGIN_MESSAGE_MAP(CNumoneDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, &CNumoneDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CNumoneDlg ��Ϣ�������


HBRUSH CNumoneDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (pWnd-> GetDlgCtrlID()==IDC_EDIT1)
	{
		pDC-> SetTextColor(RGB(255,0,0));			//����������ɫ
		pDC-> SetBkMode(TRANSPARENT);				//�������屳��Ϊ͸��
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CNumoneDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}
