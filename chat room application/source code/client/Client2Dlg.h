// Client2Dlg.h : header file
//

#if !defined(AFX_CLIENT2DLG_H__1A7CD47C_D3FC_472C_A012_F00B135A65B8__INCLUDED_)
#define AFX_CLIENT2DLG_H__1A7CD47C_D3FC_472C_A012_F00B135A65B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CClient2Dlg dialog

class CClient2Dlg : public CDialog
{
// Construction
public:
	CClient2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CClient2Dlg)
	enum { IDD = IDD_CLIENT2_DIALOG };
	CEdit	m_csComingmessage;
	CString	m_csIPAddress;
	UINT	m_sPort;
	SOCKET m_hSocket;
	CString	m_csMessage;
	CString	m_csUsername;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClient2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClient2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConnect();
	afx_msg void OnSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENT2DLG_H__1A7CD47C_D3FC_472C_A012_F00B135A65B8__INCLUDED_)
