// NetSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "FiberDetectControl.h"
#include "NetSetting.h"
#include "afxdialogex.h"


// CNetSetting 对话框

IMPLEMENT_DYNAMIC(CNetSetting, CDialogEx)

CNetSetting::CNetSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNetSetting::IDD, pParent)
{

}

CNetSetting::~CNetSetting()
{
}

void CNetSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNetSetting, CDialogEx)
	ON_BN_CLICKED(IDC_MFCBUTTON_CAMERA4_NET, &CNetSetting::OnBnClickedMfcbuttonCamera4Net)
	ON_BN_CLICKED(IDC_BUTTON_CAMERA3_NET, &CNetSetting::OnBnClickedButtonCamera3Net)
	ON_BN_CLICKED(IDC_BUTTON_CAMERA2_NET, &CNetSetting::OnBnClickedButtonCamera2Net)
	ON_BN_CLICKED(IDC_BUTTON_CAMERA1_NET, &CNetSetting::OnBnClickedButtonCamera1Net)
	ON_BN_CLICKED(IDC_BUTTON_ELECTRICAL_LOCAL_NET_SETTING, &CNetSetting::OnBnClickedButtonElectricalLocalNetSetting)
	ON_BN_CLICKED(IDC_BUTTON_ELECTRICAL_DRIVER_NET_SETTING, &CNetSetting::OnBnClickedButtonElectricalDriverNetSetting)
	ON_BN_CLICKED(IDC_BUTTON_COMPUTER2_NET_SETTING, &CNetSetting::OnBnClickedButtonComputer2NetSetting)
	ON_BN_CLICKED(IDC_BUTTON_COMPUTER1_NET_SETTING, &CNetSetting::OnBnClickedButtonComputer1NetSetting)
	ON_BN_CLICKED(IDOK, &CNetSetting::OnBnClickedOk)
END_MESSAGE_MAP()


// CNetSetting 消息处理程序


void CNetSetting::OnBnClickedMfcbuttonCamera4Net()
{
	// TODO:  在此添加控件通知处理程序代码
	int camera_total;
	char IniRead[255];
	memset(IniRead, 0, 255);
	char IniPath[255];
	memset(IniPath, 0, 255);
	//camera_ip_info ci_info;
	CString strPath = GetModulePath();
	strcpy_s(IniPath, 255, strPath.GetBuffer());
	strcat_s(IniPath, "/param.ini");

	GetPrivateProfileStringA("CameraSetting", "cameraD_ip", "", IniRead, 24, IniPath);
	//m_dlgNetworkParameters.GetDlgItem(IDC_EDIT_IP_ADRESS)->SetWindowTextA(IniRead);
	m_dlgCameraParametersSettting.m_strNetString = IniRead;

	GetPrivateProfileStringA("CameraSetting", "cameraD_port", "", IniRead, 24, IniPath);
	m_dlgCameraParametersSettting.m_u32NetPort = atoi(IniRead);

	GetPrivateProfileStringA("CameraSetting", "cameraD_scan_speed", "", IniRead, 24, IniPath);
	m_dlgCameraParametersSettting.m_nScanSpeed = atoi(IniRead);

	GetPrivateProfileStringA("CameraSetting", "cameraD_tirgging_mode", "", IniRead, 24, IniPath);
	m_dlgCameraParametersSettting.m_nTriggerMode = atoi(IniRead);

	GetPrivateProfileStringA("CameraSetting", "cameraD_exposure_time", "", IniRead, 24, IniPath);
	m_dlgCameraParametersSettting.m_nExposureTime = atoi(IniRead);

	GetPrivateProfileStringA("CameraSetting", "cameraD_gain", "", IniRead, 24, IniPath);
	m_dlgCameraParametersSettting.m_nGain = atoi(IniRead);

	if (m_dlgCameraParametersSettting.DoModal() != IDOK)
		return;

	cameraD_ip = m_dlgCameraParametersSettting.m_strNetString;
	cameraD_port = m_dlgCameraParametersSettting.m_u32NetPort;
	cameraD_scan_speed = m_dlgCameraParametersSettting.m_nScanSpeed;
	cameraD_tirgging_mode = m_dlgCameraParametersSettting.m_nTriggerMode;
	cameraD_exposure_time = m_dlgCameraParametersSettting.m_nExposureTime;
	cameraD_gain = m_dlgCameraParametersSettting.m_nGain;

	CString IniWrite;
	IniWrite.Format("%s", cameraC_ip);
	WritePrivateProfileString("System", "cameraD_ip", IniWrite, strPath);

	IniWrite.Format("%d", cameraC_port);
	WritePrivateProfileString("System", "cameraD_port", IniWrite, strPath);

	IniWrite.Format("%d", cameraC_scan_speed);
	WritePrivateProfileString("System", "cameraD_scan_speed", IniWrite, strPath);

	IniWrite.Format("%d", cameraC_tirgging_mode);
	WritePrivateProfileString("System", "cameraD_tirgging_mode", IniWrite, strPath);

	IniWrite.Format("%d", cameraC_tirgging_mode);
	WritePrivateProfileString("System", "cameraD_exposure_time", IniWrite, strPath);

	IniWrite.Format("%d", cameraC_gain);
	WritePrivateProfileString("System", "cameraD_gain", IniWrite, strPath);
}


