
// gPrjDlg.h : ��� ����
//
#include "DlgImage.h"

#pragma once


// CgPrjDlg ��ȭ ����
class CgPrjDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CgPrjDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	CDlgImage *m_pDlgImage;
	CDlgImage *m_pDlgImgResult;

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GPRJ_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedBtnDlg();
	afx_msg void OnDestroy();

	void callFunc(int n);
	afx_msg void OnBnClickedBtnTest();
	afx_msg void OnBnClickedBtnProcess();
	afx_msg void OnBnClickedBtnMakePattern();
	afx_msg void OnBnClickedBtnGetData();
	afx_msg void OnBnClickedBtnThread();
	int processImg(CRect rect);

// hokim
protected:
	int m_nOldX, m_nOldY, m_nOldRadius;
	
public:
	int m_nUserRadius;
	afx_msg void OnBnClickedButtonUserDraw();
	bool UserRadius_ValidCheck(int &nValidRadius);
	void drawCircle(unsigned char* fm, int i, int j, int nRadius, int nGray = 0x0, int nOutlineGray = 0x0, bool bIsClear = false);
	int isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	void drawCross(unsigned char* fm, int nCenterX, int nCenterY, int nLength);
};
