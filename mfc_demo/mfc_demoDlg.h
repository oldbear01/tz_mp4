
// mfc_demoDlg.h : ͷ�ļ�
//

#pragma once


// Cmfc_demoDlg �Ի���
class Cmfc_demoDlg : public CDialog
{
// ����
public:
	Cmfc_demoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFC_DEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
public:
    unsigned int m_lPlayId ;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnNextFrame();
    afx_msg void OnBnClickedBtnPreFrame();
    afx_msg void OnBnClickedBtnPause();
    afx_msg void OnBnClickedBtnResume();
    afx_msg void OnBnClickedBtnPlay();
    afx_msg void OnBnClickedBtnSpeed();
    afx_msg void OnBnClickedBtnSnap();
	afx_msg void OnBnClickedBtnSeek();
};
