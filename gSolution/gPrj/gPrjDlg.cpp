
// gPrjDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "gPrj.h"
#include "gPrjDlg.h"
#include "afxdialogex.h"

#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CgPrjDlg ��ȭ ����

enum {
	eRet_None = 0,
	eRet_InnerCircle,
	eRet_Circle,
	eRet_Max
};

CgPrjDlg::CgPrjDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GPRJ_DIALOG, pParent)
	, m_nOldX(0)
	, m_nOldY(0)
	, m_nOldRadius(0)
	, m_nUserRadius(50)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgPrjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USER_RADIUS, m_nUserRadius);
}

BEGIN_MESSAGE_MAP(CgPrjDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_TEST, &CgPrjDlg::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_BTN_PROCESS, &CgPrjDlg::OnBnClickedBtnProcess)
	ON_BN_CLICKED(IDC_BTN_MAKE_PATTERN, &CgPrjDlg::OnBnClickedBtnMakePattern)
	ON_BN_CLICKED(IDC_BTN_GET_DATA, &CgPrjDlg::OnBnClickedBtnGetData)
	ON_BN_CLICKED(IDC_BTN_THREAD, &CgPrjDlg::OnBnClickedBtnThread)
	ON_BN_CLICKED(IDC_BUTTON_USER_DRAW, &CgPrjDlg::OnBnClickedButtonUserDraw)
END_MESSAGE_MAP()


// CgPrjDlg �޽��� ó����

BOOL CgPrjDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	//ShowWindow(SW_SHOWMAXIMIZED);
	MoveWindow(0, 0, 1280, 800);
	m_pDlgImage = new CDlgImage;
	m_pDlgImage->Create(IDD_DLGIMAGE, this);
	m_pDlgImage->ShowWindow(SW_SHOW);

	m_pDlgImgResult = new CDlgImage;
	m_pDlgImgResult->Create(IDD_DLGIMAGE, this);
	m_pDlgImgResult->ShowWindow(SW_SHOW);
	m_pDlgImgResult->MoveWindow(640, 0, 640, 480);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CgPrjDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CgPrjDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CgPrjDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CgPrjDlg::OnBnClickedBtnDlg()
//{
//	m_pDlgImage->ShowWindow(SW_SHOW);
//}


void CgPrjDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if(m_pDlgImage)		delete m_pDlgImage;
	if(m_pDlgImgResult)	delete m_pDlgImgResult;
}

void CgPrjDlg::callFunc(int n)
{
	std::cout << n << std::endl;
}

void CgPrjDlg::OnBnClickedBtnTest()
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();
	memset(fm, 0, nWidth*nHeight);

	for (int k = 0; k < MAX_POINT; k++) {
		int x = rand() % nWidth;
		int y = rand() % nHeight;
		fm[y * nPitch + x] = rand()%0xff;
		//m_pDlgImgResult->m_nDataCount = k;
		//m_pDlgImgResult->m_ptData[k].x = x;
		//m_pDlgImgResult->m_ptData[k].y = y;
	}

	int nIndex = 0;
	int nTh = 100;
	for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++) {
			if (fm[j*nPitch + i] > nTh) {
				if (m_pDlgImgResult->m_nDataCount < MAX_POINT) {
					//cout << nIndex << ":" << i << "," << j << endl;
					m_pDlgImgResult->m_ptData[nIndex].x = i;
					m_pDlgImgResult->m_ptData[nIndex].y = j;
					m_pDlgImgResult->m_nDataCount = ++nIndex;
				}
			}
		}
	}

	m_pDlgImage->Invalidate();
	m_pDlgImgResult->Invalidate();

}

#include "Process.h"
#include <chrono>
#include <thread>
using namespace std;
using namespace chrono;

void CgPrjDlg::OnBnClickedBtnProcess()
{
	auto start = system_clock::now();

	CProcess process;
	int nTh = 0;
	int nRet = process.getStarInfo(&m_pDlgImage->m_image, nTh);
//	Sleep(1000);
//	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	
	auto end = system_clock::now();
	auto millisec = duration_cast<milliseconds>(end - start);

	cout << nRet << "\t"<< millisec.count()*0.001 << "sec" <<endl;
}

void CgPrjDlg::drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray, int nOutlineGray, bool bIsClear /*= false*/)
{
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_pDlgImage->m_image.GetPitch();

	if (!bIsClear)
	{
		cout << nCenterX << "\t" << nCenterY << endl;
	}

	for (int j = y; j < y + nRadius * 2; j++) {
		for (int i = x; i < x + nRadius * 2; i++) {
			switch (isInCircle(i, j, nCenterX, nCenterY, nRadius))
			{
			case eRet_InnerCircle:
				fm[j * nPitch + i] = nGray;
				break;

			case eRet_Circle:
				fm[j * nPitch + i] = nOutlineGray;
				break;

			case eRet_None:
			default:
				break;
			}

			//if (isInCircle3(i, j, nCenterX, nCenterY, nRadius) == true)
			//{
			//	fm[j * nPitch + i] = nGray;
			//}
		}
	}
}

int CgPrjDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	int nRet = eRet_None;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if ((dDist < (nRadius * nRadius)) && (((nRadius * nRadius) - dDist) < (nRadius * 2))) {
		nRet = eRet_Circle;  //Circle shape
	}
	else if (dDist < nRadius * nRadius)
	{
		nRet = eRet_InnerCircle;
	}
	else
	{
		nRet = eRet_None;
	}

	return nRet;
}


void CgPrjDlg::drawCross(unsigned char* fm, int nCenterX, int nCenterY, int nLength)
{
	int nPitch = m_pDlgImage->m_image.GetPitch();
	const int nHalfLength = nLength / 2;

	for (int i = (nCenterY - nHalfLength); i < (nCenterY + nHalfLength); i++) {
		fm[i * nPitch + nCenterX] = 1;
	}

	for (int i = (nCenterX - nHalfLength); i < (nCenterX + nHalfLength); i++) {
		fm[nCenterY * nPitch + i] = 1;
	}
}

void CgPrjDlg::OnBnClickedBtnMakePattern()
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();
	memset(fm, 0, nWidth*nHeight);

	CRect rect(100, 100, 200, 200);
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			fm[j*nPitch + i] = rand()%0xff;
		}
	}
	m_pDlgImage->Invalidate();
}


void CgPrjDlg::OnBnClickedBtnGetData()
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();

	int nTh = 0x80;
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;
	CRect rect(0, 0, nWidth, nHeight);
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			if (fm[j*nPitch + i] > nTh) {
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}
	double dCenterX = (double)nSumX / nCount;
	double dCenterY = (double)nSumY / nCount;

	cout << dCenterX << "\t" << dCenterY << endl;

	m_pDlgImage->Invalidate();
}

void threadProcess(CWnd* pParent, CRect rect, int *nRet)
{
	CgPrjDlg *pWnd = (CgPrjDlg*)pParent;
	*nRet = pWnd->processImg(rect);
}

void CgPrjDlg::OnBnClickedBtnThread()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	auto start = system_clock::now();

	int nImgSize = 4096 * 4;
	CRect rect(0, 0, nImgSize, nImgSize);
	CRect rt[4];
	int nRet[4];
	for (int k = 0; k < 4; k++) {
		rt[k] = rect;
		rt[k].OffsetRect(nImgSize*(k % 2), nImgSize*int(k / 2));
	}
	thread _thread0(threadProcess, this, rt[0], &nRet[0]);
	thread _thread1(threadProcess, this, rt[1], &nRet[1]);
	thread _thread2(threadProcess, this, rt[2], &nRet[2]);
	thread _thread3(threadProcess, this, rt[3], &nRet[3]);

	_thread0.join();
	_thread1.join();
	_thread2.join();
	_thread3.join();

	int nSum;
	for (int k = 0; k < 4; k++)
		nSum += nRet[k];

	auto end = system_clock::now();
	auto millisec = duration_cast<milliseconds>(end - start);

	cout << nSum << "\t" << millisec.count()*0.001 << "sec" << endl;

}

int CgPrjDlg::processImg(CRect rect)
{
	auto start = system_clock::now();

	CProcess process;
	int nTh = 0;
	int nRet = process.getStarInfo(&m_pDlgImage->m_image, nTh, rect);

	auto end = system_clock::now();
	auto millisec = duration_cast<milliseconds>(end - start);

	cout << nRet << "\t" << millisec.count()*0.001 << "sec" << endl;
	return nRet;
}

bool CgPrjDlg::UserRadius_ValidCheck(int &nValidRadius)
{
	bool bResult = true;
	CString strRadius = _T("");
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_USER_RADIUS);
	pEdit->GetWindowText(strRadius);
	const int nRadius = _ttoi(strRadius);

	if (nRadius < 10 || nRadius > 200)
	{
		//pEdit->SetWindowText(_T("50"));
		bResult = false;
	}
	else
	{
		nValidRadius = nRadius;
	}

	return bResult;
}

void CgPrjDlg::OnBnClickedButtonUserDraw()
{
	static bool bFirst = true;
	int nValidRadius = 0;
	if (!UserRadius_ValidCheck(nValidRadius))
	{
		return;
	}

	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();
	if (bFirst)
	{
		memset(fm, 0x0, nWidth * nHeight);
		bFirst = false;
	}

	CRect rect;// (100, 100, 200, 200);
	m_pDlgImage->GetWindowRect(&rect);
	m_pDlgImage->ScreenToClient(&rect);

	int x = rand() % rect.Width();
	int y = rand() % rect.Height();

	const int nRadius = nValidRadius;

	if (m_nOldX > 0 && m_nOldY > 0 && m_nOldRadius > 0)
	{
		drawCircle(fm, m_nOldX, m_nOldY, m_nOldRadius, 0, 0, true);  //Clear
	}

	drawCircle(fm, x, y, nRadius, 0x0, 2);
	drawCross(fm, x + nRadius, y + nRadius, 20);  //Red cross line

	m_pDlgImage->Invalidate();

	// Backup position of the current circle
	m_nOldX = x;
	m_nOldY = y;
	m_nOldRadius = nRadius;
}
