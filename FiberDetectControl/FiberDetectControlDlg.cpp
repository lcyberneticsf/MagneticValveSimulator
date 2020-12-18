
// FiberDetectControlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FiberDetectControl.h"
#include "FiberDetectControlDlg.h"
#include "afxdialogex.h"
#include "MagneticValve.h"
#include "NetSetting.h"
#include "DetectParametersSetting.h"
#include	<thread>
#include	<queue>
#include	<string>
#include	<io.h>
#pragma comment(lib,"Version.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace aq;
using namespace std;
using namespace cv;
using namespace Vsee;
std::queue<InferFrame>		CFiberDetectControlDlg::infer_queue;
HWND CFiberDetectControlDlg::m_hWnd;
HWND m_hMainWnd;
CMFCButton* CFiberDetectControlDlg::m_mfcMagneticValve[MAGNETIC_VALVE_SUM];
_io_output_transac_tag_  CFiberDetectControlDlg::valve_driver[MAGNETIC_VALVE_SUM];

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	virtual BOOL OnInitDialog();
	void  GetVersion(CString &ver);

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void CAboutDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString strVersion;
	GetVersion(strVersion);
	CString strVersionInfo;
	strVersionInfo.Format("版本号:%s", strVersion);
	GetDlgItem(IDC_STATIC_VERSION)->SetWindowTextA(strVersionInfo);
	return true;
}
void CAboutDlg::GetVersion(CString &ver)
{
	DWORD dwInfoSize = 0;
	TCHAR exePath[MAX_PATH];
	memset(exePath, 0, sizeof(exePath));

	ver.Format(_T("V1.00"));

	// 得到程序的自身路径
	GetModuleFileName(NULL, exePath, sizeof(exePath) / sizeof(TCHAR));

	// 判断是否能获取版本号
	dwInfoSize = GetFileVersionInfoSize(exePath, NULL);

	if (dwInfoSize == 0)
	{
		::OutputDebugString("GetFileVersionInfoSize fail\r\n");
	}
	else
	{
		BYTE* pData = new BYTE[dwInfoSize];

		// 获取版本信息
		if (!GetFileVersionInfo(exePath, NULL, dwInfoSize, pData))
		{
			::OutputDebugString("GetFileVersionInfo fail\r\n");
		}
		else
		{
			// 查询版本信息中的具体键值
			LPVOID lpBuffer;
			UINT uLength;
			if (!::VerQueryValue((LPCVOID)pData, _T("\\"), &lpBuffer, &uLength))
			{
				::OutputDebugString("GetFileVersionInfo fail\r\n");
			}
			else
			{
				DWORD dwVerMS;
				DWORD dwVerLS;
				dwVerMS = ((VS_FIXEDFILEINFO*)lpBuffer)->dwProductVersionMS;
				dwVerLS = ((VS_FIXEDFILEINFO*)lpBuffer)->dwProductVersionLS;
				ver.Format(_T("V%d.%d.%d.%d"), (dwVerMS >> 16), (dwVerMS & 0xFFFF), (dwVerLS >> 16), (dwVerLS & 0xFFFF));
			}
		}

		delete pData;
	}
}

// CFiberDetectControlDlg 对话框



CFiberDetectControlDlg::CFiberDetectControlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFiberDetectControlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	communicator_ = new aq::Communicator;	
	communicator_->camera_scan_speed = 10;
}

void CFiberDetectControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCBUTTON_MAGNETIC_VOLVE1, m_mfcMagneticValve1);
	DDX_Control(pDX, IDC_MFCBUTTON_MAGNETIC_VOLVE2, m_mfcMagneticValve2);
	DDX_Control(pDX, IDC_MFCBUTTON_MAGNETIC_VOLVE3, m_mfcMagneticValve3);
	DDX_Control(pDX, IDC_MFCBUTTON_MAGNETIC_VOLVE4, m_mfcMagneticValve4);
	DDX_Control(pDX, IDC_MFCBUTTON_MAGNETIC_VOLVE5, m_mfcMagneticValve5);
	DDX_Control(pDX, IDC_MFCBUTTON_MAGNETIC_VOLVE6, m_mfcMagneticValve6);
	DDX_Control(pDX, IDC_MFCBUTTON_MAGNETIC_VOLVE7, m_mfcMagneticValve7);
	DDX_Control(pDX, IDC_MFCBUTTON_MAGNETIC_VOLVE8, m_mfcMagneticValve8);
	DDX_Control(pDX, IDC_MFCBUTTON_MAGNETIC_VOLVE9, m_mfcMagneticValve9);
	DDX_Control(pDX, IDC_MFCBUTTON_MAGNETIC_VOLVE10, m_mfcMagneticValve10);
	DDX_Control(pDX, IDC_MFCBUTTON_MAGNETIC_VOLVE11, m_mfcMagneticValve11);
	DDX_Control(pDX, IDC_MFCBUTTON_MAGNETIC_VOLVE12, m_mfcMagneticValve12);
	DDX_Control(pDX, IDC_MFCBUTTON_MAGNETIC_VOLVE13, m_mfcMagneticValve13);
	DDX_Control(pDX, IDC_MFCBUTTON_MAGNETIC_VOLVE14, m_mfcMagneticValve14);
	DDX_Control(pDX, IDC_MFCBUTTON_MAGNETIC_VOLVE15, m_mfcMagneticValve15);
	DDX_Control(pDX, IDC_MFCBUTTON_MAGNETIC_VOLVE16, m_mfcMagneticValve16);
	DDX_Control(pDX, IDC_MFCBUTTON_MAGNETIC_VOLVE17, m_mfcMagneticValve17);
	DDX_Control(pDX, IDC_MFCBUTTON_MAGNETIC_VOLVE18, m_mfcMagneticValve18);
	DDX_Control(pDX, IDC_MFCBUTTON_MAGNETIC_VOLVE19, m_mfcMagneticValve19);
	DDX_Control(pDX, IDC_MFCBUTTON_MAGNETIC_VOLVE20, m_mfcMagneticValve20);
	DDX_Control(pDX, IDC_MFCBUTTON_MAGNETIC_VOLVE21, m_mfcMagneticValve21);
	DDX_Control(pDX, IDC_MFCBUTTON_MAGNETIC_VOLVE22, m_mfcMagneticValve22);
	DDX_Control(pDX, IDC_MFCBUTTON_MAGNETIC_VOLVE23, m_mfcMagneticValve23);
	DDX_Control(pDX, IDC_MFCBUTTON_MAGNETIC_VOLVE24, m_mfcMagneticValve24);
	DDX_Control(pDX, IDC_CHECK_SERVER_MODE_SELECT, m_checkServerModeSelect);
	DDX_Control(pDX, IDC_CHECK_MODE_SELECT, m_checkClientMode);
	DDX_Control(pDX, IDC_CHECK_SERVER_SEND, m_checkServerSend);
	DDX_Control(pDX, IDC_CHECK_CLIENT_SEND, m_checkClientSend);
	DDX_Control(pDX, IDC_CHECK_UDP_SELECT, m_checkUDPMode);
}

BEGIN_MESSAGE_MAP(CFiberDetectControlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_HARDWARE_TEST, &CFiberDetectControlDlg::OnBnClickedButtonHardwareTest)
	ON_BN_CLICKED(IDC_BUTTON_NET_PARAMETERS_SETTING, &CFiberDetectControlDlg::OnBnClickedButtonNetParametersSetting)
	ON_BN_CLICKED(IDC_BUTTON_PARAMETERS_SETTING, &CFiberDetectControlDlg::OnBnClickedButtonParametersSetting)
	
	ON_BN_CLICKED(IDC_START_SERVER, &CFiberDetectControlDlg::OnBnClickedStartServer)
	ON_BN_CLICKED(IDC_CHECK_SERVER_MODE_SELECT, &CFiberDetectControlDlg::OnBnClickedCheckServerModeSelect)
	ON_BN_CLICKED(IDC_CHECK_MODE_SELECT, &CFiberDetectControlDlg::OnBnClickedCheckModeSelect)
	ON_BN_CLICKED(IDC_CHECK_SERVER_SEND, &CFiberDetectControlDlg::OnBnClickedCheckServerSend)
	ON_BN_CLICKED(IDC_CHECK_CLIENT_SEND, &CFiberDetectControlDlg::OnBnClickedCheckClientSend)
	ON_MESSAGE(ID_SHOWCTRLMESSAGE, ShowCtrlMessage)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_START_DETECT, &CFiberDetectControlDlg::OnBnClickedButtonStartDetect)
	ON_BN_CLICKED(IDC_BUTTON_STOP_DETECT2, &CFiberDetectControlDlg::OnBnClickedButtonStopDetect2)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CFiberDetectControlDlg 消息处理程序

