
// BashImGetterGUI.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CBiGGUIApp:
// � ���������� ������� ������ ��. BashImGetterGUI.cpp
//

class CBiGGUIApp : public CWinApp
{
public:
	CBiGGUIApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CBiGGUIApp theApp;