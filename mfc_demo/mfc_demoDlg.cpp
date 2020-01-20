
// mfc_demoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfc_demo.h"
#include "mfc_demoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// Cmfc_demoDlg �Ի���




Cmfc_demoDlg::Cmfc_demoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cmfc_demoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cmfc_demoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cmfc_demoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_NEXT_FRAME, &Cmfc_demoDlg::OnBnClickedBtnNextFrame)
    ON_BN_CLICKED(IDC_BTN_PRE_FRAME, &Cmfc_demoDlg::OnBnClickedBtnPreFrame)
    ON_BN_CLICKED(IDC_BTN_PAUSE, &Cmfc_demoDlg::OnBnClickedBtnPause)
    ON_BN_CLICKED(IDC_BTN_RESUME, &Cmfc_demoDlg::OnBnClickedBtnResume)
    ON_BN_CLICKED(IDC_BTN_PLAY, &Cmfc_demoDlg::OnBnClickedBtnPlay)
    ON_BN_CLICKED(IDC_BTN_SPEED, &Cmfc_demoDlg::OnBnClickedBtnSpeed)
    ON_BN_CLICKED(IDC_BTN_SNAP, &Cmfc_demoDlg::OnBnClickedBtnSnap)
	ON_BN_CLICKED(IDC_BTN_SEEK, &Cmfc_demoDlg::OnBnClickedBtnSeek)
END_MESSAGE_MAP()


// Cmfc_demoDlg ��Ϣ�������

BOOL Cmfc_demoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_lPlayId = 0;
   
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Cmfc_demoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cmfc_demoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cmfc_demoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cmfc_demoDlg::OnBnClickedBtnNextFrame()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    //play_pause(m_lPlayId);

    play_step(m_lPlayId);
}

void Cmfc_demoDlg::OnBnClickedBtnPreFrame()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    play_step_prev(m_lPlayId);

}

void Cmfc_demoDlg::OnBnClickedBtnPause()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    play_pause(m_lPlayId);
}

void Cmfc_demoDlg::OnBnClickedBtnResume()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    play_resume(m_lPlayId);
}

void Cmfc_demoDlg::OnBnClickedBtnPlay()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
     unsigned int hWnd = (unsigned int)GetDlgItem(IDC_STATIC)->m_hWnd;
    open_mp4(m_lPlayId,"",1920,1080,50);

    play_start(m_lPlayId,hWnd);
}

void Cmfc_demoDlg::OnBnClickedBtnSpeed()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    play_speed(m_lPlayId,2);
}

void Cmfc_demoDlg::OnBnClickedBtnSnap()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    play_snap(m_lPlayId,"D:\\snap");
}

void Cmfc_demoDlg::OnBnClickedBtnSeek()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	play_seek(m_lPlayId,0);
}
