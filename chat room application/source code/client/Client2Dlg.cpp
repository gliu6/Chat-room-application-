// Client2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client2.h"
#include "Client2Dlg.h"
#include "fstream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int WINSOCK_VERSION=0x0101;
SOCKET g_hServerSocket;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClient2Dlg dialog

CClient2Dlg::CClient2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClient2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClient2Dlg)
	m_csIPAddress = _T("127.0.0.1");
	m_sPort = 5000;
	m_csMessage = _T("");
	m_csUsername = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClient2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClient2Dlg)
	DDX_Control(pDX, IDC_COMINGMESSAGE, m_csComingmessage);
	DDX_Text(pDX, IDC_IP, m_csIPAddress);
	DDX_Text(pDX, IDC_PORT, m_sPort);
	DDX_Text(pDX, IDC_MESSAGE, m_csMessage);
	DDX_Text(pDX, IDC_USERNAME, m_csUsername);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClient2Dlg, CDialog)
	//{{AFX_MSG_MAP(CClient2Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClient2Dlg message handlers

BOOL CClient2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClient2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClient2Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClient2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

UINT acceptconnect(LPVOID pParam)
{
	
	//short		sin_family;
	//u_short	sin_port;
	//struct	in_addr sin_addr;
	//char		sin_zero[8];
	
    char buf[1000]="";
    int buflen=1000;
	
    CClient2Dlg *pDlg=(CClient2Dlg*)pParam;//��öԻ���ָ��
	
    
	
	
	while(1)
	{
		int n=recv(g_hServerSocket,buf,buflen,0);//��������
		if(n<=0) //SOCKET_ERROR==-1
			break;
		buf[n]='\0';
		//���½�������
		pDlg->GetDlgItem(IDC_COMINGMESSAGE)->SetWindowText(buf);	//�������е�����һ��������ھ�̬�ı���
		//�������Զ�����
		int   nLength   =  pDlg->m_csComingmessage.SendMessage(WM_GETTEXTLENGTH); 
		pDlg->m_csComingmessage.SetSel(nLength,   nLength); 

	}
	return 0;
	
}

void CClient2Dlg::OnConnect() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(strlen(m_csUsername)==0)
	{
		MessageBox("Please input a username.");
		return;
	}
	CString str;
	if(GetDlgItemText(IDC_CONNECT,str),str=="����")
	{
			SetDlgItemText(IDC_CONNECT,"�Ͽ�");
			WSADATA wsaData;
			DWORD dwIPAddr;				//IP��ַ
			SOCKADDR_IN sockAddr;		//sock��ַ
			unsigned short m_usPort;	//�˿ں�
			
			UpdateData(TRUE);			//�������
			
			if ( WSAStartup(WINSOCK_VERSION,&wsaData)!=0 )  //��ʼ��Winsock DLL��ʹ��
			{
				MessageBox(_T("Could not load Windows Sockets DLL."),NULL,MB_OK);
				return;
			}
			
			if( (dwIPAddr=inet_addr(m_csIPAddress)) == INADDR_NONE )
			{
				MessageBox(_T("IP ��ַ�������������룡"),NULL,MB_OK);
				WSACleanup();//����WSACleanup�����������Socket��İ󶨲����ͷ�Socket����ռ�õ�ϵͳ��Դ��
				return;
			}
			m_usPort=htons(m_sPort);		//ת���˿ں��ֽ�˳��
			/*�����׽��ֵ�ַ*/ //ɶ���׽��ֵ�ַ��
			sockAddr.sin_family=AF_INET;
			sockAddr.sin_port=m_usPort;
			sockAddr.sin_addr.s_addr=dwIPAddr;
			////
			
			m_hSocket=socket(AF_INET,SOCK_STREAM,0);//����SOCKET
			g_hServerSocket=m_hSocket;
			if( m_hSocket == INVALID_SOCKET)
			{
				AfxMessageBox(_T("�����׽���ʧ�ܣ�"));
				WSACleanup();		//�����Socket��İ󶨲����ͷ�Socket����ռ�õ�ϵͳ��Դ
				return;
			}
			int nConnect = connect(m_hSocket,(LPSOCKADDR)&sockAddr,sizeof(sockAddr));//���ӷ�����
			if(nConnect)
			{
				MessageBox(_T("����ʧ�ܣ���"));
				closesocket(m_hSocket);		//closes an existing socket
				WSACleanup();				//�����Socket��İ󶨲����ͷ�Socket����ռ�õ�ϵͳ��Դ
				return;
			}
			
			
			/*���沿��*/
			AfxMessageBox(_T("���ӳɹ�"));
			AfxBeginThread(acceptconnect,this);	
			
	//�������������߳�//

	}
	else
	{
		SetDlgItemText(IDC_CONNECT,"����");
		if(shutdown(m_hSocket,2)==SOCKET_ERROR)			//performs the tasks required to delete a monitor instance
		{
			AfxMessageBox(_T("�ر����Ӵ���"));
			return;
		}
		
		if( closesocket(m_hSocket)==SOCKET_ERROR)	//�ر�SOCKET
		{
			AfxMessageBox(_T("�ر����Ӵ���"));
			return;
		}
		
		if(WSACleanup()==SOCKET_ERROR)				//�ر�winsocks dll��ʹ��
		{
			AfxMessageBox(_T("Cannot terminate the use of the Winsocks DLL"));
			return;
		}
			
	}
}

