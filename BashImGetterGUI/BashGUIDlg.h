
// BashGUIDlg.h : ���� ���������
//
#include "GetData.h"

#pragma once

using namespace std;

// ���������� ���� CBashGUIDlg
class CBashGUIDlg : public CDialogEx
{
// ��������
public:
	CBashGUIDlg(CWnd* pParent = NULL);	// ����������� �����������
	

	GetData getData;

	bool newQuoteClick;
	bool randomQuoteClick;
	bool bestQuoteClick;

	MapHtmlCode load;

	vector<std::string> quotes;
	int textEditBufferSize;

	void setQuotes(vector<std::string>& quotes);
	

// ������ ����������� ����
	enum { IDD = IDD_BASHIMGETTERGUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRefresh();
	afx_msg void OnBnClickedBest();
	afx_msg void OnBnClickedRandom();
	afx_msg void OnBnClickedNew();
	afx_msg void OnBnClickedMfcmenubutton1();
	afx_msg void OnEnChangeEdit1();
	CString textEdit;
	afx_msg void OnBnClickedButton1();
};
