
// BashImGetterGUI.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CBashGUIApp:
// � ���������� ������� ������ ��. BashImGetterGUI.cpp
//

class CBashGUIApp : public CWinApp
{
public:
	CBashGUIApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CBashGUIApp theApp;