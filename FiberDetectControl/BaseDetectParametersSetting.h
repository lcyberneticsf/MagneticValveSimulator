#pragma once


// CBaseDetectParametersSetting �Ի���

class CBaseDetectParametersSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CBaseDetectParametersSetting)

public:
	CBaseDetectParametersSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBaseDetectParametersSetting();

// �Ի�������
	enum { IDD = IDD_DIALOG_BASE_DETECT_PARAMETERS_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
