// ValveParametersSetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FiberDetectControl.h"
#include "ValveParametersSetting.h"
#include "afxdialogex.h"


// CValveParametersSetting �Ի���

IMPLEMENT_DYNAMIC(CValveParametersSetting, CDialogEx)

CValveParametersSetting::CValveParametersSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CValveParametersSetting::IDD, pParent)
{

}

CValveParametersSetting::~CValveParametersSetting()
{
}

void CValveParametersSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CValveParametersSetting, CDialogEx)
	ON_BN_CLICKED(IDOK, &CValveParametersSetting::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CValveParametersSetting::OnBnClickedCancel)
END_MESSAGE_MAP()


// CValveParametersSetting ��Ϣ�������


void CValveParametersSetting::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CValveParametersSetting::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnCancel();
}