void CClient2Dlg::OnSend() 
{
	//������Ϣ����ʾĿǰ�������Ĺ���
	int nBytesSent = 0;			//�Ѿ����͵�����
	int nBytesThisTime;			//ÿ��ʵ�ʷ��͵�����
	int nSize;					//��Ҫ���͵��ֽ���
	UpdateData(TRUE);
	m_csMessage = m_csUsername +":"+ m_csMessage+"\r\n";
	do
	{
			
		nSize=m_csMessage.GetLength();
		nBytesThisTime = send(m_hSocket,(char *)m_csMessage.GetBuffer(0)+nBytesSent,nSize-nBytesSent,0);//��������
		if( nBytesThisTime==SOCKET_ERROR)//SOCKET_ERROR==-1
		{
			AfxMessageBox(_T("�������ݴ���"));
			return;
		}
		nBytesSent+=nBytesThisTime;
		
	}while(nBytesSent<nSize);
	m_csMessage="";
	UpdateData(FALSE);
}



/*void CClient2Dlg::OnSettimer() 
{
	// TODO: Add your control notification handler code here
	CString str;
	if(GetDlgItemText(IDC_SETTIMER,str),str=="���ü�ʱ��")
	{
		SetDlgItemText(IDC_SETTIMER,"ֹͣ��ʱ��");
		SetTimer(1,1000,NULL);	
	}
	else
	{
		KillTimer(1);
		SetDlgItemText(IDC_SETTIMER,"���ü�ʱ��");
	}
}

//����ṹ�����ڼ���ʱ��
struct timefromclient
{
	int number;
	double dtimefromclient;
};
struct timefromserver
{
	double dtimefromserver;
};

//�ⲿ��������
int num = 1;

void CClient2Dlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	int nBytesSent = 0;//�Ѿ����͵�����
	int nBytesThisTime;//ÿ��ʵ�ʷ��͵�����
	int nSize;//��Ҫ���͵��ֽ���
	LARGE_INTEGER tickcon, freq;	
	do
	{
		UpdateData(TRUE);
		CString m_csMessage="we are testing the network delay. Results are saved as C:\\\\test.tet in the client.";
		nSize=m_csMessage.GetLength();
		nBytesThisTime = send(m_hSocket,(char *)m_csMessage.GetBuffer(0)+nBytesSent,nSize-nBytesSent,0);//��������
		if( nBytesThisTime==SOCKET_ERROR)//SOCKET_ERROR==-1
		{
			AfxMessageBox(_T("�������ݴ���"));
			return;
		}
		nBytesSent+=nBytesThisTime;
		
	}while(nBytesSent<nSize);


	//��ȡclient�η���ʱ��
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&tickcon);
	
	double dtime;
	dtime=double(tickcon.QuadPart)/double(freq.QuadPart);
	timefromclient clienttime;
	
	clienttime.dtimefromclient=dtime;
	clienttime.number=num;
	
	//�ͻ��˽��ܷ���������������Ϣ���Ҽ�¼ʱ�䣬���ʱ�䵱��������ʱ�䡣
	timefromserver servertime;
	
	//��������
	char buf[10]="";
	int buflen=10;
	int n=recv(m_hSocket,buf,buflen,0);
	buf[n]='\0';

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&tickcon);
	
	
	dtime=double(tickcon.QuadPart)/double(freq.QuadPart);
	servertime.dtimefromserver=dtime;

		
	
	//�����ļ�
	ofstream SaveMSG("c:\\test.txt",ios::app);	//��ʱ����Ϣд���ļ���
    SaveMSG<<" Number "<<" Time From Client "<<" Time From Server "<<"      Late      "<<"\n";
	CString numbers,client_time,	//client_time����ͻ���ʱ��
		sever_time,				//sever_time���������ʱ��
		delay_time;				//delay_time�����ӳ�ʱ��
	numbers.Format("%6d", clienttime.number);
    client_time.Format("  %14.5f", clienttime.dtimefromclient);
	sever_time.Format("  %14.5f", servertime.dtimefromserver);
	delay_time.Format("  %14.5f", servertime.dtimefromserver-clienttime.dtimefromclient);
	SaveMSG<<numbers<<client_time<<"  "<<sever_time<<delay_time<<"\n";
	SaveMSG.close();
	num++;//ÿ�α�����ⲿ���
	CDialog::OnTimer(nIDEvent);
}
*/
