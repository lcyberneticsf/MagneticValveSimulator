#pragma once
#include <cstdint>
#include <cstddef>
#include <array>
#include <string>
#include <string.h>
#include <cstdint>
#include "afxwin.h"

// CCameraParametersSetting �Ի���

class CCameraParametersSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CCameraParametersSetting)

public:
	CCameraParametersSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCameraParametersSetting();

// �Ի�������
	enum { IDD = IDD_DIALOG_CAMERA_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL  OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	std::string m_strNetString;		//Camera IP address
	std::uint32_t m_u32NetPort;		//Camera network port
	std::uint32_t m_nScanSpeed;		//Camera scan speed  ,unit :Hz
	std::uint32_t m_nTriggerMode;   //Camera trigger mode,0:auto trigger:1:hardware trigger
	std::uint32_t m_nExposureTime;  //Camera exposure time,unit : us 
	std::uint32_t m_nGain;			//Camera digital gain, unit : db

	afx_msg void OnBnClickedOk();
	CButton m_checkInternalTrigger;
	CButton m_externalTrigger;
	afx_msg void OnBnClickedCheckInternalTrigger();
	afx_msg void OnBnClickedCheckExternalTrigger2();
};
