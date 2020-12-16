// DetectParametersSetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FiberDetectControl.h"
#include "DetectParametersSetting.h"
#include "afxdialogex.h"



// CDetectParametersSetting �Ի���

IMPLEMENT_DYNAMIC(CDetectParametersSetting, CDialogEx)

CDetectParametersSetting::CDetectParametersSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDetectParametersSetting::IDD, pParent)
{

}

CDetectParametersSetting::~CDetectParametersSetting()
{
}

void CDetectParametersSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_PARAMETERS_SETTING, m_cTabControl);
}


BEGIN_MESSAGE_MAP(CDetectParametersSetting, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_PARAMETERS_SETTING, &CDetectParametersSetting::OnTcnSelchangeTabParametersSetting)
END_MESSAGE_MAP()


// CDetectParametersSetting ��Ϣ�������
BOOL CDetectParametersSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_cTabControl.InsertItem(1, _T("��������"));
	m_dlgBaseDetectParametersSettting.Create(IDD_DIALOG_BASE_DETECT_PARAMETERS_SETTING, &m_cTabControl);

	m_cTabControl.InsertItem(2, _T("���Բ���"));
	m_dlgDebugParametersSetting.Create(IDD_DIALOG_DEBUG_PARAMETERS, &m_cTabControl);		//m_dlgValveParametersSettting

	m_cTabControl.InsertItem(3, _T("�緧����"));
	m_dlgValveParametersSettting.Create(IDD_DIALOG_VALVA_PARAMETERS, &m_cTabControl);		//

	m_cTabControl.InsertItem(4, _T("��ɫ���A"));
	m_dlgFiberDetectParametersSettingA.Create(IDD_DIALOG_FIBER_DETECT_PARAMETERS_SETTING, &m_cTabControl);//

	m_cTabControl.InsertItem(5, _T("��ɫ���B"));
	m_dlgFiberDetectParametersSettingB.Create(IDD_DIALOG_FIBER_DETECT_PARAMETERS_SETTING, &m_cTabControl);//

	m_cTabControl.InsertItem(6, _T("�������C"));
	m_dlgFiberDetectParametersSettingC.Create(IDD_DIALOG_FIBER_DETECT_PARAMETERS_SETTING, &m_cTabControl);//

	m_cTabControl.InsertItem(7, _T("�������D"));
	m_dlgFiberDetectParametersSettingD.Create(IDD_DIALOG_FIBER_DETECT_PARAMETERS_SETTING, &m_cTabControl);//

	CRect rect;
	m_cTabControl.GetClientRect(&rect);
	rect.top += 20;
	rect.left += 1;
	rect.right -= 1;

	m_dlgBaseDetectParametersSettting.MoveWindow(rect);
	m_dlgBaseDetectParametersSettting.ShowWindow(true);

	m_dlgDebugParametersSetting.MoveWindow(rect);
	m_dlgDebugParametersSetting.ShowWindow(false);

	m_dlgValveParametersSettting.MoveWindow(rect);
	m_dlgValveParametersSettting.ShowWindow(false);

	m_dlgFiberDetectParametersSettingA.MoveWindow(rect);
	m_dlgFiberDetectParametersSettingA.ShowWindow(false);

	m_dlgFiberDetectParametersSettingB.MoveWindow(rect);
	m_dlgFiberDetectParametersSettingB.ShowWindow(false);

	m_dlgFiberDetectParametersSettingC.MoveWindow(rect);
	m_dlgFiberDetectParametersSettingC.ShowWindow(false);

	m_dlgFiberDetectParametersSettingD.MoveWindow(rect);
	m_dlgFiberDetectParametersSettingD.ShowWindow(false);

	char IniRead[255];
	memset(IniRead, 0, 255);
	char IniPath[255];
	memset(IniPath, 0, 255);
	//camera_ip_info ci_info;
	CString strPath = GetModulePath();
	strcpy_s(IniPath, 255, strPath.GetBuffer());
	strcat_s(IniPath, "/param.ini");

	GetPrivateProfileStringA("BaseDetectParameter", "cameraA_begin", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraA_begin = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA1_BEGIN_POINT)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("BaseDetectParameter", "cameraA_end", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraA_end = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA1_END_POINT)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("BaseDetectParameter", "cameraA_align_begin", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraA_align_begin = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA1_ALIGNING_BEGIN_POINT)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("BaseDetectParameter", "cameraA_align_end", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraA_align_end = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA1_ALIGNING_END_POINT)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("BaseDetectParameter", "cameraA_detect_begin", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraA_detect_begin = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA1_DETECT_BEGIN_POINT)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("BaseDetectParameter", "cameraA_detect_end", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraA_detect_end = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA1_DETECT_END_POINT)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("BaseDetectParameter", "cameraA_valve_amount", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraA_valve_amount = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA1_VALVE_AMOUNT)->SetWindowTextA(IniRead);

	GetPrivateProfileStringA("BaseDetectParameter", "cameraB_begin", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraB_begin = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA2_BEGIN_POINT)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("BaseDetectParameter", "cameraB_end", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraB_end = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA2_END_POINT)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("BaseDetectParameter", "cameraB_align_begin", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraB_align_begin = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA2_ALIGNING_BEGIN_POINT)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("BaseDetectParameter", "cameraB_align_end", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraB_align_end = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA2_ALIGNING_END_POINT)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("BaseDetectParameter", "cameraB_detect_begin", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraB_detect_begin = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA2_DETECT_BEGIN_POINT)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("BaseDetectParameter", "cameraB_detect_end", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraB_detect_end = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA2_DETECT_END_POINT)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("BaseDetectParameter", "cameraB_valve_amount", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraB_valve_amount = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA2_VALVE_AMOUNT)->SetWindowTextA(IniRead);

	GetPrivateProfileStringA("BaseDetectParameter", "cameraC_begin", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraC_begin = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA3_BEGIN_POINT)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("BaseDetectParameter", "cameraC_end", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraC_end = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA3_END_POINT)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("BaseDetectParameter", "cameraC_align_begin", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraC_align_begin = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA3_ALIGNING_BEGIN_POINT)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("BaseDetectParameter", "cameraC_align_end", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraC_align_end = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA3_ALIGNING_END_POINT)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("BaseDetectParameter", "cameraC_detect_begin", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraC_detect_begin = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA3_DETECT_BEGIN_POINT)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("BaseDetectParameter", "cameraC_detect_end", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraC_detect_end = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA3_DETECT_END_POINT)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("BaseDetectParameter", "cameraC_valve_amount", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraC_valve_amount = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA3_VALVE_AMOUNT)->SetWindowTextA(IniRead);

	GetPrivateProfileStringA("BaseDetectParameter", "cameraD_begin", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraD_begin = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA4_BEGIN_POINT)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("BaseDetectParameter", "cameraD_end", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraD_end = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA4_END_POINT)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("BaseDetectParameter", "cameraD_align_begin", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraD_align_begin = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA4_ALIGNING_BEGIN_POINT)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("BaseDetectParameter", "cameraD_align_end", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraD_align_end = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA4_ALIGNING_END_POINT)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("BaseDetectParameter", "cameraD_detect_begin", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraD_detect_begin = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA4_DETECT_BEGIN_POINT)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("BaseDetectParameter", "cameraD_detect_end", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraD_detect_end = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA4_DETECT_END_POINT)->SetWindowTextA(IniRead);
	GetPrivateProfileStringA("BaseDetectParameter", "cameraD_valve_amount", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraD_valve_amount = atoi(IniRead);
	m_dlgBaseDetectParametersSettting.GetDlgItem(IDC_EDIT_CAMERA4_VALVE_AMOUNT)->SetWindowTextA(IniRead);

	GetPrivateProfileStringA("ValveParameter", "cameraA_delay", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraA_delay = atoi(IniRead);
	m_dlgValveParametersSettting.GetDlgItem(IDC_EDIT_VALVE_A_DELAY)->SetWindowTextA(IniRead);

	GetPrivateProfileStringA("ValveParameter", "cameraA_hold", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraA_hold = atoi(IniRead);
	m_dlgValveParametersSettting.GetDlgItem(IDC_EDIT_VALVE_A_HOLD)->SetWindowTextA(IniRead);

	GetPrivateProfileStringA("ValveParameter", "cameraB_delay", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraB_delay = atoi(IniRead);
	m_dlgValveParametersSettting.GetDlgItem(IDC_EDIT_VALVE_B_DELAY)->SetWindowTextA(IniRead);

	GetPrivateProfileStringA("ValveParameter", "cameraB_hold", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraB_hold = atoi(IniRead);
	m_dlgValveParametersSettting.GetDlgItem(IDC_EDIT_VALVE_B_HOLD)->SetWindowTextA(IniRead);

	GetPrivateProfileStringA("ValveParameter", "cameraC_delay", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraC_delay = atoi(IniRead);
	m_dlgValveParametersSettting.GetDlgItem(IDC_EDIT_VALVE_C_DELAY)->SetWindowTextA(IniRead);

	GetPrivateProfileStringA("ValveParameter", "cameraC_hold", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraC_hold = atoi(IniRead);
	m_dlgValveParametersSettting.GetDlgItem(IDC_EDIT_VALVE_C_HOLD)->SetWindowTextA(IniRead);

	GetPrivateProfileStringA("ValveParameter", "cameraD_delay", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraD_delay = atoi(IniRead);
	m_dlgValveParametersSettting.GetDlgItem(IDC_EDIT_VALVE_D_DELAY)->SetWindowTextA(IniRead);

	GetPrivateProfileStringA("ValveParameter", "cameraD_hold", "", IniRead, 24, IniPath);
	parameters_setting_trans.cameraD_hold = atoi(IniRead);
	m_dlgValveParametersSettting.GetDlgItem(IDC_EDIT_VALVE_D_HOLD)->SetWindowTextA(IniRead);

	GetPrivateProfileStringA("ValveParameter", "valve_work_times", "", IniRead, 24, IniPath);
	parameters_setting_trans.valve_work_times = atoi(IniRead);
	m_dlgValveParametersSettting.GetDlgItem(IDC_EDIT_VALVE_WORK_TIMES)->SetWindowTextA(IniRead);

	GetPrivateProfileStringA("ValveParameter", "valve_stop_time", "", IniRead, 24, IniPath);
	parameters_setting_trans.valve_stop_time = atoi(IniRead);
	m_dlgValveParametersSettting.GetDlgItem(IDC_EDIT_VALVE_STOP_TIMES)->SetWindowTextA(IniRead);

	//Read the 

	return true;
}

void CDetectParametersSetting::OnTcnSelchangeTabParametersSetting(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	switch (m_cTabControl.GetCurSel())
	{
	case 0:
		m_dlgBaseDetectParametersSettting.ShowWindow(true);
		m_dlgDebugParametersSetting.ShowWindow(false);
		m_dlgValveParametersSettting.ShowWindow(false);
		m_dlgFiberDetectParametersSettingA.ShowWindow(false);
		m_dlgFiberDetectParametersSettingB.ShowWindow(false);
		m_dlgFiberDetectParametersSettingC.ShowWindow(false);
		m_dlgFiberDetectParametersSettingD.ShowWindow(false);
		break;
	case 1:
		m_dlgBaseDetectParametersSettting.ShowWindow(false);
		m_dlgDebugParametersSetting.ShowWindow(true);
		m_dlgValveParametersSettting.ShowWindow(false);
		m_dlgFiberDetectParametersSettingA.ShowWindow(false);
		m_dlgFiberDetectParametersSettingB.ShowWindow(false);
		m_dlgFiberDetectParametersSettingC.ShowWindow(false);
		m_dlgFiberDetectParametersSettingD.ShowWindow(false);
		break;	
	case 2:
		m_dlgBaseDetectParametersSettting.ShowWindow(false);
		m_dlgDebugParametersSetting.ShowWindow(false);
		m_dlgValveParametersSettting.ShowWindow(true);
		m_dlgFiberDetectParametersSettingA.ShowWindow(false);
		m_dlgFiberDetectParametersSettingB.ShowWindow(false);
		m_dlgFiberDetectParametersSettingC.ShowWindow(false);
		m_dlgFiberDetectParametersSettingD.ShowWindow(false);
		break;
	case 3:
		m_dlgBaseDetectParametersSettting.ShowWindow(false);
		m_dlgDebugParametersSetting.ShowWindow(false);
		m_dlgValveParametersSettting.ShowWindow(false);
		m_dlgFiberDetectParametersSettingA.ShowWindow(true);
		m_dlgFiberDetectParametersSettingB.ShowWindow(false);
		m_dlgFiberDetectParametersSettingC.ShowWindow(false);
		m_dlgFiberDetectParametersSettingD.ShowWindow(false);
		break;
	case 4:
		m_dlgBaseDetectParametersSettting.ShowWindow(false);
		m_dlgDebugParametersSetting.ShowWindow(false);
		m_dlgValveParametersSettting.ShowWindow(false);
		m_dlgFiberDetectParametersSettingA.ShowWindow(false);
		m_dlgFiberDetectParametersSettingB.ShowWindow(true);
		m_dlgFiberDetectParametersSettingC.ShowWindow(false);
		m_dlgFiberDetectParametersSettingD.ShowWindow(false);
		break;
	case 5:
		m_dlgBaseDetectParametersSettting.ShowWindow(false);
		m_dlgDebugParametersSetting.ShowWindow(false);
		m_dlgValveParametersSettting.ShowWindow(false);
		m_dlgFiberDetectParametersSettingA.ShowWindow(false);
		m_dlgFiberDetectParametersSettingB.ShowWindow(false);
		m_dlgFiberDetectParametersSettingC.ShowWindow(true);
		m_dlgFiberDetectParametersSettingD.ShowWindow(false);
		break;
	case 6:
		m_dlgBaseDetectParametersSettting.ShowWindow(false);
		m_dlgDebugParametersSetting.ShowWindow(false);
		m_dlgValveParametersSettting.ShowWindow(false);
		m_dlgFiberDetectParametersSettingA.ShowWindow(false);
		m_dlgFiberDetectParametersSettingB.ShowWindow(false);
		m_dlgFiberDetectParametersSettingC.ShowWindow(false);
		m_dlgFiberDetectParametersSettingD.ShowWindow(true);
		break;
	default:
		break;
	}
	*pResult = 0;
}

/*
���ܣ���õ�ǰ���������Ŀ¼(.exe)
*/
CString CDetectParametersSetting::GetModulePath(void)
{
	CString    sPath;
	GetModuleFileNameA(NULL, sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	sPath.ReleaseBuffer();
	int    nPos;
	nPos = sPath.ReverseFind('\\');
	sPath = sPath.Left(nPos);
	return   sPath;
}
