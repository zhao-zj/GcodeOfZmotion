#pragma once


// CDialogRun 对话框
#include<iostream>
#include <vector>
#include<string>
class CDialogRun : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogRun)

public:
	CDialogRun(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogRun();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	int m_nAxis;
	BOOL m_bLogic;
	BOOL m_mode;
	float m_step;
	float m_units = 85.333;
	float m_lspeed = 0;
	float m_speed = 100;
	float m_acc = 300;
	float m_dec = 3000;
	float m_sramp = 10;
	float m_creep = 10;
	float ff = -1000.0;
	ZMC_HANDLE g_handle;
	void loadGcode(CString filename);
	void Limit();
	void changedir();
	void showax(ZMC_HANDLE g_handle1);
	void G0(std::string s);
	void G1(std::string s);
	void G92(std::string s);
	void RunGcode();
	std::vector<std::string>Vec_G;
	float endCoordinate[6];
	int ax[6] = { 0,1,2,3,4,5 };
	float Eval = 0.0;
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
};
