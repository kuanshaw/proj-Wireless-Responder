
// kexieDlg.h : ͷ�ļ�
//

#pragma once
#include "mscomm1.h"
#include "afxwin.h"
#include "NumoneDlg.h"

// CkexieDlg �Ի���
class CkexieDlg : public CDialogEx
{
// ����
public:
	CkexieDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_KEXIE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMscomm1 m_mscom;
	afx_msg void OnBnClickedConnect();
	CComboBox m_com;
	CComboBox m_baud;
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedSend();


private:
	CString m_send_data;
	CString m_receive_data;
public:
	afx_msg void OnBnClickedClear();
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
	afx_msg void OnBnClickedRound();
	afx_msg void OnBnClickedOk();
private:
	CString m_state;
	CString num1;
	CString m_num1;
	CString m_num2;
	CString m_time2;
	CString m_num3;
	CString m_num4;
	CString m_num5;
	CString m_num6;
	CString m_num7;
	CString m_time3;
	CString m_time4;
	CString m_time5;
	CString m_time6;
	CString m_time7;
public:
	CEdit m_rev_edit;
	CFont m_font;
	CFont m_font2;

	CEdit m_edit_num1;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CEdit m_edit_no1;
private:
	CString m_no1;
};
