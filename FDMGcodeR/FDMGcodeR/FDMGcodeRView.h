
// FDMGcodeRView.h: CFDMGcodeRView 类的接口
//

#pragma once


class CFDMGcodeRView : public CView
{
protected: // 仅从序列化创建
	CFDMGcodeRView() noexcept;
	DECLARE_DYNCREATE(CFDMGcodeRView)

// 特性
public:
	CFDMGcodeRDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CFDMGcodeRView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFdmrconnect();
	afx_msg void Onsinglemove();
};

#ifndef _DEBUG  // FDMGcodeRView.cpp 中的调试版本
inline CFDMGcodeRDoc* CFDMGcodeRView::GetDocument() const
   { return reinterpret_cast<CFDMGcodeRDoc*>(m_pDocument); }
#endif

