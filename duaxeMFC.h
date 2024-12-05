
// duaxeMFC.h : main header file for the duaxeMFC application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CduaxeMFCApp:
// See duaxeMFC.cpp for the implementation of this class
//

class CduaxeMFCApp : public CWinApp
{
public:
	CduaxeMFCApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CduaxeMFCApp theApp;