void CNetSetting::OnBnClickedButtonCamera3Net()
{
	// TODO:  在此添加控件通知处理程序代码
	int camera_total;
	char IniRead[255];
	memset(IniRead, 0, 255);
	char IniPath[255];
	memset(IniPath, 0, 255);
	//camera_ip_info ci_info;
	CString strPath = GetModulePath();
	strcpy_s(IniPath, 255, strPath.GetBuffer());
	strcat_s(IniPath, "/param.ini");

	GetPrivateProfileStringA("CameraSetting", "cameraC_ip", "", IniRead, 24, IniPath);
	//m_dlgNetworkParameters.GetDlgItem(IDC_EDIT_IP_ADRESS)->SetWindowTextA(IniRead);
	m_dlgCameraParametersSettting.m_strNetString = IniRead;

	GetPrivateProfileStringA("CameraSetting", "cameraC_port", "", IniRead, 24, IniPath);
	m_dlgCameraParametersSettting.m_u32NetPort = atoi(IniRead);

	GetPrivateProfileStringA("CameraSetting", "cameraC_scan_speed", "", IniRead, 24, IniPath);
	m_dlgCameraParametersSettting.m_nScanSpeed = atoi(IniRead);

	GetPrivateProfileStringA("CameraSetting", "cameraC_tirgging_mode", "", IniRead, 24, IniPath);
	m_dlgCameraParametersSettting.m_nTriggerMode = atoi(IniRead);

	GetPrivateProfileStringA("CameraSetting", "cameraC_exposure_time", "", IniRead, 24, IniPath);
	m_dlgCameraParametersSettting.m_nExposureTime = atoi(IniRead);

	GetPrivateProfileStringA("CameraSetting", "cameraC_gain", "", IniRead, 24, IniPath);
	m_dlgCameraParametersSettting.m_nGain = atoi(IniRead);

	if (m_dlgCameraParametersSettting.DoModal() != IDOK)
		return;

	cameraC_ip = m_dlgCameraParametersSettting.m_strNetString;
	cameraC_port = m_dlgCameraParametersSettting.m_u32NetPort;
	cameraC_scan_speed = m_dlgCameraParametersSettting.m_nScanSpeed;
	cameraC_tirgging_mode = m_dlgCameraParametersSettting.m_nTriggerMode;
	cameraC_exposure_time = m_dlgCameraParametersSettting.m_nExposureTime;
	cameraC_gain = m_dlgCameraParametersSettting.m_nGain;

	CString IniWrite;
	IniWrite.Format("%s", cameraC_ip);
	WritePrivateProfileString("System", "cameraC_ip", IniWrite, strPath);

	IniWrite.Format("%d", cameraC_port);
	WritePrivateProfileString("System", "cameraC_port", IniWrite, strPath);

	IniWrite.Format("%d", cameraC_scan_speed);
	WritePrivateProfileString("System", "cameraC_scan_speed", IniWrite, strPath);

	IniWrite.Format("%d", cameraC_tirgging_mode);
	WritePrivateProfileString("System", "cameraC_tirgging_mode", IniWrite, strPath);

	IniWrite.Format("%d", cameraC_tirgging_mode);
	WritePrivateProfileString("System", "cameraC_exposure_time", IniWrite, strPath);

	IniWrite.Format("%d", cameraC_gain);
	WritePrivateProfileString("System", "cameraC_gain", IniWrite, strPath);
}


