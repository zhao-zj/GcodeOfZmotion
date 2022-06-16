// CDialogRun.cpp: 实现文件
//
#pragma once
#include "pch.h"
#include "FDMGcodeR.h"
#include "CDialogRun.h"
#include "afxdialogex.h"
#include <fstream>

// CDialogRun 对话框				//控制器链接句柄
IMPLEMENT_DYNAMIC(CDialogRun, CDialogEx)

CDialogRun::CDialogRun(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_nAxis(0)
	, m_bLogic(TRUE)
	, m_step(0)
	, m_mode(FALSE)
{
	for (int i = 0; i < 6; i++)endCoordinate[i] = 0.0;
}

CDialogRun::~CDialogRun()
{
	KillTimer(1);
	ZAux_Close(g_handle);
	g_handle = NULL;
}

void CDialogRun::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_nAxis);
	DDX_Check(pDX, IDC_CHECK1, m_bLogic);
	DDX_Text(pDX, IDC_EDIT1, m_step);
	DDX_Check(pDX, IDC_CHECK2, m_mode);
}


BEGIN_MESSAGE_MAP(CDialogRun, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &CDialogRun::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDialogRun::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CDialogRun::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CDialogRun::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CDialogRun::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_CHECK1, &CDialogRun::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogRun::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialogRun::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDialogRun::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_CHECK2, &CDialogRun::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_BUTTON4, &CDialogRun::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDialogRun::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_RADIO6, &CDialogRun::OnBnClickedRadio6)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON6, &CDialogRun::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CDialogRun::OnBnClickedButton7)
END_MESSAGE_MAP()


// CDialogRun 消息处理程序
void CDialogRun::Limit() {
	ZAux_Direct_SetFwdIn(g_handle, 0, 1);//硬件正限位
	ZAux_Direct_SetInvertIn(g_handle, 1, 1);//反转信号
	ZAux_Direct_SetRevIn(g_handle, 0, 2);//硬件负限位
	ZAux_Direct_SetInvertIn(g_handle, 2, 1);
	ZAux_Direct_SetFwdIn(g_handle, 1, 4);//硬件正限位
	ZAux_Direct_SetInvertIn(g_handle, 4, 1);//反转信号
	ZAux_Direct_SetRevIn(g_handle, 1, 3);//硬件负限位
	ZAux_Direct_SetInvertIn(g_handle, 3, 1);
	ZAux_Direct_SetFwdIn(g_handle, 2, 5);//硬件正限位
	ZAux_Direct_SetInvertIn(g_handle, 5, 1);//反转信号
	ZAux_Direct_SetRevIn(g_handle, 2, 6);//硬件负限位
	ZAux_Direct_SetInvertIn(g_handle, 6, 1);
	ZAux_Direct_SetFsLimit(g_handle, 0, 500); //正向软限位
	ZAux_Direct_SetRsLimit(g_handle, 0, -500);//负向软限位
	ZAux_Direct_SetFsLimit(g_handle, 1, 500); //正向软限位
	ZAux_Direct_SetRsLimit(g_handle, 1, -500);//负向软限位
	ZAux_Direct_SetFsLimit(g_handle, 2, 500); //正向软限位
	ZAux_Direct_SetRsLimit(g_handle, 2, -20);//负向软限位
	ZAux_Direct_SetFsLimit(g_handle, 3, 500); //正向软限位
	ZAux_Direct_SetRsLimit(g_handle, 3, -500);//负向软限位
	ZAux_Direct_SetFsLimit(g_handle, 4, 90); //正向软限位
	ZAux_Direct_SetRsLimit(g_handle, 4, -90);//负向软限位
	ZAux_Direct_SetFsLimit(g_handle, 5, 10000); //正向软限位
	ZAux_Direct_SetRsLimit(g_handle, 5, -10000);//负向软限位
}

void CDialogRun ::showax(ZMC_HANDLE g_handle1){
	std::cout << "起始速度: " << m_lspeed << std::endl;
	std::cout << "加速度: " << m_acc << std::endl;
	std::cout << "减速度: " << m_dec << std::endl;
	std::cout << "S曲线时间: " << m_sramp << std::endl;
	g_handle = g_handle1;
	Limit();
	//OnTimer(1);
	//SetTimer(1, 100, NULL);
}

