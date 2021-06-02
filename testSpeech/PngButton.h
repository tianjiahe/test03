#pragma once
#include <afxext.h>

// 描述: 自绘制位图按钮
// 主要函数：
//         SetButtonUpBitmapEx()设置鼠标放置在按钮上的图片
//         SetButtonDownBitmapEx()设置按钮按下的图片
//         SetButtonNormalBitmapEx()设置鼠标不在按钮是的图片

class CPngButton :	public CBitmapButton
{
	DECLARE_DYNAMIC(CPngButton)

public:
	CPngButton();
	virtual ~CPngButton();

protected:
	DECLARE_MESSAGE_MAP()

protected:

	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

public:
	// 设置按钮抬起图片
	BOOL SetButtonUpBitmapEx(const CString& szFilePath);
	// 设置按钮按下图片
	BOOL SetButtonDownBitmapEx(const CString& szFilePath);
	// 普通按钮图片
	BOOL SetButtonNormalBitmapEx(const CString& szFilePath);
protected:
	virtual void PreSubclassWindow();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
protected:
	BOOL m_lButtonDown;
	// 按钮有效区域
//     CRgn m_btRgn;
	// 绘制按钮图片区域
//     CRect m_rectDrawButton;
private:
	// 图片
	CImage m_imageButtonUp;
	CImage m_imageButtonDown;
	CImage m_imageBitmapNormal;
	CDC m_bkDc; // 记录背景
	bool m_first;


protected:
	BOOL m_bMouseOver;
	BOOL m_bTrack;


};