void CNetSetting::OnBnClickedButtonCamera2Net()
{
	// TODO:  在此添加控件通知处理程序代码
	int camera_total;
	char IniRead[255];
	memset(IniRead, 0, 255);
	char IniPath[255];
	memset(IniPath, 0, 255);
	//camera_ip_info ci_info;
	CString strPath = GetModulePath();
	strcpy_s(IniPath, 255, strPath.GetBuffer());
	strcat_s(IniPath, "/param.ini");

	GetPrivateProfileStringA("CameraSetting", "cameraB_ip", "", IniRead, 24, IniPath);
	//m_dlgNetworkParameters.GetDlgItem(IDC_EDIT_IP_ADRESS)->SetWindowTextA(IniRead);
	m_dlgCameraParametersSettting.m_strNetString = IniRead;

	GetPrivateProfileStringA("CameraSetting", "cameraB_port", "", IniRead, 24, IniPath);
	m_dlgCameraParametersSettting.m_u32NetPort = atoi(IniRead);

	GetPrivateProfileStringA("CameraSetting", "cameraB_scan_speed", "", IniRead, 24, IniPath);
	m_dlgCameraParametersSettting.m_nScanSpeed = atoi(IniRead);

	GetPrivateProfileStringA("CameraSetting", "cameraB_tirgging_mode", "", IniRead, 24, IniPath);
	m_dlgCameraParametersSettting.m_nTriggerMode = atoi(IniRead);

	GetPrivateProfileStringA("CameraSetting", "cameraB_exposure_time", "", IniRead, 24, IniPath);
	m_dlgCameraParametersSettting.m_nExposureTime = atoi(IniRead);

	GetPrivateProfileStringA("CameraSetting", "cameraB_gain", "", IniRead, 24, IniPath);
	m_dlgCameraParametersSettting.m_nGain = atoi(IniRead);

	if (m_dlgCameraParametersSettting.DoModal() != IDOK)
		return;

	cameraB_ip = m_dlgCameraParametersSettting.m_strNetString;
	cameraB_port = m_dlgCameraParametersSettting.m_u32NetPort;
	cameraB_scan_speed = m_dlgCameraParametersSettting.m_nScanSpeed;
	cameraB_tirgging_mode = m_dlgCameraParametersSettting.m_nTriggerMode;
	cameraB_exposure_time = m_dlgCameraParametersSettting.m_nExposureTime;
	cameraB_gain = m_dlgCameraParametersSettting.m_nGain;

	CString IniWrite;
	IniWrite.Format("%s", cameraB_ip);
	WritePrivateProfileString("System", "cameraB_ip", IniWrite, strPath);

	IniWrite.Format("%d", cameraB_port);
	WritePrivateProfileString("System", "cameraB_port", IniWrite, strPath);

	IniWrite.Format("%d", cameraB_scan_speed);
	WritePrivateProfileString("System", "cameraB_scan_speed", IniWrite, strPath);

	IniWrite.Format("%d", cameraB_tirgging_mode);
	WritePrivateProfileString("System", "cameraB_tirgging_mode", IniWrite, strPath);

	IniWrite.Format("%d", cameraB_tirgging_mode);
	WritePrivateProfileString("System", "cameraB_exposure_time", IniWrite, strPath);

	IniWrite.Format("%d", cameraB_gain);
	WritePrivateProfileString("System", "cameraB_gain", IniWrite, strPath);
}


