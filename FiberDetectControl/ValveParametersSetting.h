#pragma once


// CValveParametersSetting �Ի���

class CValveParametersSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CValveParametersSetting)

public:
	CValveParametersSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CValveParametersSetting();

// �Ի�������
	enum { IDD = IDD_DIALOG_VALVA_PARAMETERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
