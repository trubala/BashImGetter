
// BashGUIDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "BashImGetterGUI.h"
#include "BashGUIDlg.h"
#include "afxdialogex.h"

#include "MapHtmlCode.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;


const string newQuote = "http://bash.im";
const string bestQuote = "http://bash.im/best";
const string randomQuote = "http://bash.im/random";


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

	newQuoteClick = false;
	bestQuoteClick = false;
	randomQuoteClick = false;
	textEditBufferSize = 0;



	
	load.loadUpFromFile("HtmlCodes.txt");
	//load.test_getViewByName("&Theta;");


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
	//	ON_BN_CLICKED(IDC_MFCMENUBUTTON1, &CBashGUIDlg::OnBnClickedMfcmenubutton1)
	ON_EN_CHANGE(IDC_EDIT1, &CBashGUIDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// обработчики сообщений CBashGUIDlg

BOOL CBashGUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
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

	// Задает значок для этого диалогового окна. Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок. Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CBashGUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CBashGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBashGUIDlg::OnBnClickedRefresh()
{
	// TODO: добавьте свой код обработчика уведомлений
	//MessageBox(L"Refresh!", L"WTF?", MB_OK | MB_ICONINFORMATION);

	quotes.clear();

	if(newQuoteClick)
		quotes = getData.GetDataFromUrl(newQuote, load);
	else if(bestQuoteClick)
		quotes = getData.GetDataFromUrl(bestQuote, load);
	else
		quotes = getData.GetDataFromUrl(randomQuote, load);

}


void CBashGUIDlg::OnBnClickedBest()
{
	// TODO: добавьте свой код обработчика уведомлений
	//MessageBox(L"Best!", L"WTF?", MB_OK | MB_ICONINFORMATION);

	newQuoteClick = false;
	bestQuoteClick = true;
	randomQuoteClick = false;
	quotes.clear();
	

	quotes = getData.GetDataFromUrl(bestQuote, load);

	setQuotes(quotes);

	


}



void CBashGUIDlg::setQuotes(vector<std::string>& quotes){
	
	
	CStringW buffer;
	CStringW split("\r\n===============================================\r\n");

	if(textEditBufferSize > 0)
		textEdit.Delete(0, textEditBufferSize);

	for(unsigned i = 0; i < quotes.size(); ++i)
	{
		CStringW str(quotes.at(i).c_str());
		buffer += split;
		buffer += str;
		buffer += split;
		
	}

	textEditBufferSize = buffer.GetLength();

	textEdit.SetString(buffer);
	UpdateData(false);
}

void CBashGUIDlg::OnBnClickedRandom()
{
	// TODO: добавьте свой код обработчика уведомлений
	//MessageBox(L"Random", L"WTF?", MB_OK | MB_ICONINFORMATION);

	newQuoteClick = false;
	bestQuoteClick = false;
	randomQuoteClick = true;
	quotes.clear();

	quotes = getData.GetDataFromUrl(randomQuote, load);

	setQuotes(quotes);
}


void CBashGUIDlg::OnBnClickedNew()
{
	// TODO: добавьте свой код обработчика уведомлений
	//MessageBox(L"New", L"WTF?", MB_OK | MB_ICONINFORMATION);

	newQuoteClick = true;
	bestQuoteClick = false;
	randomQuoteClick = false;
	quotes.clear();

	quotes = getData.GetDataFromUrl(newQuote, load);

	setQuotes(quotes);

}




void CBashGUIDlg::OnEnChangeEdit1()
{

}