void CDialogRun::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	m_nAxis = 0;
	m_units = 85.3333;
	UpdateData(false);
}


void CDialogRun::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	m_nAxis = 1;
	m_units = 85.3333;
	UpdateData(false);
}


void CDialogRun::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	m_nAxis = 2;
	m_units = 85.3333;
	UpdateData(false);
}


void CDialogRun::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	m_nAxis = 3;
	m_units = 888.8888;
	UpdateData(false);
}


void CDialogRun::OnBnClickedRadio5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	m_nAxis = 4;
	m_units = 888.8888;
	UpdateData(false);
}

void CDialogRun::changedir()
{
	GetDlgItem(IDC_CHECK1)->SetWindowText(m_bLogic ? "运动方向：正向" : "运动方向：反向");
}
void CDialogRun::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bLogic = ~m_bLogic;
	UpdateData(TRUE);
	changedir();
	//std::cout << m_bLogic << std::endl;
}


void CDialogRun::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == g_handle)
	{
		MessageBox(_T("链接断开状态"));
		return;
	}

	UpdateData(true);//刷新参数

	int status = 0;
	ZAux_Direct_GetIfIdle(g_handle, m_nAxis, &status);           //判断当前轴状态

	if (status == 0) //已经在运动中
		return;
	//设定轴类型 1-脉冲轴类型 	
	ZAux_Direct_SetAtype(g_handle, m_nAxis, 7);

	//设定脉冲模式及逻辑方向（脉冲+方向）	
	ZAux_Direct_SetInvertStep(g_handle, m_nAxis, 0);

	//设置脉冲当量	1表示以一个脉冲为单位 ，设置为1MM的脉冲个数，这度量单位为MM
	ZAux_Direct_SetUnits(g_handle, m_nAxis, m_units);

	//设定速度，加减速
	ZAux_Direct_SetLspeed(g_handle, m_nAxis, m_lspeed);
	ZAux_Direct_SetSpeed(g_handle, m_nAxis, m_speed);
	ZAux_Direct_SetAccel(g_handle, m_nAxis, m_acc);
	ZAux_Direct_SetDecel(g_handle, m_nAxis, m_dec);

	//设定S曲线时间 设置为0表示梯形加减速 
	ZAux_Direct_SetSramp(g_handle, m_nAxis, m_sramp);
	if(!m_mode)ZAux_Direct_Single_Vmove(g_handle, m_nAxis, m_bLogic ? 1 : 0);
	else ZAux_Direct_Single_Move(g_handle, m_nAxis, m_step*(m_bLogic ? 1 : -1));
	UpdateData(false);
}


void CDialogRun::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == g_handle)
	{
		MessageBox(_T("链接断开状态"));
		return;
	}

	ZAux_Direct_Single_Cancel(g_handle, m_nAxis, 2);
}


void CDialogRun::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == g_handle)
	{
		MessageBox(_T("链接断开状态"));
		return;
	}
	UpdateData(true);//刷新参数
	int datumnum[3] = { 2,3,6};
	int datummode[3] = { 4,4,4};
	for (int m_datumin = 0; m_datumin < 3; m_datumin++)
	{
		int status = 0;
		ZAux_Direct_GetIfIdle(g_handle, m_datumin, &status);           //判断当前轴状态
		if (status == 0) //已经在运动中
			return;
		//设定轴类型 7-   脉冲轴类型 +	编码器Z信号		不用EZ回零也可以设置为1	
		ZAux_Direct_SetAtype(g_handle, m_datumin, 7);
		//设置脉冲当量	1表示以一个脉冲为单位 ，设置为1MM的脉冲个数，这度量单位为MM
		ZAux_Direct_SetUnits(g_handle, m_datumin, m_units);
		//设定速度，加减速
		ZAux_Direct_SetLspeed(g_handle, m_datumin, m_lspeed);
		ZAux_Direct_SetSpeed(g_handle, m_datumin, 50);
		ZAux_Direct_SetAccel(g_handle, m_datumin, m_acc);
		ZAux_Direct_SetDecel(g_handle, m_datumin, m_dec);
		ZAux_Direct_SetCreep(g_handle, m_datumin, m_creep);
		if(m_datumin==2)ZAux_Direct_Single_Move(g_handle, 2, 10.0);
		//设定对应轴的原点输入口信号
		ZAux_Direct_SetDatumIn(g_handle, m_datumin, datumnum[m_datumin]);
		ZAux_Direct_SetInvertIn(g_handle, datumnum[m_datumin], 1);	//ZMC系列认为OFF时碰到了原点信号（常闭） ，如果是常开传感器则需要反转输入口，ECI系列的不需要反转
		ZAux_Direct_Single_Datum(g_handle, m_datumin, datummode[m_datumin]);
	}
	Vec_G.clear();
	for (int i = 0; i < 6; i++)endCoordinate[i] = 0.0;
	SetTimer(1, 100, NULL);
}


