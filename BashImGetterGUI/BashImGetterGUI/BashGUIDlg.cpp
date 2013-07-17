
// BashGUIDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "BashImGetterGUI.h"
#include "BashGUIDlg.h"
#include "afxdialogex.h"

#include "MapHtmlCode.h"

#include <vector>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;


const char *kNewQuote = "http://bash.im";
const char *kBestQuote = "http://bash.im/best";
const char *kRandomQuote = "http://bash.im/random";
const char *kAbyss = "http://bash.im/abyss";
const char *kTopAbyss = "http://bash.im/abysstop";
const char *kFileStoragehtmlCodes = "HtmlCodes.txt";


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Данные диалогового окна
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// диалоговое окно CBashGUIDlg



CBashGUIDlg::CBashGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBashGUIDlg::IDD, pParent)
	, textEdit(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_textEditBufferSize = 0;




	m_mapHtmlCode.loadUpFromFile(kFileStoragehtmlCodes);

}

void CBashGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, textEdit);
}

BEGIN_MESSAGE_MAP(CBashGUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDREFRESH, &CBashGUIDlg::OnBnClickedRefresh)
	ON_BN_CLICKED(IDC_BEST, &CBashGUIDlg::OnBnClickedBest)
	ON_BN_CLICKED(IDC_RANDOM, &CBashGUIDlg::OnBnClickedRandom)
	ON_BN_CLICKED(IDC_NEW, &CBashGUIDlg::OnBnClickedNew)
	ON_BN_CLICKED(IDC_ABYSS, &CBashGUIDlg::OnBnClickedAbyss)
	ON_BN_CLICKED(IDC_TOP_ABYSS, &CBashGUIDlg::OnBnClickedTopAbyss)
	ON_BN_CLICKED(IDC_ADD, &CBashGUIDlg::OnBnClickedAdd)
END_MESSAGE_MAP()


BOOL CBashGUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		

	return TRUE; 
}

void CBashGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CBashGUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); 

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


HCURSOR CBashGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBashGUIDlg::OnBnClickedRefresh()
{
	m_storageQuotes.clear();

	switch(currentCategoryQuotes){
	case kNewQuotes:
		m_storageQuotes = m_dataFromBash.getQuotesFromUrl(kNewQuote, m_mapHtmlCode);
		break;
	case kBestQuotes:
		m_storageQuotes = m_dataFromBash.getQuotesFromUrl(kBestQuote, m_mapHtmlCode);
		break;
	case kRandomQuotes:
		m_storageQuotes = m_dataFromBash.getQuotesFromUrl(kRandomQuote, m_mapHtmlCode);
		break;
	case kAbyssQuotes:
		m_storageQuotes = m_dataFromBash.getQuotesFromUrl(kAbyss, m_mapHtmlCode);
		break;
	case kAbyssTopQuotes:
		m_storageQuotes = m_dataFromBash.getQuotesFromUrl(kTopAbyss, m_mapHtmlCode);
		break;
	};


}


void CBashGUIDlg::OnBnClickedBest()
{
	currentCategoryQuotes = kBestQuotes;

	m_storageQuotes.clear();
	m_storageQuotes = m_dataFromBash.getQuotesFromUrl(kBestQuote, m_mapHtmlCode);
	setQuotes(m_storageQuotes);

}


void CBashGUIDlg::OnBnClickedAbyss()
{
	currentCategoryQuotes = kAbyssQuotes;

	m_storageQuotes.clear();
	m_storageQuotes = m_dataFromBash.getQuotesFromUrl(kAbyss, m_mapHtmlCode);
	setQuotes(m_storageQuotes);
}


void CBashGUIDlg::OnBnClickedTopAbyss(){
	currentCategoryQuotes = kAbyssTopQuotes;

	m_storageQuotes.clear();
	m_storageQuotes = m_dataFromBash.getQuotesFromUrl(kTopAbyss, m_mapHtmlCode);
	setQuotes(m_storageQuotes);
}


void CBashGUIDlg::setQuotes(vector<std::string>& quotes){


	CStringW buffer;
	CStringW split("\r\n===============================================\r\n");

	if(m_textEditBufferSize > 0)
		textEdit.Delete(0, m_textEditBufferSize);

	for(unsigned i = 0; i < quotes.size(); ++i)
	{
		CStringW str(quotes.at(i).c_str());
		buffer += split;
		buffer += str;
		buffer += split;

	}

	m_textEditBufferSize = buffer.GetLength();

	textEdit.SetString(buffer);
	UpdateData(false);
}

void CBashGUIDlg::OnBnClickedRandom()
{
	currentCategoryQuotes = kRandomQuotes;

	m_storageQuotes.clear();
	m_storageQuotes = m_dataFromBash.getQuotesFromUrl(kRandomQuote, m_mapHtmlCode);
	setQuotes(m_storageQuotes);
}


void CBashGUIDlg::OnBnClickedNew()
{
	currentCategoryQuotes = kNewQuotes;
	m_storageQuotes.clear();
	m_storageQuotes = m_dataFromBash.getQuotesFromUrl(kNewQuote, m_mapHtmlCode);
	setQuotes(m_storageQuotes);

}

void CBashGUIDlg::OnBnClickedAdd()
{
	ShellExecuteA(NULL, "open", "http://bash.im/add", NULL, NULL, SW_SHOWNORMAL);
}
