#pragma once


// CFiberDetectParametersSettting �Ի���

class CFiberDetectParametersSettting : public CDialogEx
{
	DECLARE_DYNAMIC(CFiberDetectParametersSettting)

public:
	CFiberDetectParametersSettting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFiberDetectParametersSettting();

// �Ի�������
	enum { IDD = IDD_DIALOG_FIBER_DETECT_PARAMETERS_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
