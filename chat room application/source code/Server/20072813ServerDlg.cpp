// 20072813ServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "20072813Server.h"
#include "20072813ServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//SOCKET g_hServerSocket;
//BOOL g_bServerControl;
SOCKET g_hServerSocket,sockfromc;
SOCKET clientsocket[8]={0};

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
// CMy20072813ServerDlg dialog

CMy20072813ServerDlg::CMy20072813ServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy20072813ServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy20072813ServerDlg)
	m_sPort = 5000;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy20072813ServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy20072813ServerDlg)
	DDX_Control(pDX, IDC_INCOMINGMESSAGE, m_csComingmessage);
	DDX_Control(pDX, IDC_LIST, m_ListBox_Content);
	DDX_Text(pDX, IDC_PORT, m_sPort);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy20072813ServerDlg, CDialog)
	//{{AFX_MSG_MAP(CMy20072813ServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy20072813ServerDlg message handlers

BOOL CMy20072813ServerDlg::OnInitDialog()
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

void CMy20072813ServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy20072813ServerDlg::OnPaint() 
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
HCURSOR CMy20072813ServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

CString Str;
UINT recieve(LPVOID pParam)
{
    char buf[1000]="";
    int buflen=1000;

	SOCKET	csocket=sockfromc;
	CMy20072813ServerDlg* p=(CMy20072813ServerDlg *)pParam;
	while(1)
	{
		int n=recv(csocket,buf,buflen,0);//��������
		if(n<=0) //SOCKET_ERROR==-1
			break;
		buf[n]='\0';
		//���½�������
		Str=Str+buf;
		for (int i=0;i<8;i++)
		{
			if (clientsocket[i]!=0&&clientsocket[i]!=SOCKET_ERROR)
			{
				int nBytesSent = 0;			//�Ѿ����͵�����
				int nBytesThisTime;			//ÿ��ʵ�ʷ��͵�����
				int nSize;					//��Ҫ���͵��ֽ���
				do
				{	

					nSize=Str.GetLength();
					nBytesThisTime = send(clientsocket[i],(char *)Str.GetBuffer(0)+nBytesSent,nSize-nBytesSent,0);//��������
					if( nBytesThisTime==SOCKET_ERROR)//SOCKET_ERROR==-1
					{
						AfxMessageBox(_T("�������ݴ���"));
						return 0;
					}
					nBytesSent+=nBytesThisTime;
				}while(nBytesSent<nSize);	
			}
		}
		p->GetDlgItem(IDC_INCOMINGMESSAGE)->SetWindowText(Str);	//�������е�����һ��������ھ�̬�ı���

		//�������Զ�����
		int   nLength   =  p->m_csComingmessage.SendMessage(WM_GETTEXTLENGTH); 
		p->m_csComingmessage.SetSel(nLength,   nLength); 
	}
}

UINT acceptconnect(LPVOID pParam)
{
	SOCKADDR_IN sockClientAddr;				   //SOCKADDR_IN�ṹ�������²�����
	int testfull=1;							   //short   sin_family;
	//u_short sin_port;
	//	struct  in_addr sin_addr;
	//	char    sin_zero[8];
	
	
    CMy20072813ServerDlg *pDlg=(CMy20072813ServerDlg*)pParam;//��öԻ���ָ��
	
    int iaddrlen=sizeof(sockClientAddr);
    while(1)
    {
		SOCKET hTempSocket=accept(g_hServerSocket,(struct sockaddr *)&sockClientAddr,&iaddrlen);//��������
		if(hTempSocket==INVALID_SOCKET)
		{
			AfxMessageBox("�������Ӵ���");
			closesocket(g_hServerSocket);	//�ر�SOCKET
			WSACleanup();
			return 0;
		}
		testfull=1;
		for (int i=0;i<8;i++)
		{
			if (clientsocket[i]==0||clientsocket[i]==INVALID_SOCKET)
			{
				testfull=0;
				clientsocket[i]=hTempSocket;
				sockfromc=hTempSocket;
				AfxBeginThread(recieve,pParam);
				break;
			}
		}
		if (testfull==1)
		{
			AfxMessageBox("�޷����ӣ�");
			break;
		}
        ////��ʾ�ͻ���IP


		CString strStatus;	//�˲�����¼���ھ�̬��������ı�
		strStatus=inet_ntoa(sockClientAddr.sin_addr);	//��ȡ�ͻ��˵�IP��ַ
		strStatus+="  is online...  ";
		pDlg->m_ListBox_Content.AddString(_T(strStatus));
		pDlg->GetDlgItem(IDC_STATUS)->SetWindowText(strStatus);//�ھ�̬������ʾ
		
    }//���ܲ�ͬ�ͻ�������
}
void CMy20072813ServerDlg::OnStart() 
{
	// TODO: Add your control notification handler code here
	CString str;
	if(GetDlgItemText(IDC_START,str),str=="Start")
	{
		SetDlgItemText(IDC_START,"Stop");
		WSADATA wsaData;
		unsigned short m_usServerPort;
		
		UpdateData();//��ȡ����
		
		/*������*/
		if(WSAStartup(0x0101,&wsaData)!=0)//��ʼ��Winsock DLL��Ӧ��
		{
			MessageBox(_T("Could not load Windows Sockets DLL."),NULL,MB_OK);
			return;
		}
		
		m_usServerPort=htons(m_sPort);//ת���˿ں��ֽ�˳��
		
		/*�����׽ӵ�ַ*/
		m_sockServerAddr.sin_family=AF_INET;
		m_sockServerAddr.sin_addr.s_addr=INADDR_ANY;
		m_sockServerAddr.sin_port=m_usServerPort;//�˿ں�
		
		g_hServerSocket=socket(AF_INET,SOCK_STREAM,0);//����SOCKET
		if(g_hServerSocket==INVALID_SOCKET)
		{
			AfxMessageBox(_T("�����׽���ʧ�ܣ�"));
			WSACleanup();
			return;
		}
		//��Server SOCKET//
		if(bind(g_hServerSocket,(LPSOCKADDR)&m_sockServerAddr,
			sizeof(m_sockServerAddr))==SOCKET_ERROR)
		{
			AfxMessageBox(_T("��ʧ��"));
			closesocket(g_hServerSocket);		//�ر�SOCKET
			WSACleanup();						//�����Socket��İ󶨲����ͷ�Socket����ռ�õ�ϵͳ��Դ
			return;
		}
		//���ü���״̬
		if(listen(g_hServerSocket,1)==SOCKET_ERROR)
		{
			AfxMessageBox(_T("��������"));
			closesocket(g_hServerSocket);		//�ر�SOCKET 
			WSACleanup();
			return;
		}
		//�������������߳�//
	AfxBeginThread(acceptconnect,this);		

	}
	else
	{
		SetDlgItemText(IDC_START,"Start");
		if(closesocket(g_hServerSocket)==SOCKET_ERROR)	//�رշ���������
		{
			AfxMessageBox("�رշ���������");
			return;
		}
		if(WSACleanup()==SOCKET_ERROR)	//WSACleanup����ʱ����0������ʱ���ش�����룬SOCKET_ERROR����ֵΪ-1		
		{
			AfxMessageBox("Cannot terminate the use of the Winsocks DLL");
			return;
		}

	}
}





void CMy20072813ServerDlg::OnClear() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_INCOMINGMESSAGE)->SetWindowText("");
}


//DEL UINT CMy20072813ServerDlg::acceptconnect(LPVOID pParam)
//DEL {
//DEL 
//DEL }