BOOL CFiberDetectControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中.

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//ShowWindow(SW_MINIMIZE);
	m_hWnd = AfxGetMainWnd()->m_hWnd;            //To get the main Window Handle;
	m_hMainWnd = m_hWnd;

	CMFCButton* mfcb = (CMFCButton*)GetDlgItem(IDC_START_SERVER);
	mfcb->m_bTransparent = FALSE;
	mfcb->m_bDontUseWinXPTheme = TRUE;
	mfcb->m_bDrawFocus = FALSE;
	mfcb->m_nFlatStyle = CMFCButton::BUTTONSTYLE_3D;
	//mfcb->SetFaceColor(RGB(240,240 , 240));

	m_mfcMagneticValve1.m_bTransparent = FALSE;
	m_mfcMagneticValve1.m_bDontUseWinXPTheme = TRUE;
	m_mfcMagneticValve1.m_bDrawFocus = FALSE;
	m_mfcMagneticValve1.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_mfcMagneticValve1.SetFaceColor(RGB(0, 255, 0));

	m_mfcMagneticValve2.m_bTransparent = FALSE;
	m_mfcMagneticValve2.m_bDontUseWinXPTheme = TRUE;
	m_mfcMagneticValve2.m_bDrawFocus = FALSE;
	m_mfcMagneticValve2.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_mfcMagneticValve2.SetFaceColor(RGB(0, 255, 0));

	m_mfcMagneticValve3.m_bTransparent = FALSE;
	m_mfcMagneticValve3.m_bDontUseWinXPTheme = TRUE;
	m_mfcMagneticValve3.m_bDrawFocus = FALSE;
	m_mfcMagneticValve3.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_mfcMagneticValve3.SetFaceColor(RGB(0, 255, 0));

	m_mfcMagneticValve4.m_bTransparent = FALSE;
	m_mfcMagneticValve4.m_bDontUseWinXPTheme = TRUE;
	m_mfcMagneticValve4.m_bDrawFocus = FALSE;
	m_mfcMagneticValve4.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_mfcMagneticValve4.SetFaceColor(RGB(0, 255, 0));

	m_mfcMagneticValve5.m_bTransparent = FALSE;
	m_mfcMagneticValve5.m_bDontUseWinXPTheme = TRUE;
	m_mfcMagneticValve5.m_bDrawFocus = FALSE;
	m_mfcMagneticValve5.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_mfcMagneticValve5.SetFaceColor(RGB(0, 255, 0));

	m_mfcMagneticValve6.m_bTransparent = FALSE;
	m_mfcMagneticValve6.m_bDontUseWinXPTheme = TRUE;
	m_mfcMagneticValve6.m_bDrawFocus = FALSE;
	m_mfcMagneticValve6.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_mfcMagneticValve6.SetFaceColor(RGB(0, 255, 0));

	m_mfcMagneticValve7.m_bTransparent = FALSE;
	m_mfcMagneticValve7.m_bDontUseWinXPTheme = TRUE;
	m_mfcMagneticValve7.m_bDrawFocus = FALSE;
	m_mfcMagneticValve7.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_mfcMagneticValve7.SetFaceColor(RGB(0, 255, 0));

	m_mfcMagneticValve8.m_bTransparent = FALSE;
	m_mfcMagneticValve8.m_bDontUseWinXPTheme = TRUE;
	m_mfcMagneticValve8.m_bDrawFocus = FALSE;
	m_mfcMagneticValve8.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_mfcMagneticValve8.SetFaceColor(RGB(0, 255, 0));

	m_mfcMagneticValve9.m_bTransparent = FALSE;
	m_mfcMagneticValve9.m_bDontUseWinXPTheme = TRUE;
	m_mfcMagneticValve9.m_bDrawFocus = FALSE;
	m_mfcMagneticValve9.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_mfcMagneticValve9.SetFaceColor(RGB(0, 255, 0));

	m_mfcMagneticValve10.m_bTransparent = FALSE;
	m_mfcMagneticValve10.m_bDontUseWinXPTheme = TRUE;
	m_mfcMagneticValve10.m_bDrawFocus = FALSE;
	m_mfcMagneticValve10.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_mfcMagneticValve10.SetFaceColor(RGB(0, 255, 0));

	m_mfcMagneticValve11.m_bTransparent = FALSE;
	m_mfcMagneticValve11.m_bDontUseWinXPTheme = TRUE;
	m_mfcMagneticValve11.m_bDrawFocus = FALSE;
	m_mfcMagneticValve11.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_mfcMagneticValve11.SetFaceColor(RGB(0, 255, 0));

	m_mfcMagneticValve12.m_bTransparent = FALSE;
	m_mfcMagneticValve12.m_bDontUseWinXPTheme = TRUE;
	m_mfcMagneticValve12.m_bDrawFocus = FALSE;
	m_mfcMagneticValve12.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_mfcMagneticValve12.SetFaceColor(RGB(0, 255, 0));

	m_mfcMagneticValve13.m_bTransparent = FALSE;
	m_mfcMagneticValve13.m_bDontUseWinXPTheme = TRUE;
	m_mfcMagneticValve13.m_bDrawFocus = FALSE;
	m_mfcMagneticValve13.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_mfcMagneticValve13.SetFaceColor(RGB(0, 255, 0));

	m_mfcMagneticValve14.m_bTransparent = FALSE;
	m_mfcMagneticValve14.m_bDontUseWinXPTheme = TRUE;
	m_mfcMagneticValve14.m_bDrawFocus = FALSE;
	m_mfcMagneticValve14.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_mfcMagneticValve14.SetFaceColor(RGB(0, 255, 0));

	m_mfcMagneticValve15.m_bTransparent = FALSE;
	m_mfcMagneticValve15.m_bDontUseWinXPTheme = TRUE;
	m_mfcMagneticValve15.m_bDrawFocus = FALSE;
	m_mfcMagneticValve15.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_mfcMagneticValve15.SetFaceColor(RGB(0, 255, 0));

	m_mfcMagneticValve16.m_bTransparent = FALSE;
	m_mfcMagneticValve16.m_bDontUseWinXPTheme = TRUE;
	m_mfcMagneticValve16.m_bDrawFocus = FALSE;
	m_mfcMagneticValve16.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_mfcMagneticValve16.SetFaceColor(RGB(0, 255, 0));

	m_mfcMagneticValve17.m_bTransparent = FALSE;
	m_mfcMagneticValve17.m_bDontUseWinXPTheme = TRUE;
	m_mfcMagneticValve17.m_bDrawFocus = FALSE;
	m_mfcMagneticValve17.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_mfcMagneticValve17.SetFaceColor(RGB(0, 255, 0));

	m_mfcMagneticValve18.m_bTransparent = FALSE;
	m_mfcMagneticValve18.m_bDontUseWinXPTheme = TRUE;
	m_mfcMagneticValve18.m_bDrawFocus = FALSE;
	m_mfcMagneticValve18.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_mfcMagneticValve18.SetFaceColor(RGB(0, 255, 0));

	m_mfcMagneticValve19.m_bTransparent = FALSE;
	m_mfcMagneticValve19.m_bDontUseWinXPTheme = TRUE;
	m_mfcMagneticValve19.m_bDrawFocus = FALSE;
	m_mfcMagneticValve19.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_mfcMagneticValve19.SetFaceColor(RGB(0, 255, 0));

	m_mfcMagneticValve20.m_bTransparent = FALSE;
	m_mfcMagneticValve20.m_bDontUseWinXPTheme = TRUE;
	m_mfcMagneticValve20.m_bDrawFocus = FALSE;
	m_mfcMagneticValve20.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_mfcMagneticValve20.SetFaceColor(RGB(0, 255, 0));

	m_mfcMagneticValve21.m_bTransparent = FALSE;
	m_mfcMagneticValve21.m_bDontUseWinXPTheme = TRUE;
	m_mfcMagneticValve21.m_bDrawFocus = FALSE;
	m_mfcMagneticValve21.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_mfcMagneticValve21.SetFaceColor(RGB(0, 255, 0));

	m_mfcMagneticValve22.m_bTransparent = FALSE;
	m_mfcMagneticValve22.m_bDontUseWinXPTheme = TRUE;
	m_mfcMagneticValve22.m_bDrawFocus = FALSE;
	m_mfcMagneticValve22.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_mfcMagneticValve22.SetFaceColor(RGB(0, 255, 0));

	m_mfcMagneticValve23.m_bTransparent = FALSE;
	m_mfcMagneticValve23.m_bDontUseWinXPTheme = TRUE;
	m_mfcMagneticValve23.m_bDrawFocus = FALSE;
	m_mfcMagneticValve23.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_mfcMagneticValve23.SetFaceColor(RGB(0, 255, 0));

	m_mfcMagneticValve24.m_bTransparent = FALSE;
	m_mfcMagneticValve24.m_bDontUseWinXPTheme = TRUE;
	m_mfcMagneticValve24.m_bDrawFocus = FALSE;
	m_mfcMagneticValve24.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_mfcMagneticValve24.SetFaceColor(RGB(0, 255, 0));

	m_mfcMagneticValve[0] = new CMFCButton;
	m_mfcMagneticValve[0] = &m_mfcMagneticValve1;

	m_mfcMagneticValve[1] = new CMFCButton;
	m_mfcMagneticValve[1] = &m_mfcMagneticValve2;

	m_mfcMagneticValve[2] = new CMFCButton;
	m_mfcMagneticValve[2] = &m_mfcMagneticValve3;

	m_mfcMagneticValve[3] = new CMFCButton;
	m_mfcMagneticValve[3] = &m_mfcMagneticValve4;

	m_mfcMagneticValve[4] = new CMFCButton;
	m_mfcMagneticValve[4] = &m_mfcMagneticValve5;

	m_mfcMagneticValve[5] = new CMFCButton;
	m_mfcMagneticValve[5] = &m_mfcMagneticValve6;

	m_mfcMagneticValve[6] = new CMFCButton;
	m_mfcMagneticValve[6] = &m_mfcMagneticValve7;

	m_mfcMagneticValve[7] = new CMFCButton;
	m_mfcMagneticValve[7] = &m_mfcMagneticValve8;

	m_mfcMagneticValve[8] = new CMFCButton;
	m_mfcMagneticValve[8] = &m_mfcMagneticValve9;

	m_mfcMagneticValve[9] = new CMFCButton;
	m_mfcMagneticValve[9] = &m_mfcMagneticValve10;

	m_mfcMagneticValve[10] = new CMFCButton;
	m_mfcMagneticValve[10] = &m_mfcMagneticValve11;

	m_mfcMagneticValve[11] = new CMFCButton;
	m_mfcMagneticValve[11] = &m_mfcMagneticValve12;

	m_mfcMagneticValve[12] = new CMFCButton;
	m_mfcMagneticValve[12] = &m_mfcMagneticValve13;

	m_mfcMagneticValve[13] = new CMFCButton;
	m_mfcMagneticValve[13] = &m_mfcMagneticValve14;

	m_mfcMagneticValve[14] = new CMFCButton;
	m_mfcMagneticValve[14] = &m_mfcMagneticValve15;

	m_mfcMagneticValve[15] = new CMFCButton;
	m_mfcMagneticValve[15] = &m_mfcMagneticValve16;

	m_mfcMagneticValve[16] = new CMFCButton;
	m_mfcMagneticValve[16] = &m_mfcMagneticValve17;

	m_mfcMagneticValve[17] = new CMFCButton;
	m_mfcMagneticValve[17] = &m_mfcMagneticValve18;

	m_mfcMagneticValve[18] = new CMFCButton;
	m_mfcMagneticValve[18] = &m_mfcMagneticValve19;

	m_mfcMagneticValve[19] = new CMFCButton;
	m_mfcMagneticValve[19] = &m_mfcMagneticValve20;

	m_mfcMagneticValve[20] = new CMFCButton;
	m_mfcMagneticValve[20] = &m_mfcMagneticValve21;

	m_mfcMagneticValve[21] = new CMFCButton;
	m_mfcMagneticValve[21] = &m_mfcMagneticValve22;

	m_mfcMagneticValve[22] = new CMFCButton;
	m_mfcMagneticValve[22] = &m_mfcMagneticValve23;

	m_mfcMagneticValve[23] = new CMFCButton;
	m_mfcMagneticValve[23] = &m_mfcMagneticValve24;

	for (int i = 0; i < MAGNETIC_VALVE_SUM; i++)  //MAGNETIC_VALVE_SUM
	{	
		valve_driver[i].dura=0;	
	}

	m_bServerMode = true;
	m_bClientMode = false;
	m_checkServerModeSelect.SetCheck(m_bServerMode);
	m_checkClientMode.SetCheck(m_bClientMode);

	m_bServerSendMode = false;
	m_bClientSendMode = true;
	communicator_->m_bServerSendMode = m_bServerSendMode;
	communicator_->m_bClientSendMode = m_bClientSendMode;
	m_checkServerSend.SetCheck(m_bServerSendMode);
	m_checkClientSend.SetCheck(m_bClientSendMode);

	m_pwnd = GetDlgItem(IDC_STATIC_IMAGE_SHOW);//IDC_SHOWIMAGE
	//m_pwnd = GetDlgItem(IDC_SHOWIMAGE);//IDC_SHOWIMAGE
	//pwnd->MoveWindow(35,30,352,288);
	m_pDC = m_pwnd->GetDC();
	//pDC =GetDC();
	m_hDC = m_pDC->GetSafeHdc();
	m_pwnd->GetClientRect(&m_ImageRect);
	m_pDC->TextOut(20, 20, "写字");
	m_nRectWidth = m_ImageRect.Width();
	m_nRectHeight = m_ImageRect.Height();

	CString cs_str;
	string str_str;
	str_str = cs_str;
	Point P1, P2, P0, P3;
	Point pRect1, pRect2;
	POINT  pTopLeft, pRightBottom;
	pTopLeft.x = 5000; pTopLeft.y = 5000; pRightBottom.x = 0; pRightBottom.y = 0;
	CString strText = "经纬异纤检测电磁阀模拟器";
	CRect DrawRect(100, 100, 300, 100);
	ShowText(m_pwnd, strText, DrawRect);
	for (int i = 0; i < SHOWTEXTLENGTH; i++)
	{
		memset(m_strShowText[i], 0, 255);
	}
	ReadIni();
	m_checkUDPMode.SetCheck(true);
	int nUDPMode = m_checkUDPMode.GetCheck();
	if (nUDPMode == 1)
	{
		m_bTcpMode = false;
	}
	else
	{
		m_bTcpMode = true;
	}
	OnBnClickedStartServer();
	SetTimer(1, 2, nullptr);
	
//	Sleep(200);
//	run_tcp_server("192.168.1.11", 9713);
//	Sleep(200);

	// TODO:  在此添加额外的初始化代码
	SetWindowTextA("MagneticValveSimulator电磁阀模拟器");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFiberDetectControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFiberDetectControlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
		RefreshWnd(m_pwnd);   //clear the print words from the show window;

		CString cs_str;
		string str_str;
		str_str = cs_str;
		Point P1, P2, P0, P3;
		Point pRect1, pRect2;
		POINT  pTopLeft, pRightBottom;
		pTopLeft.x = 5000; pTopLeft.y = 5000; pRightBottom.x = 0; pRightBottom.y = 0;
		CString strText = "经纬异纤检测";
		CRect DrawRect(0, 0, 300, 100);
		ShowText(m_pwnd, strText, DrawRect);
	}
	else
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		//SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		//// 使图标在工作区矩形中居中
		//int cxIcon = GetSystemMetrics(SM_CXICON);
		//int cyIcon = GetSystemMetrics(SM_CYICON);
		//CRect rect;
		//GetClientRect(&rect);
		//int x = (rect.Width() - cxIcon + 1) / 2;
		//int y = (rect.Height() - cyIcon + 1) / 2;
		RefreshWnd(m_pwnd);   //clear the print words from the show window;

		CString cs_str;
		string str_str;
		str_str = cs_str;
		Point P1, P2, P0, P3;
		Point pRect1, pRect2;
		POINT  pTopLeft, pRightBottom;
		pTopLeft.x = 5000; pTopLeft.y = 5000; pRightBottom.x = 0; pRightBottom.y = 0;
		CString strText = "经纬异纤检测电磁阀模拟器启动";
		PushTailShowText(strText);
		CRect DrawRect(0, 0, 300, 50);
		ShowText(m_pwnd, m_strShowText, nullptr);

		strText.Format("服务器地址:%s,端口号:%d", parameters_setting_trans.electric_board_ip, parameters_setting_trans.electric_board_port);
		PushTailShowText(strText);
		ShowText(m_pwnd, m_strShowText, nullptr);

		//OnBnClickedStartServer();

		CDialogEx::OnPaint();
		
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFiberDetectControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFiberDetectControlDlg::OnBnClickedButtonHardwareTest()
{
	// TODO:  在此添加控件通知处理程序代码
	CMagneticValve dlg;
	if (dlg.DoModal()!=IDOK)
		return;

}


