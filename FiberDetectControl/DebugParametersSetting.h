#pragma once


// CDebugParametersSetting 对话框

class CDebugParametersSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CDebugParametersSetting)

public:
	CDebugParametersSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDebugParametersSetting();

// 对话框数据
	enum { IDD = IDD_DIALOG_DEBUG_PARAMETERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
