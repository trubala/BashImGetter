
// BashImGetterGUI.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CBashGUIApp:
// О реализации данного класса см. BashImGetterGUI.cpp
//

class CBashGUIApp : public CWinApp
{
public:
	CBashGUIApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CBashGUIApp theApp;