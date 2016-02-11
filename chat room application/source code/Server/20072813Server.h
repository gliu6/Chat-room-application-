// 20072813Server.h : main header file for the 20072813SERVER application
//

#if !defined(AFX_20072813SERVER_H__83E696E8_1BD1_49A0_8BD4_14B50852DE2E__INCLUDED_)
#define AFX_20072813SERVER_H__83E696E8_1BD1_49A0_8BD4_14B50852DE2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMy20072813ServerApp:
// See 20072813Server.cpp for the implementation of this class
//

#define WINSOCK_VERSION 0x0202
#define MAX_APPLICATION_BUFFER 1000

class CMy20072813ServerApp : public CWinApp
{
public:
	CMy20072813ServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy20072813ServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMy20072813ServerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_20072813SERVER_H__83E696E8_1BD1_49A0_8BD4_14B50852DE2E__INCLUDED_)
