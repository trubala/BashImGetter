
// BashGUIDlg.h : файл заголовка
//
#include "QuotesBash.h"

#pragma once

// диалоговое окно CBashGUIDlg
class CBashGUIDlg : public CDialogEx
{
	// Создание
public:
	CBashGUIDlg(CWnd* pParent = NULL);	// стандартный конструктор


	QuotesBash m_dataFromBash;

	enum CurrentCategoryQuotes {kNewQuotes, kRandomQuotes, kBestQuotes, kAbyssQuotes, kAbyssTopQuotes};

	MapHtmlCode m_mapHtmlCode;

	std::vector<std::string> m_storageQuotes;

	int m_textEditBufferSize;

	void setQuotes(std::vector<std::string>& storageQuotes);


	// Данные диалогового окна
	enum { IDD = IDD_BASHIMGETTERGUI_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


	// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
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
	CString textEdit;
	afx_msg void OnBnClickedAbyss();
	afx_msg void OnBnClickedTopAbyss();

private:
	CurrentCategoryQuotes currentCategoryQuotes;
public:
	afx_msg void OnBnClickedAdd();
};