void CDialogRun::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_mode = ~m_mode;
	UpdateData(TRUE);
}

void CDialogRun::loadGcode(CString filename)
{
	std::string strFilename(filename);
	std::cout << strFilename << std::endl;
	std::ifstream inFile(strFilename);
	if (!inFile) {
		std::cout << "error" << std::endl;
		return;
	}
	std::string line;
	//连续以行为单位，读取 in.txt 文件中的数据
	while (std::getline(inFile, line))
		Vec_G.push_back(line);
	inFile.close();
}
void CDialogRun::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//if (NULL == g_handle)
	//{
	//	MessageBox(_T("链接断开状态"));
	//	return;
	//}
	//UpdateData(true);//刷新参数
	float units_ax[6] = { 85.333,85.333,85.333,888.888,888.888,764.331 };
	for (int m_datumin = 0; m_datumin < 6; m_datumin++)
	{
		//设定轴类型 7-   脉冲轴类型 +	编码器Z信号		不用EZ回零也可以设置为1	
		ZAux_Direct_SetAtype(g_handle, m_datumin, 7);
		////设定脉冲模式及逻辑方向（脉冲+方向）	
		//ZAux_Direct_SetInvertStep(g_handle, m_datumin, 0);
		//设置脉冲当量	1表示以一个脉冲为单位 ，设置为1MM的脉冲个数，这度量单位为MM
		ZAux_Direct_SetUnits(g_handle, m_datumin, units_ax[m_datumin]);
		//设定速度，加减速
		ZAux_Direct_SetSpeed(g_handle, m_datumin, m_speed);
		ZAux_Direct_SetAccel(g_handle, m_datumin, m_acc);
		ZAux_Direct_SetDecel(g_handle, m_datumin, m_dec);
		ZAux_Direct_SetSramp(g_handle, m_datumin, m_sramp);
	}
	CFileDialog dlg1(TRUE, "", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "All Files (*.*)|*.*||", NULL);
	dlg1.DoModal();
	CString filename = dlg1.GetPathName();
	std::string strFilename(filename);
	std::size_t foundStart = strFilename.find_last_of("\\");
	std::size_t foundEnd = strFilename.find_last_of(".");
	std::string modelName;
	std::string decideName;
	modelName = strFilename.substr(0, foundEnd);
	modelName = modelName.substr(foundStart + 1);
	decideName = strFilename.substr(foundEnd + 1);
	//std::cout << "Input tetrahedral mesh from: " << filename << std::endl;
	std::cout << "The Gcode name is :" << modelName << std::endl;
	this->loadGcode(filename);
	for (int i = 0; i < 6; i++) {
		ZAux_Direct_SetMerge(g_handle, i, 1);//连续插补
	}
	ZAux_Direct_SetSpeed(g_handle, 0, 100);
	ZAux_Direct_SetAccel(g_handle, 0, 1000);
	this->RunGcode();
	for (int i = 0; i < 6; i++)endCoordinate[i] = 0.0;
}
void CDialogRun::RunGcode() {
	for (int i = 0; i < Vec_G.size(); i++) {
		std::string s = Vec_G[i];
		std::string s1 = s.substr(0, 2);
		if (s1 == "G0")this->G0(s);
		else if (s1 == "G1")this->G1(s);
		else if (s1 == "G9")this->G92(s);
	}
}
void CDialogRun::G0(std::string s)
{
	std::vector<float>coord(6, -1000.0);
	std::string temp; float ff1 = -1000.0;
	for (int i = 3; i < s.size(); i++) {
		if (s[i] != 32) {
			temp += s[i];
		}
		if (s[i] == 32 || i == s.size() - 1) {
			std::string t2 = temp.substr(1);
			switch (temp[0])
			{
			case 'X': coord[0] = std::stof(t2);
				break;
			case 'Y': coord[1] = std::stof(t2);
				break;
			case 'Z': coord[2] = std::stof(t2)- (float)40.5;
				break;
			case 'B': coord[3] = std::stof(t2);
				break;
			case 'C': coord[4] = std::stof(t2);
				break;
			case 'E': coord[5] = std::stof(t2);
				break;
			case 'F': ff1 = std::stof(t2);
				break;
			default:
				break;
			}
			temp.clear();
		}
	}
	if (ff1 != -1000.0) {
		ff = ff1/60.0;
		if (ff > 700.0)ff = 700.0;
		for (int i = 0; i < 6; i++)ZAux_Direct_SetForceSpeed(g_handle, i, ff);
	}
	for (int i = 0; i < 5; i++) {
		if (coord[i] != -1000.0)endCoordinate[i] = coord[i];
		std::cout << endCoordinate[i] << ",";
	}
	if (coord[5] != -1000.0)endCoordinate[5] = coord[5] + Eval;
	std::cout << endCoordinate[5] << ",";
	std::cout << ff << std::endl;
	ZAux_Direct_MoveAbsSp(g_handle, 6, ax, endCoordinate);
	//std::cout << s << std::endl;
}
void CDialogRun::G1(std::string s)
{
	std::vector<float>coord(6, -1000.0);
	std::string temp; float ff1 = -1000.0;
	for (int i = 3; i < s.size(); i++) {
		if (s[i] != 32) {
			temp += s[i];
		}
		if (s[i] == 32 || i == s.size() - 1) {
			std::string t2 = temp.substr(1);
			switch (temp[0])
			{
			case 'X': coord[0] = std::stof(t2);
				break;
			case 'Y': coord[1] = std::stof(t2);
				break;
			case 'Z': coord[2] = std::stof(t2)-(float)40.5;
				break;
			case 'B': coord[3] = std::stof(t2);
				break;
			case 'C': coord[4] = std::stof(t2);
				break;
			case 'E': coord[5] = std::stof(t2);
				break;
			case 'F': ff1 = std::stof(t2);
				break;
			default:
				break;
			}
			temp.clear();
		}
	}
	if (ff1 != -1000.0) {
		ff = ff1/60.0;
		if (ff > 700.0)ff = 700.0;
		for (int i = 0; i < 6; i++)ZAux_Direct_SetForceSpeed(g_handle, i, ff);
	}
	for (int i = 0; i < 5; i++) {
		if (coord[i] != -1000.0)endCoordinate[i] = coord[i];
		std::cout << endCoordinate[i] << ",";
	}
	if (coord[5] != -1000.0)endCoordinate[5] = coord[5] + Eval;
	std::cout << endCoordinate[5] << ",";
	std::cout <<ff<< std::endl;
	ZAux_Direct_MoveAbsSp(g_handle, 6, ax, endCoordinate);
	//std::cout << s << std::endl;
}
void CDialogRun::G92(std::string s) {
	if (s[2] != '2')return;
	Eval = endCoordinate[5];
	//endCoordinate[5] = 0.0;
	//ZAux_Direct_SetMpos(g_handle, 5, 0.0);
	std::cout << s << std::endl;
}
void CDialogRun::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == g_handle)
	{
		MessageBox(_T("链接断开状态"));
		return;
	}
	ZAux_Direct_Rapidstop(g_handle, 2);
	/*ZAux_Direct_Single_Cancel(g_handle, 0, 2);
	ZAux_Direct_Single_Cancel(g_handle, 1, 2);
	ZAux_Direct_Single_Cancel(g_handle, 2, 2);
	ZAux_Direct_Single_Cancel(g_handle, 3, 2);
	ZAux_Direct_Single_Cancel(g_handle, 4, 2);
	ZAux_Direct_Single_Cancel(g_handle, 5, 2);*/
}


