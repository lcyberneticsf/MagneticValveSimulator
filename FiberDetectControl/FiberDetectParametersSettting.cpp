// FiberDetectParametersSettting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FiberDetectControl.h"
#include "FiberDetectParametersSettting.h"
#include "afxdialogex.h"


// CFiberDetectParametersSettting �Ի���

IMPLEMENT_DYNAMIC(CFiberDetectParametersSettting, CDialogEx)

CFiberDetectParametersSettting::CFiberDetectParametersSettting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFiberDetectParametersSettting::IDD, pParent)
{

}

CFiberDetectParametersSettting::~CFiberDetectParametersSettting()
{
}

void CFiberDetectParametersSettting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFiberDetectParametersSettting, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFiberDetectParametersSettting::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CFiberDetectParametersSettting::OnBnClickedCancel)
END_MESSAGE_MAP()


// CFiberDetectParametersSettting ��Ϣ�������


void CFiberDetectParametersSettting::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CFiberDetectParametersSettting::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnCancel();
}