void CNetSetting::OnBnClickedButtonCamera1Net()
{
	// TODO:  在此添加控件通知处理程序代码
	int camera_total;
	char IniRead[255];
	memset(IniRead, 0, 255);
	char IniPath[255];
	memset(IniPath, 0, 255);
	//camera_ip_info ci_info;
	CString strPath = GetModulePath();
	strcpy_s(IniPath, 255, strPath.GetBuffer());
	strcat_s(IniPath, "/param.ini");

	GetPrivateProfileStringA("CameraSetting", "cameraA_ip", "", IniRead, 24, IniPath);
	//m_dlgNetworkParameters.GetDlgItem(IDC_EDIT_IP_ADRESS)->SetWindowTextA(IniRead);
	m_dlgCameraParametersSettting.m_strNetString = IniRead;

	GetPrivateProfileStringA("CameraSetting", "cameraA_port", "", IniRead, 24, IniPath);
	m_dlgCameraParametersSettting.m_u32NetPort = atoi(IniRead);

	GetPrivateProfileStringA("CameraSetting", "cameraA_scan_speed", "", IniRead, 24, IniPath);
	m_dlgCameraParametersSettting.m_nScanSpeed = atoi(IniRead);

	GetPrivateProfileStringA("CameraSetting", "cameraA_tirgging_mode", "", IniRead, 24, IniPath);
	m_dlgCameraParametersSettting.m_nTriggerMode = atoi(IniRead);

	GetPrivateProfileStringA("CameraSetting", "cameraA_exposure_time", "", IniRead, 24, IniPath);
	m_dlgCameraParametersSettting.m_nExposureTime = atoi(IniRead);

	GetPrivateProfileStringA("CameraSetting", "cameraA_gain", "", IniRead, 24, IniPath);
	m_dlgCameraParametersSettting.m_nGain = atoi(IniRead);

	if (m_dlgCameraParametersSettting.DoModal() != IDOK)
		return;

	cameraA_ip = m_dlgCameraParametersSettting.m_strNetString;
	cameraA_port = m_dlgCameraParametersSettting.m_u32NetPort;
	cameraA_scan_speed = m_dlgCameraParametersSettting.m_nScanSpeed;
	cameraA_tirgging_mode = m_dlgCameraParametersSettting.m_nTriggerMode;
	cameraA_exposure_time = m_dlgCameraParametersSettting.m_nExposureTime;
	cameraA_gain = m_dlgCameraParametersSettting.m_nGain;

	CString IniWrite;
	IniWrite.Format("%s", cameraA_ip);
	WritePrivateProfileString("System", "cameraA_ip", IniWrite, strPath);

	IniWrite.Format("%d", cameraA_port);
	WritePrivateProfileString("System", "cameraA_port", IniWrite, strPath);

	IniWrite.Format("%d", cameraA_scan_speed);
	WritePrivateProfileString("System", "cameraA_scan_speed", IniWrite, strPath);

	IniWrite.Format("%d", cameraA_tirgging_mode);
	WritePrivateProfileString("System", "cameraA_tirgging_mode", IniWrite, strPath);

	IniWrite.Format("%d", cameraA_tirgging_mode);
	WritePrivateProfileString("System", "cameraA_exposure_time", IniWrite, strPath);

	IniWrite.Format("%d", cameraA_gain);
	WritePrivateProfileString("System", "cameraA_gain", IniWrite, strPath);
	
}


void CNetSetting::OnBnClickedButtonElectricalLocalNetSetting()
{
	// TODO:  在此添加控件通知处理程序代码
	int camera_total;
	char IniRead[255];
	memset(IniRead, 0, 255);
	char IniPath[255];
	memset(IniPath, 0, 255);
	//camera_ip_info ci_info;
	CString strPath = GetModulePath();
	strcpy_s(IniPath, 255, strPath.GetBuffer());
	strcat_s(IniPath, "/param.ini");
	GetPrivateProfileStringA("System", "local_ip", "", IniRead, 24, IniPath);
	//m_dlgNetworkParameters.GetDlgItem(IDC_EDIT_IP_ADRESS)->SetWindowTextA(IniRead);
	m_dlgNetworkParameters.m_strNetString = IniRead;
	GetPrivateProfileStringA("System", "local_port", "", IniRead, 24, IniPath);
	//m_dlgNetworkParameters.GetDlgItem(IDC_EDIT_IP_PORT_NUMBER)->SetWindowTextA(IniRead);

	m_dlgNetworkParameters.m_u32NetPort = atoi(IniRead);

	if (m_dlgNetworkParameters.DoModal() != IDOK)
		return;
	local_ip = m_dlgNetworkParameters.m_strNetString;
	local_port = m_dlgNetworkParameters.m_u32NetPort;

	CString IniWrite;
	IniWrite.Format("%s", local_ip);
	WritePrivateProfileString("System", "local_ip", IniWrite, strPath);

	IniWrite.Format("%d", local_port);
	WritePrivateProfileString("System", "local_port", IniWrite, strPath);
}


void CNetSetting::OnBnClickedButtonElectricalDriverNetSetting()
{
	// TODO:  在此添加控件通知处理程序代码
	int camera_total;
	char IniRead[255];
	memset(IniRead, 0, 255);
	char IniPath[255];
	memset(IniPath, 0, 255);
	//camera_ip_info ci_info;
	CString strPath = GetModulePath();
	strcpy_s(IniPath, 255, strPath.GetBuffer());
	strcat_s(IniPath, "/param.ini");
	GetPrivateProfileStringA("System", "electric_board_ip", "", IniRead, 24, IniPath);
	//m_dlgNetworkParameters.GetDlgItem(IDC_EDIT_IP_ADRESS)->SetWindowTextA(IniRead);
	m_dlgNetworkParameters.m_strNetString = IniRead;
	GetPrivateProfileStringA("System", "electric_board_port", "", IniRead, 24, IniPath);
	//m_dlgNetworkParameters.GetDlgItem(IDC_EDIT_IP_PORT_NUMBER)->SetWindowTextA(IniRead);
	m_dlgNetworkParameters.m_u32NetPort = atoi(IniRead);

	if (m_dlgNetworkParameters.DoModal() != IDOK)
		return;

	electric_board_ip = m_dlgNetworkParameters.m_strNetString;
	electric_board_port = m_dlgNetworkParameters.m_u32NetPort;

	CString IniWrite;
	IniWrite.Format("%s", electric_board_ip);
	WritePrivateProfileString("System", "electric_board_ip", IniWrite, strPath);

	IniWrite.Format("%d", electric_board_port);
	WritePrivateProfileString("System", "electric_board_port", IniWrite, strPath);
}