void CDialogRun::OnBnClickedRadio6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	m_nAxis = 5;
	m_units = 764.331;
	UpdateData(false);
}


void CDialogRun::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (NULL == g_handle)
	{
		MessageBox(_T("链接断开"));
		return;
	}

	if (1 == nIDEvent)
	{
		CString string;
		float position = 0;
		ZAux_Direct_GetDpos(g_handle, 0, &position);          //获取当前轴位置
		string.Format("X：%.2f", position);
		GetDlgItem(IDC_x)->SetWindowText(string);

		CString string1;
		float position1 = 0;
		ZAux_Direct_GetDpos(g_handle, 1, &position1);          //获取当前轴位置
		string1.Format("Y：%.2f", position1);
		GetDlgItem(IDC_y)->SetWindowText(string1);

		CString string2;
		float position2 = 0;
		ZAux_Direct_GetDpos(g_handle, 2, &position2);          //获取当前轴位置
		string2.Format("Z：%.2f", position2);
		GetDlgItem(IDC_z)->SetWindowText(string2);

		CString string3;
		float position3 = 0;
		ZAux_Direct_GetDpos(g_handle, 3, &position3);          //获取当前轴位置
		string3.Format("B：%.2f", position3);
		GetDlgItem(IDC_b)->SetWindowText(string3);

		CString string4;
		float position4 = 0;
		ZAux_Direct_GetDpos(g_handle, 4, &position4);          //获取当前轴位置
		string4.Format("C：%.2f", position4);
		GetDlgItem(IDC_c)->SetWindowText(string4);

		CString string5;
		float position5 = 0;
		ZAux_Direct_GetDpos(g_handle, 5, &position5);          //获取当前轴位置
		string5.Format("E：%.2f", position5);
		GetDlgItem(IDC_e)->SetWindowText(string5);

	}
	CDialogEx::OnTimer(nIDEvent);
}


