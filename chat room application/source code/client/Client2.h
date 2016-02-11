// Client2.h : main header file for the CLIENT2 application
//

#if !defined(AFX_CLIENT2_H__E1947E98_A497_4223_B51F_D34B9C20F53F__INCLUDED_)
#define AFX_CLIENT2_H__E1947E98_A497_4223_B51F_D34B9C20F53F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CClient2App:
// See Client2.cpp for the implementation of this class
//

class CClient2App : public CWinApp
{
public:
	CClient2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClient2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CClient2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENT2_H__E1947E98_A497_4223_B51F_D34B9C20F53F__INCLUDED_)
