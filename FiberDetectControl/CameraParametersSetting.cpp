// CameraParametersSetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FiberDetectControl.h"
#include "CameraParametersSetting.h"
#include "afxdialogex.h"


// CCameraParametersSetting �Ի���

IMPLEMENT_DYNAMIC(CCameraParametersSetting, CDialogEx)

CCameraParametersSetting::CCameraParametersSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCameraParametersSetting::IDD, pParent)
{
	m_nTriggerMode = 0;
}

CCameraParametersSetting::~CCameraParametersSetting()
{
}

void CCameraParametersSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_INTERNAL_TRIGGER, m_checkInternalTrigger);
	DDX_Control(pDX, IDC_CHECK_EXTERNAL_TRIGGER2, m_externalTrigger);
}


BEGIN_MESSAGE_MAP(CCameraParametersSetting, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCameraParametersSetting::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK_INTERNAL_TRIGGER, &CCameraParametersSetting::OnBnClickedCheckInternalTrigger)
	ON_BN_CLICKED(IDC_CHECK_EXTERNAL_TRIGGER2, &CCameraParametersSetting::OnBnClickedCheckExternalTrigger2)
END_MESSAGE_MAP()


// CCameraParametersSetting ��Ϣ�������
BOOL CCameraParametersSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//m_checkInternalTrigger.SetCheck(true);
	//m_externalTrigger.SetCheck(false);
	//m_nTriggerMode = m_externalTrigger.GetCheck();

	GetDlgItem(IDC_EDIT_IP_ADRESS)->SetWindowTextA(m_strNetString.c_str());
	GetDlgItem(IDC_EDIT_CAMERA_SCAN_SPEED)->SetWindowTextA(std::to_string(m_nScanSpeed).c_str());
	GetDlgItem(IDC_EDIT_CAMERA_EXPOSURE_TIME)->SetWindowTextA(std::to_string(m_nExposureTime).c_str());
	GetDlgItem(IDC_EDIT_CAMERA_DIGITAL_GAIN)->SetWindowTextA(std::to_string(m_nGain).c_str());
	if (m_nTriggerMode == 1)
	{
		m_externalTrigger.SetCheck(m_nTriggerMode);
		m_checkInternalTrigger.SetCheck(!m_nTriggerMode);
	}
	else if (m_nTriggerMode == 0)
	{
		m_externalTrigger.SetCheck(m_nTriggerMode);
		m_checkInternalTrigger.SetCheck(!m_nTriggerMode);
	}
	else{}

	return true;
}

void CCameraParametersSetting::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItem(IDC_EDIT_IP_ADRESS)->GetWindowTextA(str);
	m_strNetString = str.GetBuffer();
	GetDlgItem(IDC_EDIT_CAMERA_SCAN_SPEED)->GetWindowTextA(str);
	m_nScanSpeed = atoi(str);
	GetDlgItem(IDC_EDIT_CAMERA_EXPOSURE_TIME)->GetWindowTextA(str);
	m_nExposureTime = atoi(str);
	GetDlgItem(IDC_EDIT_CAMERA_DIGITAL_GAIN)->GetWindowTextA(str);
	m_nGain = atoi(str);
	m_nTriggerMode = m_externalTrigger.GetCheck();

	CDialogEx::OnOK();
}


void CCameraParametersSetting::OnBnClickedCheckInternalTrigger()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_checkInternalTrigger.GetCheck() == 1)
	{
		m_checkInternalTrigger.SetCheck(true);
		m_externalTrigger.SetCheck(false);
		m_nTriggerMode = m_externalTrigger.GetCheck();
	}
	else if (m_externalTrigger.GetCheck() == 1)
	{
		m_checkInternalTrigger.SetCheck(false);
		m_externalTrigger.SetCheck(true);
		m_nTriggerMode = m_externalTrigger.GetCheck();
	}
	else
	{}
}


void CCameraParametersSetting::OnBnClickedCheckExternalTrigger2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_checkInternalTrigger.GetCheck() == 1)
	{
		m_checkInternalTrigger.SetCheck(true);
		m_externalTrigger.SetCheck(false);
		m_nTriggerMode = m_externalTrigger.GetCheck();
	}
	else if (m_externalTrigger.GetCheck() == 1)
	{
		m_checkInternalTrigger.SetCheck(false);
		m_externalTrigger.SetCheck(true);
		m_nTriggerMode = m_externalTrigger.GetCheck();
	}
	else
	{}
}
