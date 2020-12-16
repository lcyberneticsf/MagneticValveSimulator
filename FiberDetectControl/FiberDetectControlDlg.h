
// FiberDetectControlDlg.h : 头文件
//

#pragma once
#include "afxbutton.h"
#include "ParameterSetting.h"
#include "communicator.h"
#include <opencv2\opencv.hpp>
#include "VTx2Session.h"
#include <iostream>
#include <string> 
#include "VCameraFrame.h"
#include "afxwin.h"
#define  SHOWTEXTLENGTH 4

using namespace Vsee;
using namespace std;
using namespace aq;

// CFiberDetectControlDlg 对话框
class CFiberDetectControlDlg : public CDialogEx
{
// 构造
public:
	CFiberDetectControlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FIBERDETECTCONTROL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	CString		GetModulePath(void);


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButtonHardwareTest();
	afx_msg void OnBnClickedButtonNetParametersSetting();
	afx_msg void OnBnClickedButtonParametersSetting();
	DECLARE_MESSAGE_MAP()
public:
	void	run_tcp_server(std::string _ip, int _port);
	void	run_udp_server(std::string _ip, int _port);
	void	tcp_server(std::string _ip, int _port);
	void	udp_server(std::string _ip, int _port);
	void	run_tcp_client(std::string _ip, int _port);
	void	tcp_client(std::string _ip, int port, io_service* io);
	bool	connect_and_reconnect(int beg, int end, asio::io_service& io);
	void	ShowText(CWnd *pwnd, CString strText, CRect DrawRect);
	void	ShowText(CWnd *pwnd, char strText[SHOWTEXTLENGTH][255], CRect DrawRect);
	void	RefreshWnd(CWnd *pwnd);
	void    PushTailShowText(CString strText);
	void    PushTailShowText(char* strText);
	void    ReadIni();
	void	WriteIni(CParameterSetting parameters_setting_trans);
public:
	CMFCButton m_mfcMagneticValve1;
	CMFCButton m_mfcMagneticValve2;
	CMFCButton m_mfcMagneticValve3;
	CMFCButton m_mfcMagneticValve4;
	CMFCButton m_mfcMagneticValve5;
	CMFCButton m_mfcMagneticValve6;
	CMFCButton m_mfcMagneticValve7;
	CMFCButton m_mfcMagneticValve8;
	CMFCButton m_mfcMagneticValve9;
	CMFCButton m_mfcMagneticValve10;
	CMFCButton m_mfcMagneticValve11;
	CMFCButton m_mfcMagneticValve12;
	CMFCButton m_mfcMagneticValve13;
	CMFCButton m_mfcMagneticValve14;
	CMFCButton m_mfcMagneticValve15;
	CMFCButton m_mfcMagneticValve16;
	CMFCButton m_mfcMagneticValve17;
	CMFCButton m_mfcMagneticValve18;
	CMFCButton m_mfcMagneticValve19;
	CMFCButton m_mfcMagneticValve20;
	CMFCButton m_mfcMagneticValve21;
	CMFCButton m_mfcMagneticValve22;
	CMFCButton m_mfcMagneticValve23;
	CMFCButton m_mfcMagneticValve24;

	static CMFCButton* m_mfcMagneticValve[MAGNETIC_VALVE_SUM];

	std::string nx_box1_ip;				//computer 1 network address
	std::string nx_box2_ip;				//computer 2 network address
	int nx_box1_port;					//NX computer 1 port number
	int nx_box2_port;					//NX computer 2 port number 
	std::string local_ip;				//local computer ip address
	int local_ip_port;					//local computer ip port;
	aq::Communicator*			communicator_;
	Vsee::VTx2Session*			sessions[8];
	tcp::socket*				sockets[8];
	io_service*					ios[8];
	static std::queue<InferFrame>		infer_queue;
	std::mutex					infer_mutex;
	InferFrame					infer_frame;
	tcp::endpoint				eps[8];
	CParameterSetting			parameters_setting_trans;
	afx_msg void OnBnClickedStartServer();
	CButton m_checkServerModeSelect;
	CButton m_checkClientMode;
	CButton m_checkServerSend;
	CButton m_checkClientSend;
	bool	m_bClientMode;
	bool	m_bServerMode;
	bool    m_bServerSendMode;
	bool    m_bClientSendMode;
	int		m_nRectWidth;
	int		m_nRectHeight;
	CRect	m_ImageRect;			//The area th show image
	CDC		*m_pDC;
	HDC		m_hDC;
	CWnd	*m_pwnd;
	char    m_strShowText[SHOWTEXTLENGTH][255];
	static HWND m_hWnd;				//=AfxGetMainWnd()->m_hWnd;
	bool    m_bTcpMode = false;
	bool m_bLeihangProtocal = true;
	static _io_output_transac_tag_  valve_driver[MAGNETIC_VALVE_SUM];
	afx_msg void OnBnClickedCheckServerModeSelect();
	afx_msg void OnBnClickedCheckModeSelect();
	afx_msg void OnBnClickedCheckServerSend();
	afx_msg void OnBnClickedCheckClientSend();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowMessage(UINT nID, LPARAM lParam);
	afx_msg LRESULT ShowCtrlMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonStartDetect();
	afx_msg void OnBnClickedButtonStopDetect2();
	CButton m_checkUDPMode;
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