void CDialogRun::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == g_handle)
	{
		MessageBox(_T("链接断开状态"));
		return;
	}
	ZAux_Direct_SetDpos(g_handle, m_nAxis, 0);
}


void CDialogRun::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == g_handle)
	{
		MessageBox(_T("链接断开状态"));
		return;
	}

	UpdateData(true);//刷新参数

	int status = 0;
	ZAux_Direct_GetIfIdle(g_handle, m_nAxis, &status);           //判断当前轴状态

	if (status == 0) //已经在运动中
		return;
	//设定轴类型 1-脉冲轴类型 	
	ZAux_Direct_SetAtype(g_handle, m_nAxis, 7);

	//设定脉冲模式及逻辑方向（脉冲+方向）	
	ZAux_Direct_SetInvertStep(g_handle, m_nAxis, 0);

	//设置脉冲当量	1表示以一个脉冲为单位 ，设置为1MM的脉冲个数，这度量单位为MM
	ZAux_Direct_SetUnits(g_handle, m_nAxis, m_units);

	//设定速度，加减速
	ZAux_Direct_SetLspeed(g_handle, m_nAxis, m_lspeed);
	ZAux_Direct_SetSpeed(g_handle, m_nAxis, m_speed);
	ZAux_Direct_SetAccel(g_handle, m_nAxis, m_acc);
	ZAux_Direct_SetDecel(g_handle, m_nAxis, m_dec);

	//设定S曲线时间 设置为0表示梯形加减速 
	ZAux_Direct_SetSramp(g_handle, m_nAxis, m_sramp);
	ZAux_Direct_Single_MoveAbs(g_handle, m_nAxis, m_step);
	UpdateData(false);
}
