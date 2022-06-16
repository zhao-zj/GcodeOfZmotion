
// FDMGcodeRView.cpp: CFDMGcodeRView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "FDMGcodeR.h"
#endif

#include "FDMGcodeRDoc.h"
#include "FDMGcodeRView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CDialogRun.h"
// CFDMGcodeRView
ZMC_HANDLE       g_handle1 = NULL;				//控制器链接句柄
IMPLEMENT_DYNCREATE(CFDMGcodeRView, CView)

BEGIN_MESSAGE_MAP(CFDMGcodeRView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_FDMR_connect, &CFDMGcodeRView::OnFdmrconnect)
	ON_COMMAND(ID_singlemove, &CFDMGcodeRView::Onsinglemove)
END_MESSAGE_MAP()

// CFDMGcodeRView 构造/析构

CFDMGcodeRView::CFDMGcodeRView() noexcept
{
	// TODO: 在此处添加构造代码

}

CFDMGcodeRView::~CFDMGcodeRView()
{
}

BOOL CFDMGcodeRView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CFDMGcodeRView 绘图

void CFDMGcodeRView::OnDraw(CDC* /*pDC*/)
{
	CFDMGcodeRDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CFDMGcodeRView 打印

BOOL CFDMGcodeRView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CFDMGcodeRView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CFDMGcodeRView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CFDMGcodeRView 诊断

#ifdef _DEBUG
void CFDMGcodeRView::AssertValid() const
{
	CView::AssertValid();
}

void CFDMGcodeRView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFDMGcodeRDoc* CFDMGcodeRView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFDMGcodeRDoc)));
	return (CFDMGcodeRDoc*)m_pDocument;
}
#endif //_DEBUG


// CFDMGcodeRView 消息处理程序


void CFDMGcodeRView::OnFdmrconnect()
{
	// TODO: 在此添加命令处理程序代码
	char   buffer[256] = "192.168.0.11";
	int32 iresult;
	std::cout << "IP: 192.168.0.11" << std::endl;
	if (NULL != g_handle1)
	{
		ZAux_Close(g_handle1);
		g_handle1 = NULL;
	}

	//GetDlgItemText(IDC_IPLIST, buffer, 255);
	buffer[255] = '\0';

	iresult = ZAux_OpenEth(buffer, &g_handle1);
	if (ERR_SUCCESS != iresult)
	{
		g_handle1 = NULL;
		MessageBox(_T("链接失败"));
		SetWindowText("未链接");
		std::cout << "链接失败" << std::endl;
		return;
	}

	MessageBox(_T("已链接"));
	std::cout << "已链接" << std::endl;
	//SetTimer(1, 100, NULL);
}


void CFDMGcodeRView::Onsinglemove()
{
	// TODO: 在此添加命令处理程序代码
	CDialogRun dlg;
	dlg.showax(g_handle1);
	dlg.DoModal();
}
