#pragma once
#include "afxcmn.h"
#include "BaseDetectParametersSetting.h"
#include "DebugParametersSetting.h"
#include "ValveParametersSetting.h"
#include "FiberDetectParametersSettting.h"
#include "ParameterSetting.h"


// CDetectParametersSetting �Ի���

class CDetectParametersSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CDetectParametersSetting)

public:
	CDetectParametersSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDetectParametersSetting();

// �Ի�������
	enum { IDD = IDD_DIALOG_DETECT_PARAMETERS_SETTINGS };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_cTabControl;
	CBaseDetectParametersSetting	m_dlgBaseDetectParametersSettting;
	CDebugParametersSetting			m_dlgDebugParametersSetting;
	CValveParametersSetting			m_dlgValveParametersSettting;

	CFiberDetectParametersSettting  m_dlgFiberDetectParametersSettingA;
	CFiberDetectParametersSettting  m_dlgFiberDetectParametersSettingB;
	CFiberDetectParametersSettting  m_dlgFiberDetectParametersSettingC;
	CFiberDetectParametersSettting  m_dlgFiberDetectParametersSettingD;
	CParameterSetting				parameters_setting_trans;            //parameters settig dialog;

	afx_msg void OnTcnSelchangeTabParametersSetting(NMHDR *pNMHDR, LRESULT *pResult);
	CString		GetModulePath(void);
};