void CFiberDetectControlDlg::OnBnClickedButtonNetParametersSetting()
{
	// TODO:  在此添加控件通知处理程序代码
	CNetSetting dlg;
	if (dlg.DoModal() != IDOK)
		return;

	int camera_total;
	char IniRead[255];
	memset(IniRead, 0, 255);
	char IniPath[255];
	memset(IniPath, 0, 255);
	//camera_ip_info ci_info;
	CString strPath = GetModulePath();
	strcpy_s(IniPath, 255, strPath.GetBuffer());
	strcat_s(IniPath, "/param.ini");
	GetPrivateProfileStringA("System", "box1_ip", "", IniRead, 24, IniPath);
	//m_dlgNetworkParameters.GetDlgItem(IDC_EDIT_IP_ADRESS)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("System", "box1_port", "", IniRead, 24, IniPath);
	//m_dlgNetworkParameters.GetDlgItem(IDC_EDIT_IP_PORT_NUMBER)->SetWindowTextA(IniRead);

	parameters_setting_trans.signalling = 1;     //Use siggnalling = 1 to indicate send the network setting command;
	
	GetPrivateProfileStringA("System", "box1_ip", "", IniRead, 24, IniPath);
	strcpy(parameters_setting_trans.box1_ip , IniRead);
	GetPrivateProfileStringA("System", "box1_port", "", IniRead, 24, IniPath);
	parameters_setting_trans.box1_port = atoi(IniRead);

	GetPrivateProfileStringA("System", "box2_ip", "", IniRead, 24, IniPath);
	strcpy(parameters_setting_trans.box2_ip , IniRead);
	GetPrivateProfileStringA("System", "box2_port", "", IniRead, 24, IniPath);
	parameters_setting_trans.box2_port = atoi(IniRead);

	GetPrivateProfileStringA("System", "electric_board_ip", "", IniRead, 24, IniPath);
	strcpy(parameters_setting_trans.electric_board_ip , IniRead);
	GetPrivateProfileStringA("System", "electric_board_port", "", IniRead, 24, IniPath);
	parameters_setting_trans.electric_board_port = atoi(IniRead);

	GetPrivateProfileStringA("System", "local_ip", "", IniRead, 24, IniPath);
	strcpy(parameters_setting_trans.local_ip , IniRead);
	GetPrivateProfileStringA("System", "local_port", "", IniRead, 24, IniPath);
	parameters_setting_trans.local_port = atoi(IniRead);

	GetPrivateProfileStringA("CameraSetting", "cameraA_ip", "", IniRead, 24, IniPath);
	strcpy(parameters_setting_trans.cameraA_ip , IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraA_port", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraA_port = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraA_scan_speed", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraA_scan_speed = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraA_tirgging_mode", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraA_tirgging_mode = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraA_exposure_time", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraA_exposure_time = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraA_gain", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraA_gain = atoi(IniRead);

	GetPrivateProfileStringA("CameraSetting", "cameraB_ip", "", IniRead, 24, IniPath);
	strcpy(parameters_setting_trans.cameraB_ip , IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraB_port", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraB_port = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraB_scan_speed", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraB_scan_speed = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraB_tirgging_mode", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraB_tirgging_mode = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraB_exposure_time", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraB_exposure_time = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraB_gain", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraB_gain = atoi(IniRead);

	GetPrivateProfileStringA("CameraSetting", "cameraC_ip", "", IniRead, 24, IniPath);
	strcpy(parameters_setting_trans.cameraC_ip , IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraC_port", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraC_port = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraC_scan_speed", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraC_scan_speed = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraC_tirgging_mode", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraC_tirgging_mode = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraC_exposure_time", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraC_exposure_time = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraC_gain", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraC_gain = atoi(IniRead);

	GetPrivateProfileStringA("CameraSetting", "cameraD_ip", "", IniRead, 24, IniPath);
	strcpy(parameters_setting_trans.cameraD_ip , IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraD_port", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraD_port = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraD_scan_speed", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraD_scan_speed = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraD_tirgging_mode", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraD_tirgging_mode = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraD_exposure_time", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraD_exposure_time = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraD_gain", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraD_gain = atoi(IniRead);

}


void CFiberDetectControlDlg::OnBnClickedButtonParametersSetting()
{
	// TODO:  在此添加控件通知处理程序代码
	CDetectParametersSetting dlg;
	if (dlg.DoModal() != IDOK)
		return;
}


void CFiberDetectControlDlg::run_tcp_server(std::string _ip, int _port)
{
	std::thread t(&CFiberDetectControlDlg::tcp_server, this, _ip, _port);
	t.detach();
}

void CFiberDetectControlDlg::run_udp_server(std::string _ip, int _port)
{
	std::thread t(&CFiberDetectControlDlg::udp_server, this, _ip, _port);
	t.detach();
}


void CFiberDetectControlDlg::tcp_server(std::string _ip, int _port)
{

	std::string error_str;
	if (!communicator_->server(_ip, _port, error_str))	//Start a Server state machine,to server for all the net request from client,
	{													//here the the function "server()" actuall is an endless loop.
		std::cerr << error_str << std::endl;
		return;
	}
}

void CFiberDetectControlDlg::udp_server(std::string _ip, int _port)
{

	std::string error_str;
	if (!communicator_->udp_rcv_server(_ip, _port, error_str))	//Start a Server state machine,to server for all the net request from client,
	{													//here the the function "server()" actuall is an endless loop.
		std::cerr << error_str << std::endl;
		return;
	}
}

void CFiberDetectControlDlg::run_tcp_client(std::string _ip, int _port)
{
	//ios[0] = new io_service(1);
	//sockets[0] = new tcp::socket(*ios[0]);
	//eps[0] = tcp::endpoint(address::from_string(_ip), _port);
	////asio::io_service* io;
	//std::thread t(&CDataSimulatorDlg::tcp_client, this, _ip, _port, ios[0]);
	//t.detach();
	int nsize = sizeof(std::size_t);
	nsize = sizeof(int);
	nsize = sizeof(std::string);

	communicator_->run_tcp_connect(_ip, _port);
}

void CFiberDetectControlDlg::tcp_client(std::string _ip, int port, io_service* io)
{
	while (true)
	{
		//connect_and_reconnect(_ip, _port, io);
		connect_and_reconnect(0, 1, *io);
		io->run();			//只有在IO.run()运行后，socket才开始起启动
		//	sessions[0]->startSession();

	}
}


bool  CFiberDetectControlDlg::connect_and_reconnect(int beg, int end, asio::io_service& io)
{
	for (int i = beg; i < end; ++i)
	{
		auto socket = sockets[i];

		if (!sessions[i])		//如果第一次执行sessions[i]还没有初始化，则进行如下的初始化操作
		{						//如果不是第一次执行，则下述代码不执行
			sessions[i] = new Vsee::VTx2Session(*socket);

			sessions[i]->setProcessFrameFunc([&, i](VCameraFrame&& frame) //将sessions[i]->_process_frame_func设置为以下{ ...}中的执行代码,但仅仅是定义_process_frame_func，
			{								 //在此时并不执行_process_frame_func()函数，需在VCameraSession::asyncRecv()->VTx2Session::ProcessMessage()函数被调用时才会执行

				//MutexLock lock(infer_mutex);
				infer_queue.push(InferFrame(sessions[i], std::move(frame)));//定义一个InferFrame,InferFrame._session=sessions[i],InferFrame._frame=frame,并将InferFrame;
				//push进infer_queue中
				VCameraFrame _frame;
			});

			sessions[i]->setSessionAbortedFunc([&, i, beg, end]()
			{

				connect_and_reconnect(beg, end, io);		//这里用嵌套设计，在connect_and_reconnect（）执行完后面的代码还是要继续执行的
			});
		}

		if (socket->is_open())//如果socket已经打开并连接，则忽略以后代码，进入无限循环
			continue;

		asio::error_code ec;
		socket->cancel(ec);

		socket->async_connect(eps[i], [&, i, beg, end](asio::error_code ec)//第一次执行，进行socket的连接操作
		{
			if (ec)//执行socket->cancel(ec)出错，socket还没初始化好
			{
				connect_and_reconnect(beg, end, io);
				return;
			}

			sessions[i]->startSession();
		});
	}
	return true;
}
/*
功能：获得当前程序的运行目录(.exe)
*/
CString CFiberDetectControlDlg::GetModulePath(void)
{
	CString    sPath;
	GetModuleFileNameA(NULL, sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	sPath.ReleaseBuffer();
	int    nPos;
	nPos = sPath.ReverseFind('\\');
	sPath = sPath.Left(nPos);
	return   sPath;
}


void CFiberDetectControlDlg::ReadIni()
{
	int camera_total;
	char IniRead[255];
	memset(IniRead, 0, 255);
	char IniPath[255];
	memset(IniPath, 0, 255);
	//camera_ip_info ci_info;
	CString strPath = GetModulePath();
	strcpy_s(IniPath, 255, strPath.GetBuffer());
	strcat_s(IniPath, "/param.ini");
	GetPrivateProfileStringA("System", "box1_ip", "", IniRead, 24, IniPath);
	//m_dlgNetworkParameters.GetDlgItem(IDC_EDIT_IP_ADRESS)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("System", "box1_port", "", IniRead, 24, IniPath);
	//m_dlgNetworkParameters.GetDlgItem(IDC_EDIT_IP_PORT_NUMBER)->SetWindowTextA(IniRead);

	parameters_setting_trans.signalling = 1;     //Use siggnalling = 1 to indicate send the network setting command;

	GetPrivateProfileStringA("System", "box1_ip", "", IniRead, 24, IniPath);
	strcpy(parameters_setting_trans.box1_ip , IniRead);
	GetPrivateProfileStringA("System", "box1_port", "", IniRead, 24, IniPath);
	parameters_setting_trans.box1_port = atoi(IniRead);

	GetPrivateProfileStringA("System", "box2_ip", "", IniRead, 24, IniPath);
	strcpy(parameters_setting_trans.box2_ip , IniRead);
	GetPrivateProfileStringA("System", "box2_port", "", IniRead, 24, IniPath);
	parameters_setting_trans.box2_port = atoi(IniRead);

	GetPrivateProfileStringA("System", "electric_board_ip", "", IniRead, 24, IniPath);
	strcpy(parameters_setting_trans.electric_board_ip , IniRead);
	GetPrivateProfileStringA("System", "electric_board_port", "", IniRead, 24, IniPath);
	parameters_setting_trans.electric_board_port = atoi(IniRead);

	GetPrivateProfileStringA("System", "local_ip", "", IniRead, 24, IniPath);
	strcpy(parameters_setting_trans.local_ip , IniRead);
	GetPrivateProfileStringA("System", "local_port", "", IniRead, 24, IniPath);
	parameters_setting_trans.local_port = atoi(IniRead);

	GetPrivateProfileStringA("CameraSetting", "cameraA_ip", "", IniRead, 24, IniPath);
	strcpy(parameters_setting_trans.cameraA_ip , IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraA_port", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraA_port = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraA_scan_speed", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraA_scan_speed = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraA_tirgging_mode", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraA_tirgging_mode = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraA_exposure_time", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraA_exposure_time = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraA_gain", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraA_gain = atoi(IniRead);

	GetPrivateProfileStringA("CameraSetting", "cameraB_ip", "", IniRead, 24, IniPath);
	strcpy(parameters_setting_trans.cameraB_ip , IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraB_port", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraB_port = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraB_scan_speed", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraB_scan_speed = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraB_tirgging_mode", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraB_tirgging_mode = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraB_exposure_time", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraB_exposure_time = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraB_gain", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraB_gain = atoi(IniRead);

	GetPrivateProfileStringA("CameraSetting", "cameraC_ip", "", IniRead, 24, IniPath);
	strcpy(parameters_setting_trans.cameraC_ip , IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraC_port", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraC_port = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraC_scan_speed", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraC_scan_speed = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraC_tirgging_mode", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraC_tirgging_mode = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraC_exposure_time", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraC_exposure_time = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraC_gain", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraC_gain = atoi(IniRead);

	GetPrivateProfileStringA("CameraSetting", "cameraD_ip", "", IniRead, 24, IniPath);
	strcpy(parameters_setting_trans.cameraD_ip , IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraD_port", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraD_port = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraD_scan_speed", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraD_scan_speed = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraD_tirgging_mode", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraD_tirgging_mode = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraD_exposure_time", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraD_exposure_time = atoi(IniRead);
	GetPrivateProfileStringA("CameraSetting", "cameraD_gain", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraD_gain = atoi(IniRead);

	return;

}

void CFiberDetectControlDlg::OnBnClickedStartServer()
{
	// TODO:  在此添加控件通知处理程序代码
	m_bClientMode = m_checkClientMode.GetCheck();
	if (1)			//To get the latest parameters setting form param.ini file.
	{
		int camera_total;
		char IniRead[255];
		memset(IniRead, 0, 255);
		char IniPath[255];
		memset(IniPath, 0, 255);
		//camera_ip_info ci_info;
		CString strPath = GetModulePath();
		strcpy_s(IniPath, 255, strPath.GetBuffer());
		strcat_s(IniPath, "/param.ini");
		GetPrivateProfileStringA("System", "box1_ip", "", IniRead, 24, IniPath);
		//m_dlgNetworkParameters.GetDlgItem(IDC_EDIT_IP_ADRESS)->SetWindowTextA(IniRead);
		GetPrivateProfileStringA("System", "box1_port", "", IniRead, 24, IniPath);
		//m_dlgNetworkParameters.GetDlgItem(IDC_EDIT_IP_PORT_NUMBER)->SetWindowTextA(IniRead);

		parameters_setting_trans.signalling = 1;     //Use siggnalling = 1 to indicate send the network setting command;

		GetPrivateProfileStringA("System", "box1_ip", "", IniRead, 24, IniPath);
		strcpy(parameters_setting_trans.box1_ip , IniRead);
		GetPrivateProfileStringA("System", "box1_port", "", IniRead, 24, IniPath);
		parameters_setting_trans.box1_port = atoi(IniRead);

		GetPrivateProfileStringA("System", "box2_ip", "", IniRead, 24, IniPath);
		strcpy(parameters_setting_trans.box2_ip , IniRead);
		GetPrivateProfileStringA("System", "box2_port", "", IniRead, 24, IniPath);
		parameters_setting_trans.box2_port = atoi(IniRead);

		GetPrivateProfileStringA("System", "electric_board_ip", "", IniRead, 24, IniPath);
		strcpy(parameters_setting_trans.electric_board_ip , IniRead);
		GetPrivateProfileStringA("System", "electric_board_port", "", IniRead, 24, IniPath);
		parameters_setting_trans.electric_board_port = atoi(IniRead);

		GetPrivateProfileStringA("System", "local_ip", "", IniRead, 24, IniPath);
		strcpy(parameters_setting_trans.local_ip , IniRead);
		GetPrivateProfileStringA("System", "local_port", "", IniRead, 24, IniPath);
		parameters_setting_trans.local_port = atoi(IniRead);

		GetPrivateProfileStringA("CameraSetting", "cameraA_ip", "", IniRead, 24, IniPath);
		strcpy(parameters_setting_trans.cameraA_ip , IniRead);
		GetPrivateProfileStringA("CameraSetting", "cameraA_port", "", IniRead, 24, IniPath);
		parameters_setting_trans.cameraA_port = atoi(IniRead);
		GetPrivateProfileStringA("CameraSetting", "cameraA_scan_speed", "", IniRead, 24, IniPath);
		parameters_setting_trans.cameraA_scan_speed = atoi(IniRead);
		GetPrivateProfileStringA("CameraSetting", "cameraA_tirgging_mode", "", IniRead, 24, IniPath);
		parameters_setting_trans.cameraA_tirgging_mode = atoi(IniRead);
		GetPrivateProfileStringA("CameraSetting", "cameraA_exposure_time", "", IniRead, 24, IniPath);
		parameters_setting_trans.cameraA_exposure_time = atoi(IniRead);
		GetPrivateProfileStringA("CameraSetting", "cameraA_gain", "", IniRead, 24, IniPath);
		parameters_setting_trans.cameraA_gain = atoi(IniRead);

		GetPrivateProfileStringA("CameraSetting", "cameraB_ip", "", IniRead, 24, IniPath);
		strcpy(parameters_setting_trans.cameraB_ip , IniRead);
		GetPrivateProfileStringA("CameraSetting", "cameraB_port", "", IniRead, 24, IniPath);
		parameters_setting_trans.cameraB_port = atoi(IniRead);
		GetPrivateProfileStringA("CameraSetting", "cameraB_scan_speed", "", IniRead, 24, IniPath);
		parameters_setting_trans.cameraB_scan_speed = atoi(IniRead);
		GetPrivateProfileStringA("CameraSetting", "cameraB_tirgging_mode", "", IniRead, 24, IniPath);
		parameters_setting_trans.cameraB_tirgging_mode = atoi(IniRead);
		GetPrivateProfileStringA("CameraSetting", "cameraB_exposure_time", "", IniRead, 24, IniPath);
		parameters_setting_trans.cameraB_exposure_time = atoi(IniRead);
		GetPrivateProfileStringA("CameraSetting", "cameraB_gain", "", IniRead, 24, IniPath);
		parameters_setting_trans.cameraB_gain = atoi(IniRead);

		GetPrivateProfileStringA("CameraSetting", "cameraC_ip", "", IniRead, 24, IniPath);
		strcpy(parameters_setting_trans.cameraC_ip , IniRead);
		GetPrivateProfileStringA("CameraSetting", "cameraC_port", "", IniRead, 24, IniPath);
		parameters_setting_trans.cameraC_port = atoi(IniRead);
		GetPrivateProfileStringA("CameraSetting", "cameraC_scan_speed", "", IniRead, 24, IniPath);
		parameters_setting_trans.cameraC_scan_speed = atoi(IniRead);
		GetPrivateProfileStringA("CameraSetting", "cameraC_tirgging_mode", "", IniRead, 24, IniPath);
		parameters_setting_trans.cameraC_tirgging_mode = atoi(IniRead);
		GetPrivateProfileStringA("CameraSetting", "cameraC_exposure_time", "", IniRead, 24, IniPath);
		parameters_setting_trans.cameraC_exposure_time = atoi(IniRead);
		GetPrivateProfileStringA("CameraSetting", "cameraC_gain", "", IniRead, 24, IniPath);
		parameters_setting_trans.cameraC_gain = atoi(IniRead);

		GetPrivateProfileStringA("CameraSetting", "cameraD_ip", "", IniRead, 24, IniPath);
		strcpy(parameters_setting_trans.cameraD_ip , IniRead);
		GetPrivateProfileStringA("CameraSetting", "cameraD_port", "", IniRead, 24, IniPath);
		parameters_setting_trans.cameraD_port = atoi(IniRead);
		GetPrivateProfileStringA("CameraSetting", "cameraD_scan_speed", "", IniRead, 24, IniPath);
		parameters_setting_trans.cameraD_scan_speed = atoi(IniRead);
		GetPrivateProfileStringA("CameraSetting", "cameraD_tirgging_mode", "", IniRead, 24, IniPath);
		parameters_setting_trans.cameraD_tirgging_mode = atoi(IniRead);
		GetPrivateProfileStringA("CameraSetting", "cameraD_exposure_time", "", IniRead, 24, IniPath);
		parameters_setting_trans.cameraD_exposure_time = atoi(IniRead);
		GetPrivateProfileStringA("CameraSetting", "cameraD_gain", "", IniRead, 24, IniPath);
		parameters_setting_trans.cameraD_gain = atoi(IniRead);
	}
	if (!m_bClientMode)
	{
		if (m_bTcpMode)
			run_tcp_server(parameters_setting_trans.electric_board_ip, parameters_setting_trans.electric_board_port);   //to start a server mode;
		else
			run_udp_server(parameters_setting_trans.electric_board_ip, parameters_setting_trans.electric_board_port);   //to start a server mode;
	}

	else
		run_tcp_client(parameters_setting_trans.local_ip, parameters_setting_trans.local_port);   //to start a client mode;

	CString cs_str;
	string str_str;
	str_str = cs_str;
	Point P1, P2, P0, P3;
	Point pRect1, pRect2;
	POINT  pTopLeft, pRightBottom;
	pTopLeft.x = 5000; pTopLeft.y = 5000; pRightBottom.x = 0; pRightBottom.y = 0;
	CString strText = "启动服务";
	CRect DrawRect(0, 0, 600, 50);
	RefreshWnd(m_pwnd);
	PushTailShowText(strText);
	ShowText(m_pwnd, m_strShowText, DrawRect);
}
void    CFiberDetectControlDlg::PushTailShowText(CString strText)
{
	int i = 0;
	bool bPush = false;
	for (i = 0; i < SHOWTEXTLENGTH; i++)
	{
		if (m_strShowText[i][0] == '\0')
		{
			strcpy(m_strShowText[i], strText);
			bPush = true;
			break;
		}
	}
	if (bPush)
		return;
	else
	{
		for (i = 0; i < SHOWTEXTLENGTH-1; i++)
		{
			strcpy(m_strShowText[i], m_strShowText[i + 1]);
		}
		strcpy(m_strShowText[i], strText);
		return;
	}
}

void    CFiberDetectControlDlg::PushTailShowText(char* strText)
{
	int i = 0;
	bool bPush = false;
	for (i = 0; i < SHOWTEXTLENGTH; i++)
	{
		if (m_strShowText[i][0] == '\0')
		{
			strcpy(m_strShowText[i], strText);
			bPush = true;
			break;
		}
	}
	if (bPush)
		return;
	else
	{
		for (i = 0; i < SHOWTEXTLENGTH - 1; i++)
		{
			strcpy(m_strShowText[i], m_strShowText[i + 1]);
		}
		strcpy(m_strShowText[i], strText);
		return;
	}
}


void CFiberDetectControlDlg::OnBnClickedCheckServerModeSelect()
{
	// TODO:  在此添加控件通知处理程序代码
	int n = m_checkServerModeSelect.GetCheck();
	if (m_checkServerModeSelect.GetCheck() == 1)
	{
		m_bServerMode = true;
		m_bClientMode = false;
		m_checkServerModeSelect.SetCheck(m_bServerMode);
		m_checkClientMode.SetCheck(m_bClientMode);
	}
	else
	{
		m_bServerMode = false;
		m_bClientMode = true;
		m_checkServerModeSelect.SetCheck(m_bServerMode);
		m_checkClientMode.SetCheck(m_bClientMode);
	}
}


void CFiberDetectControlDlg::OnBnClickedCheckModeSelect() //Client mode set
{
	// TODO:  在此添加控件通知处理程序代码
	int n = m_checkClientMode.GetCheck();
	//int m_checkServerModeSelect.GetCheck();

	if (m_checkClientMode.GetCheck() == 1)
	{
		m_bServerMode = false;
		m_bClientMode = true;
		m_checkServerModeSelect.SetCheck(m_bServerMode);
		m_checkClientMode.SetCheck(m_bClientMode);
	}
	else
	{
		m_bServerMode = true;
		m_bClientMode = false;
		m_checkServerModeSelect.SetCheck(m_bServerMode);
		m_checkClientMode.SetCheck(m_bClientMode);
	}
}


void CFiberDetectControlDlg::OnBnClickedCheckServerSend()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_checkServerSend.GetCheck() == 1)
	{
		m_bServerSendMode = true;
		m_bClientSendMode = false;
		communicator_->m_bServerSendMode = m_bServerSendMode;
		communicator_->m_bClientSendMode = m_bClientSendMode;
		m_checkServerSend.SetCheck(m_bServerSendMode);
		m_checkClientSend.SetCheck(m_bClientSendMode);
	}
	else
	{
		m_bServerSendMode = false;
		m_bClientSendMode = true;
		communicator_->m_bServerSendMode = m_bServerSendMode;
		communicator_->m_bClientSendMode = m_bClientSendMode;
		m_checkServerSend.SetCheck(m_bServerSendMode);
		m_checkClientSend.SetCheck(m_bClientSendMode);
	}
}


void CFiberDetectControlDlg::OnBnClickedCheckClientSend()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_checkClientSend.GetCheck() == 1)
	{
		m_bClientSendMode = true;
		m_bServerSendMode = false;
		communicator_->m_bServerSendMode = m_bServerSendMode;
		communicator_->m_bClientSendMode = m_bClientSendMode;
		m_checkClientSend.SetCheck(m_bClientSendMode);
		m_checkServerSend.SetCheck(m_bServerSendMode);
	}
	else
	{
		m_bClientSendMode = false;
		m_bServerSendMode = true;
		communicator_->m_bServerSendMode = m_bServerSendMode;
		communicator_->m_bClientSendMode = m_bClientSendMode;
		m_checkClientSend.SetCheck(m_bClientSendMode);
		m_checkServerSend.SetCheck(m_bServerSendMode);
	}
}


void CFiberDetectControlDlg::ShowText(CWnd *pwnd, CString strText, CRect DrawRect)
{
	
		//CWnd *pwnd = GetDlgItem(IDC_ShowImage);
		CClientDC pDc(pwnd);
		CPen pen(PS_SOLID, 5, RGB(255, 0, 0));//创建一个画笔工具	
		m_nRectWidth = m_ImageRect.Width();
		m_nRectHeight = m_ImageRect.Height();

		pDc.SetTextColor(RGB(0, 255, 0));
		//	pDc.DrawText(strText, DrawRect, DT_SINGLELINE | DT_LEFT | DT_VCENTER); //显示文本

		CFont font;

		font.CreateFont(
			20, // nHeight
			0, // nWidth
			0, // nEscapement
			0, // nOrientation
			FW_NORMAL, // nWeight
			FALSE, // bItalic
			FALSE, // bUnderline
			0, // cStrikeOut
			ANSI_CHARSET, // nCharSet
			OUT_DEFAULT_PRECIS, // nOutPrecision
			CLIP_DEFAULT_PRECIS, // nClipPrecision
			DEFAULT_QUALITY, // nQuality
			DEFAULT_PITCH | FF_SWISS,
			_T("Arial") // nPitchAndFamily Arial
			);
		pDc.SelectObject(&font);
		pDc.SetBkMode(TRANSPARENT);


		pDc.SetTextColor(RGB(0, 0, 0));

		pDc.SetBkColor(RGB(255, 255, 0));
		//pDc.TextOut(0, 0, "写字");
		char str[5][255];
		memset(str[0], 0, 255);
		strcpy(str[0], strText);

		pDc.DrawText(str[0], DrawRect, DT_SINGLELINE | DT_LEFT | DT_VCENTER); //显示文本

		POINT pt1;
		pt1.x = 0; pt1.y = 0;
		POINT pt2;
		pt2.x = 100;// (100, 100);
		pt2.y = 100;
		//pDc.SelectObject(&pen);//选择画笔
		//pDc.MoveTo(pt1);
		//pDc.LineTo(pt2);	
}

void CFiberDetectControlDlg::ShowText(CWnd *pwnd, char strText[SHOWTEXTLENGTH][255], CRect DrawRect)
{

	//CWnd *pwnd = GetDlgItem(IDC_ShowImage);
	
	
	CClientDC pDc(pwnd);
	CPen pen(PS_SOLID, 5, RGB(255, 0, 0));//创建一个画笔工具	
	m_nRectWidth = m_ImageRect.Width();
	m_nRectHeight = m_ImageRect.Height();

	pDc.SetTextColor(RGB(0, 255, 0));
	//	pDc.DrawText(strText, DrawRect, DT_SINGLELINE | DT_LEFT | DT_VCENTER); //显示文本

	CFont font;

	font.CreateFont(
		20, // nHeight
		0, // nWidth
		0, // nEscapement
		0, // nOrientation
		FW_NORMAL, // nWeight
		FALSE, // bItalic
		FALSE, // bUnderline
		0, // cStrikeOut
		ANSI_CHARSET, // nCharSet
		OUT_DEFAULT_PRECIS, // nOutPrecision
		CLIP_DEFAULT_PRECIS, // nClipPrecision
		DEFAULT_QUALITY, // nQuality
		DEFAULT_PITCH | FF_SWISS,
		_T("Arial") // nPitchAndFamily Arial
		);
	pDc.SelectObject(&font);
	pDc.SetBkMode(TRANSPARENT);

	pDc.SetTextColor(RGB(0, 0, 0));

	pDc.SetBkColor(RGB(255, 255, 0));
	//pDc.TextOut(0, 0, "写字");
	int i = 0;
	for (i = 0; i < SHOWTEXTLENGTH; i++)
	{
		if (m_strShowText[i][0] != '\0')
		{
			CRect TextRect(10, i*50, 600, (i+1)*50);
			pDc.DrawText(m_strShowText[i], TextRect, DT_SINGLELINE | DT_LEFT | DT_VCENTER); //显示文本
		}	
	}
}

void CFiberDetectControlDlg::RefreshWnd(CWnd *pwnd)
{

	//CWnd *pwnd = GetDlgItem(IDC_ShowImage);
	CRect PictureRect; 
	pwnd->GetClientRect(&PictureRect);
	int nWidth = PictureRect.Width();
	int nHeight = PictureRect.Height();
	CClientDC pDc(pwnd);
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));//创建一个画笔工具
	CBrush brush;
	brush.CreateSolidBrush(RGB(BACK_COLOR_GRAY, BACK_COLOR_GRAY, BACK_COLOR_GRAY));   //BACK_COLOR_GRAY: Window default color;

	//	pDc.DrawText(strText, DrawRect, DT_SINGLELINE | DT_LEFT | DT_VCENTER); //显示文本

	pDc.FillRect(PictureRect, &brush);

	POINT pt1;
	pt1.x = 0; pt1.y = 0;
	POINT pt2;
	pt2.x = 100;// (100, 100);
	pt2.y = 100;
	pDc.SelectObject(&pen);//选择画笔
	POINT point;
	point.x = 0;
	point.y = 0;
	pDc.MoveTo(point);

	point.x = nWidth;
	point.y = 0;
	pDc.LineTo(point);

	point.x = nWidth;
	point.y = nHeight;
	pDc.LineTo(point);

	point.x = 0;
	point.y = nHeight;
	pDc.LineTo(point);

	point.x = 0;
	point.y = 0;
	pDc.LineTo(point);

}

void CFiberDetectControlDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1)
	{
		for (int i = 0; i < MAGNETIC_VALVE_SUM; i++)  //MAGNETIC_VALVE_SUM
		{
			if (Communicator::valve_driver[i].dura > 0)
			{
				Communicator::valve_driver[i].dura -= 20;
				m_mfcMagneticValve[i]->m_bTransparent = FALSE;
				m_mfcMagneticValve[i]->m_bDontUseWinXPTheme = TRUE;
				m_mfcMagneticValve[i]->m_bDrawFocus = FALSE;
				m_mfcMagneticValve[i]->m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
				m_mfcMagneticValve[i]->SetFaceColor(RGB(255, 0, 0));
			}
			else
			{
				m_mfcMagneticValve[i]->m_bTransparent = FALSE;
				m_mfcMagneticValve[i]->m_bDontUseWinXPTheme = TRUE;
				m_mfcMagneticValve[i]->m_bDrawFocus = FALSE;
				m_mfcMagneticValve[i]->m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
				m_mfcMagneticValve[i]->SetFaceColor(RGB(0, 255, 0));
			}
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}

LRESULT CFiberDetectControlDlg::ShowCtrlMessage(WPARAM wParam, LPARAM lParam)
{
	CString strMsg;
	int nCtrlSignalling = (int)wParam;
	Vsee::VCameraMessageTrans *MagneticVolveMsg = nullptr;
	_io_output_transac_tag_*  valve_driver_frame=nullptr;
	RefreshWnd(m_pwnd);   //clear the print words from the show window;

	strMsg.Format("Receive socket message!");
	PushTailShowText(strMsg);

	//AfxMessageBox(strMsg);

	if (nCtrlSignalling == 10)
	{
		RefreshWnd(m_pwnd);   //clear the print words from the show window;
		//CString str;
		char * strMessage = (char*)lParam;
		//str.Format("%s", strMessage);
		PushTailShowText(strMessage);
		ShowText(m_pwnd, m_strShowText, NULL);
		//MagneticVolveMsg = (Vsee::VCameraMessageTrans*)lParam;
	}
	else if (nCtrlSignalling == 3)      //To test the magnetic valve hardware;
	{
		if (!m_bLeihangProtocal)
		{
			MagneticVolveMsg = (Vsee::VCameraMessageTrans*)lParam;
			int nMagneticNum;
			int nCameraSeriesNum = MagneticVolveMsg->magnetic_valve_num;  //To indicate the camera series number
			strMsg.Format("wParam=%d,MagneticNum=%d", wParam, MagneticVolveMsg->magnetic_valve_num);
			int nDelayTimes;  //Magnetic valve delay timed for each camera detect result
			switch (nCameraSeriesNum)
			{
			case 1:
				nDelayTimes = MagneticVolveMsg->parameters_setting_trans.cameraA_delay;
				break;
			case 2:
				nDelayTimes = MagneticVolveMsg->parameters_setting_trans.cameraB_delay;
				break;
			case 3:
				nDelayTimes = MagneticVolveMsg->parameters_setting_trans.cameraC_delay;
				break;
			case 4:
				nDelayTimes = MagneticVolveMsg->parameters_setting_trans.cameraD_delay;
				break;
			default:
				nDelayTimes = 0;
				break;
			}
			memcpy(&aq::Communicator::box_ctrl_msg, MagneticVolveMsg, sizeof(Vsee::VCameraMessageTrans));
			for (int i = 0; i < 24; i++)
			{
				if (MagneticVolveMsg->magnetic_valve[i] == 1)
				{
					//if (i==0)
					nMagneticNum = i + 1;
				}
				else
				{
					continue;
				}

				if (nMagneticNum == 1)
				{
					aq::Communicator::box_ctrl_msg.signalling = nCtrlSignalling;
					aq::Communicator::box_ctrl_msg.magnetic_valve_num = nMagneticNum;
					m_mfcMagneticValve1.m_bTransparent = FALSE;
					m_mfcMagneticValve1.m_bDontUseWinXPTheme = TRUE;
					m_mfcMagneticValve1.m_bDrawFocus = FALSE;
					m_mfcMagneticValve1.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
					m_mfcMagneticValve1.SetFaceColor(RGB(255, 0, 0));
					//Sleep(100);
					//m_mfcMagneticValve1.SetFaceColor(RGB(0, 255, 0));
					//Sleep(100);
					//CString str;
					strMsg.Format("Camera %dth,Trig the %d electro_magnetic_valve,delay %d ms", nCameraSeriesNum, nMagneticNum, nDelayTimes);
					PushTailShowText(strMsg);
					//RefreshWnd(m_pwnd);
					//ShowText(m_pwnd, m_strShowText, NULL);
				}

				else if (nMagneticNum == 2)
				{
					aq::Communicator::box_ctrl_msg.signalling = nCtrlSignalling;
					aq::Communicator::box_ctrl_msg.magnetic_valve_num = nMagneticNum;
					m_mfcMagneticValve2.m_bTransparent = FALSE;
					m_mfcMagneticValve2.m_bDontUseWinXPTheme = TRUE;
					m_mfcMagneticValve2.m_bDrawFocus = FALSE;
					m_mfcMagneticValve2.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
					m_mfcMagneticValve2.SetFaceColor(RGB(255, 0, 0));
					//Sleep(100);
					//m_mfcMagneticValve2.SetFaceColor(RGB(0, 255, 0));
					//Sleep(100);
					strMsg.Format("Camera %dth,Trig the %d electro_magnetic_valve,delay %d ms", nCameraSeriesNum, nMagneticNum, nDelayTimes);
					PushTailShowText(strMsg);
					//RefreshWnd(m_pwnd);
					//ShowText(m_pwnd, m_strShowText, NULL);
				}

				else if (nMagneticNum == 3)
				{
					aq::Communicator::box_ctrl_msg.signalling = nCtrlSignalling;
					aq::Communicator::box_ctrl_msg.magnetic_valve_num = nMagneticNum;
					m_mfcMagneticValve3.m_bTransparent = FALSE;
					m_mfcMagneticValve3.m_bDontUseWinXPTheme = TRUE;
					m_mfcMagneticValve3.m_bDrawFocus = FALSE;
					m_mfcMagneticValve3.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
					m_mfcMagneticValve3.SetFaceColor(RGB(255, 0, 0));
					//Sleep(100);
					//m_mfcMagneticValve3.SetFaceColor(RGB(0, 255, 0));
					//Sleep(100);
					strMsg.Format("Camera %dth,Trig the %d electro_magnetic_valve,delay %d ms", nCameraSeriesNum, nMagneticNum, nDelayTimes);
					PushTailShowText(strMsg);
					//RefreshWnd(m_pwnd);
					//ShowText(m_pwnd, m_strShowText, NULL);
				}
				else if (nMagneticNum == 4)
				{
					aq::Communicator::box_ctrl_msg.signalling = nCtrlSignalling;
					aq::Communicator::box_ctrl_msg.magnetic_valve_num = nMagneticNum;
					m_mfcMagneticValve4.m_bTransparent = FALSE;
					m_mfcMagneticValve4.m_bDontUseWinXPTheme = TRUE;
					m_mfcMagneticValve4.m_bDrawFocus = FALSE;
					m_mfcMagneticValve4.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
					m_mfcMagneticValve4.SetFaceColor(RGB(255, 0, 0));
					//Sleep(100);
					//m_mfcMagneticValve4.SetFaceColor(RGB(0, 255, 0));
					//Sleep(100);
					strMsg.Format("Camera %dth,Trig the %d electro_magnetic_valve,delay %d ms", nCameraSeriesNum, nMagneticNum, nDelayTimes);
					PushTailShowText(strMsg);
					//RefreshWnd(m_pwnd);
					//ShowText(m_pwnd, m_strShowText, NULL);

				}
				else if (nMagneticNum == 5)
				{
					aq::Communicator::box_ctrl_msg.signalling = nCtrlSignalling;
					aq::Communicator::box_ctrl_msg.magnetic_valve_num = nMagneticNum;
					m_mfcMagneticValve5.m_bTransparent = FALSE;
					m_mfcMagneticValve5.m_bDontUseWinXPTheme = TRUE;
					m_mfcMagneticValve5.m_bDrawFocus = FALSE;
					m_mfcMagneticValve5.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
					m_mfcMagneticValve5.SetFaceColor(RGB(255, 0, 0));
					//Sleep(100);
					//m_mfcMagneticValve5.SetFaceColor(RGB(0, 255, 0));
					//Sleep(100);
					strMsg.Format("Camera %dth,Trig the %d electro_magnetic_valve,delay %d ms", nCameraSeriesNum, nMagneticNum, nDelayTimes);
					PushTailShowText(strMsg);
					//RefreshWnd(m_pwnd);
					//ShowText(m_pwnd, m_strShowText, NULL);

				}
				else if (nMagneticNum == 6)
				{
					aq::Communicator::box_ctrl_msg.signalling = nCtrlSignalling;
					aq::Communicator::box_ctrl_msg.magnetic_valve_num = nMagneticNum;
					m_mfcMagneticValve6.m_bTransparent = FALSE;
					m_mfcMagneticValve6.m_bDontUseWinXPTheme = TRUE;
					m_mfcMagneticValve6.m_bDrawFocus = FALSE;
					m_mfcMagneticValve6.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
					m_mfcMagneticValve6.SetFaceColor(RGB(255, 0, 0));
					//Sleep(100);
					//m_mfcMagneticValve6.SetFaceColor(RGB(0, 255, 0));
					//Sleep(100);
					strMsg.Format("Camera %dth,Trig the %d electro_magnetic_valve,delay %d ms", nCameraSeriesNum, nMagneticNum, nDelayTimes);
					PushTailShowText(strMsg);
					//RefreshWnd(m_pwnd);
					//ShowText(m_pwnd, m_strShowText, NULL);

				}
				else if (nMagneticNum == 7)
				{
					aq::Communicator::box_ctrl_msg.signalling = nCtrlSignalling;
					aq::Communicator::box_ctrl_msg.magnetic_valve_num = nMagneticNum;
					m_mfcMagneticValve7.m_bTransparent = FALSE;
					m_mfcMagneticValve7.m_bDontUseWinXPTheme = TRUE;
					m_mfcMagneticValve7.m_bDrawFocus = FALSE;
					m_mfcMagneticValve7.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
					m_mfcMagneticValve7.SetFaceColor(RGB(255, 0, 0));
					//Sleep(100);
					//m_mfcMagneticValve7.SetFaceColor(RGB(0, 255, 0));
					//Sleep(100);
					strMsg.Format("Camera %dth,Trig the %d electro_magnetic_valve,delay %d ms", nCameraSeriesNum, nMagneticNum, nDelayTimes);
					PushTailShowText(strMsg);
					//RefreshWnd(m_pwnd);
					//ShowText(m_pwnd, m_strShowText, NULL);

				}
				else if (nMagneticNum == 8)
				{
					aq::Communicator::box_ctrl_msg.signalling = nCtrlSignalling;
					aq::Communicator::box_ctrl_msg.magnetic_valve_num = nMagneticNum;
					m_mfcMagneticValve8.m_bTransparent = FALSE;
					m_mfcMagneticValve8.m_bDontUseWinXPTheme = TRUE;
					m_mfcMagneticValve8.m_bDrawFocus = FALSE;
					m_mfcMagneticValve8.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
					m_mfcMagneticValve8.SetFaceColor(RGB(255, 0, 0));
					//Sleep(100);
					//m_mfcMagneticValve8.SetFaceColor(RGB(0, 255, 0));
					//Sleep(100);
					strMsg.Format("Camera %dth,Trig the %d electro_magnetic_valve,delay %d ms", nCameraSeriesNum, nMagneticNum, nDelayTimes);
					PushTailShowText(strMsg);
					//RefreshWnd(m_pwnd);
					//ShowText(m_pwnd, m_strShowText, NULL);

				}
				else if (nMagneticNum == 9)
				{
					aq::Communicator::box_ctrl_msg.signalling = nCtrlSignalling;
					aq::Communicator::box_ctrl_msg.magnetic_valve_num = nMagneticNum;
					m_mfcMagneticValve9.m_bTransparent = FALSE;
					m_mfcMagneticValve9.m_bDontUseWinXPTheme = TRUE;
					m_mfcMagneticValve9.m_bDrawFocus = FALSE;
					m_mfcMagneticValve9.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
					m_mfcMagneticValve9.SetFaceColor(RGB(255, 0, 0));
					//Sleep(100);
					//m_mfcMagneticValve9.SetFaceColor(RGB(0, 255, 0));
					//Sleep(100);
					strMsg.Format("Camera %dth,Trig the %d electro_magnetic_valve,delay %d ms", nCameraSeriesNum, nMagneticNum, nDelayTimes);
					PushTailShowText(strMsg);
					//RefreshWnd(m_pwnd);
					//ShowText(m_pwnd, m_strShowText, NULL);

				}
				else if (nMagneticNum == 10)
				{
					aq::Communicator::box_ctrl_msg.signalling = nCtrlSignalling;
					aq::Communicator::box_ctrl_msg.magnetic_valve_num = nMagneticNum;
					m_mfcMagneticValve10.m_bTransparent = FALSE;
					m_mfcMagneticValve10.m_bDontUseWinXPTheme = TRUE;
					m_mfcMagneticValve10.m_bDrawFocus = FALSE;
					m_mfcMagneticValve10.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
					m_mfcMagneticValve10.SetFaceColor(RGB(255, 0, 0));
					//Sleep(100);
					//m_mfcMagneticValve10.SetFaceColor(RGB(0, 255, 0));
					//Sleep(100);
					strMsg.Format("Camera %dth,Trig the %d electro_magnetic_valve,delay %d ms", nCameraSeriesNum, nMagneticNum, nDelayTimes);
					PushTailShowText(strMsg);
					//RefreshWnd(m_pwnd);
					//ShowText(m_pwnd, m_strShowText, NULL);

				}
				else if (nMagneticNum == 11)
				{
					aq::Communicator::box_ctrl_msg.signalling = nCtrlSignalling;
					aq::Communicator::box_ctrl_msg.magnetic_valve_num = nMagneticNum;
					m_mfcMagneticValve11.m_bTransparent = FALSE;
					m_mfcMagneticValve11.m_bDontUseWinXPTheme = TRUE;
					m_mfcMagneticValve11.m_bDrawFocus = FALSE;
					m_mfcMagneticValve11.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
					m_mfcMagneticValve11.SetFaceColor(RGB(255, 0, 0));
					//Sleep(100);
					//m_mfcMagneticValve11.SetFaceColor(RGB(0, 255, 0));
					//Sleep(100);
					strMsg.Format("Camera %dth,Trig the %d electro_magnetic_valve,delay %d ms", nCameraSeriesNum, nMagneticNum, nDelayTimes);
					PushTailShowText(strMsg);
					//RefreshWnd(m_pwnd);
					//ShowText(m_pwnd, m_strShowText, NULL);

				}
				else if (nMagneticNum == 12)
				{
					aq::Communicator::box_ctrl_msg.signalling = nCtrlSignalling;
					aq::Communicator::box_ctrl_msg.magnetic_valve_num = nMagneticNum;
					m_mfcMagneticValve12.m_bTransparent = FALSE;
					m_mfcMagneticValve12.m_bDontUseWinXPTheme = TRUE;
					m_mfcMagneticValve12.m_bDrawFocus = FALSE;
					m_mfcMagneticValve12.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
					m_mfcMagneticValve12.SetFaceColor(RGB(255, 0, 0));
					//Sleep(100);
					//m_mfcMagneticValve12.SetFaceColor(RGB(0, 255, 0));
					//Sleep(100);
					strMsg.Format("Camera %dth,Trig the %d electro_magnetic_valve,delay %d ms", nCameraSeriesNum, nMagneticNum, nDelayTimes);
					PushTailShowText(strMsg);
					//RefreshWnd(m_pwnd);
					//ShowText(m_pwnd, m_strShowText, NULL);

				}
				else if (nMagneticNum == 13)
				{
					aq::Communicator::box_ctrl_msg.signalling = nCtrlSignalling;
					aq::Communicator::box_ctrl_msg.magnetic_valve_num = nMagneticNum;
					m_mfcMagneticValve13.m_bTransparent = FALSE;
					m_mfcMagneticValve13.m_bDontUseWinXPTheme = TRUE;
					m_mfcMagneticValve13.m_bDrawFocus = FALSE;
					m_mfcMagneticValve13.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
					m_mfcMagneticValve13.SetFaceColor(RGB(255, 0, 0));
					//Sleep(100);
					//m_mfcMagneticValve13.SetFaceColor(RGB(0, 255, 0));
					//Sleep(100);
					strMsg.Format("Camera %dth,Trig the %d electro_magnetic_valve,delay %d ms", nCameraSeriesNum, nMagneticNum, nDelayTimes);
					PushTailShowText(strMsg);
					//RefreshWnd(m_pwnd);
					//ShowText(m_pwnd, m_strShowText, NULL);

				}
				else if (nMagneticNum == 14)
				{
					aq::Communicator::box_ctrl_msg.signalling = nCtrlSignalling;
					aq::Communicator::box_ctrl_msg.magnetic_valve_num = nMagneticNum;
					m_mfcMagneticValve14.m_bTransparent = FALSE;
					m_mfcMagneticValve14.m_bDontUseWinXPTheme = TRUE;
					m_mfcMagneticValve14.m_bDrawFocus = FALSE;
					m_mfcMagneticValve14.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
					m_mfcMagneticValve14.SetFaceColor(RGB(255, 0, 0));
					//Sleep(100);
					//m_mfcMagneticValve14.SetFaceColor(RGB(0, 255, 0));
					//Sleep(100);
					strMsg.Format("Camera %dth,Trig the %d electro_magnetic_valve,delay %d ms", nCameraSeriesNum, nMagneticNum, nDelayTimes);
					PushTailShowText(strMsg);
					//RefreshWnd(m_pwnd);
					//ShowText(m_pwnd, m_strShowText, NULL);

				}
				else if (nMagneticNum == 15)
				{
					aq::Communicator::box_ctrl_msg.signalling = nCtrlSignalling;
					aq::Communicator::box_ctrl_msg.magnetic_valve_num = nMagneticNum;
					m_mfcMagneticValve15.m_bTransparent = FALSE;
					m_mfcMagneticValve15.m_bDontUseWinXPTheme = TRUE;
					m_mfcMagneticValve15.m_bDrawFocus = FALSE;
					m_mfcMagneticValve15.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
					m_mfcMagneticValve15.SetFaceColor(RGB(255, 0, 0));
					//Sleep(100);
					//m_mfcMagneticValve15.SetFaceColor(RGB(0, 255, 0));
					//Sleep(100);
					strMsg.Format("Camera %dth,Trig the %d electro_magnetic_valve,delay %d ms", nCameraSeriesNum, nMagneticNum, nDelayTimes);
					PushTailShowText(strMsg);
					//RefreshWnd(m_pwnd);
					//ShowText(m_pwnd, m_strShowText, NULL);

				}
				else if (nMagneticNum == 16)
				{
					aq::Communicator::box_ctrl_msg.signalling = nCtrlSignalling;
					aq::Communicator::box_ctrl_msg.magnetic_valve_num = nMagneticNum;
					m_mfcMagneticValve16.m_bTransparent = FALSE;
					m_mfcMagneticValve16.m_bDontUseWinXPTheme = TRUE;
					m_mfcMagneticValve16.m_bDrawFocus = FALSE;
					m_mfcMagneticValve16.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
					m_mfcMagneticValve16.SetFaceColor(RGB(255, 0, 0));
					//Sleep(100);
					//m_mfcMagneticValve16.SetFaceColor(RGB(0, 255, 0));
					//Sleep(100);
					strMsg.Format("Camera %dth,Trig the %d electro_magnetic_valve,delay %d ms", nCameraSeriesNum, nMagneticNum, nDelayTimes);
					PushTailShowText(strMsg);
					//RefreshWnd(m_pwnd);
					//ShowText(m_pwnd, m_strShowText, NULL);

				}
				else if (nMagneticNum == 17)
				{
					aq::Communicator::box_ctrl_msg.signalling = nCtrlSignalling;
					aq::Communicator::box_ctrl_msg.magnetic_valve_num = nMagneticNum;
					m_mfcMagneticValve17.m_bTransparent = FALSE;
					m_mfcMagneticValve17.m_bDontUseWinXPTheme = TRUE;
					m_mfcMagneticValve17.m_bDrawFocus = FALSE;
					m_mfcMagneticValve17.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
					m_mfcMagneticValve17.SetFaceColor(RGB(255, 0, 0));
					//Sleep(100);
					//m_mfcMagneticValve17.SetFaceColor(RGB(0, 255, 0));
					//Sleep(100);
					strMsg.Format("Camera %dth,Trig the %d electro_magnetic_valve,delay %d ms", nCameraSeriesNum, nMagneticNum, nDelayTimes);
					PushTailShowText(strMsg);
					//RefreshWnd(m_pwnd);
					//ShowText(m_pwnd, m_strShowText, NULL);

				}
				else if (nMagneticNum == 18)
				{
					aq::Communicator::box_ctrl_msg.signalling = nCtrlSignalling;
					aq::Communicator::box_ctrl_msg.magnetic_valve_num = nMagneticNum;
					m_mfcMagneticValve18.m_bTransparent = FALSE;
					m_mfcMagneticValve18.m_bDontUseWinXPTheme = TRUE;
					m_mfcMagneticValve18.m_bDrawFocus = FALSE;
					m_mfcMagneticValve18.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
					m_mfcMagneticValve18.SetFaceColor(RGB(255, 0, 0));
					//Sleep(100);
					//m_mfcMagneticValve18.SetFaceColor(RGB(0, 255, 0));
					//Sleep(100);
					strMsg.Format("Camera %dth,Trig the %d electro_magnetic_valve,delay %d ms", nCameraSeriesNum, nMagneticNum, nDelayTimes);
					PushTailShowText(strMsg);
					//RefreshWnd(m_pwnd);
					//ShowText(m_pwnd, m_strShowText, NULL);

				}
				else if (nMagneticNum == 19)
				{
					aq::Communicator::box_ctrl_msg.signalling = nCtrlSignalling;
					aq::Communicator::box_ctrl_msg.magnetic_valve_num = nMagneticNum;
					m_mfcMagneticValve19.m_bTransparent = FALSE;
					m_mfcMagneticValve19.m_bDontUseWinXPTheme = TRUE;
					m_mfcMagneticValve19.m_bDrawFocus = FALSE;
					m_mfcMagneticValve19.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
					m_mfcMagneticValve19.SetFaceColor(RGB(255, 0, 0));
					//Sleep(100);
					//m_mfcMagneticValve19.SetFaceColor(RGB(0, 255, 0));
					//Sleep(100);
					strMsg.Format("Camera %dth,Trig the %d electro_magnetic_valve,delay %d ms", nCameraSeriesNum, nMagneticNum, nDelayTimes);
					PushTailShowText(strMsg);
					//RefreshWnd(m_pwnd);
					//ShowText(m_pwnd, m_strShowText, NULL);

				}
				else if (nMagneticNum == 20)
				{
					aq::Communicator::box_ctrl_msg.signalling = nCtrlSignalling;
					aq::Communicator::box_ctrl_msg.magnetic_valve_num = nMagneticNum;
					m_mfcMagneticValve20.m_bTransparent = FALSE;
					m_mfcMagneticValve20.m_bDontUseWinXPTheme = TRUE;
					m_mfcMagneticValve20.m_bDrawFocus = FALSE;
					m_mfcMagneticValve20.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
					m_mfcMagneticValve20.SetFaceColor(RGB(255, 0, 0));
					//Sleep(100);
					//m_mfcMagneticValve20.SetFaceColor(RGB(0, 255, 0));
					//Sleep(100);
					strMsg.Format("Camera %dth,Trig the %d electro_magnetic_valve,delay %d ms", nCameraSeriesNum, nMagneticNum, nDelayTimes);
					PushTailShowText(strMsg);
					//RefreshWnd(m_pwnd);
					//ShowText(m_pwnd, m_strShowText, NULL);

				}
				else if (nMagneticNum == 21)
				{
					aq::Communicator::box_ctrl_msg.signalling = nCtrlSignalling;
					aq::Communicator::box_ctrl_msg.magnetic_valve_num = nMagneticNum;
					m_mfcMagneticValve21.m_bTransparent = FALSE;
					m_mfcMagneticValve21.m_bDontUseWinXPTheme = TRUE;
					m_mfcMagneticValve21.m_bDrawFocus = FALSE;
					m_mfcMagneticValve21.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
					m_mfcMagneticValve21.SetFaceColor(RGB(255, 0, 0));
					//Sleep(100);
					//m_mfcMagneticValve21.SetFaceColor(RGB(0, 255, 0));
					//Sleep(100);
					strMsg.Format("Camera %dth,Trig the %d electro_magnetic_valve,delay %d ms", nCameraSeriesNum, nMagneticNum, nDelayTimes);
					PushTailShowText(strMsg);
					//RefreshWnd(m_pwnd);
					//ShowText(m_pwnd, m_strShowText, NULL);

				}
				else if (nMagneticNum == 22)
				{
					aq::Communicator::box_ctrl_msg.signalling = nCtrlSignalling;
					aq::Communicator::box_ctrl_msg.magnetic_valve_num = nMagneticNum;
					m_mfcMagneticValve22.m_bTransparent = FALSE;
					m_mfcMagneticValve22.m_bDontUseWinXPTheme = TRUE;
					m_mfcMagneticValve22.m_bDrawFocus = FALSE;
					m_mfcMagneticValve22.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
					m_mfcMagneticValve22.SetFaceColor(RGB(255, 0, 0));
					//Sleep(100);
					//m_mfcMagneticValve22.SetFaceColor(RGB(0, 255, 0));
					//Sleep(100);
					strMsg.Format("Camera %dth,Trig the %d electro_magnetic_valve,delay %d ms", nCameraSeriesNum, nMagneticNum, nDelayTimes);
					PushTailShowText(strMsg);
					//RefreshWnd(m_pwnd);
					//ShowText(m_pwnd, m_strShowText, NULL);

				}
				else if (nMagneticNum == 23)
				{
					aq::Communicator::box_ctrl_msg.signalling = nCtrlSignalling;
					aq::Communicator::box_ctrl_msg.magnetic_valve_num = nMagneticNum;
					m_mfcMagneticValve23.m_bTransparent = FALSE;
					m_mfcMagneticValve23.m_bDontUseWinXPTheme = TRUE;
					m_mfcMagneticValve23.m_bDrawFocus = FALSE;
					m_mfcMagneticValve23.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
					m_mfcMagneticValve23.SetFaceColor(RGB(255, 0, 0));
					//Sleep(100);
					//m_mfcMagneticValve23.SetFaceColor(RGB(0, 255, 0));
					//Sleep(100);
					strMsg.Format("Camera %dth,Trig the %d electro_magnetic_valve,delay %d ms", nCameraSeriesNum, nMagneticNum, nDelayTimes);
					PushTailShowText(strMsg);
					//RefreshWnd(m_pwnd);
					//ShowText(m_pwnd, m_strShowText, NULL);

				}
				else if (nMagneticNum == 24)
				{
					aq::Communicator::box_ctrl_msg.signalling = nCtrlSignalling;
					aq::Communicator::box_ctrl_msg.magnetic_valve_num = nMagneticNum;
					m_mfcMagneticValve24.m_bTransparent = FALSE;
					m_mfcMagneticValve24.m_bDontUseWinXPTheme = TRUE;
					m_mfcMagneticValve24.m_bDrawFocus = FALSE;
					m_mfcMagneticValve24.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
					m_mfcMagneticValve24.SetFaceColor(RGB(255, 0, 0));
					//Sleep(100);
					//m_mfcMagneticValve24.SetFaceColor(RGB(0, 255, 0));
					//Sleep(100);
					strMsg.Format("Camera %dth,Trig the %d electro_magnetic_valve,delay %d ms", nCameraSeriesNum, nMagneticNum, nDelayTimes);
					PushTailShowText(strMsg);
					//RefreshWnd(m_pwnd);
					//ShowText(m_pwnd, m_strShowText, NULL);
				}
				else
				{
					;
				}
			}
			if (1)
			{
				Sleep(10);
				m_mfcMagneticValve1.SetFaceColor(RGB(0, 255, 0));
				m_mfcMagneticValve2.SetFaceColor(RGB(0, 255, 0));
				m_mfcMagneticValve3.SetFaceColor(RGB(0, 255, 0));
				m_mfcMagneticValve4.SetFaceColor(RGB(0, 255, 0));
				m_mfcMagneticValve5.SetFaceColor(RGB(0, 255, 0));
				m_mfcMagneticValve6.SetFaceColor(RGB(0, 255, 0));
				m_mfcMagneticValve7.SetFaceColor(RGB(0, 255, 0));
				m_mfcMagneticValve8.SetFaceColor(RGB(0, 255, 0));
				m_mfcMagneticValve9.SetFaceColor(RGB(0, 255, 0));
				m_mfcMagneticValve10.SetFaceColor(RGB(0, 255, 0));
				m_mfcMagneticValve11.SetFaceColor(RGB(0, 255, 0));
				m_mfcMagneticValve12.SetFaceColor(RGB(0, 255, 0));
				m_mfcMagneticValve13.SetFaceColor(RGB(0, 255, 0));
				m_mfcMagneticValve14.SetFaceColor(RGB(0, 255, 0));
				m_mfcMagneticValve15.SetFaceColor(RGB(0, 255, 0));
				m_mfcMagneticValve16.SetFaceColor(RGB(0, 255, 0));
				m_mfcMagneticValve17.SetFaceColor(RGB(0, 255, 0));
				m_mfcMagneticValve18.SetFaceColor(RGB(0, 255, 0));
				m_mfcMagneticValve19.SetFaceColor(RGB(0, 255, 0));
				m_mfcMagneticValve20.SetFaceColor(RGB(0, 255, 0));
				m_mfcMagneticValve21.SetFaceColor(RGB(0, 255, 0));
				m_mfcMagneticValve22.SetFaceColor(RGB(0, 255, 0));
				m_mfcMagneticValve23.SetFaceColor(RGB(0, 255, 0));
				m_mfcMagneticValve24.SetFaceColor(RGB(0, 255, 0));
				//Sleep(50);
				RefreshWnd(m_pwnd);
				ShowText(m_pwnd, m_strShowText, NULL);
			}
		}  //If in Leihang protocol Mode
		else if (m_bLeihangProtocal)
		{
			//MagneticVolveMsg = (Vsee::VCameraMessageTrans*)lParam;
			valve_driver_frame = (_io_output_transac_tag_*)lParam;
			uint32_t type = 0;		// = valve_driver_frame->type;
			uint32_t src = 0;		// = valve_driver_frame->src;
			uint32_t port = 0;		// = valve_driver_frame->port;
			uint32_t ref = 0;		// = valve_driver_frame->ref;
			uint32_t delay = 0;		// = valve_driver_frame->delay;
			uint32_t dura = 0;		// = valve_driver_frame->dura;
			type = valve_driver_frame->type;
			src = valve_driver_frame->src;
			port = valve_driver_frame->port;
			ref = valve_driver_frame->ref;
			delay = valve_driver_frame->delay/10000;
			dura = valve_driver_frame->dura/10000;

			valve_driver[port].type = type;
			valve_driver[port].src = src;
			valve_driver[port].port = port;
			valve_driver[port].ref = ref;
			valve_driver[port].delay = delay;
			valve_driver[port].dura = dura;

			int nMagneticNum;
			strMsg.Format("wParam=%d,MagneticNum=%d", wParam, port);
			int nDelayTimes;  //Magnetic valve delay timed for each camera detect result
			PushTailShowText(strMsg);
			RefreshWnd(m_pwnd);
			ShowText(m_pwnd, m_strShowText, NULL);		
		}

	}
	else if (nCtrlSignalling == 4)     //To set the camera detect parameters;
	{
		MagneticVolveMsg = (Vsee::VCameraMessageTrans*)lParam;
		int nMagneticNum = MagneticVolveMsg->magnetic_valve_num;
		strMsg.Format("wParam=%d,MagneticNum=%d", wParam, MagneticVolveMsg->magnetic_valve_num);
		memcpy(&aq::Communicator::box_ctrl_msg, MagneticVolveMsg, sizeof(Vsee::VCameraMessageTrans));
		RefreshWnd(m_pwnd);   //clear the print words from the show window;
		CString str;
		str.Format("To set camera detect parameters.");
		PushTailShowText(str);
		ShowText(m_pwnd, m_strShowText, NULL);
		WriteIni(MagneticVolveMsg->parameters_setting_trans);

	}
	//if (MagneticVolveMsg != nullptr)    //Here need to delete the data pointer that transmit from ::PostMessage() function;
	//{
	//	delete MagneticVolveMsg;
	//	MagneticVolveMsg = nullptr;
	//}

	UpdateData(true);

	//Invalidate(TRUE);   //If use function "Invalidate(TRUE)" will induce window flashing;
	return 1;
}


void CFiberDetectControlDlg::OnBnClickedButtonStartDetect()
{
	// TODO:  在此添加控件通知处理程序代码
	aq::Communicator::box_ctrl_msg.signalling = 1;     //To start detect fiber;
	aq::Communicator::box_ctrl_msg.magnetic_valve_num = 0;
	
	CString str;
	str.Format("Start detect fiber.");
	PushTailShowText(str);
	RefreshWnd(m_pwnd);
	ShowText(m_pwnd, m_strShowText, NULL);
}


void CFiberDetectControlDlg::OnBnClickedButtonStopDetect2()
{
	// TODO:  在此添加控件通知处理程序代码
	aq::Communicator::box_ctrl_msg.signalling = 2;     //To start detect fiber;
	aq::Communicator::box_ctrl_msg.magnetic_valve_num = 0;

	CString str;
	str.Format("Stop detect fiber.");
	PushTailShowText(str);
	RefreshWnd(m_pwnd);
	ShowText(m_pwnd, m_strShowText, NULL);
}


void CFiberDetectControlDlg::WriteIni(CParameterSetting parameters_setting_trans)
{
	//char IniRead[255];
	//memset(IniRead, 0, 255);
	char IniPath[255];
	memset(IniPath, 0, 255);
	//camera_ip_info ci_info;
	CString strPath = GetModulePath();
	strcpy_s(IniPath, 255, strPath.GetBuffer());
	strcat_s(IniPath, "/param.ini");
	CString IniRead;
	CString IniWrite;

	//GetPrivateProfileStringA("BaseDetectParameter", "cameraA_begin", "", IniRead, 24, IniPath);	
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA1_BEGIN_POINT)->GetWindowTextA(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraA_begin);
	WritePrivateProfileString("BaseDetectParameter", "cameraA_begin", IniWrite, IniPath);
	//parameters_setting_trans.cameraA_begin = atoi(IniWrite);

	//GetPrivateProfileStringA("BaseDetectParameter", "cameraA_end", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA1_END_POINT)->GetWindowTextA(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraA_end);
	WritePrivateProfileString("BaseDetectParameter", "cameraA_end", IniWrite, IniPath);
	//parameters_setting_trans.cameraA_end = atoi(IniWrite);

	//GetPrivateProfileStringA("BaseDetectParameter", "cameraA_align_begin", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA1_ALIGNING_BEGIN_POINT)->GetWindowTextA(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraA_align_begin);
	WritePrivateProfileString("BaseDetectParameter", "cameraA_align_begin", IniWrite, IniPath);
	//parameters_setting_trans.cameraA_align_begin = atoi(IniRead);


	//GetPrivateProfileStringA("BaseDetectParameter", "cameraA_align_end", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA1_ALIGNING_END_POINT)->GetWindowTextA(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraA_align_end);
	WritePrivateProfileString("BaseDetectParameter", "cameraA_align_end", IniWrite, IniPath);
	//parameters_setting_trans.cameraA_align_end = atoi(IniRead);

	//GetPrivateProfileStringA("BaseDetectParameter", "cameraA_detect_begin", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA1_DETECT_BEGIN_POINT)->GetWindowTextA(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraA_detect_begin);
	WritePrivateProfileString("BaseDetectParameter", "cameraA_detect_begin", IniWrite, IniPath);
	//parameters_setting_trans.cameraA_detect_begin = atoi(IniRead);


	//GetPrivateProfileStringA("BaseDetectParameter", "cameraA_detect_end", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA1_DETECT_END_POINT)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraA_detect_end = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraA_detect_end);
	WritePrivateProfileString("BaseDetectParameter", "cameraA_detect_end", IniWrite, IniPath);


	//GetPrivateProfileStringA("BaseDetectParameter", "cameraA_valve_amount", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA1_VALVE_AMOUNT)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraA_valve_amount = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraA_valve_amount);
	WritePrivateProfileString("BaseDetectParameter", "cameraA_valve_amount", IniWrite, IniPath);


	//GetPrivateProfileStringA("BaseDetectParameter", "cameraB_begin", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA2_BEGIN_POINT)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraB_begin = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraB_begin);
	WritePrivateProfileString("BaseDetectParameter", "cameraB_begin", IniWrite, IniPath);


	//GetPrivateProfileStringA("BaseDetectParameter", "cameraB_end", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA2_END_POINT)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraB_end = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraB_end);
	WritePrivateProfileString("BaseDetectParameter", "cameraB_end", IniWrite, IniPath);


	//GetPrivateProfileStringA("BaseDetectParameter", "cameraB_align_begin", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA2_ALIGNING_BEGIN_POINT)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraB_align_begin = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraB_align_begin);
	WritePrivateProfileString("BaseDetectParameter", "cameraB_align_begin", IniWrite, IniPath);


	//GetPrivateProfileStringA("BaseDetectParameter", "cameraB_align_end", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA2_ALIGNING_END_POINT)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraB_align_end = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraB_align_end);
	WritePrivateProfileString("BaseDetectParameter", "cameraB_align_end", IniWrite, IniPath);


	//GetPrivateProfileStringA("BaseDetectParameter", "cameraB_detect_begin", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA2_DETECT_BEGIN_POINT)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraB_detect_begin = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraB_detect_begin);
	WritePrivateProfileString("BaseDetectParameter", "cameraB_detect_begin", IniWrite, IniPath);


	//GetPrivateProfileStringA("BaseDetectParameter", "cameraB_detect_end", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA2_DETECT_END_POINT)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraB_detect_end = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraB_detect_end);
	WritePrivateProfileString("BaseDetectParameter", "cameraB_detect_end", IniWrite, IniPath);


	//GetPrivateProfileStringA("BaseDetectParameter", "cameraB_valve_amount", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA2_VALVE_AMOUNT)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraB_valve_amount = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraB_valve_amount);
	WritePrivateProfileString("BaseDetectParameter", "cameraB_valve_amount", IniWrite, IniPath);


	//GetPrivateProfileStringA("BaseDetectParameter", "cameraC_begin", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA3_BEGIN_POINT)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraC_begin = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraC_begin);
	WritePrivateProfileString("BaseDetectParameter", "cameraC_begin", IniWrite, IniPath);


	//GetPrivateProfileStringA("BaseDetectParameter", "cameraC_end", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA3_END_POINT)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraC_end = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraC_end);
	WritePrivateProfileString("BaseDetectParameter", "cameraC_end", IniWrite, IniPath);


	//GetPrivateProfileStringA("BaseDetectParameter", "cameraC_align_begin", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA3_ALIGNING_BEGIN_POINT)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraC_align_begin = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraC_align_begin);
	WritePrivateProfileString("BaseDetectParameter", "cameraC_align_begin", IniWrite, IniPath);


	//GetPrivateProfileStringA("BaseDetectParameter", "cameraC_align_end", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA3_ALIGNING_END_POINT)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraC_align_end = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraC_align_end);
	WritePrivateProfileString("BaseDetectParameter", "cameraC_align_end", IniWrite, IniPath);


	//GetPrivateProfileStringA("BaseDetectParameter", "cameraC_detect_begin", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA3_DETECT_BEGIN_POINT)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraC_detect_begin = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraC_detect_begin);
	WritePrivateProfileString("BaseDetectParameter", "cameraC_detect_begin", IniWrite, IniPath);


	//GetPrivateProfileStringA("BaseDetectParameter", "cameraC_detect_end", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA3_DETECT_END_POINT)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraC_detect_end = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraC_detect_end);
	WritePrivateProfileString("BaseDetectParameter", "cameraC_detect_end", IniWrite, IniPath);


	//GetPrivateProfileStringA("BaseDetectParameter", "cameraC_valve_amount", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA3_VALVE_AMOUNT)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraC_valve_amount = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraC_valve_amount);
	WritePrivateProfileString("BaseDetectParameter", "cameraC_valve_amount", IniWrite, IniPath);


	//GetPrivateProfileStringA("BaseDetectParameter", "cameraD_begin", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA4_BEGIN_POINT)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraD_begin = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraD_begin);
	WritePrivateProfileString("BaseDetectParameter", "cameraD_begin", IniWrite, IniPath);


	//GetPrivateProfileStringA("BaseDetectParameter", "cameraD_end", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA4_END_POINT)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraD_end = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraD_end);
	WritePrivateProfileString("BaseDetectParameter", "cameraD_end", IniWrite, IniPath);


	//GetPrivateProfileStringA("BaseDetectParameter", "cameraD_align_begin", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA4_ALIGNING_BEGIN_POINT)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraD_align_begin = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraD_align_begin);
	WritePrivateProfileString("BaseDetectParameter", "cameraD_align_begin", IniWrite, IniPath);

	//GetPrivateProfileStringA("BaseDetectParameter", "cameraD_align_end", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA4_ALIGNING_END_POINT)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraD_align_end = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraD_align_end);
	WritePrivateProfileString("BaseDetectParameter", "cameraD_align_end", IniWrite, IniPath);


	//GetPrivateProfileStringA("BaseDetectParameter", "cameraD_detect_begin", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA4_DETECT_BEGIN_POINT)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraD_detect_begin = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraD_detect_begin);
	WritePrivateProfileString("BaseDetectParameter", "cameraD_detect_begin", IniWrite, IniPath);


	//GetPrivateProfileStringA("BaseDetectParameter", "cameraD_detect_end", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA4_DETECT_END_POINT)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraD_detect_end = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraD_detect_end);
	WritePrivateProfileString("BaseDetectParameter", "cameraD_detect_end", IniWrite, IniPath);


	//GetPrivateProfileStringA("BaseDetectParameter", "cameraD_valve_amount", "", IniRead, 24, IniPath);
	//m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA4_VALVE_AMOUNT)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraD_valve_amount = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraD_valve_amount);
	WritePrivateProfileString("BaseDetectParameter", "cameraD_valve_amount", IniWrite, IniPath);


	//Camera A detect parameter setting;
	//GetPrivateProfileStringA("ValveParameter", "cameraA_delay", "", IniRead, 24, IniPath);
	//m_dlgValveParametersSettting.GetDlgItem(IDC_EDIT_VALVE_A_DELAY)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraA_delay = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraA_delay);
	WritePrivateProfileString("ValveParameter", "cameraA_delay", IniWrite, IniPath);


	//GetPrivateProfileStringA("ValveParameter", "cameraA_hold", "", IniRead, 24, IniPath);
	//m_dlgValveParametersSettting.GetDlgItem(IDC_EDIT_VALVE_A_HOLD)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraA_hold = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraA_hold);
	WritePrivateProfileString("ValveParameter", "cameraA_hold", IniWrite, IniPath);


	//GetPrivateProfileStringA("ValveParameter", "cameraB_delay", "", IniRead, 24, IniPath);
	//m_dlgValveParametersSettting.GetDlgItem(IDC_EDIT_VALVE_B_DELAY)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraB_delay = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraB_delay);
	WritePrivateProfileString("ValveParameter", "cameraB_delay", IniWrite, IniPath);
	//-----------------------------------------------------------------------------------------

	//GetPrivateProfileStringA("ValveParameter", "cameraB_hold", "", IniRead, 24, IniPath);
	//m_dlgValveParametersSettting.GetDlgItem(IDC_EDIT_VALVE_B_HOLD)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraB_hold = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraB_hold);
	WritePrivateProfileString("ValveParameter", "cameraB_hold", IniWrite, IniPath);


	//GetPrivateProfileStringA("ValveParameter", "cameraC_delay", "", IniRead, 24, IniPath);
	//m_dlgValveParametersSettting.GetDlgItem(IDC_EDIT_VALVE_C_DELAY)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraC_delay = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraC_delay);
	WritePrivateProfileString("ValveParameter", "cameraC_delay", IniWrite, IniPath);


	//GetPrivateProfileStringA("ValveParameter", "cameraC_hold", "", IniRead, 24, IniPath);
	//m_dlgValveParametersSettting.GetDlgItem(IDC_EDIT_VALVE_C_HOLD)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraC_hold = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraC_hold);
	WritePrivateProfileString("ValveParameter", "cameraC_hold", IniWrite, IniPath);

	//GetPrivateProfileStringA("ValveParameter", "cameraD_delay", "", IniRead, 24, IniPath);
	//m_dlgValveParametersSettting.GetDlgItem(IDC_EDIT_VALVE_D_DELAY)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraD_delay = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraD_delay);
	WritePrivateProfileString("ValveParameter", "cameraD_delay", IniWrite, IniPath);

	//GetPrivateProfileStringA("ValveParameter", "cameraD_hold", "", IniRead, 24, IniPath);
	//m_dlgValveParametersSettting.GetDlgItem(IDC_EDIT_VALVE_D_HOLD)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraD_hold = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraD_hold);
	WritePrivateProfileString("ValveParameter", "cameraD_hold", IniWrite, IniPath);

	//GetPrivateProfileStringA("ValveParameter", "valve_work_times", "", IniRead, 24, IniPath);
	//m_dlgValveParametersSettting.GetDlgItem(IDC_EDIT_VALVE_WORK_TIMES)->GetWindowTextA(IniRead);
	//parameters_setting_trans.valve_work_times = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.valve_work_times);
	WritePrivateProfileString("ValveParameter", "valve_work_times", IniWrite, IniPath);

	//GetPrivateProfileStringA("ValveParameter", "valve_stop_time", "", IniRead, 24, IniPath);
	//m_dlgValveParametersSettting.GetDlgItem(IDC_EDIT_VALVE_STOP_TIMES)->GetWindowTextA(IniRead);
	//parameters_setting_trans.valve_stop_time = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.valve_stop_time);
	WritePrivateProfileString("ValveParameter", "valve_stop_time", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraA_point_area_min", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingA.GetDlgItem(IDC_EDIT_POINT_AREA_MIN)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraA_point_area_min = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraA_point_area_min);
	WritePrivateProfileString("DetectParameter", "cameraA_point_area_min", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraA_point_area_max", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingA.GetDlgItem(IDC_EDIT_POINT_AREA_MAX)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraA_point_area_max = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraA_point_area_max);
	WritePrivateProfileString("DetectParameter", "cameraA_point_area_max", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraA_point_length_min", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingA.GetDlgItem(IDC_EDIT_POINT_LENGTH_MIN)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraA_point_length_min = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraA_point_length_min);
	WritePrivateProfileString("DetectParameter", "cameraA_point_length_min", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraA_point_length_max", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingA.GetDlgItem(IDC_EDIT_POINT_LENGTH_MAX)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraA_point_length_max = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraA_point_length_max);
	WritePrivateProfileString("DetectParameter", "cameraA_point_length_max", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraA_point_width_min", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingA.GetDlgItem(IDC_EDIT_POINT_WIDTH_MIN)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraA_point_width_min = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraA_point_width_min);
	WritePrivateProfileString("DetectParameter", "cameraA_point_width_min", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraA_point_width_max", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingA.GetDlgItem(IDC_EDIT_POINT_WIDTH_MAX)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraA_point_width_max = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraA_point_width_max);
	WritePrivateProfileString("DetectParameter", "cameraA_point_width_max", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraA_thread_area_min", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingA.GetDlgItem(IDC_EDIT_THREAD_AREA_MIN)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraA_thread_area_min = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraA_thread_area_min);
	WritePrivateProfileString("DetectParameter", "cameraA_thread_area_min", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraA_thread_area_max", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingA.GetDlgItem(IDC_EDIT_THREAD_AREA_MAX)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraA_thread_area_max = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraA_thread_area_max);
	WritePrivateProfileString("DetectParameter", "cameraA_thread_area_max", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraA_thread_length_min", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingA.GetDlgItem(IDC_EDIT_THREAD_LENGTH_MIN)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraA_thread_length_min = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraA_thread_length_min);
	WritePrivateProfileString("DetectParameter", "cameraA_thread_length_min", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraA_thread_length_max", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingA.GetDlgItem(IDC_EDIT_THREAD_LENGTH_MAX)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraA_thread_length_max = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraA_thread_length_max);
	WritePrivateProfileString("DetectParameter", "cameraA_thread_length_max", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraA_thread_width_min", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingA.GetDlgItem(IDC_EDIT_THREAD_WIDTH_MIN)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraA_thread_width_min = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraA_thread_width_min);
	WritePrivateProfileString("DetectParameter", "cameraA_thread_width_min", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraA_thread_width_max", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingA.GetDlgItem(IDC_EDIT_THREAD_WIDTH_MAX)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraA_thread_width_max = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraA_thread_width_max);
	WritePrivateProfileString("DetectParameter", "cameraA_thread_width_max", IniWrite, IniPath);


	//Camera B detect parameter setting;
	//GetPrivateProfileStringA("DetectParameter", "cameraB_point_area_min", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingB.GetDlgItem(IDC_EDIT_POINT_AREA_MIN)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraB_point_area_min = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraB_point_area_min);
	WritePrivateProfileString("DetectParameter", "cameraB_point_area_min", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraB_point_area_max", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingB.GetDlgItem(IDC_EDIT_POINT_AREA_MAX)->SetWindowTextA(IniRead);
	//parameters_setting_trans.cameraB_point_area_max = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraB_point_area_max);
	WritePrivateProfileString("DetectParameter", "cameraB_point_area_max", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraB_point_length_min", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingB.GetDlgItem(IDC_EDIT_POINT_LENGTH_MIN)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraB_point_length_min = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraB_point_length_min);
	WritePrivateProfileString("DetectParameter", "cameraB_point_length_min", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraB_point_length_max", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingB.GetDlgItem(IDC_EDIT_POINT_LENGTH_MAX)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraB_point_length_max = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraB_point_length_max);
	WritePrivateProfileString("DetectParameter", "cameraB_point_length_max", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraB_point_width_min", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingB.GetDlgItem(IDC_EDIT_POINT_WIDTH_MIN)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraB_point_width_min = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraB_point_width_min);
	WritePrivateProfileString("DetectParameter", "cameraB_point_width_min", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraB_point_width_max", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingB.GetDlgItem(IDC_EDIT_POINT_WIDTH_MAX)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraB_point_width_max = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraB_point_width_max);
	WritePrivateProfileString("DetectParameter", "cameraB_point_width_max", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraB_thread_area_min", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingB.GetDlgItem(IDC_EDIT_THREAD_AREA_MIN)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraB_thread_area_min = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraB_thread_area_min);
	WritePrivateProfileString("DetectParameter", "cameraB_thread_area_min", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraB_thread_area_max", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingB.GetDlgItem(IDC_EDIT_THREAD_AREA_MAX)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraB_thread_area_max = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraB_thread_area_max);
	WritePrivateProfileString("DetectParameter", "cameraB_thread_area_max", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraB_thread_length_min", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingB.GetDlgItem(IDC_EDIT_THREAD_LENGTH_MIN)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraB_thread_length_min = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraB_thread_length_min);
	WritePrivateProfileString("DetectParameter", "cameraB_thread_length_min", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraB_thread_length_max", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingB.GetDlgItem(IDC_EDIT_THREAD_LENGTH_MAX)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraB_thread_length_max = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraB_thread_length_max);
	WritePrivateProfileString("DetectParameter", "cameraB_thread_length_max", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraB_thread_width_min", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingB.GetDlgItem(IDC_EDIT_THREAD_WIDTH_MIN)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraB_thread_width_min = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraB_thread_width_min);
	WritePrivateProfileString("DetectParameter", "cameraB_thread_width_min", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraB_thread_width_max", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingB.GetDlgItem(IDC_EDIT_THREAD_WIDTH_MAX)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraB_thread_width_max = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraB_thread_width_max);
	WritePrivateProfileString("DetectParameter", "cameraB_thread_width_max", IniWrite, IniPath);


	//Camera C detect parameter setting;
	//GetPrivateProfileStringA("DetectParameter", "cameraC_point_area_min", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingC.GetDlgItem(IDC_EDIT_POINT_AREA_MIN)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraC_point_area_min = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraC_point_area_min);
	WritePrivateProfileString("DetectParameter", "cameraC_point_area_min", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraC_point_area_max", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingC.GetDlgItem(IDC_EDIT_POINT_AREA_MAX)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraC_point_area_max = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraC_point_area_max);
	WritePrivateProfileString("DetectParameter", "cameraC_point_area_max", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraC_point_length_min", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingC.GetDlgItem(IDC_EDIT_POINT_LENGTH_MIN)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraC_point_length_min = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraC_point_length_min);
	WritePrivateProfileString("DetectParameter", "cameraC_point_length_min", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraC_point_length_max", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingC.GetDlgItem(IDC_EDIT_POINT_LENGTH_MAX)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraC_point_length_max = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraC_point_length_max);
	WritePrivateProfileString("DetectParameter", "cameraC_point_length_max", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraC_point_width_min", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingC.GetDlgItem(IDC_EDIT_POINT_WIDTH_MIN)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraC_point_width_min = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraC_point_width_min);
	WritePrivateProfileString("DetectParameter", "cameraC_point_width_min", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraC_point_width_max", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingC.GetDlgItem(IDC_EDIT_POINT_WIDTH_MAX)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraC_point_width_max = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraC_point_width_max);
	WritePrivateProfileString("DetectParameter", "cameraC_point_width_max", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraC_thread_area_min", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingC.GetDlgItem(IDC_EDIT_THREAD_AREA_MIN)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraC_thread_area_min = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraC_thread_area_min);
	WritePrivateProfileString("DetectParameter", "cameraC_thread_area_min", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraC_thread_area_max", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingC.GetDlgItem(IDC_EDIT_THREAD_AREA_MAX)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraC_thread_area_max = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraC_thread_area_max);
	WritePrivateProfileString("DetectParameter", "cameraC_thread_area_max", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraC_thread_length_min", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingC.GetDlgItem(IDC_EDIT_THREAD_LENGTH_MIN)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraC_thread_length_min = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraC_thread_length_min);
	WritePrivateProfileString("DetectParameter", "cameraC_thread_length_min", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraC_thread_length_max", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingC.GetDlgItem(IDC_EDIT_THREAD_LENGTH_MAX)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraC_thread_length_max = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraC_thread_length_max);
	WritePrivateProfileString("DetectParameter", "cameraC_thread_length_max", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraC_thread_width_min", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingC.GetDlgItem(IDC_EDIT_THREAD_WIDTH_MIN)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraC_thread_width_min = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraC_thread_width_min);
	WritePrivateProfileString("DetectParameter", "cameraC_thread_width_min", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraC_thread_width_max", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingC.GetDlgItem(IDC_EDIT_THREAD_WIDTH_MAX)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraC_thread_width_max = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraC_thread_width_max);
	WritePrivateProfileString("DetectParameter", "cameraC_thread_width_max", IniWrite, IniPath);


	//Camera D detect parameter setting;
	//GetPrivateProfileStringA("DetectParameter", "cameraD_point_area_min", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingD.GetDlgItem(IDC_EDIT_POINT_AREA_MIN)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraD_point_area_min = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraD_point_area_min);
	WritePrivateProfileString("DetectParameter", "cameraD_point_area_min", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraD_point_area_max", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingD.GetDlgItem(IDC_EDIT_POINT_AREA_MAX)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraD_point_area_max = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraD_point_area_max);
	WritePrivateProfileString("DetectParameter", "cameraD_point_area_max", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraD_point_length_min", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingD.GetDlgItem(IDC_EDIT_POINT_LENGTH_MIN)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraD_point_length_min = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraD_point_length_min);
	WritePrivateProfileString("DetectParameter", "cameraD_point_length_min", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraD_point_length_max", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingD.GetDlgItem(IDC_EDIT_POINT_LENGTH_MAX)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraD_point_length_max = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraD_point_length_max);
	WritePrivateProfileString("DetectParameter", "cameraD_point_length_max", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraD_point_width_min", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingD.GetDlgItem(IDC_EDIT_POINT_WIDTH_MIN)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraD_point_width_min = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraD_point_width_min);
	WritePrivateProfileString("DetectParameter", "cameraD_point_width_min", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraD_point_width_max", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingD.GetDlgItem(IDC_EDIT_POINT_WIDTH_MAX)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraD_point_width_max = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraD_point_width_max);
	WritePrivateProfileString("DetectParameter", "cameraD_point_width_max", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraD_thread_area_min", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingD.GetDlgItem(IDC_EDIT_THREAD_AREA_MIN)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraD_thread_area_min = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraD_thread_area_min);
	WritePrivateProfileString("DetectParameter", "cameraD_thread_area_min", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraD_thread_area_max", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingD.GetDlgItem(IDC_EDIT_THREAD_AREA_MAX)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraD_thread_area_max = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraD_thread_area_max);
	WritePrivateProfileString("DetectParameter", "cameraD_thread_area_max", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraD_thread_length_min", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingD.GetDlgItem(IDC_EDIT_THREAD_LENGTH_MIN)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraD_thread_length_min = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraD_thread_length_min);
	WritePrivateProfileString("DetectParameter", "cameraD_thread_length_min", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraD_thread_length_max", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingD.GetDlgItem(IDC_EDIT_THREAD_LENGTH_MAX)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraD_thread_length_max = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraD_thread_length_max);
	WritePrivateProfileString("DetectParameter", "cameraD_thread_length_max", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraD_thread_width_min", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingD.GetDlgItem(IDC_EDIT_THREAD_WIDTH_MIN)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraD_thread_width_min = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraD_thread_width_min);
	WritePrivateProfileString("DetectParameter", "cameraD_thread_width_min", IniWrite, IniPath);

	//GetPrivateProfileStringA("DetectParameter", "cameraD_thread_width_max", "", IniRead, 24, IniPath);
	//m_dlgFiberDetectParametersSettingD.GetDlgItem(IDC_EDIT_THREAD_WIDTH_MAX)->GetWindowTextA(IniRead);
	//parameters_setting_trans.cameraD_thread_width_max = atoi(IniRead);
	IniWrite.Format("%d", parameters_setting_trans.cameraD_thread_width_max);
	WritePrivateProfileString("DetectParameter", "cameraD_thread_width_max", IniWrite, IniPath);


	//DebugParaneters setting;
	//GetPrivateProfileStringA("DebugParameter", "debug_cameraA", "", IniRead, 24, IniPath);
	//parameters_setting_trans.debug_cameraA = m_dlgDebugParametersSetting.m_checkDebugCameraA.GetCheck();
	IniWrite.Format("%d", parameters_setting_trans.debug_cameraA);
	WritePrivateProfileString("DebugParameter", "debug_cameraA", IniWrite, IniPath);


	//GetPrivateProfileStringA("DebugParameter", "debug_cameraB", "", IniRead, 24, IniPath);
	//parameters_setting_trans.debug_cameraB = m_dlgDebugParametersSetting.m_checkDebugCameraB.GetCheck();
	IniWrite.Format("%d", parameters_setting_trans.debug_cameraB);
	WritePrivateProfileString("DebugParameter", "debug_cameraB", IniWrite, IniPath);

	//GetPrivateProfileStringA("DebugParameter", "debug_cameraC", "", IniRead, 24, IniPath);
	//parameters_setting_trans.debug_cameraC = m_dlgDebugParametersSetting.m_checkDebugCameraC.GetCheck();
	IniWrite.Format("%d", parameters_setting_trans.debug_cameraC);
	WritePrivateProfileString("DebugParameter", "debug_cameraC", IniWrite, IniPath);

	//GetPrivateProfileStringA("DebugParameter", "debug_cameraD", "", IniRead, 24, IniPath);
	//parameters_setting_trans.debug_cameraD = m_dlgDebugParametersSetting.m_checkDebugCameraD.GetCheck();
	IniWrite.Format("%d", parameters_setting_trans.debug_cameraD);
	WritePrivateProfileString("DebugParameter", "debug_cameraD", IniWrite, IniPath);

	//GetPrivateProfileStringA("DebugParameter", "stop_volve", "", IniRead, 24, IniPath);
	//parameters_setting_trans.stop_volve = m_dlgDebugParametersSetting.m_checkStopValve.GetCheck();
	IniWrite.Format("%d", parameters_setting_trans.stop_volve);
	WritePrivateProfileString("DebugParameter", "stop_volve", IniWrite, IniPath);

	//GetPrivateProfileStringA("DebugParameter", "save_blob", "", IniRead, 24, IniPath);
	//parameters_setting_trans.save_blob = m_dlgDebugParametersSetting.m_checkSaveBolb.GetCheck();
	IniWrite.Format("%d", parameters_setting_trans.save_blob);
	WritePrivateProfileString("DebugParameter", "save_blob", IniWrite, IniPath);

	return;
}


void CFiberDetectControlDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	RedrawWindow();
}