void CNetSetting::OnBnClickedButtonComputer2NetSetting()
{
	// TODO:  在此添加控件通知处理程序代码
	int camera_total;
	char IniRead[255];
	memset(IniRead, 0, 255);
	char IniPath[255];
	memset(IniPath, 0, 255);
	//camera_ip_info ci_info;
	CString strPath = GetModulePath();
	strcpy_s(IniPath, 255, strPath.GetBuffer());
	strcat_s(IniPath, "/param.ini");
	GetPrivateProfileStringA("System", "box2_ip", "", IniRead, 24, IniPath);
	//m_dlgNetworkParameters.GetDlgItem(IDC_EDIT_IP_ADRESS)->SetWindowTextA(IniRead);
	m_dlgNetworkParameters.m_strNetString = IniRead;
	GetPrivateProfileStringA("System", "box2_port", "", IniRead, 24, IniPath);
	//m_dlgNetworkParameters.GetDlgItem(IDC_EDIT_IP_PORT_NUMBER)->SetWindowTextA(IniRead);
	m_dlgNetworkParameters.m_u32NetPort = atoi(IniRead);

	if (m_dlgNetworkParameters.DoModal() != IDOK)
		return;
	box2_ip = m_dlgNetworkParameters.m_strNetString;
	box2_port = m_dlgNetworkParameters.m_u32NetPort;

	CString IniWrite;
	IniWrite.Format("%s", box2_ip);
	WritePrivateProfileString("System", "box2_ip", IniWrite, strPath);

	IniWrite.Format("%d", box2_port);
	WritePrivateProfileString("System", "box2_port", IniWrite, strPath);
}


void CNetSetting::OnBnClickedButtonComputer1NetSetting()
{
	// TODO:  在此添加控件通知处理程序代码
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
	m_dlgNetworkParameters.m_strNetString = IniRead;
	GetPrivateProfileStringA("System", "box1_port", "", IniRead, 24, IniPath);
	//m_dlgNetworkParameters.GetDlgItem(IDC_EDIT_IP_PORT_NUMBER)->SetWindowTextA(IniRead);
	m_dlgNetworkParameters.m_u32NetPort = atoi(IniRead);

	if (m_dlgNetworkParameters.DoModal() != IDOK)
		return;

	box1_ip = m_dlgNetworkParameters.m_strNetString;
	box1_port = m_dlgNetworkParameters.m_u32NetPort;

	CString IniWrite;
	IniWrite.Format("%s", box1_ip);
	WritePrivateProfileString("System", "box1_ip", IniWrite, strPath);

	IniWrite.Format("%d", box1_port);
	WritePrivateProfileString("System", "box1_port", IniWrite, strPath);
}


/*
功能：获得当前程序的运行目录(.exe)
*/
CString CNetSetting::GetModulePath(void)
{
	CString    sPath;
	GetModuleFileNameA(NULL, sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	sPath.ReleaseBuffer();
	int    nPos;
	nPos = sPath.ReverseFind('\\');
	sPath = sPath.Left(nPos);
	return   sPath;
}

void CNetSetting::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strPath = GetModulePath() + "/param.ini";
	CString IniWrite;
	IniWrite.Format("%d", 100);

	int camera_total;
	char IniRead[255];
	memset(IniRead, 0, 255);
	char IniPath[255];
	memset(IniPath, 0, 255);
	char strCameraRateMark[50];
	memset(strCameraRateMark, 0, 50);
	char strPictureSaveMark[50];
	memset(strPictureSaveMark, 0, 50);
	//camera_ip_info ci_info;
	CString sPath = GetModulePath();
	strcpy_s(IniPath, 255, sPath.GetBuffer());
	strcat_s(IniPath, "/param.ini");
	GetPrivateProfileStringA("CameraIP", "CameraToTal", "", IniRead, 24, IniPath);

	CDialogEx::OnOK();
}
