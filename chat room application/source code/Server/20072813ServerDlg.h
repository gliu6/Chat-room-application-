// 20072813ServerDlg.h : header file
//

#if !defined(AFX_20072813SERVERDLG_H__35366C12_BDE8_4001_BC24_347E230FD8BD__INCLUDED_)
#define AFX_20072813SERVERDLG_H__35366C12_BDE8_4001_BC24_347E230FD8BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMy20072813ServerDlg dialog

class CMy20072813ServerDlg : public CDialog
{
// Construction
public:
	CMy20072813ServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMy20072813ServerDlg)
	enum { IDD = IDD_MY20072813SERVER_DIALOG };
	CEdit	m_csComingmessage;
	CListBox	m_ListBox_Content;
	UINT	m_sPort;
	CString	m_csName;
	SOCKADDR_IN m_sockServerAddr;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy20072813ServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy20072813ServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStart();
	afx_msg void OnClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_20072813SERVERDLG_H__35366C12_BDE8_4001_BC24_347E230FD8BD__INCLUDED_)
