// DebugParametersSetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FiberDetectControl.h"
#include "DebugParametersSetting.h"
#include "afxdialogex.h"


// CDebugParametersSetting �Ի���

IMPLEMENT_DYNAMIC(CDebugParametersSetting, CDialogEx)

CDebugParametersSetting::CDebugParametersSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDebugParametersSetting::IDD, pParent)
{

}

CDebugParametersSetting::~CDebugParametersSetting()
{
}

void CDebugParametersSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDebugParametersSetting, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDebugParametersSetting::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDebugParametersSetting::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDebugParametersSetting ��Ϣ�������


void CDebugParametersSetting::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CDebugParametersSetting::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnCancel();
}
