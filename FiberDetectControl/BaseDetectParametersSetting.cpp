// BaseDetectParametersSetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FiberDetectControl.h"
#include "BaseDetectParametersSetting.h"
#include "afxdialogex.h"


// CBaseDetectParametersSetting �Ի���

IMPLEMENT_DYNAMIC(CBaseDetectParametersSetting, CDialogEx)

CBaseDetectParametersSetting::CBaseDetectParametersSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBaseDetectParametersSetting::IDD, pParent)
{

}

CBaseDetectParametersSetting::~CBaseDetectParametersSetting()
{
}

void CBaseDetectParametersSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBaseDetectParametersSetting, CDialogEx)
	ON_BN_CLICKED(IDOK, &CBaseDetectParametersSetting::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CBaseDetectParametersSetting::OnBnClickedCancel)
END_MESSAGE_MAP()


// CBaseDetectParametersSetting ��Ϣ�������


void CBaseDetectParametersSetting::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CBaseDetectParametersSetting::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnCancel();
}
